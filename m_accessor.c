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
#include "m_lcd.h"
#include "eventer.h"
#include "m_smachine.h"
#include "trace.h"

rom static char * ver = "AC0.01";
static mailbox_t mailbox;
static accessor_state_e state = WAIT_UID;
static event_t event;

#define MYSELF	MODULE_ACCESSOR

static int process_host_buffer(bd_t handler);
static int process_tout_buffer(bd_t handler);


void accessor_module(void)
{
	bd_t ipacket, opacket;
	static uid_t uid;
	static WORD label_cache;

	if (mail_reciev(MYSELF, &ipacket)) {

		if (bcp_buffer(ipacket)->status == BD_TIMEOUT)
			process_tout_buffer(ipacket);
		else if (bcp_buffer(ipacket)->status == BD_OBTAINED)
			process_host_buffer(ipacket);
	}

	switch (state) {
	case WAIT_UID:
		if (readers_get_uid(&uid)) {
        	memset((void *)LCDText, ' ', LCD_SIZE);
        	LCDText[LCD_SIZE] = '\0';
        	LCDUpdate();
			state = CHECK_SM;
		}

		break;
	case CHECK_SM:
		if(sm_is_ready()) {
			event_send(MODULE_SRVMACHINE, EVT_SM_PREPARE);
		} else {
			strcpy(LCD_STRING_0, AppConfig.acc_busy_msg);
			LCD_decode(LCD_ALL);
			LCDUpdate();
			LCD_set_tout(TICK_SECOND * 5);

			state = WAIT_UID;
			break;
		}

		/* It's OK, send to host */
		opacket = bcp_obtain_buffer(MYSELF);
		

		if (opacket < 0) {

			TRACE("\n\rACS: can't obtaine buffer (QAC_AR_REQUEST)");
			
			break;
		}
		{
			bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(opacket)->buf;
			ar_req *request = (ar_req *) &hdr->raw[RAW_DATA];
			TRACE("\n\rACS: buffer obtained (QAC_AR_REQUEST)");
			
			hdr->hdr_s.type = TYPE_NPDL;
			SET_FQ(hdr->hdr_s.type);
			hdr->hdr_s.packtype_u.npdl.qac = QAC_AR_REQUEST;
			hdr->hdr_s.packtype_u.npdl.len = (sizeof(ar_req) - MAX_UID_SIZE)
					+ strlen(uid.uid) + CRC16_BYTES;

			request->retries = AppConfig.acc_retry_cnt;
			request->reader_n = uid.gate;
			request->req_label = label_cache = (WORD) TickGet();
			strcpy(request->uid, uid.uid);

			bcp_send_buffer(opacket);
			state = WAIT_HOST_ANSWER;
		}
		break;
	case WAIT_HOST_ANSWER:

		break;
	case WAIT_SM:
		if(event_recieve(MYSELF, &event)) {

			opacket = bcp_obtain_buffer(MYSELF);
			if (opacket < 0) {
				break;
			}

			if(event & EVT_AC_DONE) {

				bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(opacket)->buf;
				eos_req *request = (eos_req *) &hdr->raw[RAW_DATA];

				TRACE("\n\rACS: buffer obtained (QAC_SERV_DONE)");

				hdr->hdr_s.type = TYPE_NPDL;
				SET_FQ(hdr->hdr_s.type);
				hdr->hdr_s.packtype_u.npdl.qac = QAC_SERV_DONE;
				hdr->hdr_s.packtype_u.npdl.len = sizeof(eos_req) + CRC16_BYTES;

				request->retries = AppConfig.acc_retry_cnt;
				request->reader_n = uid.gate;
				request->req_label = label_cache;

				bcp_send_buffer(opacket);

				state = WAIT_UID;
				readers_reset_state();

			} else if (event & EVT_AC_TOUT) {

				bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(opacket)->buf;
				eos_req *request = (eos_req *) &hdr->raw[RAW_DATA];

				TRACE("\n\rACS: buffer obtained (QAC_SERV_REJECT)");

				hdr->hdr_s.type = TYPE_NPDL;
				SET_FQ(hdr->hdr_s.type);
				hdr->hdr_s.packtype_u.npdl.qac = QAC_SERV_REJECT;
				hdr->hdr_s.packtype_u.npdl.len = sizeof(eos_req) + CRC16_BYTES;

				request->retries = AppConfig.acc_retry_cnt;
				request->reader_n = uid.gate;
				request->req_label = label_cache;

				bcp_send_buffer(opacket);

				state = WAIT_UID;
				readers_reset_state();

			} else {
				bcp_release_buffer(opacket);
			}
		}

		break;
	}

}

void accessor_init(void)
{
	mail_subscribe(MYSELF, &mailbox);
}

