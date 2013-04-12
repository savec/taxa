/*
 * eventer.h
 *
 *  Created on: 12.04.2013
 *      Author: admin
 */

#ifndef EVENTER_H_
#define EVENTER_H_

#include "TCPIP Stack/TCPIP.h"
#include "modules.h"

typedef DWORD event_t;

void event_send(modules_e module, event_t event);
int event_recieve(modules_e module, event_t *event);

#endif /* EVENTER_H_ */
