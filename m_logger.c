/*
 * m_logger.c
 *
 *  Created on: 09.03.2013
 *      Author: admin
 */

#include "m_logger.h"

static BOOL slog_need_format(void);

static DWORD slog_pos;

void slog_init(void)
{
	if (slog_need_format()) {
		slog_format();
	} else {
		XEEBeginRead(SLOG_START);
		for (slog_pos = 0; (XEERead() != SLOG_EOF) && (slog_pos < SLOG_LEN); slog_pos++)
			;
		XEEEndRead();
	}
}

void slog_format(void)
{
	DWORD addr;
	XEEBeginWrite(SLOG_START);
	for (addr = SLOG_START; addr < SLOG_START + SLOG_LEN; addr++)
		XEEWrite(SLOG_EOF);
	XEEEndWrite();
	slog_pos = 0;
}

static BOOL slog_need_format(void)
{
	/*
	 * check's first slog page
	 */
	WORD addr;
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

int slog_puts(const BYTE *str, BOOL need_timestamp)
{
	int put = 0;

	// XXX timestamp

	for (XEEBeginWrite(SLOG_START + slog_pos); (*str) && (slog_pos < SLOG_LEN); slog_pos++, put++, str++)
		XEEWrite(*str);
	XEEEndWrite();

	return put;
}

int slog_putrs(const rom BYTE *str, BOOL need_timestamp)
{
	int put = 0;

	// XXX timestamp

	for (XEEBeginWrite(SLOG_START + slog_pos); (*str) && (slog_pos < SLOG_LEN); slog_pos++, put++, str++)
		XEEWrite(*str);
	XEEEndWrite();

	return put;
}


int slog_gets(WORD pos, BYTE *buf, BYTE len)
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

	uitoa((WORD)(SLOG_LEN - all), buf);

	putsUSART(buf);
	putrsUSART(" bytes free\n\r");
}