void ServiceIt (BYTE aCode, char* msg, int len_msg)
{
    int l;
    l=(len_msg > LCD_SIZE) ? LCD_SIZE : len_msg;
	memset((void *)LCDText, ' ', LCD_SIZE);
	memcpy((void *)LCDText, (void *)msg, l);
	LCDText[l] = '\0';
	LCD_decode(LCDText);
	LCDUpdate();

    if(aCode & ACCESS_INDICATOR)        
    	event_send(MODULE_SRVMACHINE, EVT_SM_ENABLE_INDICATOR);

	if(!(aCode & ACCESS_CONTROL)) {
		event_send(MODULE_SRVMACHINE, EVT_SM_DISABLE_CONTROL);
		state = WAIT_UID;
		readers_reset_state();
		LCD_set_tout(TICK_SECOND * 5);
	} else {
		event_send(MODULE_SRVMACHINE, EVT_SM_ENABLE_CONTROL);
		state = WAIT_SM;
    }
}

static int process_tout_buffer(bd_t handler)
{
	int result = 0;
	bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(handler)->buf;

	switch (TYPE(hdr->hdr_s.type)) {
	case TYPE_NPDL:

		if (hdr->hdr_s.packtype_u.npdl.qac == QAC_AR_REQUEST) {

			ar_req *request = (ar_req *) &hdr->raw[RAW_DATA];

			if (request->retries) {
				request->retries--;
				bcp_send_buffer(handler);
				TRACE("\n\rACS: resend QAC_AR_REQUEST");
			} else {
				bcp_release_buffer(handler);
				TRACE("\n\rACS: buffer released (no rsp QAC_AR_REQUEST)");
//### OFF-LineMode
            	ServiceIt (AppConfig.acc_local_access, AppConfig.acc_local_msg, strlen(AppConfig.acc_local_msg));

//				if(state == WAIT_HOST_ANSWER) {
//					state = WAIT_UID;
//					readers_reset_state();
//				}
//
			}
		} else if (hdr->hdr_s.packtype_u.npdl.qac == QAC_SERV_DONE) {

			eos_req *request = (eos_req *) &hdr->raw[RAW_DATA];

			if (request->retries) {
				request->retries--;
				bcp_send_buffer(handler);
				TRACE("\n\rACS: resend QAC_SERV_DONE");
			} else {
				bcp_release_buffer(handler);
				TRACE("\n\rACS: buffer released (no rsp QAC_SERV_DONE)");
//				if(state == WAIT_HOST_ANSWER) {
//					state = WAIT_UID;
//					readers_reset_state();
//				}
//
			}
		} else if (hdr->hdr_s.packtype_u.npdl.qac == QAC_SERV_REJECT) {

			eos_req *request = (eos_req *) &hdr->raw[RAW_DATA];

			if (request->retries) {
				request->retries--;
				bcp_send_buffer(handler);
				TRACE("\n\rACS: resend QAC_SERV_REJECT");
			} else {
				bcp_release_buffer(handler);
				TRACE("\n\rACS: buffer released (no rsp QAC_SERV_REJECT)");
//				if(state == WAIT_HOST_ANSWER) {
//					state = WAIT_UID;
//					readers_reset_state();
//				}
//
			}
		} else {
			result = -1;
		}
		break;

	default:
		result = -1;
	}

	return result;
}


static int process_host_buffer(bd_t handler)
{
	int result = 0;
//    event_t sm_evnt=0;
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
				break;
			default:
				result = -1;
			}
			break;

		default:
			result = -1;
		}
		break;
	case TYPE_NPDL:

	if(hdr->hdr_s.packtype_u.npdl.qac == QAC_AR_REQUEST) {

		BYTE msg_len = hdr->hdr_s.packtype_u.npdl.len - (sizeof(ar_rsp) - MAX_MSG_SIZE) - 2;
		ar_rsp *request = (ar_rsp *) &hdr->raw[RAW_DATA];

		if(state == WAIT_HOST_ANSWER)	// else DropIt() )
			ServiceIt (request->access_code, request->msg,  msg_len);


//		msg_len = (msg_len > 32) ? 32 : msg_len;

//		memset((void *)LCDText, ' ', 32);
//		memcpy((void *)LCDText, (void *)request->msg, msg_len);
//		LCDText[msg_len] = '\0';
//		LCD_decode(LCDText);
//		LCDUpdate();

//        if(request->access_code & ACCESS_INDICATOR)        
//        	event_send(MODULE_SRVMACHINE, EVT_SM_ENABLE_INDICATOR);
//
//		if(!(request->access_code & ACCESS_CONTROL)) {
//			event_send(MODULE_SRVMACHINE, EVT_SM_DISABLE_CONTROL);
//			state = WAIT_UID;
//			readers_reset_state();
//		} else {
//			event_send(MODULE_SRVMACHINE, EVT_SM_ENABLE_CONTROL);
//			state = WAIT_SM;
//		}

	}
		break;

	default:
		result = -1;
	}

	bcp_release_buffer(handler);
	TRACE("\n\rACS: buffer released (rsp sent)");

	return result;
}

