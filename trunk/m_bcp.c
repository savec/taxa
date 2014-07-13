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
#include "version.h"
#include "trace.h"

#define MYSELF	MODULE_BCP

static rom char * buildlabel = SVN_URL " " SVN_DATETIME;
//rom char * buildlabel = PROJ_NAME " " SVN_DATETIME " Rev:" SVN_REVISION SVN_MODIFYED;

rom static char * ver = "CR0.01";

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

	if (handler < 0 || handler > NBUFFERS - 1) {
		TRACE("\n\rbcp_reciev_buffer: invalid handler");
		return -1;
	}

	recieved = net_recieve_data(bpool[handler].buf, SIZEOF_BUF);
	if (recieved <= 0)
		return recieved;

	hdr = (bcp_header_t *) bpool[handler].buf;

	crc = CRC16_MODBUS((BYTE *) hdr, BCP_HEADER_SIZE - 2);

	if ((hdr->hdr_s.crcl ^ (BYTE) crc) || (hdr->hdr_s.crch ^ (BYTE) (crc >> 8))) {
		TRACE("\n\rbcp_reciev_buffer: header crc error");
		return 0;
	}
		
	if (TYPE(hdr->hdr_s.type) == TYPE_NPDL) {
		crc = CRC16_MODBUS((BYTE *) hdr + BCP_HEADER_SIZE,
				hdr->hdr_s.packtype_u.npdl.len - 2);
		if ((hdr->raw[BCP_HEADER_SIZE + hdr->hdr_s.packtype_u.npdl.len - 2]
				^ (BYTE) crc) || (hdr->raw[BCP_HEADER_SIZE
				+ hdr->hdr_s.packtype_u.npdl.len - 1] ^ (BYTE) (crc >> 8))) {
			TRACE("\n\rbcp_reciev_buffer: npdl crc error");
			return 0;
		}
	}

	return recieved;
}

