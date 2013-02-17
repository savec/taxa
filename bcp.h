/*
 * bcp.h
 *
 *  Created on: 16.02.2013
 *      Author: admin
 */

#ifndef BCP_H_
#define BCP_H_

#include "TCPIP Stack/TCPIP.h"

#define BCP_HEADER_SIZE	7

#define BCP_SYNC 0x9c

typedef enum {
	QAC_GETVER 	= 0x00,
	QAC_ECHO 	= 0x09,
} qac_e;

typedef enum {
	TYPE_CTRL = 0,
	TYPE_NPRQ,
	TYPE_NPD1,
	TYPE_NPDL
} pkt_type_e;

#define TYPE(x)		((x) & 0x0f)
#define FQ(x)		((x) & (1 << 7))
#define SET_FQ(x)	(x) |= FQ
#define RST_FQ(x)	(x) &= ~FQ

#define BNUM(x)		(((x) & (7 << 4)) >> 4)

typedef struct {
	BYTE blen;
	BYTE mtmo;
} ht_ctrl_t;

typedef struct {
	BYTE qac;
	BYTE dummy;
} ht_nprq_t;

typedef struct {
	BYTE qac;
	BYTE data;
} ht_npd1_t;

typedef struct {
	BYTE qac;
	BYTE len;
} ht_npdl_t;

typedef struct {
	union {
		BYTE sync;
		BYTE type;
		BYTE addr;
		union {
			ht_ctrl_t ctrl;
			ht_nprq_t nprq;
			ht_npd1_t npd1;
			ht_npdl_t npdl;
		};
		BYTE crcl;
		BYTE crch;
	} hdr_u;
	BYTE raw[BCP_HEADER_SIZE];
} bcp_header_t;

#endif /* BCP_H_ */
