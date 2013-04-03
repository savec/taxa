/*
 * bcp.h
 *
 *  Created on: 16.02.2013
 *      Author: admin
 */

#ifndef M_BCP_H_
#define M_BCP_H_

#include "TCPIP Stack/TCPIP.h"
#include "modules.h"

#define NBUFFERS	3

#define BCP_HEADER_SIZE	7

#define PAYLOADLEN	(64 + 2)

#define SIZEOF_BUF (BCP_HEADER_SIZE + PAYLOADLEN)

#define BCP_SYNC 0x9c

//typedef enum {
//
//} bcp_status_e;

typedef signed char bd_t;

typedef enum {
	BD_FREE = 0,
	BD_OBTAINED,
	BD_NEED_ACK,
	BD_TIMEOUT
} bd_status_e;

typedef enum {
	QAC_GETVER 	= 0x00,
	QAC_ECHO 	= 0x09,
	QAC_AR_REQUEST = 0x1E
} qac_e;

typedef enum {
	TYPE_CTRL = 0,
	TYPE_NPRQ,
	TYPE_NPD1,
	TYPE_NPDL
} pkt_type_e;

#define TYPE(x)		((x) & 0x0f)
#define FQ(x)		((x) & (1 << 7))
#define SET_FQ(x)	(x) |= (1 << 7)
#define RST_FQ(x)	(x) &= ~(1 << 7)

#define BNUM(x)		(((x) & (7 << 4)) >> 4)

#define ARRAYLEN(p)	(sizeof(p)/*/sizeof(p[0])*/)

#define CRC16_BYTES	2

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

typedef union {
	struct {
		BYTE sync;
		BYTE type;
		BYTE addr;
		union {
			ht_ctrl_t ctrl;
			ht_nprq_t nprq;
			ht_npd1_t npd1;
			ht_npdl_t npdl;
		} packtype_u;
		BYTE crcl;
		BYTE crch;
	} hdr_s;
	BYTE raw[BCP_HEADER_SIZE];
} bcp_header_t;

#define RAW_QAC		3
#define RAW_DATA	BCP_HEADER_SIZE

typedef struct {
	bd_status_e status;
	DWORD 		timestamp;
	BYTE		owner;
	BYTE 		buf[SIZEOF_BUF];
} buf_t;

void bcp_module(void);
int bcp_send_buffer(bd_t handler);
buf_t *bcp_buffer(bd_t handler);
void bcp_release_buffer(bd_t handler);
bd_t bcp_obtain_buffer(modules_e owner);

#endif /* M_BCP_H_ */
