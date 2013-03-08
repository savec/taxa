/*
 * m_lcd.h
 *
 *  Created on: 08.03.2013
 *      Author: admin
 */

#ifndef M_LCD_H_
#define M_LCD_H_

#include "TCPIP Stack/TCPIP.h"

typedef BYTE (*decode_t)(BYTE);

void LCDTest(WORD offset);
void LCD_init(void);
void LCD_print(BYTE *str);

#endif /* M_LCD_H_ */
