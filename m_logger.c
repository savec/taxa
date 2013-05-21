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
static BYTE host_read = 0;

#define MYSELF	MODULE_LOGGER


//static BOOL slog_need_format(void);

//static DWORD slog_pos;
//static DWORD get_pos;
static DWORD cnt_events;
static DWORD cnt_not_read;

static DWORD cnt_lost = 0;

static struct {
  int head;
  int tail;
} indx;


static void slog_get_time(time_t *time)
{
	QWORD qw_time = TickGetFullScale();

	time->hours = (DWORD)(qw_time/TICK_HOUR);
	qw_time %= TICK_HOUR;
	time->minutes = (BYTE)(qw_time/TICK_MINUTE);
	qw_time %= TICK_MINUTE;
	time->seconds = (BYTE)(qw_time/TICK_SECOND);
}

//void slog_init(void)
//{
//	if (slog_need_format()) {
//		slog_fast_format();
//	} else {
//		cnt_events = 0;
//		XEEBeginRead(SLOG_START);
//		for (slog_pos = 0; slog_pos < SLOG_LEN; slog_pos++) {
//			BYTE ch = XEERead();
//			if(ch == SLOG_EOF)
//				break;
//			if(ch == '\n')
//				cnt_events ++;
//		}
//		XEEEndRead();
//	}
//
//	slog_getlast(NULL, 0); // set get_pos pointer
//
//	mail_subscribe(MYSELF, &mailbox);
//}



//unsigned char buf[SLOG_LEN];
//int cnt_events;



//void WriteEEX(int pos, unsigned char ch)
//{
//  buf[pos] = ch;
//}
//
//unsigned char ReadEEX(int pos)
//{
//  return buf[pos];
//}

int tail(void) {
	return indx.tail;
}

void set_tail(int p) {
	indx.tail = p;
}

int move_tail(void) {
	indx.tail++;
	indx.tail &= SLOG_MASK;

	return (indx.head == indx.tail);
}

int head(void) {
	return indx.head;
}

void set_head(int p) {
	indx.head = p;
}

int move_head(void) {
	indx.head++;
	indx.head &= SLOG_MASK;

	return (indx.head == indx.tail);
}

static BYTE XEEReadNext(DWORD addr)
{
	if(addr % PAGE_SIZE == 0)
		XEEBeginRead(addr);
	return XEERead();
}


static void XEEWriteNext(DWORD addr, BYTE data)
{
	if(addr % PAGE_SIZE == 0)
		XEEBeginWrite(addr);
	XEEWrite(data);
}

static void CyclicFill(DWORD start, DWORD end, BYTE data)
{
	XEEBeginWrite(SLOG_START + start);

	do {
		XEEWriteNext(SLOG_START + start, data);
		start ++;
		start &= SLOG_MASK;
	} while (start != end);

	XEEEndWrite();
}

//static void slog_put_str(BYTE * str)
//{
//	XEEBeginWrite(SLOG_START + head());
//
//	while (*str++) {
//		XEEWriteNext(SLOG_START + head(), *str);
//		move_head();
//	}
//
//	XEEEndWrite();
//}


static int cyclic_search(int from, unsigned char from_char, unsigned char to_char) {
	int pos = from;
	BYTE ch;

	XEEBeginRead(SLOG_START + pos);

	do {
		ch = XEEReadNext(SLOG_START + pos);

		if (ch >= from_char && ch <= to_char) {
			XEEEndRead();
			return pos;
		}

		pos++;
		pos &= SLOG_MASK;
	} while (pos != from);

	XEEEndRead();

	return -1;
}

static void pull_tail(unsigned char erase) {

	DWORD pos = cyclic_search(tail(), SLOG_EOE, SLOG_EOE);

	if(erase)
		CyclicFill(tail(), pos, SLOG_EMPTY);

	set_tail(pos);
	if(erase) {
		XEEBeginWrite(SLOG_START + tail());
		XEEWrite(SLOG_EMPTY);
		XEEEndWrite();
	}
	move_tail();

	if (cnt_events)
		cnt_events--;
}


