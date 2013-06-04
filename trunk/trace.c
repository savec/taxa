/*
 * trace.c
 *
 *  Created on: 04.06.2013
 *      Author: admin
 */

#include "TCPIP Stack/TCPIP.h"

#include "skipic.h"
#include <stdio.h>
#include "trace.h"

#ifdef UART_TRACE
BYTE trace_buf[40];
//void putsUSART( char *data);
//void trace(auto const MEM_MODEL rom char *fmt, ...)
//{
//	sprintf (trace_buf, fmt);
//	putsUSART(trace_buf);
//}
#endif
