/*
 * m_smachine.h
 *
 *  Created on: 12.04.2013
 *      Author: admin
 */

#ifndef M_SMACHINE_H_
#define M_SMACHINE_H_

#include "TCPIP Stack/TCPIP.h"

typedef enum {
	SM_INIT = 0x0000,
	SM_READY = 0x0001,
	SM_PREPARE = 0x0002,
	SM_WORK = 0x0003,
	SM_FINAL = 0x0004,
	SM_FAILURE = 0x0100
}sm_state_e;

typedef enum {
	EVT_SM_PREPARE = 0x0001,
	EVT_SM_ENABLE_CONTROL = 0x0002,
	EVT_SM_ENABLE_INDICATOR = 0x0004,
	EVT_SM_DISABLE = 0x0008,
	EVT_SM_FINALIZE = 0x0010
} sm_events;

#define P_REL1	LED5_IO
#define P_REL2	LED6_IO

#define P_IN1	(!BUTTON2_IO)
#define P_IN2	(!BUTTON3_IO)
#define P_IN3	(!BUTTON4_IO)

void sm_init(void);
void sm_module(void);
BOOL sm_is_ready(void);

#endif /* M_SMACHINE_H_ */
