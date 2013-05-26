/*
 * test.c
 *
 *  Created on: 31.03.2013
 *      Author: admin
 */

#include "TCPIP Stack/TCPIP.h"
#include "test.h"
#include <stdio.h>
#include <string.h>
#include "m_lcd.h"
#include "m_readers.h"
#include "m_logger.h"
#include "m_smachine.h"
#include "version.h"

static rom char * projectname = SVN_URL;
static rom char * buildtime = SVN_DATETIME;

void test(void) {
	uid_t uid;
	BYTE str_log[60];
	DWORD t, data;

	strncpypgm2ram(LCD_STRING_0, projectname, 16);
	strncpypgm2ram(LCD_STRING_1, buildtime, 16);

	LCD_decode(LCD_ALL);
	LCDUpdate();

	t = TickGet();

	while(TickGet() - t < TICK_SECOND * 3)
		continue;

	sprintf(LCD_STRING_0, "[--------]");

	while (1) {

		if (readers_get_uid(&uid)) {
//			if(uid.gate == 0) {
				data = swapl(uid.uid);
				sprintf(LCD_STRING_0, "[%04X%04X]:%d", (WORD) (data >> 16), (WORD) data, uid.gate);
				sprintf(str_log, "RD [%04X%04X]:%d", (WORD) (data >> 16),
						(WORD) data, uid.gate);

				slog_put(str_log);

//			} else if(uid.gate == 1) {
//				data = uid.uid;
//				sprintf(LCD_STRING_0, "[%06d]:%u", (WORD) data, uid.gate);
//				sprintf(str_log, "RD [%06d]:%u", (WORD) data, uid.gate);
//
//				slog_put(str_log);
//
//			}
		}

		if (!BUTTON0_IO)
			P_REL1 = 1;
		else
			P_REL1 = 0;

		if(!BUTTON1_IO)
			P_REL2 = 1;
		else
			P_REL2 = 0;

		sprintf(LCD_STRING_1, "R[%c%c]    S[%c%c%c%c]", P_REL1?'*':'-', P_REL2?'*':'-', P_IN1?'*':'-', P_IN2?'*':'-', P_IN3?'*':'-', P_IN4?'*':'-');

		LCD_decode(LCD_ALL);
		LCDUpdate();
		}
	}