static int slog_cnt_events(DWORD from, DWORD to) {
	DWORD cnt = 0;

	XEEBeginRead(SLOG_START + from);

	do {
		if (XEEReadNext(SLOG_START + from) == SLOG_EOE)
			cnt++;

		from ++;
		from &= SLOG_MASK;

	} while (from != to);

	XEEEndRead();

	return cnt;
}

static int slog_scan(void) {
	int pos_start, pos_end, cnt;
	BYTE str_buf[40];

	pos_start = cyclic_search(0, SLOG_EMPTY, SLOG_EMPTY);

	if (pos_start == -1) {
		putrsUSART("\n\rcan't find SLOG_EMPTY, need format.");
		return -1; /*can't find SLOG_EMPTY, need format.*/// XXX
	}

	sprintf(str_buf, "\n\rfind SLOG_EMPTY at %u ", (int)pos_start);
	putsUSART(str_buf);


	pos_start = cyclic_search(pos_start, ASCII_PRINTABLE_FIRST,
			ASCII_PRINTABLE_LAST);

	if (pos_start == -1) {

		cnt = slog_cnt_events(0, 0);

		if (cnt == 0) {
			/* all empty, need reset */
			putrsUSART("\n\rall empty, need reset.");
			return -2;
		} else if (cnt > 1) {
			/* multiple SLOG_EOE, need format */
			putrsUSART("\n\rmultiple SLOG_EOE, need format.");
			return -1;
		} else {
			/* after format+reset state */
			set_tail(0);
			set_head(0);
			cnt_not_read = cnt_events = 0;
			putrsUSART("\n\rafter format+reset state.");
			return 0;
		}
	}

	sprintf(str_buf, "\n\rfind PRINTABLE at %u ", (int)pos_start);
	putsUSART(str_buf);

	set_tail(pos_start);
	pos_end = (cyclic_search(pos_start, SLOG_EMPTY, SLOG_EMPTY) - 1) & SLOG_MASK; // . . . . EOE EOE EMPTY
	set_head(pos_end);
	cnt_not_read = cnt_events = slog_cnt_events(pos_start, pos_end) - 1; // last EOE is not event

	{


		putrsUSART("\n\rslog not empty, normal.");
		sprintf(str_buf, "\n\rtail=%u, head=%u, not_read=%u ", (int)tail(), (int)head(), (int)cnt_not_read);
		putsUSART(str_buf);
	}


	return 0;
}

static void slog_reset(void) {
	set_tail(0);
	set_head(0);

	cnt_events = 0;

	XEEBeginWrite(SLOG_START);
	XEEWrite(SLOG_EOE);
	XEEEndWrite();
}

void slog_format(void) {

	CyclicFill(0, 0, SLOG_EMPTY);

	slog_reset();
}

void slog_clean(void) {
	CyclicFill(tail(), (head() - 1) & SLOG_MASK, SLOG_EMPTY);
	set_tail(head());
	cnt_events = 0;
}

void slog_init(void) {
	switch (slog_scan()) {
	case SLOG_NEED_FORMAT:
		slog_format();
		break;
	case SLOG_NEED_RESET:
		slog_reset();
		break;
	default:
		;
	}

	mail_subscribe(MYSELF, &mailbox);
}

//void slog_fast_format(void)
//{
//	XEEBeginWrite(SLOG_START);
//	XEEWrite(SLOG_EOF);
//	XEEEndWrite();
//	slog_pos = 0;
//	cnt_events = 0;
//}
//
//void slog_format(void)
//{
//	DWORD addr = SLOG_START;
//
//	for (XEEBeginWrite(addr); addr < SLOG_START + SLOG_LEN; addr++) {
//		if(addr % PAGE_SIZE == 0)
//			XEEBeginWrite(addr);
//		XEEWrite(SLOG_EOF);
//	}
//	XEEEndWrite();
//	slog_pos = 0;
//	cnt_events = 0;
//}
//
//static BOOL slog_need_format(void)
//{
//	/*
//	 * check's first slog page
//	 */
//	DWORD addr;
//	XEEBeginRead(SLOG_START);
//	for (addr = SLOG_START; addr < SLOG_START + PAGE_SIZE; addr++) {
//		if (XEERead() ^ 0xFF) {
//			XEEEndRead();
//			return FALSE;
//		}
//	}
//	XEEEndRead();
//	return TRUE;
//}

