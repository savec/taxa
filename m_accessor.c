/*
 * m_accessor.c
 *
 *  Created on: 01.04.2013
 *      Author: admin
 */

#include "m_accessor.h"
#include "m_bcp.h"
#include "post.h"

rom static char * ver = "AC0.01";
static mailbox_t mailbox;
#define MYSELF	MODULE_ACCESSOR


static int accessor_process_buffer(bd_t handler);

void accessor_module(void)
{
	bd_t ipacket;


	if(mail_reciev(MYSELF, &ipacket)) {
		accessor_process_buffer(ipacket);
	}
}

void accessor_init(void)
{
	mail_subscribe(MYSELF, &mailbox);
}

static int accessor_process_buffer(bd_t handler)
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
