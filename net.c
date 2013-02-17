/*
 * net.c
 *
 *  Created on: 09.02.2013
 *      Author: admin
 */

#include "net.h"

static SOCKET host_soc;
static net_status_e status;
static struct sockaddr host_addr;

void net_init(void)
{
	struct sockaddr_in addr;

	host_soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	addr.sin_port = PORT_TO_LISTENING;
	addr.sin_addr.S_un.S_addr = IP_ADDR_ANY;
	bind(host_soc, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));

	status = NET_LISTENING;
}

BOOL net_recieve_data(BYTE *data, WORD *size)
{
	int recieved, addrlen;

	switch (status) {

	case NET_LISTENING:

		addrlen = sizeof(struct sockaddr);
		recieved = recvfrom(host_soc, (char*) data, *size, 0,
				(struct sockaddr*) &host_addr, &addrlen);

		if (!recieved)
			return FALSE;

		connect(host_soc, (struct sockaddr*) &host_addr, addrlen);
		status = NET_CONNECTED;
		break;

	case NET_CONNECTED:

		recieved = recv(host_soc, (char*) data, *size, 0);
		if (!recieved)
			return FALSE;
	}

	*size = recieved;
	return TRUE;
}

void net_disconnect(void)
{
	status = NET_LISTENING;
}

BOOL net_send_data(const BYTE *data, WORD size)
{

	if (status != NET_CONNECTED)
		return FALSE;
	if (send(host_soc, (const char*) data, size, 0) > 0)
		return TRUE;
	else
		return FALSE;
}

net_status_e net_getstatus(void) {
	return status;
}
