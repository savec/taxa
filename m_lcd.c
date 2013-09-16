/*
 * m_lcd.c
 *
 *  Created on: 08.03.2013
 *      Author: admin
 */

#include "TCPIP Stack/TCPIP.h"
#include "m_lcd.h"
#include "config.h"

decode_t decode_cb = NULL;
//BYTE (*decode_cb)(BYTE);

static DWORD lcd_tout, lcd_timestamp;


static rom BYTE cp1251[] = {/*À*/65, /*Á*/160, /*Â*/66, /*Ã*/161, /*Ä*/224, /*Å*/
71, /*Æ*/163, /*Ç*/164, /*È*/165, /*É*/166, /*Ê*/75, /*Ë*/167, /*Ì*/77, /*Í*/
72, /*Î*/79, /*Ï*/168, /*Ð*/80, /*Ñ*/67, /*Ò*/84, /*Ó*/169, /*Ô*/170, /*Õ*/88, /*Ö*/
225, /*×*/171, /*Ø*/172, /*Ù*/226, /*Ú*/173, /*Û*/174, /*Ü*/196, /*Ý*/175, /*Þ*/
176, /*ß*/177, /*à*/97, /*á*/178, /*â*/179, /*ã*/180, /*ä*/227, /*å*/101, /*æ*/
182, /*ç*/183, /*è*/184, /*é*/185, /*ê*/186, /*ë*/187, /*ì*/188, /*í*/189, /*î*/
111, /*ï*/190, /*ð*/112, /*ñ*/99, /*ò*/191, /*ó*/121, /*ô*/228, /*õ*/120, /*ö*/
229, /*÷*/192, /*ø*/193, /*ù*/230, /*ú*/194, /*û*/195, /*ü*/196, /*ý*/197,
/*þ*/198, /*ÿ*/199 };


void LCDTest(WORD offset)
{
	BYTE ch;

	uitoa(offset, LCDText);
	for (ch = 0; ch < 16; ch++) {
		LCDText[ch + 16] = offset + ch;
	}
	LCDUpdate();
}

static BYTE _LCD_cp1251(BYTE in)
{
	if (in < 0xC0)
		return in;
	return cp1251[in - 0xC0];
}

void LCD_init(void)
{
	decode_cb = _LCD_cp1251;
}

BYTE * LCD_decode(BYTE *str)
{
	BYTE *s = str;
	for(; *s; s++) {
		*s = decode_cb ? (*decode_cb)(*s) : *s;
	}

	return str;
}

void LCD_set_tout(DWORD tout)
{
	 lcd_tout = tout;
	 lcd_timestamp = TickGet();
}

void LCD_serve_tout_prompt(void)
{
	 static DWORD t;

	 if(lcd_tout && ((TickGet() - lcd_timestamp) > lcd_tout)) {
		 LCD_prompt();
	 	lcd_tout = 0;
	 }
}

void LCD_prompt(void)
{
	strcpy(LCD_STRING_0, AppConfig.acc_prompt_msg);
	strcpypgm2ram(LCD_STRING_1, "                ");
	LCD_decode(LCD_ALL);
	LCDUpdate();
}

void LCD_show_addresses(void)
{
	BYTE *p_str = LCD_STRING_1;
	BYTE i;

	cvrt_ip_out(&AppConfig.MyIPAddr, LCD_STRING_0);

	for (i = 0; i < 6; i++) {
		*p_str ++ = btohexa_high(AppConfig.MyMACAddr.v[i]);
		*p_str ++ = btohexa_low(AppConfig.MyMACAddr.v[i]);
	}
	*p_str = '\0';
	LCD_decode(LCD_ALL);
	LCDUpdate();
}

void LCD_BackLight(BYTE light)
{
	// LCD light on/off
	LATGbits.LATG5 = light ? 1 : 0;
	TRISGbits.TRISG5 = 0;
} 