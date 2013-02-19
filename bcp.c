/*
 * bcp.c
 *
 *  Created on: 16.02.2013
 *      Author: admin
 */

#include "net.h"
#include "bcp.h"
#include "CRCMOD.h"

static buf_t bpool[NBUFFERS] = { 0 };

bd_t bcp_obtain_buffer(void)
{
	signed char i;
	for (i = 0; i < NBUFFERS; i++) {
		if (bpool[i].status == BD_FREE) {
			bpool[i].status = BD_OBTAINED;
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

	recieved = net_recieve_data(bpool[handler].buf, SIZEOF_BUF);
	if(recieved <= 0)
		return recieved;

	// TODO CRC etc

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
		*((BYTE *) hdr + BCP_HEADER_SIZE + hdr->hdr_u.npdl.len - 2) = crc; /* LO as we are in little endian */
		*((BYTE *) hdr + BCP_HEADER_SIZE + hdr->hdr_u.npdl.len - 1) = crc >> 8; /* HI as we are in little endian */

	} else {

		return -1; // unknown type or datalen error
	}

	hdr->hdr_u.sync = BCP_SYNC;
	//	hdr->hdr_u.addr =	// XXX ?

	/* header crc*/
	crc = CRC16_MODBUS((BYTE *) hdr, BCP_HEADER_SIZE);
	hdr->hdr_u.crcl = crc;
	hdr->hdr_u.crch = crc >> 8;

	if (need_ack) {
		bpool[handler].timestamp = TickGet();
		bpool[handler].status = BD_NEED_ACK;
	}

	return net_send_data((BYTE *) hdr, size);
}

int bcp_process_buffer(bd_t handler)
{
	bcp_header_t * hdr = (bcp_header_t *) bpool[handler].buf;

	if (hdr->hdr_u.type != BCP_SYNC) {
		net_disconnect();
		return FALSE;
	}

}
