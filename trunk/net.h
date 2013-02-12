/*
 * net.h
 *
 *  Created on: 09.02.2013
 *      Author: admin
 */

#ifndef NET_H_
#define NET_H_

#include "TCPIP Stack/TCPIP.h"

#define PORT_TO_LISTENING	50

typedef enum {
	NET_LISTENING = 0,
	NET_CONNECTED
} net_status_e;


void net_init(void);
BYTE net_recieve_data(BYTE *data, WORD *size);
BYTE net_send_data(const BYTE *data, WORD size);
net_status_e net_getstatus(void);

#endif /* NET_H_ */
