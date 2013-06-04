/*
 * trace.h
 *
 *  Created on: 04.06.2013
 *      Author: admin
 */

#ifndef TRACE_H_
#define TRACE_H_

//#define UART_TRACE

#ifdef UART_TRACE
extern BYTE trace_buf[];
void putsUSART( char *data);
#define TRACE(...) 	do {	\
					sprintf (trace_buf, __VA_ARGS__); \
					putsUSART(trace_buf); \
					} while(0)
#else
#define TRACE(...)
#endif


#endif /* TRACE_H_ */