int bcp_send_buffer(bd_t handler)
{
	size_t size;
	bcp_header_t * hdr;
	WORD crc;

	if (handler < 0 || handler > NBUFFERS - 1) {
		TRACE("\n\rbcp_send_buffer: invalid handler");
		return -1;
	}

	hdr = (bcp_header_t *) bpool[handler].buf;

	switch (TYPE(hdr->hdr_s.type)) {
	case TYPE_CTRL:
	case TYPE_NPRQ:
	case TYPE_NPD1:
		size = BCP_HEADER_SIZE;

		break;
	case TYPE_NPDL:
		if (hdr->hdr_s.packtype_u.npdl.len <= 2)
			return -1;

		size = BCP_HEADER_SIZE + hdr->hdr_s.packtype_u.npdl.len;
		/* data crc*/
		crc = CRC16_MODBUS((BYTE *) hdr + BCP_HEADER_SIZE,
				hdr->hdr_s.packtype_u.npdl.len - 2);
		hdr->raw[BCP_HEADER_SIZE + hdr->hdr_s.packtype_u.npdl.len - 2]
				= (BYTE) crc; /* LO as we are in little endian */
		hdr->raw[BCP_HEADER_SIZE + hdr->hdr_s.packtype_u.npdl.len - 1]
				= (BYTE) (crc >> 8); /* HI as we are in little endian */
		break;
	default:
		TRACE("\n\rbcp_send_buffer: invalid packet type");
		return -1;
	}

	hdr->hdr_s.sync = BCP_SYNC;
	hdr->hdr_s.addr = 1; // XXX ==1 CHECK IT!!

	/* header crc*/
	crc = CRC16_MODBUS((BYTE *) hdr, BCP_HEADER_SIZE - 2);
	hdr->hdr_s.crcl = (BYTE) crc;
	hdr->hdr_s.crch = (BYTE) (crc >> 8);

	if (FQ(hdr->hdr_s.type)) {
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

	switch (TYPE(hdr->hdr_s.type)) {
	case TYPE_NPRQ:
		switch (hdr->raw[RAW_QAC]) {
		case QAC_LG_CLEAR_ALL:
			return MODULE_LOGGER;
		case QAC_LG_READ_LAST:
			return MODULE_LOGGER;
		case QAC_LG_READ_NEXT:
			return MODULE_LOGGER;
		case QAC_LG_GET_COUNT:
			return MODULE_LOGGER;

		default:
			return MODULE_BCP;
		}

	case TYPE_NPD1:
		switch (hdr->raw[RAW_QAC]) {
		case QAC_GETVER:
			switch (hdr->hdr_s.packtype_u.npd1.data) {
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
//			case 6:
//				return MODULE_LCD;
			default:
				return MODULE_BCP;
			}
		case QAC_ECHO:
			return MODULE_BCP;

		default:
			return MODULE_BCP; //MODULE_UNKNOWN;
		}

	case TYPE_NPDL:
		switch (hdr->raw[RAW_QAC]) {
		case QAC_AR_REQUEST:
		case QAC_SERV_DONE:
		case QAC_SERV_REJECT:
			return MODULE_ACCESSOR;
		case QAC_ECHO:
			return MODULE_BCP;
		case QAC_LG_WRITE_EVENT:
			return MODULE_LOGGER;

		default:
			return MODULE_BCP; //MODULE_UNKNOWN;
		}
	case TYPE_CTRL:
		return MODULE_BCP;
	default:
		return MODULE_BCP; //MODULE_UNKNOWN;
	}
}

int bcp_process_buffer(bd_t handler)
{
	int result = 0;
	bcp_header_t * hdr = (bcp_header_t *) bpool[handler].buf;

	switch (TYPE(hdr->hdr_s.type)) {
	case TYPE_CTRL:

		break;
	case TYPE_NPRQ:

		break;
	case TYPE_NPD1:
		switch (hdr->raw[RAW_QAC]) {
		case QAC_GETVER:
			switch (hdr->hdr_s.packtype_u.npd1.data) {
			case 0:
				/* buildlabel */
				hdr->hdr_s.type = TYPE_NPDL;
				hdr->raw[RAW_DATA] = hdr->hdr_s.packtype_u.npd1.data;
				hdr->hdr_s.packtype_u.npdl.len = strlenpgm(buildlabel) + 3;
				strcpypgm2ram((char *) &hdr->raw[RAW_DATA + 1], buildlabel);
				bcp_send_buffer(handler);
				//				bcp_release_buffer(handler);

				break;
			case (MYSELF + 1):
				/* bcp ver */
				hdr->hdr_s.type = TYPE_NPDL;
				hdr->raw[RAW_DATA] = hdr->hdr_s.packtype_u.npd1.data;
				hdr->hdr_s.packtype_u.npdl.len = strlenpgm(ver) + 3;
				strcpypgm2ram((char *) &hdr->raw[RAW_DATA + 1], ver);
				bcp_send_buffer(handler);
				//				bcp_release_buffer(handler);

				break;
			default:
				/* no more modules */
				hdr->hdr_s.type = TYPE_NPDL;
				hdr->raw[RAW_DATA] = hdr->hdr_s.packtype_u.npd1.data;
				strcpypgm2ram((char *) &hdr->raw[RAW_DATA + 1], "\xFF");
				hdr->hdr_s.packtype_u.npdl.len = 1 + 3;
				bcp_send_buffer(handler);
				//				bcp_release_buffer(handler);

				break;
			}
			break;

		default:
			result = -1;
		}
	case TYPE_NPDL:
		switch (hdr->raw[RAW_QAC]) {
		case QAC_ECHO:
			/* echo request*/
			RST_FQ(hdr->hdr_s.type);
			bcp_send_buffer(handler);
			//			bcp_release_buffer(handler);

			break;
		default:
			result = -1;
		}

		break;
	default:
		result = -1;
	}

	bcp_release_buffer(handler);
	TRACE("\n\rBCP: buffer released (rsp sent)");
	return result;
}

static void bcp_check_acked(bd_t buffer) {

	bcp_header_t * ihdr = (bcp_header_t *) bpool[buffer].buf;
	BYTE i;

	for (i = 0; i < NBUFFERS; i++) {
		bcp_header_t * hdr = (bcp_header_t *) bpool[i].buf;

		if (bpool[i].status == BD_NEED_ACK && hdr->raw[RAW_QAC] == ihdr->raw[RAW_QAC]) {
			bcp_release_buffer(i);
			TRACE("\n\rBCP: buffer released (acked)");
		}
	}

}

void bcp_module(void)
{
	bd_t ibuffer = bcp_obtain_buffer(MYSELF);
	modules_e subscriber;
	bd_t i;

	if (ibuffer < 0) {
		TRACE("\n\rBCP: can't obtaine buffer");
		goto skip_reciev;
	}

	if (bcp_reciev_buffer(ibuffer) <= 0) {
		bcp_release_buffer(ibuffer);
		goto skip_reciev;
	}

	TRACE("\n\rBCP: buffer obtained (ipacket)");

	subscriber = bcp_determine_subscriber(ibuffer);

	if (subscriber == MYSELF)
		bcp_process_buffer(ibuffer);
	else
		mail_send(subscriber, ibuffer);

	bcp_check_acked(ibuffer);

skip_reciev:

	/* check timeouts */
	for (i = 0; i < NBUFFERS; i++) {
		if ((bpool[i].status == BD_NEED_ACK) && (TickGet() - bpool[i].timestamp
				> ((TICK_SECOND / 100L) * (DWORD)AppConfig.acc_host_tout))) {
			bpool[i].status = BD_TIMEOUT;
			mail_send(bpool[i].owner, i);
		}
	}
}

