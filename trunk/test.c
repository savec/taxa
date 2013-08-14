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
//static rom char * projectname = PROJ_NAME;
static rom char * buildtime = SVN_DATETIME;

static uid_t uid;
static BYTE str_log[40];


void test(void) {
	DWORD t/*, data*/;
	BYTE read_cnt = 0;

	strncpypgm2ram(LCD_STRING_0, projectname, 16);
	strncpypgm2ram(LCD_STRING_1, buildtime, 16);

	LCD_decode(LCD_ALL);
	LCDUpdate();

	t = TickGet();

	while(TickGet() - t < TICK_SECOND * 3)
		continue;

	sprintf(LCD_STRING_0, "[--------]");

	while (1) {

		led(-1);

		if (readers_get_uid(&uid)) {

			sprintf(LCD_STRING_0, "[%s]:%d %d", (char *) uid.uid, uid.gate, ++read_cnt);
			sprintf(str_log, "RD [%s]:%d", (char *) uid.uid, uid.gate);

			slog_put(str_log);
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
