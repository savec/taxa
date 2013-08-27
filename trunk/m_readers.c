/* 
 * readers.c
 *
 *  Created on: 02.02.2013
 *      Author: admin
 */
#include "bit_pattern.h"
#include "m_readers.h"
#include "m_bcp.h"
#include "post.h"
#include "skipic.h"
#include "trace.h"


volatile static unsigned char code[BP_SIZE], processing_code[BP_SIZE];

volatile static BYTE position;
volatile static wg_reader_status_e wg_status = WG_READER_VOID;
static serial_reader_status_e serial_status = SERIAL_WAIT_FRAME;

rom static char * ver = "RD0.00";
static mailbox_t mailbox;
#define MYSELF	MODULE_READERS

volatile static serial_buffer_t sb;


static void led_on(void)
{
	LED1_IO = 1;
}

static void led_off(void)
{
	LED1_IO = 0;
}

void led(int on)
{
	static DWORD t;
	static BOOL armed = 0;

	switch(on) {
	case -1:
		if(armed && ((TickGet() - t) > (TICK_SECOND / 10L))) {
			led_off();
			armed = 0;
		}
		break;
	case 0:
		led_off();
		armed = 0;
		break;
	case 1:
		t = TickGet();
		led_on();
		armed = 1;
		break;
	}

}

static void serial_reset_state(void)
{
//	BYTE l = splhigh();
	sb.in = sb.out = sb.cnt = 0;
	serial_status = SERIAL_WAIT_FRAME;
//	splx(l);
}

BOOL serial_in(BYTE data)
{
	if(((sb.in + 1)& SERIAL_BUF_MASK) == sb.out)
		return FALSE;

	sb.buf[sb.in] = data;
	sb.in ++;
	sb.in &= SERIAL_BUF_MASK;
	sb.cnt ++;

	return TRUE;
}

BOOL serial_out(BYTE *data)
{
	if(sb.cnt == 0)
		return FALSE;

	*data = sb.buf[sb.out];
	sb.out ++;
	sb.out &= SERIAL_BUF_MASK;
	sb.cnt--;

	return TRUE;
}

BYTE serial_cnt(void)
{
	return sb.cnt;
}

static BYTE wg_remove_odd(void)
{
	BYTE odd = bp_tstbit(code, WIEGAND_LEN - 1);
	bp_rstbit(code, WIEGAND_LEN - 1);

	return !!odd;
}

static BYTE wg_remove_even(void)
{
	BYTE even = bp_tstbit(code, 0);
	bp_rstbit(code, 0);

	return !!even;
}

/*
 * byte_num: 0 - LSB
 * parity bits must be set to 0 before calling
 * returns byte of data from code (whithout parity bits), if byte_num out of range returns 0
 */

static BYTE wg_get_byte(BYTE byte_num)
{
	int i;
	BYTE data = 0;

	if(byte_num > sizeof(code) - 1)
		return 0;

	for(i = (byte_num + 1) * 8 - 1; i >= byte_num * 8; i--) {
		data <<= 1;
		if(bp_tstbit(code, WIEGAND_DATA_START + i)) data |= 1;
	}

	return data;
}

#define wg_reset_state()						\
do {										\
	bp_bzero(processing_code, sizeof(processing_code));					\
	position = WIEGAND_LEN - 1;	\
	wg_status = WG_READER_VOID;					\
} while(0)


// Reader Command Processor
static int readers_process_buffer(bd_t handler)
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
	TRACE("\n\rRDR: buffer released (rsp sent)");

	return result;
}

#define isdigit(ch) ((ch) >= '0' && (ch) <= '9')

void serial_isr(void)
{
//	BYTE data;

	if(PIR1bits.RC1IF) {
//		data = RCREG;
//		if(isdigit(data))
		serial_in(RCREG);
	}
}

static void serial_init(void)
{
	set_uart(AppConfig.rs232_baudrate, TRUE, FALSE);
	serial_reset_state();
}

void readers_reset_state(void)
{
	wg_reset_state();
	serial_reset_state();
}

static void wg_init(void)
{
	TRISBbits.TRISB0 = 1;		// INT0
	TRISBbits.TRISB2 = 1;		// INT2

	INTCON2bits.INTEDG0 = 0;
	INTCONbits.INT0IF = 0;		// clear pending
	INTCONbits.INT0IE = 1;		// enable interrupt

	INTCON2bits.INTEDG2 = 0;
	INTCON3bits.INT2IP = 1;		// INT2 high priority (INT0 is high always)
	INTCON3bits.INT2IF = 0;		// clear pending
	INTCON3bits.INT2IE = 1;		// enable interrupt

	wg_reset_state();
}

// *** Reader Initiator
void readers_init(void)
{
	if(AppConfig.r1_activity)
		wg_init();
	if(AppConfig.r2_activity)
		serial_init();
	mail_subscribe(MYSELF, &mailbox);
}

#define shift_position()							\
	do{												\
		if(position) {								\
			position --;							\
			wg_status = WG_READER_INPROGRESS;				\
		} else { 									\
			bp_cp(processing_code, code, sizeof(processing_code)); 				\
			wg_status = WG_READER_READY; 					\
		} 											\
	}while(0)

