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



static unsigned char code[BP_SIZE], processing_code[BP_SIZE];

static BYTE position;
static volatile DWORD t = 0;
static wg_reader_status_e wg_status = WG_READER_VOID;
static serial_reader_status_e serial_status = SERIAL_WAIT_CODE;

rom static char * ver = "RD0.00";
static mailbox_t mailbox;
#define MYSELF	MODULE_READERS

volatile static serial_buffer_t sb;

static void uid2hex(BYTE * uid, BYTE * hex, BYTE size)
{
	BYTE *s = hex;
	BYTE *b = uid + (size - 1);

	for (; size--; s += 2, b--) {
		s[0] = btohexa_high(*b);
		s[1] = btohexa_low(*b);
	}

	*s = '\0';
}

void serial_reset(void)
{
//	BYTE l = splhigh();
	sb.in = sb.out = sb.cnt = 0;
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

BYTE w34_get_odd(unsigned char *bp)
{
	return bp_tstbit(bp, 0) ? 1 : 0;
}

BYTE w34_get_even(unsigned char *bp)
{
	return bp_tstbit(bp, WIEGAND_34_LEN - 1) ? 1 : 0;
}

void w34_get_ldata(unsigned char *bp, WORD *ldata)
{
	int i;

	for(*ldata = 0, i = WIEGAND_34_HALF_DATA_LEN - 1; i >= 0; i--) {
		*ldata <<= 1;
		if(bp_tstbit(bp, WIEGAND_34_LDATA_START + i)) *ldata |= 1;
	}
}

void w34_get_hdata(unsigned char *bp, WORD *hdata)
{
	int i;

	for(*hdata = 0, i = WIEGAND_34_HALF_DATA_LEN - 1; i >= 0; i--) {
		*hdata <<= 1;
		if(bp_tstbit(bp, WIEGAND_34_HDATA_START + i)) *hdata |= 1;
	}
}



//#define w34_get_ldata(bp, ldata)	((bp >> 1) & 0xffff)
//#define w34_get_hdata(bp, hdata)	((bp >> (WIEGAND_34_LEN / 2)) & 0xffff)
#define wg_reset_state()						\
do {										\
	bp_bzero(processing_code, sizeof(processing_code));					\
	position = WIEGAND_34_LEN - 1;	\
	wg_status = WG_READER_VOID;					\
} while(0)


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
	putrsUSART("\n\rRDR: buffer released (rsp sent)");

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
	serial_reset();
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
			bp_bzero(processing_code, sizeof(processing_code)); 					\
			position = WIEGAND_34_LEN - 1;			\
			wg_status = WG_READER_READY; 					\
		} 											\
	}while(0)

void wg_readers_isr(void)
{
	if(INTCONbits.INT0IF) {
		INTCONbits.INT0IF = 0;
		shift_position();
		t = TickGet();
	}
	if(INTCON3bits.INT2IF) {
		INTCON3bits.INT2IF = 0;
		bp_setbit(processing_code, position);
		shift_position();
		t = TickGet();
	}
}

static BOOL serial_get_uid(BYTE *uid)
{
	static BYTE code_str[40], cnt = 0;
	BYTE data;

	while (serial_cnt()) {
		serial_out(&data);
		switch (serial_status) {
		case SERIAL_WAIT_CODE:
			if(isdigit(data)) {
				code_str[cnt ++] = data;
				if(cnt >= SERIAL_CODE_LEN) {
					serial_status = SERIAL_WAIT_CR;
				}
			} else if(data == 0x0d) { // <CR>
				cnt = 0;
			}

			break;
		case SERIAL_WAIT_CR:

			if(data == 0x0d) {
				code_str[cnt] = '\0';
				strcpy(uid, code_str);
				return TRUE;
			}
			cnt = 0;
			serial_status = SERIAL_WAIT_CODE;
			break;
		}
	}
	return FALSE;
}


static BOOL wg_get_uid(BYTE *uid)
{
	WORD ldata;
	WORD hdata;
	DWORD d_uid;


	switch(wg_status) {
	case WG_READER_VOID:
		return FALSE;

	case WG_READER_INPROGRESS:
		if(TickGet() - t > TICK_SECOND/2) {
			wg_reset_state();
		}
		return FALSE;

	case WG_READER_READY:

		w34_get_ldata(code, &ldata);
		w34_get_hdata(code, &hdata);

		// odd/even check here

		d_uid = swapl(((DWORD)hdata << 16) | ldata);

		wg_reset_state();

		uid2hex(&d_uid, uid, sizeof(d_uid));

		return TRUE;

	}
}


BYTE readers_get_uid(uid_t *uid)
{
	if(AppConfig.r1_activity) {
		if(wg_get_uid(uid->uid)) {
			uid->gate = 0;
			return 1;
		}
	}

	if(AppConfig.r2_activity) {
		if(serial_get_uid(uid->uid)) {
			uid->gate = 1;
			return 1;
		}
	}
	return 0;
}

wg_reader_status_e wg_readers_getstatus(void)
{
	return wg_status;
}

void readers_module(void)
{
	bd_t ipacket;

	if(mail_reciev(MYSELF, &ipacket)) {
		readers_process_buffer(ipacket);
	}
}



