/*
 * m_smachine.c
 *
 *  Created on: 12.04.2013
 *      Author: admin
 */
#include "post.h"
#include "m_bcp.h"
#include "m_smachine.h"
#include "eventer.h"
#include "m_accessor.h"
#include "m_lcd.h"
#include "trace.h"

sm_state_e state;
rom static char * ver = "SM0.01";
static mailbox_t mailbox;
static event_t event;
static BOOL sm_is_sig_done(void);

#define MYSELF	MODULE_SRVMACHINE

static int process_buffer(bd_t handler)
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
	TRACE("\n\rSM: buffer released (rsp sent)");

	return result;
}

void sm_init(void)
{
	// XXX check INs

	LCD_prompt();

	mail_subscribe(MYSELF, &mailbox);
	state = SM_READY;

}

BOOL sm_is_ready(void) {
	return !sm_is_sig_done();	// XXX check it
}

static void sm_control_off(void)
{
	if(AppConfig.sm_sig_control_en) {
		if(AppConfig.sm_sig_control_inverse)
			switch(AppConfig.sm_sig_control_relay)
			{
			case 0:
				P_REL1 = 1;
				break;
			case 1:
				P_REL2 = 1;
				break;
			}
		else
			switch(AppConfig.sm_sig_control_relay)
			{
			case 0:
				P_REL1 = 0;
				break;
			case 1:
				P_REL2 = 0;
				break;
			}
	}
}

static void sm_control_on(void)
{
	if(AppConfig.sm_sig_control_en) {
		if(AppConfig.sm_sig_control_inverse)
			switch(AppConfig.sm_sig_control_relay)
			{
			case 0:
				P_REL1 = 0;
				break;
			case 1:
				P_REL2 = 0;
				break;
			}
		else
			switch(AppConfig.sm_sig_control_relay)
			{
			case 0:
				P_REL1 = 1;
				break;
			case 1:
				P_REL2 = 1;
				break;
			}
	}
}

static void sm_indicator_off(void)
{
	if(AppConfig.sm_sig_indicator_en) {
		if(AppConfig.sm_sig_indicator_inverse)
			switch(AppConfig.sm_sig_indicator_relay)
			{
			case 0:
				P_REL1 = 1;
				break;
			case 1:
				P_REL2 = 1;
				break;
			}
		else
			switch(AppConfig.sm_sig_indicator_relay)
			{
			case 0:
				P_REL1 = 0;
				break;
			case 1:
				P_REL2 = 0;
				break;
			}
	}
}

static void sm_indicator_on(void)
{
	if(AppConfig.sm_sig_indicator_en) {
		if(AppConfig.sm_sig_indicator_en) {
			if(AppConfig.sm_sig_indicator_inverse)
				switch(AppConfig.sm_sig_indicator_relay)
				{
				case 0:
					P_REL1 = 0;
					break;
				case 1:
					P_REL2 = 0;
					break;
				}
			else
				switch(AppConfig.sm_sig_indicator_relay)
				{
				case 0:
					P_REL1 = 1;
					break;
				case 1:
					P_REL2 = 1;
					break;
				}
		}
	}
}



static void sm_indicator(int on)
{
	static DWORD t;
	static BOOL armed = 0;

	switch(on) {
	case -1:
		if(armed && ((TickGet() - t) > ((TICK_SECOND / 100L) * (DWORD)AppConfig.sm_sig_indicator_duration))) {
			sm_indicator_off();
			armed = 0;
		}
		break;
	case 0:
		sm_indicator_off();
		armed = 0;
		break;
	case 1:
		t = TickGet(); 
		sm_indicator_on();
		armed = 1;
		break;
	}
}

static void sm_control(int on)
{
	static DWORD t;
	static BOOL armed = 0;

	switch(on) {
	case -1:
		if(armed && ((TickGet() - t) > ((TICK_SECOND / 100L) * (DWORD)AppConfig.sm_sig_control_duration))) {
			sm_control_off();
			armed = 0;
		}
		break;
	case 0:
		sm_control_off();
		armed = 0;
		break;
	case 1:
		t = TickGet();
		sm_control_on();
		armed = 1;
		break;
	}
}
//static void sm_lcd(int on)
//{
//	static DWORD t;
//	static BOOL armed = 0;
//
//	switch(on) {
//	case -1:
//		if(armed && ((TickGet() - t) > (TICK_SECOND * 5))) {
//			LCD_prompt();
//			armed = 0;
//		}
//		break;
//	case 1:
//		t = TickGet();
//
//		armed = 1;
//		break;
//	}
//
//}

static BOOL sm_is_sig_done(void)
{
	BOOL result = FALSE;

	if(AppConfig.sm_sig_done_en) {
		switch(AppConfig.sm_sig_done_sensor) {
		case 0:
			result = AppConfig.sm_sig_done_inverse ? !P_IN1 : P_IN1;
			break;
		case 1:
			result = AppConfig.sm_sig_done_inverse ? !P_IN2 : P_IN2;
			break;
		}
	}
	return result;
}

static BOOL sm_is_sig_failure(void)
{
	BOOL result = FALSE;

	if(AppConfig.sm_sig_failure_en) {
		switch(AppConfig.sm_sig_failure_sensor) {
		case 0:
			result = AppConfig.sm_sig_failure_inverse ? !P_IN1 : P_IN1;
			break;
		case 1:
			result = AppConfig.sm_sig_failure_inverse ? !P_IN2 : P_IN2;
			break;
		}
	}
	return result;
}


void sm_module(void)
{
	bd_t ipacket;
	static DWORD t;

	if (mail_reciev(MYSELF, &ipacket))
			process_buffer(ipacket);

	sm_indicator(-1);
	sm_control(-1);
//	sm_lcd(-1);

	switch(state) {
	case SM_INIT:
		break;
	case SM_READY:
		if(event_recieve(MYSELF, &event)) {
			if(event & EVT_SM_PREPARE) {
				state = SM_PREPARE;
                sm_indicator(0);
			}
		}
		break;
	case SM_PREPARE:
		if(event_recieve(MYSELF, &event)) {

            if(event & EVT_SM_ENABLE_INDICATOR)
                sm_indicator(1);
            else
                sm_indicator(0);
           
            if (event & EVT_SM_ENABLE_CONTROL)
            {
                sm_control(1);
				t = TickGet();
				state = SM_WORK;
            }
            else {
            	state = SM_READY;
            }
		}
		break;
	case SM_WORK:
		if((TickGet() - t) > ((TICK_SECOND * (DWORD)AppConfig.sm_service_time) / 100L)) {
			event_send(MODULE_ACCESSOR, EVT_AC_TOUT);
			LCD_prompt();
			state = SM_FINAL;
		} else if (sm_is_sig_done()) {
			sm_control(0);
			event_send(MODULE_ACCESSOR, EVT_AC_DONE);
			LCD_prompt();
			state = SM_FINAL;
		}
		break;
	case SM_FINAL:
		state = SM_READY;	// XXX
		break;
	case SM_FAILURE:
		break;
	}
}
