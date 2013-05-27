/*
 * readers.h
 *
 *  Created on: 02.02.2013
 *      Author: admin
 */

#ifndef M_READERS_H_
#define M_READERS_H_

#include "TCPIP Stack/TCPIP.h"
#include "modules.h"

//#define MIN_WIEGAND_PULSE_LEN	TICK_SECOND/2ul

#define BP_SIZE	5

#define WIEGAND_34_LEN				34
#define WIEGAND_34_HALF_DATA_LEN	16
#define WIEGAND_34_LDATA_START		1
#define WIEGAND_34_HDATA_START		(WIEGAND_34_LEN/2)

typedef enum {
	WG_READER_VOID = 0,
	WG_READER_INPROGRESS,
	WG_READER_READY
} wg_reader_status_e;

typedef enum {
	SERIAL_WAIT_CODE = 0,
	SERIAL_WAIT_CR
//	SERIAL_WAIT_LF
} serial_reader_status_e;

#define MAX_UID_LEN 40

typedef struct {
	BYTE uid[MAX_UID_LEN];
	BYTE gate;
} uid_t;

#define SERIAL_CODE_LEN	6	// replace whith prm
#define SERIAL_MAX_CODE_LEN	16
#define SERIAL_BUF_MASK	(SERIAL_MAX_CODE_LEN - 1)



typedef struct {
	BYTE buf[SERIAL_MAX_CODE_LEN];
	BYTE in;
	BYTE out;
	BYTE cnt;
} serial_buffer_t;

//typedef union {
//	QWORD all;
//	struct {
//		QWORD odd:		1;
//		QWORD ldata: 	16;
//		QWORD hdata: 	16;
//		QWORD even:		1;
//	} field;
//} w34_code_t;

void readers_init(void);
void wg_readers_isr(void);
BYTE readers_get_uid(uid_t *uid);
wg_reader_status_e wg_readers_getstatus(void);
void readers_module(void);
void serial_isr(void);


#endif /* M_READERS_H_ */
