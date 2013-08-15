/*
 * m_lcd.h
 *
 *  Created on: 08.03.2013
 *      Author: admin
 */

#ifndef M_LCD_H_
#define M_LCD_H_

#define LCD_LENGTH  16 //20
#define LCD_HEIDHT  2
#define LCD_SIZE LCD_LENGTH*LCD_HEIDHT

#include "TCPIP Stack/TCPIP.h"
#include "modules.h"

typedef BYTE (*decode_t)(BYTE);

void LCDTest(WORD offset);
void LCD_init(void);
BYTE * LCD_decode(BYTE *str);
void LCD_serve_tout_prompt(void);
void LCD_apply(DWORD tout);

#define LCD_STRING_0	(LCDText)
#if LCD_HEIDHT>1
  #define LCD_STRING_1	(LCDText + LCD_LENGTH)
#endif
#if LCD_HEIDHT>2
  #define LCD_STRING_2	(LCDText + 2*LCD_LENGTH)
#endif
#if LCD_HEIDHT>3
  #define LCD_STRING_3	(LCDText + 3*LCD_LENGTH)
#endif

#define LCD_ALL			(LCD_STRING_0)

#endif /* M_LCD_H_ */
