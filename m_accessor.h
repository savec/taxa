/*
 * m_accessor.h
 *
 *  Created on: 01.04.2013
 *      Author: admin
 */

#include "TCPIP Stack/TCPIP.h"

#ifndef M_ACCESSOR_H_
#define M_ACCESSOR_H_

#define MAX_UID_SIZE	30

typedef struct {
	BYTE retries;
	BYTE reader_n;
	WORD req_label;
	BYTE uid[MAX_UID_SIZE];
} ar_req;

typedef struct {
	BYTE retries;
	BYTE reader_n;
	WORD req_label;
	BYTE uid[MAX_UID_SIZE];
} ar_req;

void accessor_init(void);
void accessor_module(void);
#endif /* M_ACCESSOR_H_ */
