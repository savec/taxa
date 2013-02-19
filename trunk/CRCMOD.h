// *********** сервисные функции общего назначения **************
#ifndef __CRCMOD_h
  #define __CRCMOD_h

//#include <stdint.h>
#include "TCPIP Stack/TCPIP.h"
typedef WORD uint16_t;
typedef BYTE uint8_t;

// ф-ия возвращает CRC16 по алгоритму MODBUS для массива данных, (полином 0xA001)
// на первый элемент массива указывает puchMsg; usDataLen - кол-во байт в масcиве 
uint16_t CRC16_MODBUS(uint8_t *puchMsg, uint16_t usDataLen); 

#endif
