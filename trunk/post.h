/*
 * post.h
 *
 *  Created on: 23.02.2013
 *      Author: admin
 */

#ifndef POST_H_
#define POST_H_

#include "TCPIP Stack/TCPIP.h"
#include "bcp.h"

typedef enum {
	MODULE_BCP,
	MODULE_READERS,
	MODULE_ACCESSOR,
	MODULE_SRVMACHINE,
	MODULE_LOGGER,
	MODULES_NUM
} modules_e;

#define MAILBOX_SIZE	4	/* must be pow of 2 */
#define MAILBOX_MASK	(MAILBOX_SIZE - 1)

typedef buf_t* mail_t;

typedef struct {
	mail_t mailbox[MAILBOX_SIZE];
	BYTE in;
	BYTE out;
} mailbox_t;


int mail_subscribe(modules_e module, mail_t mailbox);
int mail_unsubscribe(modules_e module);
mail_t mail_reciev(mailbox_t *mailbox);
int mail_send(mailbox_t *mailbox, mail_t mail);

#endif /* POST_H_ */
