/*
 * test.c
 *
 *  Created on: 31.03.2013
 *      Author: admin
 */

#include "test.h"
#include <stdio.h>
#include "m_lcd.h"
#include "m_readers.h"
#include "m_logger.h"
#include "m_smachine.h"



void test(void)
{
	DWORD uid;

	sprintf(LCD_STRING_0, "[--------]");

	while (1) {

		if (readers_get_uid(&uid)) {
			uid = swapl(uid);
			sprintf(LCD_STRING_0, "[%X%X]", (WORD) (uid >> 16), (WORD) uid);
			slog_putrs("Getting uid: ", 1);
			slog_puts(LCD_STRING_0, 1);
			slog_putrs(" (reader1)\n\r", 1);
		}

		if (!BUTTON0_IO)
			P_REL1 = 1;
		else
			P_REL1 = 0;

			if(!BUTTON1_IO)
			P_REL2 = 1;
			else
			P_REL2 = 0;

			sprintf(LCD_STRING_1, "R1%cR2%cS1%cS2%cS3%c", P_REL1?'*':' ', P_REL2?'*':' ', P_IN1?'*':' ', P_IN2?'*':' ', P_IN3?'*':' ');

			LCD_decode(LCD_ALL);
			LCDUpdate();
		}
	}
