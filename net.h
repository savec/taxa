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
int net_recieve_data(BYTE *data, size_t size);
int net_send_data(const BYTE *data, size_t size);
net_status_e net_getstatus(void);
void net_disconnect(void);
BOOL net_cfg_activity(void);
void net_serve_dk(void);
int net_send_string(const BYTE *str);
BYTE net_get_string(BYTE *str, BYTE maxlen);

#endif /* NET_H_ */
