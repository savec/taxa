/*
 * bit_pattern.h
 *
 *  Created on: 03.02.2013
 *      Author: admin
 */

#ifndef BIT_PATTERN_H_
#define BIT_PATTERN_H_

#include <stddef.h>

void bp_setbit(unsigned char *bitPattern, unsigned char bitIndex);
void bp_rstbit(unsigned char *bitPattern, unsigned char bitIndex);
unsigned char bp_tstbit(unsigned char *bitPattern, unsigned char bitIndex);
void bp_cp(const unsigned char *from, unsigned char *to, size_t bsize);
void bp_bzero(unsigned char *bitPattern, size_t bsize);

#endif /* BIT_PATTERN_H_ */
