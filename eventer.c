/*
 * eventer.c
 *
 *  Created on: 12.04.2013
 *      Author: admin
 */

#include "eventer.h"

event_t events[MODULES_NUM];

void eventer_init(void)
{
	int i;

	for(i = 0; i < MODULES_NUM; i++)	
		events[i] = 0;
}

void event_send(modules_e module, event_t event) {
	events[module] |= event;
}

int event_recieve(modules_e module, event_t *event) {
	if(events[module]) {
		*event = events[module];
		events[module] = 0;
		return 1;
	}
	return 0;
}

