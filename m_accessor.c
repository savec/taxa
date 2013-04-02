/*
 * m_accessor.c
 *
 *  Created on: 01.04.2013
 *      Author: admin
 */

#include "m_accessor.h"
#include "m_bcp.h"
#include "m_readers.h"
#include "post.h"

rom static char * ver = "AC0.01";
static mailbox_t mailbox;
static accessor_state_e state = WAIT_UID;

#define MYSELF	MODULE_ACCESSOR

static int process_buffer_wait_uid(bd_t handler);
static int process_buffer_wait_host(bd_t handler);

void accessor_module(void)
{
	bd_t ipacket, opacket;
	static DWORD uid;

	switch(state) {
	case WAIT_UID:
		if(readers_get_uid(&uid)) {
			state = CHECK_SM;
		}

		if (mail_reciev(MYSELF, &ipacket)) {
			process_buffer_wait_uid(ipacket);
		}
		break;
	case CHECK_SM:
		// XXX Service Machine implementation

		/* It's OK, send to host */
		opacket = bcp_obtain_buffer(MYSELF);

		if (opacket < 0) {
			// XXX ASSERT (LOGGER)
			putrsUSART("\r\nACS: can't obtaine buffer");
			break;
		}
		{
			bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(opacket)->buf;
			ar_req *request = (ar_req *)&hdr->raw[RAW_DATA];

			putrsUSART("\r\nACS: buffer obtained");

			hdr->hdr_s.type = TYPE_NPDL;
			SET_FQ(hdr->hdr_s.type);
			hdr->hdr_s.packtype_u.npdl.qac = QAC_AR_REQUEST;
			hdr->hdr_s.packtype_u.npdl.len = sizeof(ar_req) + 2;

			request->retries = 2;
			request->reader_n = 1;
			request->req_label = (WORD)TickGet();
			request->uid = uid;

			bcp_send_buffer(opacket);

			bcp_release_buffer(opacket); // XXX remove!
			putrsUSART("\r\nACS: buffer released");
			state = WAIT_UID; // XXX remove!

		}

//		state = WAIT_HOST_ANSWER;
		break;
	case WAIT_HOST_ANSWER:
		break;
	case WAIT_SM:
		break;
	}

}

void accessor_init(void)
{
	mail_subscribe(MYSELF, &mailbox);
}

static int process_buffer_wait_host(bd_t handler)
{
	int result = 0;
	bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(handler)->buf;

	switch (TYPE(hdr->hdr_s.type)) {
	case TYPE_NPDL:

		break;

	default:
		result = -1;
	}

	bcp_release_buffer(handler);
	putrsUSART("\n\rACCESSOR: buffer released");
	return result;
}

static int process_buffer_wait_uid(bd_t handler)
{
	int result = 0;
	bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(handler)->buf;

	switch (TYPE(hdr->hdr_s.type)) {
	case TYPE_NPD1:
		switch (hdr->raw[RAW_QAC]) {
		case QAC_GETVER:
			switch (hdr->hdr_s.packtype_u.npd1.data) {
			case (MYSELF + 1):
				/* readers ver */
				hdr->hdr_s.type = TYPE_NPDL;
				hdr->raw[RAW_DATA] = hdr->hdr_s.packtype_u.npd1.data;
				hdr->hdr_s.packtype_u.npdl.len = strlenpgm(ver) + 3;
				strcpypgm2ram((char *) &hdr->raw[RAW_DATA + 1], ver);
				bcp_send_buffer(handler);
				//				bcp_release_buffer(handler);

				break;
			default:
				result = -1;
			}
			break;

		default:
			result = -1;
		}
		break;
	default:
		result = -1;
	}

	bcp_release_buffer(handler);
	putrsUSART("\n\rACCESSOR: buffer released");
	return result;
}