static void slog_get_timestamp(BYTE * str_buf)
{
	int put;
	time_t time;
	char *str_time;

	slog_get_time(&time);
	sprintf(str_buf, "%05i:%02i:%02i ", (int)time.hours, (int)time.minutes, (int)time.seconds);
}

//static int slog_terminate(void)
//{
//	BYTE str_buf[] = {'\r', '\n', SLOG_EOF};
//	BYTE *str = str_buf;
//
//	XEEBeginWrite(SLOG_START + slog_pos);
//	do
//	{
//		if((SLOG_START + slog_pos) % PAGE_SIZE == 0)
//			XEEBeginWrite(SLOG_START + slog_pos);
//		XEEWrite(*str);
//	} while(*str++);
//	XEEEndWrite();
//
//	slog_pos += (sizeof(str_buf) - 1);
//
//	return (sizeof(str_buf) - 1);
//}
//
//int slog_puts(const BYTE *str)
//{
//	int put = slog_put_timestamp();
//
//	XEEBeginWrite(SLOG_START + slog_pos);
//	for (; (*str) && (slog_pos < SLOG_LEN); slog_pos++, put++, str++) {
//		if((SLOG_START + slog_pos) % PAGE_SIZE == 0)
//			XEEBeginWrite(SLOG_START + slog_pos);
//		XEEWrite(*str);
//	}
//	XEEEndWrite();
//
//	put += slog_terminate();
//	cnt_events ++;
//
//	return put;
//}
//
//int slog_putrs(const rom BYTE *str)
//{
//	int put = slog_put_timestamp();
//
//	XEEBeginWrite(SLOG_START + slog_pos);
//	for (; (*str) && (slog_pos < SLOG_LEN); slog_pos++, put++, str++) {
//		if((SLOG_START + slog_pos) % PAGE_SIZE == 0)
//			XEEBeginWrite(SLOG_START + slog_pos);
//		XEEWrite(*str);
//	}
//	XEEEndWrite();
//
//	put += slog_terminate();
//	cnt_events ++;
//
//	return put;
//}


//int slog_gets(DWORD pos, BYTE *buf, BYTE len)
//{
//	int got = 0;
//
//	if (pos >= SLOG_LEN)
//		return -1;
//	if (!len)
//		return 0;
//
//	for (XEEBeginRead(pos + SLOG_START); got < len; got++, buf++)
//		if ((*buf = XEERead()) == SLOG_EOF)
//			break;
//	XEEEndRead();
//
//	return got;
//}


/*
 *  size MUST be > 0
 *
 */

static int check_empty(DWORD from, BYTE size)
{
	BYTE ch;

	from ++;
	from &= SLOG_MASK;

	XEEBeginRead(SLOG_START + from);

	do {
		if (XEEReadNext(SLOG_START + from) != SLOG_EMPTY) {
			XEEEndRead();
			return -1;
		}

		from ++;
		from &= SLOG_MASK;
	} while (-- size);

	XEEEndRead();

	return 0;

}

int slog_put(const char *buf) {
	BYTE ch;
	BYTE timestamp[20], *p_timestamp = timestamp;
	BYTE total_len;

	slog_get_timestamp(timestamp);

	total_len = strlen(timestamp) + strlen(buf) + 2;

	if (check_empty(head(), total_len) < 0) {
		cnt_lost ++;
		return -1;
	}

	XEEBeginWrite(SLOG_START + head());

	for (; *p_timestamp; p_timestamp++) {
		XEEWriteNext(SLOG_START + head(), *p_timestamp);
		move_head();
	}

	for (; *buf; buf++) {
		ch = IS_PRINTABLE(*buf) ? *buf : ASCII_PRINTABLE_FIRST;
		XEEWriteNext(SLOG_START + head(), ch);
		move_head();
	}

	XEEWriteNext(SLOG_START + head(), SLOG_EOE); // end of event

	move_head();

	XEEWriteNext(SLOG_START + head(), SLOG_EOE); // . . . . . SLOG_EOE SLOG_EOE - end of log

	XEEEndWrite();

	cnt_events++;
	cnt_not_read ++;

	return 0;
}

