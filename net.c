/*
 * net.c
 *
 *  Created on: 09.02.2013
 *      Author: admin
 */
//#include <string.h>
#include "TCPIP Stack/TCPIP.h"
#include <stdio.h>
#include "net.h"
#include "config.h"
#include "trace.h"
#include "version.h"

static SOCKET host_soc, cfg_soc, dk_soc;
static net_status_e status;
static struct sockaddr host_addr, cfg_addr, dk_host_addr;

#define DK_T_REQUEST		"X"
#define DK_T_ANSWER			"A"
#define DK_T_STATUS_STR		"N**M*"
#define DK_T_BUFSTAT_STR	"nc"

//#define NET_NAME	"R2D2_0"

void net_init(void)
{
	struct sockaddr_in addr;

	if((host_soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
		TRACE("\n\nPANIC: can't create host socket");
		INTCONbits.GIEL = 0;
		INTCONbits.GIEH = 0;
		for(;;);
	}

	addr.sin_port = AppConfig.comm_port;
	addr.sin_addr.S_un.S_addr = IP_ADDR_ANY;
	bind(host_soc, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));

	if((cfg_soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
		TRACE("\n\nPANIC: can't create config socket");
		INTCONbits.GIEL = 0;
		INTCONbits.GIEH = 0;
		for(;;);
	}

	addr.sin_port = 8080;
	addr.sin_addr.S_un.S_addr = IP_ADDR_ANY;
	bind(cfg_soc, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));

	if((dk_soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
		TRACE("\n\nPANIC: can't create dk-tibbo socket");
		INTCONbits.GIEL = 0;
		INTCONbits.GIEH = 0;
		for(;;);
	}

	addr.sin_port = 65535;
	addr.sin_addr.S_un.S_addr = IP_ADDR_ANY;
	bind(dk_soc, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));


	status = NET_LISTENING;
}

int net_recieve_data(BYTE *data, size_t size) {
	int recieved, addrlen;
	net_status_e c_status = status;

	//	switch (status) {
	//
	//	case NET_LISTENING:
	//	case NET_CONNECTED:

	addrlen = sizeof(struct sockaddr);
	recieved = recvfrom(host_soc, (char*) data, size, 0,
			(struct sockaddr*) &host_addr, &addrlen);

	if (recieved > 0) {
		//			connect(host_soc, (struct sockaddr*) &host_addr, addrlen);
		status = NET_CONNECTED;
		TRACE("\n\rnet_recieve_data: %i bytes recieved", recieved);
	} else if(recieved < 0) {
		TRACE("\n\rnet_recieve_data: SOCKET_ERROR");
	}

	if(c_status != status)
		TRACE("\n\rnet_recieve_data: status changed to %i", (int)status);


	return recieved;

	//	case NET_CONNECTED:
	//
	//		return recv(host_soc, (char*) data, size, 0);
	//	}
}

void net_disconnect(void)
{
	status = NET_LISTENING;
}


char * strtok(char *s, const char *delim)
{
	int i;
	static char *last_pos;
	char *pos = (s) ? s : last_pos;
	char *res;

	if(*pos == '\0')
		return NULL;

	while(1) {									/*remove leading delimiters*/
		for(i = 0; i < strlen(delim); i++)
			if(*pos == delim[i]) {
				pos ++;
			}
		if(i == strlen(delim)/* || *res == '\0'*/)
			break;
	}
	res = pos;
	while(*pos) {
		for(i = 0; i < strlen(delim); i++)
			if(*pos == delim[i]) {
				*pos = '\0';
				last_pos = pos + 1;
				return res;
			}
		pos ++;
	}

	last_pos = pos;
	return res;
}

#define IP_IS_VALID(ip) (ip.v[0] > 0 && ip.v[0] < 256)

static int get_dot_delimit_octets(char * s, char *out, char size)
{
	int i, oct;
	char * tok;
	char d[] = {'.', '\0'};

	for (tok = strtok(s, d), i = 0; tok && i < size; tok = strtok(NULL, d), i ++) {
		oct = atoi(tok);
		if(oct >= 0 && oct < 256)
			*out++ = oct;
		else
			return -1;
	}

	if(i < size - 1)
		return -1;
	else
		return 0;
}
/*
        public static UInt32 FNV_hash_32(UInt32 Mkey, byte[] Bytes)

        {

            //const UInt32 offset_basis = 2166136261 ;

            const UInt32 FNV_prime = 16777619;

            //UInt32 hash = offset_basis;

            UInt32 hash = Mkey;

            foreach(byte  b in Bytes)

               {hash ^= b; hash *= FNV_prime;}

            return hash;

        }
*/

