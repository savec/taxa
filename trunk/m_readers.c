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



static unsigned char code[BP_SIZE], processing_code[BP_SIZE];

static BYTE position;
static DWORD t = 0;
reader_status_e status = READER_VOID;

rom static char * ver = "RD0.01";
static mailbox_t mailbox;
#define MYSELF	MODULE_READERS

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
#define reset_state()						\
do {										\
	bp_bzero(processing_code, sizeof(processing_code));					\
	position = WIEGAND_34_LEN - 1;	\
	status = READER_VOID;					\
} while(0)


int readers_process_buffer(bd_t handler)
{
	int result = 0;
	bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(handler)->buf;

	switch (TYPE(hdr->hdr_s.type)) {
	case TYPE_NPD1:
		switch (hdr->raw[RAW_QAC]) {
		case QAC_GETVER:
			switch (hdr->hdr_s.packtype_u.npd1.data) {
			case 2:
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
	return result;
}


void readers_init(void)
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

	reset_state();

	mail_subscribe(MYSELF, &mailbox);
}

#define shift_position()							\
	do{												\
		if(position) {								\
			position --;							\
			status = READER_INPROGRESS;				\
		} else { 									\
			bp_cp(processing_code, code, sizeof(processing_code)); 				\
			bp_bzero(processing_code, sizeof(processing_code)); 					\
			position = WIEGAND_34_LEN - 1;			\
			status = READER_READY; 					\
		} 											\
	}while(0)

void readers_isr(void)
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

BYTE readers_get_uid(DWORD *uid)
{
	WORD ldata;
	WORD hdata;


	switch(status) {
	case READER_VOID:
		return 0;

	case READER_INPROGRESS:
		if(TickGet() - t >= TICK_SECOND/10ul) {
			reset_state();
		}
		return 0;

	case READER_READY:

		w34_get_ldata(code, &ldata);
		w34_get_hdata(code, &hdata);

		// odd/even check here

		*uid = ((DWORD)hdata << 16) | ldata;

		reset_state();

		return 1;

	}
}

reader_status_e readers_getstatus(void)
{
	return status;
}

void readers_module(void)
{
	bd_t ipacket;
	DWORD uid;

	if(readers_get_uid(&uid)) {
		/* send to host */
	}

	if(mail_reciev(MYSELF, &ipacket)) {
		readers_process_buffer(ipacket);
	}
}


//unsigned int get_cnt0(void)
//{
//	return cnt0;
//}
//
//unsigned int get_cnt1(void)
//{
//	return cnt1;
//}



