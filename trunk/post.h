/*
 * post.h
 *
 *  Created on: 23.02.2013
 *      Author: admin
 */

#ifndef POST_H_
#define POST_H_

#include "TCPIP Stack/TCPIP.h"
#include "modules.h"
#include "m_bcp.h"



#define MAILBOX_SIZE	4	/* must be pow of 2 */
#define MAILBOX_MASK	(MAILBOX_SIZE - 1)

//typedef bd_t mail_t;

typedef struct {
	bd_t mailbox[MAILBOX_SIZE];
	BYTE in;
	BYTE out;
} mailbox_t;


int mail_subscribe(modules_e module, mailbox_t *mailbox);
int mail_unsubscribe(modules_e module);
int mail_reciev(modules_e module, bd_t *mail);
int mail_send(modules_e module, bd_t mail);

#endif /* POST_H_ */
