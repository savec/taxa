/*
 * m_accessor.h
 *
 *  Created on: 01.04.2013
 *      Author: admin
 */

#include "TCPIP Stack/TCPIP.h"
#include "modules.h"

#ifndef M_ACCESSOR_H_
#define M_ACCESSOR_H_

#define MAX_UID_SIZE	30
#define MAX_MSG_SIZE	40

typedef enum {
	WAIT_UID,
	CHECK_SM,
	WAIT_HOST_ANSWER,
	WAIT_SM
}accessor_state_e;

typedef struct {
	BYTE retries;
	BYTE reader_n;
	WORD req_label;
	WORD uid;
//	BYTE uid[MAX_UID_SIZE];		// XXX check it!
} ar_req;

typedef struct {
	BYTE reader_n;
	WORD req_label;
	BYTE access_code;
	BYTE msg[MAX_MSG_SIZE];
} ar_rsp;

void accessor_init(void);
void accessor_module(void);
#endif /* M_ACCESSOR_H_ */
