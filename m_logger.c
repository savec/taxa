/*
 * m_logger.c
 *
 *  Created on: 09.03.2013
 *      Author: admin
 */

#include "m_logger.h"
#include "post.h"
#include <string.h>

rom static char * ver = "LG0.01";
static mailbox_t mailbox;

#define MYSELF	MODULE_LOGGER


static BOOL slog_need_format(void);

static DWORD slog_pos;
static DWORD get_pos;
static DWORD cnt_events;

static void slog_get_time(time_t *time)
{
	QWORD qw_time = TickGetFullScale();

	time->hours = (DWORD)(qw_time/TICK_HOUR);
	qw_time %= TICK_HOUR;
	time->minutes = (BYTE)(qw_time/TICK_MINUTE);
	qw_time %= TICK_MINUTE;
	time->seconds = (BYTE)(qw_time/TICK_SECOND);
}

void slog_init(void)
{
	if (slog_need_format()) {
		slog_fast_format();
	} else {
		cnt_events = 0;
		XEEBeginRead(SLOG_START);
		for (slog_pos = 0; slog_pos < SLOG_LEN; slog_pos++) {
			BYTE ch = XEERead();
			if(ch == SLOG_EOF)
				break;
			if(ch == '\n')
				cnt_events ++;
		}
		XEEEndRead();
	}

	slog_getlast(NULL, 0); // set get_pos pointer

	mail_subscribe(MYSELF, &mailbox);
}

void slog_fast_format(void)
{
	XEEBeginWrite(SLOG_START);
	XEEWrite(SLOG_EOF);
	XEEEndWrite();
	slog_pos = 0;
	cnt_events = 0;
}

void slog_format(void)
{
	DWORD addr = SLOG_START;

	for (XEEBeginWrite(addr); addr < SLOG_START + SLOG_LEN; addr++) {
		if(addr % PAGE_SIZE == 0)
			XEEBeginWrite(addr);
		XEEWrite(SLOG_EOF);
	}
	XEEEndWrite();
	slog_pos = 0;
	cnt_events = 0;
}

static BOOL slog_need_format(void)
{
	/*
	 * check's first slog page
	 */
	DWORD addr;
	XEEBeginRead(SLOG_START);
	for (addr = SLOG_START; addr < SLOG_START + PAGE_SIZE; addr++) {
		if (XEERead() ^ 0xFF) {
			XEEEndRead();
			return FALSE;
		}
	}
	XEEEndRead();
	return TRUE;
}

static int slog_put_timestamp(void)
{
	int put;
	time_t time;
	BYTE str_buf[13];
	char *str_time;

	slog_get_time(&time);
	sprintf(str_buf, "%05i:%02i:%02i ", (int)time.hours, (int)time.minutes, (int)time.seconds);

	XEEBeginWrite(SLOG_START + slog_pos);
	for (put = 0, str_time = str_buf; (*str_time) && (slog_pos < SLOG_LEN); slog_pos++, put++, str_time++) {
		if((SLOG_START + slog_pos) % PAGE_SIZE == 0)
			XEEBeginWrite(SLOG_START + slog_pos);
		XEEWrite(*str_time);
	}
	XEEEndWrite();

	return put;
}

static int slog_terminate(void)
{
	BYTE str_buf[] = {'\r', '\n', SLOG_EOF};
	BYTE *str = str_buf;

	XEEBeginWrite(SLOG_START + slog_pos);
	do
	{
		if((SLOG_START + slog_pos) % PAGE_SIZE == 0)
			XEEBeginWrite(SLOG_START + slog_pos);
		XEEWrite(*str);
	} while(*str++);
	XEEEndWrite();

	slog_pos += (sizeof(str_buf) - 1);

	return (sizeof(str_buf) - 1);
}

int slog_puts(const BYTE *str)
{
	int put = slog_put_timestamp();

	XEEBeginWrite(SLOG_START + slog_pos);
	for (; (*str) && (slog_pos < SLOG_LEN); slog_pos++, put++, str++) {
		if((SLOG_START + slog_pos) % PAGE_SIZE == 0)
			XEEBeginWrite(SLOG_START + slog_pos);
		XEEWrite(*str);
	}
	XEEEndWrite();

	put += slog_terminate();
	cnt_events ++;

	return put;
}

int slog_putrs(const rom BYTE *str)
{
	int put = slog_put_timestamp();

	XEEBeginWrite(SLOG_START + slog_pos);
	for (; (*str) && (slog_pos < SLOG_LEN); slog_pos++, put++, str++) {
		if((SLOG_START + slog_pos) % PAGE_SIZE == 0)
			XEEBeginWrite(SLOG_START + slog_pos);
		XEEWrite(*str);
	}
	XEEEndWrite();

	put += slog_terminate();
	cnt_events ++;

	return put;
}


int slog_gets(DWORD pos, BYTE *buf, BYTE len)
{
	int got = 0;

	if (pos >= SLOG_LEN)
		return -1;
	if (!len)
		return 0;

	for (XEEBeginRead(pos + SLOG_START); got < len; got++, buf++)
		if ((*buf = XEERead()) == SLOG_EOF)
			break;
	XEEEndRead();

	return got;
}

