/*
 * m_lcd.h
 *
 *  Created on: 08.03.2013
 *      Author: admin
 */

#ifndef M_LCD_H_
#define M_LCD_H_

#include "TCPIP Stack/TCPIP.h"
#include "modules.h"

typedef BYTE (*decode_t)(BYTE);

void LCDTest(WORD offset);
void LCD_init(void);
BYTE * LCD_decode(BYTE *str);

#define LCD_STRING_0	(LCDText)
#define LCD_STRING_1	(LCDText + 16)
#define LCD_ALL			(LCD_STRING_0)

#endif /* M_LCD_H_ */