static DWORD FNV_hash_32(DWORD mkey, char * s)
{
	DWORD FNV_prime = 16777619;
	DWORD hash = mkey;
	char *p;

	for(p = s; *p; p++)
	{
		hash ^= *p;
		hash *= FNV_prime;
	}
	return hash;
}

static void get_substring(const char * s, const char *ss, char c, char size)
{
	char *from = s;
	char *to = ss;

	while(*from != c && *from && size--)
		*to++ = *from++;
	*to = '\0';
}

void net_serve_dk(void)
{
	int recieved, addrlen, result;
	static BYTE buf[100];
	char *tok;
	static DWORD last_mkey = 0;

	addrlen = sizeof(struct sockaddr);

	recieved = recvfrom(dk_soc, (char*) buf, sizeof(buf), 0,
			(struct sockaddr*) &dk_host_addr, &addrlen);

	if (!recieved)
		return;

	if (buf[0] == DK_T_REQUEST[0]) {
		TRACE("net_serve_dk: dk-t soc resieved %c\n\r", buf[0]);

		while((last_mkey = TickGet()) == 0)	// MKEY must not be equal 0
			;

		sprintf(buf, DK_T_ANSWER"%d.%d.%d.%d.%d.%d/%d/"DK_T_STATUS_STR"/"
//		DK_T_BUFSTAT_STR"/"PROJ_NAME" "SVN_DATETIME"|12345678",
//		DK_T_BUFSTAT_STR"/" "R2D2_%d" "|%lu",
		DK_T_BUFSTAT_STR"/"PROJ_NAME"#%d/rv"SVN_REVISION"|%lu",

				AppConfig.MyMACAddr.v[0], AppConfig.MyMACAddr.v[1],
				AppConfig.MyMACAddr.v[2], AppConfig.MyMACAddr.v[3],
				AppConfig.MyMACAddr.v[4], AppConfig.MyMACAddr.v[5],
				AppConfig.comm_port, AppConfig.comm_station_id, last_mkey);

		result = sendto(dk_soc, (const char*) buf, strlen(buf), 0,
				(struct sockaddr*) &dk_host_addr, sizeof(struct sockaddr));

		TRACE("net_serve_dk: %d bytes sent to host:\n\r%s\n\r", result, buf);
	} else if (buf[0] == DK_T_ANSWER[0]) {
		char delim[] = {DK_T_ANSWER[0], '|', '/', '\0'};
		char str_mac[24];
		char str_ip[16];
		char str_hkey[16];
		static BYTE str[42];
		MAC_ADDR mac;
		IP_ADDR ip;
		DWORD expected_hash, hash;

		buf[recieved] = '\0';
		TRACE("net_serve_dk: dk-t soc resieved %s\n\r", buf);

		get_substring(buf, str, '|', sizeof(str) - 1);	// get copy of buf
		TRACE("net_serve_dk: getting copy %s\n\r", str);


		/* get MAC */
		tok = strtok(buf, delim);
		strncpy(str_mac, tok, sizeof(str_mac));

		/* get IP */
		tok = strtok(NULL, delim);
		strncpy(str_ip, tok, sizeof(str_ip));

		/* get HKEY */
		tok = strtok(NULL, delim);
		strncpy(str_hkey, tok, sizeof(str_hkey));

//		TRACE("net_serve_dk: MAC:%s IP:%s HKEY:%s\n\r", str_mac, str_ip, str_hkey);
		if(get_dot_delimit_octets(str_mac, (char *)&mac, sizeof(mac)) < 0) {
			TRACE("net_serve_dk: wrong MAC format!\n\r");
			return;
		}

		TRACE("net_serve_dk: MAC %d-%d-%d-%d-%d-%d\n\r",
				mac.v[0], mac.v[1],
				mac.v[2], mac.v[3],
				mac.v[4], mac.v[5]);

		if(AppConfig.MyMACAddr.v[0] != mac.v[0] || AppConfig.MyMACAddr.v[1] != mac.v[1] ||
		   AppConfig.MyMACAddr.v[2] != mac.v[2] || AppConfig.MyMACAddr.v[3] != mac.v[3] ||
		   AppConfig.MyMACAddr.v[4] != mac.v[4] || AppConfig.MyMACAddr.v[5] != mac.v[5])
			return;

		if (last_mkey == 0) {
			TRACE("net_serve_dk: unexpected request\n\r");

			sprintf(buf, "F|%s", str_hkey); /* F */
			result = sendto(dk_soc, (const char*) buf, strlen(buf), 0,
					(struct sockaddr*) &dk_host_addr, sizeof(struct sockaddr));
			TRACE("net_serve_dk: %d bytes sent to host\n\r", result);
			return;
		}

		if(get_dot_delimit_octets(str_ip, (char *)&ip, sizeof(ip)) < 0) {
			TRACE("net_serve_dk: wrong IP format!\n\r");

			sprintf(buf, "F|%s", str_hkey);	/* F */
			result = sendto(dk_soc, (const char*) buf, strlen(buf), 0,
					(struct sockaddr*) &dk_host_addr, sizeof(struct sockaddr));
			TRACE("net_serve_dk: %d bytes sent to host\n\r", result);
			return;
		}

		expected_hash = FNV_hash_32(last_mkey, str);

		if(expected_hash != atoul(str_hkey)) {
			TRACE("net_serve_dk: expected hash:%lu, but recieved:%lu\n\r",
					expected_hash, atoul(str_hkey));
			sprintf(buf, "D|%s", str_hkey);	/* D */
			result = sendto(dk_soc, (const char*) buf, strlen(buf), 0,
					(struct sockaddr*) &dk_host_addr, sizeof(struct sockaddr));
			TRACE("net_serve_dk: %d bytes sent to host\n\r", result);
			return;
		}

		TRACE("net_serve_dk: IP %d-%d-%d-%d\n\r",
				ip.v[0], ip.v[1],
				ip.v[2], ip.v[3]);

		AppConfig.MyIPAddr.Val = ip.Val;

		sprintf(buf, DK_T_ANSWER"|%s", str_hkey);	/* OK */
		result = sendto(dk_soc, (const char*) buf, strlen(buf), 0,
				(struct sockaddr*) &dk_host_addr, sizeof(struct sockaddr));
		TRACE("net_serve_dk: %d bytes sent to host\n\r", result);


	} else {
	}
}


