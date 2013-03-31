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

#define P_REL1	LED5_IO
#define P_REL2	LED6_IO

#define P_IN1	BUTTON2_IO
#define P_IN2	BUTTON3_IO

void test(void)
{
	DWORD uid;

	sprintf(LCD_STRING_0, "[--------]");

	while (1) {

		if (readers_get_uid(&uid)) {
			sprintf(LCD_STRING_0, "[%X%X]", (WORD) (uid >> 16), (WORD) uid);
			slog_putrs("Getting uid: ", 1);
			slog_puts(LCD_STRING_0, 1);
			slog_putrs(" (reader1)\n\r", 1);
		}

		if(!BUTTON0_IO)
			P_REL1 = 1;
		else
			P_REL1 = 0;


		if(!BUTTON1_IO)
			P_REL2 = 1;
		else
			P_REL2 = 0;

		sprintf(LCD_STRING_1, "R1:%d R2:%d", (WORD) P_REL1, (WORD) P_REL2);

		LCD_decode(LCD_ALL);
		LCDUpdate();
	}
}
