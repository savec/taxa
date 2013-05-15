/*
 * m_logger.h
 *
 *  Created on: 09.03.2013
 *      Author: admin
 */

#ifndef M_LOGGER_H_
#define M_LOGGER_H_

#include "TCPIP Stack/TCPIP.h"
#include "modules.h"

typedef struct {
	WORD hours;
	BYTE minutes;
	BYTE seconds;
} time_t;

#define PAGE_SIZE	264ul
#define PAGES_NUM	496

#define SLOG_START	(10ul*PAGE_SIZE)
//#define SLOG_LEN	(10ul*PAGE_SIZE)

//#define SLOG_EOF	0	// we cant't use standart EOF(-1) because of it's a symbol in cp1251 coding

#define SLOG_LEN    4096L
#define SLOG_MASK   (SLOG_LEN - 1)
#define SLOG_EMPTY  0xFF
#define SLOG_EOE    '\0'

#define SLOG_NEED_FORMAT    -1
#define SLOG_NEED_RESET     -2

#define ASCII_PRINTABLE_FIRST ' '
#define ASCII_PRINTABLE_LAST  '~'

#define IS_PRINTABLE(ch) (ch >= ASCII_PRINTABLE_FIRST && ch <= ASCII_PRINTABLE_LAST)

//#define slog_puts(__s, __ts) slog_putrs((far rom BYTE *)__s, __ts)

void slog_init(void);
void slog_format(void);
void slog_clean(void);
//void slog_fast_format(void);
//int slog_putrs(const rom BYTE *str);
//int slog_puts(const BYTE *str);
//int slog_gets(DWORD pos, BYTE *buf, BYTE len);
void slog_flush(void);
int slog_getlast(BYTE *buf, size_t len);
int slog_getnext(BYTE *buf, size_t len);
void slog_evt(const BYTE *buf);


void slog_module(void);

#endif /* M_LOGGER_H_ */