BOOL net_cfg_activity(void)
{
	int recieved, addrlen;
	BYTE str[15];

	addrlen = sizeof(struct sockaddr);

	recieved = recvfrom(cfg_soc, (char*) str, sizeof(str), 0,
			(struct sockaddr*) &cfg_addr, &addrlen);

	if(recieved && recieved < sizeof(str)) {	/* 	potential exposure: if recieved == sizeof(str)
	 	 	 	 	 	 	 	 	 	 	 		then '\0' will be placed out of str boundaries */
		BYTE cfg_str[15];
		strcpypgm2ram(cfg_str, CFG_START);
		str[recieved] = '\0';
		if(!strncmp(str, cfg_str, strlen(cfg_str)))
			return TRUE;
	}

	return FALSE;
}

int net_send_data(const BYTE *data, size_t size)
{
	int result;
	net_status_e c_status = status;

	if (status != NET_CONNECTED) {
		TRACE("\n\rnet_send_data: status = %i", (int)status);
		return -1;
	}

	result = sendto( host_soc, (const char*) data, size, 0, (struct sockaddr*) &host_addr, sizeof(struct sockaddr) );

	if(c_status != status)
		TRACE("\n\rnet_send_data: status changed to %i", (int)status);

	TRACE("\n\rnet_send_data: sendto result %i", result);

	return result;
//	return send(host_soc, (const char*) data, size, 0);
}

int net_send_string(const BYTE *str)
{
	return sendto( cfg_soc, (const char*) str, strlen(str), 0, (struct sockaddr*) &cfg_addr, sizeof(struct sockaddr) );
}

BYTE net_get_string(BYTE *str, BYTE maxlen)
{
	int recieved, addrlen;

	addrlen = sizeof(struct sockaddr);
	recieved = recvfrom(cfg_soc, (char*) str, maxlen - 1, 0,
			(struct sockaddr*) &cfg_addr, &addrlen);
	str[recieved - 1] = '\0'; // replace '\n' with '\0'

	return recieved;
}

net_status_e net_getstatus(void) {
	return status;
}