void wg_readers_isr(void)
{
	if(INTCONbits.INT0IF) {
		INTCONbits.INT0IF = 0;
		shift_position();
		// t = TickGet();
	}
	if(INTCON3bits.INT2IF) {
		INTCON3bits.INT2IF = 0;
		bp_setbit(processing_code, position);
		shift_position();
		// t = TickGet();
	}
}
//Serial reading
static BOOL serial_decode(BYTE *from, BYTE * to, BYTE count)
{
	// static BYTE code_str[SERIAL_MAX_FRAME_LEN];
	BYTE code_begin = (AppConfig.r2_code_begin) ? (AppConfig.r2_code_begin - 1) : 0; // 0, 1 -> 0
	BYTE code_len = (AppConfig.r2_code_len) ? AppConfig.r2_code_len : count;
	int i;

	if(count < (code_begin + code_len))
		return FALSE;

	from += code_begin;

	if(AppConfig.r2_convert2hex) {
		for(i = 0; i < code_len; i ++, from ++) {
			*to++ = btohexa_high(*from);
			*to++ = btohexa_low(*from);
		}
		*to = '\0';
	} else {
		strncpy(to, from, code_len);
	    *(to + code_len) = '\0';
	}

	return TRUE;
}

static BOOL serial_get_uid(BYTE *uid)
{
	static BYTE code_str[SERIAL_MAX_FRAME_LEN], cnt = 0;
    static DWORD t;
	BYTE data;
	BOOL result = FALSE;

// intreChar delay
	if(serial_status==SERIAL_WAIT_ENDFRAME
       && AppConfig.r2_max_delay  
       && ((TickGet() - t) > ((TICK_SECOND / 100L) * (DWORD)AppConfig.r2_max_delay))) {
		//serial_reset_state();
    	cnt = 0;
   		serial_status = SERIAL_WAIT_FRAME;
    }

	while (serial_cnt()) {
		serial_out(&data);
        t = TickGet();
		switch (serial_status) {
		case SERIAL_WAIT_FRAME:
			code_str[cnt ++] = data;
			serial_status = SERIAL_WAIT_ENDFRAME;
			break;

		case SERIAL_WAIT_ENDFRAME:
            code_str[cnt ++] = data;
            
            if (cnt > SERIAL_MAX_FRAME_LEN)  { // BufferCLenontrol
		    	result = serial_decode(code_str, uid, cnt);
		    	cnt = 0;
	    		serial_status = SERIAL_WAIT_FRAME;
	    		led(1);
            } else if (AppConfig.r2_framelen && cnt >= AppConfig.r2_framelen) { // stopbyte & FrameLen - Alternative
				result = serial_decode(code_str, uid, cnt);
				cnt = 0;
				serial_status = SERIAL_WAIT_FRAME;
				led(1);
			} else if (data == AppConfig.r2_stop_byte) {
				result = serial_decode(code_str, uid, --cnt);
				cnt = 0;
				serial_status = SERIAL_WAIT_FRAME;
				led(1);
			}

			break;

        default: serial_reset_state();
		}
	}
	return result;
}

static BOOL wg_lo_is_even(void)
{
	BYTE s;
	int i;
	BYTE start = WIEGAND_DATA_START;
	BYTE end = WIEGAND_DATA_START + ((WIEGAND_DATA_BITS / 2) + ((WIEGAND_DATA_BITS & 1) ? 1 : 0));

	for(i = start; i < end; i ++)
		if(bp_tstbit(code, i))
			s ^= 1;

	return (s == 0);
}

static BOOL wg_hi_is_odd(void)
{
	BYTE s;
	int i;
	BYTE start = WIEGAND_DATA_START + ((WIEGAND_DATA_BITS / 2) - ((WIEGAND_DATA_BITS & 1) ? 1 : 0));
	BYTE end = WIEGAND_LEN - 1;

	for(i = start; i < end; i ++)
		if(bp_tstbit(code, i))
			s ^= 1;

	return (s == 1);
}


//  Wiegand reading
static BOOL wg_get_uid(BYTE *uid)
{
	BYTE data;
	DWORD d_uid;
	BYTE odd, even;
	int i;
	static DWORD t = 0;


	switch(wg_status) {
	case WG_READER_VOID:
		t = TickGet();
		return FALSE;

	case WG_READER_INPROGRESS:
		if(TickGet() - t > TICK_SECOND) {
			wg_reset_state();
		}
		return FALSE;

	case WG_READER_READY:

		wg_reset_state();
		led(1);

		odd = wg_remove_odd();
		even = wg_remove_even();

		if((wg_lo_is_even() && !even) || (wg_hi_is_odd() && !odd))
			return FALSE;

		for(i = 0; i < WIEGAND_DATA_BYTES; i ++) {
			data = wg_get_byte(i);
			*uid++ = btohexa_high(data);
			*uid++ = btohexa_low(data);
		}

		*uid = '\0';

		return TRUE;
	}
}


BYTE readers_get_uid(uid_t *uid)
{
	if(AppConfig.r1_activity) {
		if(wg_get_uid(uid->uid)) {
			uid->gate = 1;
			return 1;
		}
	}

	if(AppConfig.r2_activity) {
		if(serial_get_uid(uid->uid)) {
			uid->gate = 2;
			return 1;
		}
	}
	return 0;
}

wg_reader_status_e wg_readers_getstatus(void)
{
	return wg_status;
}

// Reader Processor
void readers_module(void)
{
	bd_t ipacket;

	led(-1);

	if(mail_reciev(MYSELF, &ipacket)) {
		readers_process_buffer(ipacket);
	}
}



