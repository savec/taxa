/*
 * post.c
 *
 *  Created on: 23.02.2013
 *      Author: admin
 */

#include "post.h"

mailbox_t *mail_index[MODULES_NUM];



int mail_subscribe(modules_e module, mailbox_t *mailbox)
{
	if(module >= MODULE_UNKNOWN)
		return -1;
	mail_index[module] = mailbox;
	return 0;
}

int mail_unsubscribe(modules_e module)
{
	if(module >= MODULE_UNKNOWN)
		return -1;
	mail_index[module] = NULL;
	return 0;
}

int mail_reciev(modules_e module, mail_t *mail)
{
	mailbox_t *mailbox = mail_index[module];
	if(mailbox == NULL)
		return -1;

	if(mailbox->in != mailbox->out) {
		*mail = mailbox->mailbox[mailbox->out];
		mailbox->out ++;
		mailbox->out &= MAILBOX_MASK;
		return 1;
	} else {
		return 0;
	}
}

int mail_send(modules_e module, mail_t mail)
{
	mailbox_t *mailbox;

	if(module >= MODULE_UNKNOWN)
		return -1;

	mailbox = mail_index[module];

	if(mailbox == NULL)
		return -1;

	mailbox->mailbox[mailbox->in] = mail;
	mailbox->in ++;
	mailbox->in &= MAILBOX_MASK;
	if(mailbox->in == mailbox->out)
		return -1;
	return 0;
}
