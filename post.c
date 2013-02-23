/*
 * post.c
 *
 *  Created on: 23.02.2013
 *      Author: admin
 */

#include "post.h"

mail_t mail_index[MODULES_NUM];

int mail_subscribe(modules_e module, mail_t mailbox)
{
	if(module >= MODULES_NUM)
		return -1;
	mail_index[module] = mailbox;
	return 0;
}

int mail_unsubscribe(modules_e module)
{
	if(module >= MODULES_NUM)
		return -1;
	mail_index[module] = NULL;
	return 0;
}

mail_t mail_reciev(mailbox_t *mailbox)
{
	mail_t mail = NULL;

	if(mailbox->in != mailbox->out) {
		mail = mailbox->mailbox[mailbox->out];
		mailbox->out ++;
		mailbox->out &= MAILBOX_MASK;
	}
	return mail;
}

int mail_send(mailbox_t *mailbox, mail_t mail)
{
	mailbox->mailbox[mailbox->in] = mail;
	mailbox->in ++;
	mailbox->in &= MAILBOX_MASK;
	if(mailbox->in == mailbox->out)
		return -1;
	return 0;
}
