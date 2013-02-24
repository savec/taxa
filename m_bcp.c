/*
 * bcp.c
 *
 *  Created on: 16.02.2013
 *      Author: admin
 */

#include "net.h"
#include "m_bcp.h"
#include "CRCMOD.h"
#include "post.h"

#define MYSELF	MODULE_BCP

static buf_t bpool[NBUFFERS] = { 0 };

bd_t bcp_obtain_buffer(modules_e owner)
{
	signed char i;
	for (i = 0; i < NBUFFERS; i++) {
		if (bpool[i].status == BD_FREE) {
			bpool[i].status = BD_OBTAINED;
			bpool[i].owner = owner;
			return i;
		}
	}
	return -1;
}

void bcp_release_buffer(bd_t handler)
{
	bpool[handler].status = BD_FREE;
}

buf_t *bcp_buffer(bd_t handler)
{
	return &bpool[handler];
}

int bcp_reciev_buffer(bd_t handler)
{
	int recieved;
	bcp_header_t * hdr;
	WORD crc;

	recieved = net_recieve_data(bpool[handler].buf, SIZEOF_BUF);
	if (recieved <= 0)
		return recieved;

	hdr = (bcp_header_t *) bpool[handler].buf;

	crc = CRC16_MODBUS((BYTE *) hdr, BCP_HEADER_SIZE - 2);

	if ((WORD) hdr->hdr_u.crcl | ((WORD) hdr->hdr_u.crch << 8) != crc)
		return 0;

	if (TYPE(hdr->hdr_u.type) == TYPE_NPDL) {
		crc = CRC16_MODBUS((BYTE *) hdr + BCP_HEADER_SIZE, hdr->hdr_u.npdl.len - 2);
		if (((WORD) hdr->raw[BCP_HEADER_SIZE + hdr->hdr_u.npdl.len - 2]
		   | (WORD) hdr->raw[BCP_HEADER_SIZE + hdr->hdr_u.npdl.len - 1] << 8) != crc)
			return 0;
	}

	return recieved;
}

int bcp_send_buffer(bd_t handler, BOOL need_ack)
{
	size_t size;
	bcp_header_t * hdr;
	WORD crc;

	if (handler < 0 || handler > NBUFFERS - 1)
		return -1;

	hdr = (bcp_header_t *) bpool[handler].buf;

	if (TYPE(hdr->hdr_u.type) == TYPE_CTRL || TYPE(hdr->hdr_u.type)
			== TYPE_NPRQ || TYPE(hdr->hdr_u.type) == TYPE_NPD1) {
		size = BCP_HEADER_SIZE;
	} else if (TYPE(hdr->hdr_u.type) == TYPE_NPDL && hdr->hdr_u.npdl.len > 2) {
		size = BCP_HEADER_SIZE + hdr->hdr_u.npdl.len;
		/* data crc*/
		crc = CRC16_MODBUS((BYTE *) hdr + BCP_HEADER_SIZE, hdr->hdr_u.npdl.len - 2);
		hdr->raw[BCP_HEADER_SIZE + hdr->hdr_u.npdl.len - 2] = crc; /* LO as we are in little endian */
		hdr->raw[BCP_HEADER_SIZE + hdr->hdr_u.npdl.len - 1] = crc >> 8; /* HI as we are in little endian */
	} else {
		return -1; // unknown type or datalen error
	}

	hdr->hdr_u.sync = BCP_SYNC;
	//	hdr->hdr_u.addr =	// XXX ==1 :)

	/* header crc*/
	crc = CRC16_MODBUS((BYTE *) hdr, BCP_HEADER_SIZE - 2);
	hdr->hdr_u.crcl = crc;
	hdr->hdr_u.crch = crc >> 8;

	if (need_ack) {
		bpool[handler].timestamp = TickGet();
		bpool[handler].status = BD_NEED_ACK;
	}

	return net_send_data((BYTE *) hdr, size);
}

void bcp_init(void)
{
}

modules_e bcp_determine_subscriber(bd_t handler)
{
	bcp_header_t * hdr = (bcp_header_t *) bpool[handler].buf;

	switch(hdr->raw[RAW_QAC]) {
	case QAC_GETVER:
		switch(hdr->raw[RAW_DATA] ){
		case 0:
		case 1:
			return MODULE_BCP;
		case 2:
			return MODULE_READERS;
		case 3:
			return MODULE_ACCESSOR;
		case 4:
			return MODULE_SRVMACHINE;
		case 5:
			return MODULE_LOGGER;
		case 6:
			return MODULE_LCD;
		default:
			return MODULE_BCP;
		}
	case QAC_ECHO:
		return MODULE_BCP;
	default:
		return MODULE_UNKNOWN;
	}
}

int bcp_process_buffer(bd_t handler)
{
	bcp_header_t * hdr = (bcp_header_t *) bpool[handler].buf;




	bcp_release_buffer(handler);
}


void bcp_module(void)
{
	bd_t ibuffer = bcp_obtain_buffer(MYSELF);
	modules_e subscriber;
	bd_t i;


	if(ibuffer < 0) {
		// XXX ASSERT (LOGGER)
		return;
	}

	if(bcp_reciev_buffer(ibuffer) <= 0) {
		bcp_release_buffer(ibuffer);
		goto skip_reciev;
	}

	subscriber = bcp_determine_subscriber(ibuffer);

	if(subscriber == MYSELF)
		bcp_process_buffer(ibuffer);
	else
		mail_send(subscriber, ibuffer);

skip_reciev:

	/* check timeouts */
	for (i = 0; i < NBUFFERS; i++) {
		if((bpool[i].status == BD_NEED_ACK) && (TickGet() - bpool[i].timestamp > TICK_SECOND/2)) {
			bpool[i].status = BD_TIMEOUT;
			mail_send(bpool[i].owner, i);
		}
	}
}


