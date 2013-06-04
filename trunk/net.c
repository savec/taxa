/*
 * net.c
 *
 *  Created on: 09.02.2013
 *      Author: admin
 */

#include "net.h"
#include "config.h"

static SOCKET host_soc;
static net_status_e status;
static struct sockaddr host_addr;

void net_init(void)
{
	struct sockaddr_in addr;

	host_soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	addr.sin_port = AppConfig.comm_port;
	addr.sin_addr.S_un.S_addr = IP_ADDR_ANY;
	bind(host_soc, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));

	status = NET_LISTENING;
}

int net_recieve_data(BYTE *data, size_t size) {
	int recieved, addrlen;

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
	}

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

int net_send_data(const BYTE *data, size_t size)
{
	if (status != NET_CONNECTED)
		return -1;

	return sendto( host_soc, (const char*) data, size, 0, (struct sockaddr*) &host_addr, sizeof(struct sockaddr) );
//	return send(host_soc, (const char*) data, size, 0);
}

net_status_e net_getstatus(void) {
	return status;
}
