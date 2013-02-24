/*
 * post.h
 *
 *  Created on: 23.02.2013
 *      Author: admin
 */

#ifndef POST_H_
#define POST_H_

#include "TCPIP Stack/TCPIP.h"
#include "m_bcp.h"

typedef enum {
	MODULE_BCP = 0,
	MODULE_READERS,
	MODULE_ACCESSOR,
	MODULE_SRVMACHINE,
	MODULE_LOGGER,
	MODULE_LCD,
	MODULES_NUM,
	MODULE_UNKNOWN = MODULES_NUM
} modules_e;

#define MAILBOX_SIZE	4	/* must be pow of 2 */
#define MAILBOX_MASK	(MAILBOX_SIZE - 1)

typedef bd_t mail_t;

typedef struct {
	mail_t mailbox[MAILBOX_SIZE];
	BYTE in;
	BYTE out;
} mailbox_t;


int mail_subscribe(modules_e module, mailbox_t *mailbox);
int mail_unsubscribe(modules_e module);
mail_t mail_reciev(modules_e module);
int mail_send(modules_e module, mail_t mail);

#endif /* POST_H_ */