void slog_flush(void)
{
	static BYTE buf[PAGE_SIZE/4];
	int read, all = 0;

	putrsUSART("\n\r<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\r");

	while((read = slog_gets(all, buf, sizeof(buf))) > 0) {
		buf[read] = '\0';
		putsUSART(buf);
		all += read;
	}

	putrsUSART("\n\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\r");

	putrsUSART("Total: ");
	uitoa(cnt_events, buf);
	putsUSART(buf);
	putrsUSART(" events, ");

	uitoa((WORD)(SLOG_LEN - all), buf);
	putsUSART(buf);
	putrsUSART(" bytes free\n\r");

}



int slog_getlast(BYTE *buf, BYTE len)
{
	get_pos = slog_pos;
	if(slog_pos == 0)
		return 0;
	return slog_getnext(buf, len, 0);
}

/*
 * slog_getlast MUST be called before slog_getnext!!!
 */

int slog_getnext(BYTE *buf, BYTE len, BOOL erase)
{
	BYTE read, ch;

	if (erase) {
		XEEBeginWrite(get_pos + SLOG_START);
		XEEWrite(SLOG_EOF);
		XEEEndWrite();
		slog_pos = get_pos;
		if (cnt_events)
			cnt_events--;
	}

	if(get_pos < 2)
		return 0;

	get_pos -= 2;

	for(; get_pos > 0; get_pos--)
	{
		XEEBeginRead(get_pos + SLOG_START);
		ch = XEERead();
		XEEEndRead();
		if(ch == '\n') {
			get_pos ++;
			break;
		}
	}

	if(buf == NULL)
		return 0;

	for(read = 0, XEEBeginRead(get_pos + SLOG_START); (read < len); read ++)
	{
		*buf++ = ch = XEERead();
		if(ch == '\n')
			break;
	}

	XEEEndRead();
	*buf = '\0';

	return read + 1; // + '\0'
}

static int process_buffer(bd_t handler)
{
	int result = 0;
	bcp_header_t * hdr = (bcp_header_t *) bcp_buffer(handler)->buf;

	switch (TYPE(hdr->hdr_s.type)) {
	case TYPE_NPRQ:
		switch (hdr->raw[RAW_QAC]) {
		case QAC_LG_CLEAR_ALL:
			putrsUSART("QAC_LG_CLEAR_ALL");

			break;
		case QAC_LG_READ_LAST:
			putrsUSART("QAC_LG_READ_LAST");

			hdr->hdr_s.type = TYPE_NPDL;
			hdr->hdr_s.packtype_u.npdl.len = slog_getlast(
					(BYTE *) &hdr->raw[RAW_DATA], (PAYLOADLEN - 2)) + 2;
			bcp_send_buffer(handler);

			break;
		case QAC_LG_READ_NEXT:
			putrsUSART("QAC_LG_READ_NEXT");

			hdr->hdr_s.type = TYPE_NPDL;
			hdr->hdr_s.packtype_u.npdl.len = slog_getnext(
					(BYTE *) &hdr->raw[RAW_DATA], (PAYLOADLEN - 2), 1) + 2;
			bcp_send_buffer(handler);

			break;
		case QAC_LG_GET_COUNT:
			putrsUSART("QAC_LG_GET_COUNT");

			hdr->hdr_s.type = TYPE_NPDL;
//			*(DWORD *)&hdr->raw[RAW_DATA] = cnt_events; // alignment problems possible
			memcpy((void *)&hdr->raw[RAW_DATA], (void *)&cnt_events, sizeof(cnt_events));
			hdr->hdr_s.packtype_u.npdl.len = sizeof(cnt_events) + 2;
			bcp_send_buffer(handler);

			break;
		default:
			result = -1;
		}

		break;
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
		switch (hdr->raw[RAW_QAC]) {

		case QAC_LG_WRITE_EVENT:
			putrsUSART("QAC_LG_WRITE_EVENT");

			hdr->raw[RAW_DATA + hdr->hdr_s.packtype_u.npdl.len - 2] = '\0';
			slog_puts((BYTE *)&hdr->raw[RAW_DATA]);

			hdr->hdr_s.type = TYPE_NPDL;
//			*(DWORD *)&hdr->raw[RAW_DATA] = cnt_events; // alignment problems possible
			memcpy((void *)&hdr->raw[RAW_DATA], (void *)&cnt_events, sizeof(cnt_events));
			hdr->hdr_s.packtype_u.npdl.len = sizeof(cnt_events) + 2;
			bcp_send_buffer(handler);

			break;

		default:
			result = -1;
		}

		break;

	default:
		result = -1;
	}

	bcp_release_buffer(handler);
	putrsUSART("\n\rLOG: buffer released (rsp sent)");

	return result;
}


void slog_module(void)
{
	bd_t ipacket;

	if(mail_reciev(MYSELF, &ipacket)) {
		process_buffer(ipacket);
	}
}

