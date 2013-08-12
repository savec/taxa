/*
 * bit_pattern.c
 *
 *  Created on: 03.02.2013
 *      Author: admin
 */

#include "bit_pattern.h"

void bp_setbit(unsigned char *bitPattern, unsigned char bitIndex)
{
   unsigned char bytePos = bitIndex >> 3;
   unsigned char bitPos = bitIndex & 7;
   bitPattern[bytePos] |= 1 << bitPos;
}

void bp_rstbit(unsigned char *bitPattern, unsigned char bitIndex)
{
   unsigned char bytePos = bitIndex >> 3;
   unsigned char bitPos = bitIndex & 7;
   bitPattern[bytePos] &= ~(1 << bitPos);
}


unsigned char bp_tstbit(unsigned char *bitPattern, unsigned char bitIndex)
{
   unsigned char bytePos = bitIndex >> 3;
   unsigned char bitPos = bitIndex & 7;
   return bitPattern[bytePos] & (1 << bitPos);
}

void bp_cp(const unsigned char *from, unsigned char *to, size_t bsize)
{
	while(bsize --)
		*to++ = *from++;
}

void bp_bzero(unsigned char *bitPattern, size_t bsize)
{
	while(bsize --)
		*bitPattern++ = 0;
}
