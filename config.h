/*
 * config.h
 *
 *  Created on: 24.03.2013
 *      Author: admin
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define CFG_START "config"

//#define put_string	putsUSART
//#define put_rom_string	putrsUSART
//#define get_string	ReadStringUART

#define get_string	net_get_string

//					putsUSART(string_buf); \

#define put_string(...) 	do {	\
					sprintf (string_buf, __VA_ARGS__); \
					net_send_string(string_buf); \
					} while(0)


#define MAX_PRMS	20

typedef enum {
	TYPE_STRING, TYPE_CHAR, TYPE_SHORT, TYPE_LONG, TYPE_VECTOR, TYPE_ACTION
} type_e;

typedef enum {
	SHOW_SECTIONS,
	SHOW_SECTION,
	SHOW_PARAM
} menu_state_e;

typedef int (* ROM convert_prm_cb)(char *, char *);

typedef struct {
	ROM const type_e type;
	ROM const BYTE *caption;
	void *prm;
	union {
		ROM DWORD ROM raw[3];
		struct {
			ROM DWORD min;
			ROM DWORD max;
		} d;
		struct {
			ROM DWORD maxlen;
		} s;
		struct {
			ROM DWORD cvrt_in;
			ROM DWORD cvrt_out;
			ROM DWORD len;
		} v;
	} lim;
} menu_prm_t;

typedef struct {
	ROM const BYTE *caption;
	ROM const menu_prm_t * ROM prms[MAX_PRMS];
} menu_section_t;

#define DFLT_COMM_STATION_ID 1
#define DFLT_COMM_PORT 50
#define DFLT_RS232_BAUDRATE 9600
#define DFLT_RS232_PARITY 1
#define DFLT_RS232_DATABITS 8
#define DFLT_RS232_STOPBITS 2
#define DFLT_RS232_HANDSHAKE 0

#define DFLT_R1_ACTIVITY 1
#define DFLT_R1_FRAMELEN 34

#define DFLT_R1_PARITY "Classic e/o"
#define DFLT_R2_ACTIVITY 1
#define DFLT_R2_CONVERT2HEX 0
#define DFLT_R2_FRAMELEN 20
#define DFLT_R2_STOPBYTE 0x0D
#define DFLT_R2_CODE_BEGIN 0
#define DFLT_R2_CODE_LEN 0
#define DFLT_R2_MAX_DELAY 10

#define DFLT_ACC_HOST_TOUT 10
#define DFLT_ACC_RETRY_CNT 2
#define DFLT_ACC_LOCAL_ACCESS 3
#define DFLT_ACC_LOCAL_MSG "Проходите пожалуйста"
#define DFLT_ACC_BUSY_MSG "Извините, временно не работаю"
#define DFLT_ACC_FAILURE_MSG "Извините, временно не работаю"
#define DFLT_ACC_PROMPT_MSG "Предъявите карту"

#define DFLT_SM_SERVICE_TIME 1000
#define DFLT_SM_SIG_CONTROL_EN 1
#define DFLT_SM_SIG_CONTROL_RELAY 1
#define DFLT_SM_SIG_CONTROL_INVERSE 0
#define DFLT_SM_SIG_CONTROL_DURATION 100
#define DFLT_SM_SIG_INDICATOR_EN 1
#define DFLT_SM_SIG_INDICATOR_RELAY 0
#define DFLT_SM_SIG_INDICATOR_INVERSE 0
#define DFLT_SM_SIG_INDICATOR_DURATION 100
#define DFLT_SM_SIG_DONE_EN 1
#define DFLT_SM_SIG_DONE_SENSOR 0
#define DFLT_SM_SIG_DONE_INVERSE 0
#define DFLT_SM_SIG_FAILURE_EN 1
#define DFLT_SM_SIG_FAILURE_SENSOR 1
#define DFLT_SM_SIG_FAILURE_INVERSE 0

void config(void);
void config_restore_defaults(void);
void config_restore(void);
void config_save(void);
extern APP_CONFIG AppConfig;

#endif /* CONFIG_H_ */