int slog_getlast(BYTE *buf, size_t len) {
	int got = 0;
	DWORD cached_tail;
	BYTE ch;

	if (cnt_events == 0)
		return 0;

	cached_tail = tail();
	XEEBeginRead(SLOG_START + cached_tail);

	for (; len; len--, got++) {
		if ((ch = XEEReadNext(SLOG_START + tail())) == SLOG_EOE)
			break;
		*buf++ = ch;
		move_tail();
	}

	XEEEndRead();

	set_tail(cached_tail);

	return got;
}

int slog_getnext(BYTE *buf, size_t len) {
	if (cnt_events == 0)
		return 0;

	if(host_read) {
		pull_tail(1);
	}

	if(cnt_not_read)
		cnt_not_read --;

	return slog_getlast(buf, len);
}

void slog_flush(void) {
	DWORD cached_tail = tail();
	DWORD cache_cnt = cnt_events;
	BYTE buf[40];

	putrsUSART("\n\r<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\r");

	while (cnt_events) {
		putrsUSART("\n\r");
		buf[slog_getlast(buf, sizeof(buf))] = '\0';
		pull_tail(0);
		putsUSART(buf);

	}

	putrsUSART("\n\r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\r");

	set_tail(cached_tail);
	cnt_events = cache_cnt;

	putrsUSART("Total: ");
	uitoa(cnt_events, buf);
	putsUSART(buf);
	putrsUSART(" events\r\n");

}


//
//int slog_getlast(BYTE *buf, BYTE len)
//{
//	get_pos = slog_pos;
//	if(slog_pos == 0)
//		return 0;
//	return slog_getnext(buf, len, 0);
//}
//
///*
// * slog_getlast MUST be called before slog_getnext!!!
// */
//
//int slog_getnext(BYTE *buf, BYTE len, BOOL erase)
//{
//	BYTE read, ch;
//
//	if (erase) {
//		XEEBeginWrite(get_pos + SLOG_START);
//		XEEWrite(SLOG_EOF);
//		XEEEndWrite();
//		slog_pos = get_pos;
//		if (cnt_events)
//			cnt_events--;
//	}
//
//	if(get_pos < 2)
//		return 0;
//
//	get_pos -= 2;
//
//	for(; get_pos > 0; get_pos--)
//	{
//		XEEBeginRead(get_pos + SLOG_START);
//		ch = XEERead();
//		XEEEndRead();
//		if(ch == '\n') {
//			get_pos ++;
//			break;
//		}
//	}
//
//	if(buf == NULL)
//		return 0;
//
//	for(read = 0, XEEBeginRead(get_pos + SLOG_START); (read < len); read ++)
//	{
//		*buf++ = ch = XEERead();
//		if(ch == '\n')
//			break;
//	}
//
//	XEEEndRead();
//	*buf = '\0';
//
//	return read + 1; // + '\0'
//}






static int process_buffer(bd_t handler)
{
	int result = 0, read_cnt;
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

			read_cnt = slog_getnext(
					(BYTE *) &hdr->raw[RAW_DATA], (PAYLOADLEN - 2));
			host_read = 1;

			if(read_cnt) {
				hdr->hdr_s.type = TYPE_NPDL;
				hdr->hdr_s.packtype_u.npdl.len = read_cnt + 2;
			} else {
				hdr->hdr_s.type = TYPE_NPRQ;
				hdr->hdr_s.packtype_u.nprq.dummy = 0;
			}

			bcp_send_buffer(handler);

			break;
		case QAC_LG_GET_COUNT:
			putrsUSART("QAC_LG_GET_COUNT");

			hdr->hdr_s.type = TYPE_NPDL;
//			*(DWORD *)&hdr->raw[RAW_DATA] = cnt_events; // alignment problems possible
			memcpy((void *)&hdr->raw[RAW_DATA], (void *)&cnt_not_read, sizeof(cnt_not_read));
			hdr->hdr_s.packtype_u.npdl.len = sizeof(cnt_not_read) + 2;
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
			slog_put((BYTE *)&hdr->raw[RAW_DATA]);

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

