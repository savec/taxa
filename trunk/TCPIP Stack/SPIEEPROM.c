/*********************************************************************
 *
 *               Data SPI EEPROM Access Routines
 *
 *********************************************************************
 * FileName:        SPIEEPROM.c
 * Dependencies:    Compiler.h
 *                  XEEPROM.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F
 * Complier:        Microchip C18 v3.02 or higher
 *					Microchip C30 v2.01 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2002-2007 Microchip Technology Inc.  All rights 
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and 
 * distribute: 
 * (i)  the Software when embedded on a Microchip microcontroller or 
 *      digital signal controller product (“Device”) which is 
 *      integrated into Licensee’s product; or
 * (ii) ONLY the Software driver source files ENC28J60.c and 
 *      ENC28J60.h ported to a non-Microchip device used in 
 *      conjunction with a Microchip ethernet controller for the 
 *      sole purpose of interfacing with the ethernet controller. 
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT 
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL 
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS 
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT 
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     5/20/02     Original (Rev. 1.0)
 * Howard Schlunder		9/01/04		Rewritten for SPI EEPROMs
 * Howard Schlunder		8/10/06		Modified to control SPI module 
 *									frequency whenever EEPROM accessed 
 *									to allow bus sharing with different 
 *									frequencies.
  * Ivan Vasilev, Olimex Ltd  14/08/07	Imported support for Atmel dataflash
********************************************************************/
#define __SPIEEPROM_C

#include "TCPIP Stack/TCPIP.h"

#if defined(OLIMEX_HW)
	#define	USE_ATMEL_FLASH
	/* Psuedo functions */
#define SPISelectEEPROM()	EEPROM_CS_IO = 0
#define SPIUnselectEEPROM()	EEPROM_CS_IO = 1
#define PIR1_SSPIF	EEPROM_SPI_IF

void WriteBufferToMainMemory(DWORD address);
void ReadBufferFromMainMemory(DWORD address);
void ByteToBuffer(unsigned int byte, DWORD address);
void SPITransfer(unsigned char inbyte)
{	
	SSPBUF = inbyte;
	while(!PIR1_SSPIF);
	PIR1_SSPIF = 0;	
}	

#endif

#if defined(EEPROM_CS_TRIS)
//#if defined(MPFS_USE_EEPROM) && defined(EEPROM_CS_TRIS) && defined(STACK_USE_MPFS2)
// IMPORTANT SPI NOTE: The code in this file expects that the SPI interrupt 
//		flag (EEPROM_SPI_IF) be clear at all times.  If the SPI is shared with 
//		other hardware, the other code should clear the EEPROM_SPI_IF when it is 
//		done using the SPI.

// SPI Serial EEPROM buffer size.  To enhance performance while
// cooperatively sharing the SPI bus with other peripherals, bytes 
// read and written to the memory are locally buffered. Legal 
// sizes are 1 to the EEPROM page size.
#define EEPROM_BUFFER_SIZE    			(32)
#define FLASH_BUFFER_SIZE    			(12)

/* Atmel opcodes*/
#define BUFFER_1_WRITE 						0x84	// buffer 1 write 
#define BUFFER_2_WRITE 						0x87 	// buffer 2 write 
#define BUFFER_1_READ 						0x54	// buffer 1 read
#define BUFFER_2_READ 						0x56	// buffer 2 read		
#define B1_TO_MM_PAGE_PROG_WITH_ERASE 		0x83	// buffer 1 to main memory page program with built-in erase
#define B2_TO_MM_PAGE_PROG_WITH_ERASE 		0x86	// buffer 2 to main memory page program with built-in erase
#define B1_TO_MM_PAGE_PROG_WITHOUT_ERASE 	0x88	// buffer 1 to main memory page program without built-in erase
#define B2_TO_MM_PAGE_PROG_WITHOUT_ERASE 	0x89	// buffer 2 to main memory page program without built-in erase
#define MM_PAGE_PROG_THROUGH_B1 			0x82	// main memory page program through buffer 1
#define MM_PAGE_PROG_THROUGH_B2 			0x85	// main memory page program through buffer 2
#define AUTO_PAGE_REWRITE_THROUGH_B1 		0x58	// auto page rewrite through buffer 1
#define AUTO_PAGE_REWRITE_THROUGH_B2 		0x59	// auto page rewrite through buffer 2
#define MM_PAGE_TO_B1_COMP 					0x60	// main memory page compare to buffer 1
#define MM_PAGE_TO_B2_COMP 					0x61	// main memory page compare to buffer 2
#define MM_PAGE_TO_B1_XFER 					0x53	// main memory page to buffer 1 transfer
#define MM_PAGE_TO_B2_XFER 					0x55	// main memory page to buffer 2 transfer
#define	READ_STATUS_REGISTER				0xD7	// read status register
#define CONTINUOUS_ARRAY_READ				0xE8	// continuous read 
#define MAIN_MEMORY_PAGE_READ               0x52	// main page read
#define PAGE_ERASE                          0x81	// page erase


// EEPROM SPI opcodes
#define READ	0x03	// Read data from memory array beginning at selected address
#define WRITE	0x02	// Write data to memory array beginning at selected address
#define WRDI	0x04	// Reset the write enable latch (disable write operations)
#define WREN	0x06	// Set the write enable latch (enable write operations)
#define RDSR	0x05	// Read Status register
#define WRSR	0x01	// Write Status register



#if defined(USE_ATMEL_FLASH)
BYTE FLASHReadyFlag;
DWORD FLASHAddress;
BYTE *FLASHBufferPtr;
BYTE FLASHBuffer[FLASH_BUFFER_SIZE];
#else
static void DoWrite(void);

static DWORD EEPROMAddress;
static BYTE EEPROMBuffer[EEPROM_BUFFER_SIZE];
static BYTE *EEPROMBufferPtr;
#endif

/*********************************************************************
 * Function:        void XEEInit(unsigned char speed)
 *
 * PreCondition:    None
 *
 * Input:           speed - not used (included for compatibility only)
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Initialize SPI module to communicate to serial
 *                  EEPROM.
 *
 * Note:            Code sets SPI clock to Fosc/16.  
 ********************************************************************/
#if defined(HPC_EXPLORER) && !defined(__18F87J10)
	#define PROPER_SPICON1	(0x20)		/* SSPEN bit is set, SPI in master mode, FOSC/4, IDLE state is low level */
#elif defined(__PIC24F__)
    #define PROPER_SPICON1 	(0x0013 | 0x0120)	/* 1:1 primary prescale, 4:1 secondary prescale, CKE=1, MASTER mode */
#elif defined(__dsPIC30F__)
    #define PROPER_SPICON1 	(0x0017 | 0x0120)	/* 1:1 primary prescale, 3:1 secondary prescale, CKE=1, MASTER mode */
#elif defined(__dsPIC33F__) || defined(__PIC24H__)
    #define PROPER_SPICON1	(0x0003 | 0x0120)	/* 1:1 primary prescale, 8:1 secondary prescale, CKE=1, MASTER mode */
#else
	#define PROPER_SPICON1	(0x21)		/* SSPEN bit is set, SPI in master mode, FOSC/16, IDLE state is low level */
#endif

void XEEInit(void)
{
	EEPROM_CS_IO = 1;
	EEPROM_CS_TRIS = 0;		// Drive SPI EEPROM chip select pin

	EEPROM_SCK_TRIS = 0;	// Set SCK pin as an output
	EEPROM_SDI_TRIS = 1;	// Make sure SDI pin is an input
	EEPROM_SDO_TRIS = 0;	// Set SDO pin as an output

	EEPROM_SPICON1 = PROPER_SPICON1; // See PROPER_SPICON1 definition above
	#if defined(__C30__)
	    EEPROM_SPICON2 = 0;
	    EEPROM_SPISTAT = 0;    // clear SPI
	    EEPROM_SPISTATbits.SPIEN = 1;
	#elif defined(__18CXX)
		EEPROM_SPI_IF = 0;
		EEPROM_SPISTATbits.CKE = 1; 	// Transmit data on rising edge of clock
		EEPROM_SPISTATbits.SMP = 0;		// Input sampled at middle of data output time
	#endif
	#if defined(USE_ATMEL_FLASH)
	FLASHReadyFlag = 1;
	#endif
}


/*********************************************************************
 * Function:        XEE_RESULT XEEBeginRead(unsigned char control,
 *                                          XEE_ADDR address)
 *
 * PreCondition:    XEEInit() is already called.
 *
 * Input:           control - EEPROM control and address code.
 *                  address - Address at which read is to be performed.
 *
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 *
 * Side Effects:    None
 *
 * Overview:        Sets internal address counter to given address.
 *                  Puts EEPROM in sequential read mode.
 *
 * Note:            This function does not release I2C bus.
 *                  User must call XEEEndRead() when read is not longer
 *                  needed; I2C bus will released after XEEEndRead()
 *                  is called.
 ********************************************************************/
XEE_RESULT XEEBeginRead(DWORD address)
{
#if defined(USE_ATMEL_FLASH)

	FLASHAddress = address;
	FLASHBufferPtr = FLASHBuffer + FLASH_BUFFER_SIZE;
	return XEE_SUCCESS;

#else
	// Save the address and emptry the contents of our local buffer
	EEPROMAddress = address;
	EEPROMBufferPtr = EEPROMBuffer + EEPROM_BUFFER_SIZE;
	return XEE_SUCCESS;
	#endif
}


/*********************************************************************
 * Function:        XEE_RESULT XEERead(void)
 *
 * PreCondition:    XEEInit() && XEEBeginRead() are already called.
 *
 * Input:           None
 *
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 *
 * Side Effects:    None
 *
 * Overview:        Reads next byte from EEPROM; internal address
 *                  is incremented by one.
 *
 * Note:            This function does not release I2C bus.
 *                  User must call XEEEndRead() when read is not longer
 *                  needed; I2C bus will released after XEEEndRead()
 *                  is called.
 ********************************************************************/
BYTE XEERead(void)
{
#if defined(USE_ATMEL_FLASH)

	// Check if no more bytes are left in our local buffer
	if( FLASHBufferPtr == FLASHBuffer + FLASH_BUFFER_SIZE )
	{ 
		// Get a new set of bytes
		XEEReadArray(FLASHAddress, FLASHBuffer, FLASH_BUFFER_SIZE);
		FLASHAddress += FLASH_BUFFER_SIZE;
		FLASHBufferPtr = FLASHBuffer;
	}

	// Return a byte from our local buffer
	return *FLASHBufferPtr++;
#else
	// Check if no more bytes are left in our local buffer
	if( EEPROMBufferPtr == EEPROMBuffer + EEPROM_BUFFER_SIZE )
	{ 
		// Get a new set of bytes
		XEEReadArray(EEPROMAddress, EEPROMBuffer, EEPROM_BUFFER_SIZE);
		EEPROMAddress += EEPROM_BUFFER_SIZE;
		EEPROMBufferPtr = EEPROMBuffer;
	}

	// Return a byte from our local buffer
	return *EEPROMBufferPtr++;
#endif
}

/*********************************************************************
 * Function:        XEE_RESULT XEEEndRead(void)
 *
 * PreCondition:    XEEInit() && XEEBeginRead() are already called.
 *
 * Input:           None
 *
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 *
 * Side Effects:    None
 *
 * Overview:        Ends sequential read cycle.
 *
 * Note:            This function ends sequential cycle that was in
 *                  progress.  It releases I2C bus.
 ********************************************************************/
XEE_RESULT XEEEndRead(void)
{
    return XEE_SUCCESS;
}


/*********************************************************************
 * Function:        XEE_RESULT XEEReadArray(unsigned char control,
 *                                          XEE_ADDR address,
 *                                          unsigned char *buffer,
 *                                          unsigned char length)
 *
 * PreCondition:    XEEInit() is already called.
 *
 * Input:           control     - Unused
 *                  address     - Address from where array is to be read
 *                  buffer      - Caller supplied buffer to hold the data
 *                  length      - Number of bytes to read.
 *
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 *
 * Side Effects:    None
 *
 * Overview:        Reads desired number of bytes in sequential mode.
 *                  This function performs all necessary steps
 *                  and releases the bus when finished.
 *
 * Note:            None
 ********************************************************************/
XEE_RESULT XEEReadArray(DWORD address,
                        BYTE *buffer,
                        BYTE length)
{
#if defined(USE_ATMEL_FLASH)

	unsigned int addr	= 0;
	unsigned int page	= 0;

	page = address/264;
	addr = address%264;

	page<<=1;	

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 0;	// Data transmitted on falling edge of SCK
	SSPCON1 = 0x30;			// perform SPI Mode 3

	SPISelectEEPROM();

	// Send READ opcode
	//SPITransfer = CONTINUOUS_ARRAY_READ;
	//SSPBUF = MAIN_MEMORY_PAGE_READ;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(CONTINUOUS_ARRAY_READ);
	
	// 24 bit page and address
	//SSPBUF = (*((unsigned char*)&page+1));
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer((*((unsigned char*)&page+1)));

	//SSPBUF = (((unsigned char)page&0xFE)|(*((unsigned char*)&addr+1) & 0x01));
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer((((unsigned char)page&0xFE)|(*((unsigned char*)&addr+1) & 0x01)));

	//SSPBUF = (unsigned char)addr;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer((unsigned char)addr);

	// 32 don't care bits
	//SSPBUF = 0;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer(0);

	//SSPBUF = 0;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(0);

	//SSPBUF = 0;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(0);

	//SSPBUF = 0;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(0);


	while(length--)
	{
		//SSPBUF = 0;
		//while(!PIR1_SSPIF);
		//PIR1_SSPIF = 0;
		SPITransfer(0);
		*buffer++ = SSPBUF;
	};
	
	SPIUnselectEEPROM();

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 1;	// Transmit data on rising edge of clock
	SSPCON1 = 0x20;			// perform SPI Mode 0

	return XEE_SUCCESS;

#else
	BYTE Dummy;
	#if defined(__18CXX)
	BYTE SPICON1Save;
	#else
	WORD SPICON1Save;
	#endif	

	// Save SPI state (clock speed)
	SPICON1Save = EEPROM_SPICON1;
	EEPROM_SPICON1 = PROPER_SPICON1;

	EEPROM_CS_IO = 0;

	// Send READ opcode
	EEPROM_SSPBUF = READ;
	while(!EEPROM_SPI_IF);
	Dummy = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	
	// Send address
	EEPROM_SSPBUF = ((WORD_VAL*)&address)->v[1];
	while(!EEPROM_SPI_IF);
	Dummy = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	EEPROM_SSPBUF = ((WORD_VAL*)&address)->v[0];
	while(!EEPROM_SPI_IF);
	Dummy = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	
	while(length--)
	{
		EEPROM_SSPBUF = 0;
		while(!EEPROM_SPI_IF);
		*buffer++ = EEPROM_SSPBUF;
		EEPROM_SPI_IF = 0;
	};
	
	EEPROM_CS_IO = 1;

	// Restore SPI state
	EEPROM_SPICON1 = SPICON1Save;

	return XEE_SUCCESS;
#endif
}


/*********************************************************************
 * Function:        XEE_RESULT XEESetAddr(unsigned char control,
 *                                        XEE_ADDR address)
 *
 * PreCondition:    XEEInit() is already called.
 *
 * Input:           control     - data EEPROM control code
 *                  address     - address to be set for writing
 *
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 *
 * Side Effects:    None
 *
 * Overview:        Modifies internal address counter of EEPROM.
 *
 * Note:            Unlike XEESetAddr() in xeeprom.c for I2C EEPROM 
 *					 memories, this function is used only for writing
 *					 to the EEPROM.  Reads must use XEEBeginRead(), 
 *					 XEERead(), and XEEEndRead().
 *					This function does not release the SPI bus.
 ********************************************************************/
XEE_RESULT XEEBeginWrite(DWORD address)
{
#if defined(USE_ATMEL_FLASH)
	FLASHReadyFlag = 1;
	FLASHAddress = address;
	FLASHBufferPtr = FLASHBuffer;
	return XEE_SUCCESS;
#else
	EEPROMAddress = address;
	EEPROMBufferPtr = EEPROMBuffer;
	return XEE_SUCCESS;
#endif
}


/*********************************************************************
 * Function:        XEE_RESULT XEEWrite(unsigned char val)
 *
 * PreCondition:    XEEInit() && XEEBeginWrite() are already called.
 *
 * Input:           val - Byte to be written
 *
 * Output:          XEE_SUCCESS
 *
 * Side Effects:    None
 *
 * Overview:        Adds a byte to the current page to be writen when
 *					XEEEndWrite() is called.
 *
 * Note:            Page boundary cannot be exceeded or the byte 
 *					to be written will be looped back to the 
 *					beginning of the page.
 ********************************************************************/
XEE_RESULT XEEWrite(BYTE val)
{
#if defined(USE_ATMEL_FLASH)

	if(FLASHReadyFlag == 1) {
		ReadBufferFromMainMemory(FLASHAddress);
		FLASHReadyFlag = 0;
	}

	
	ByteToBuffer(val, FLASHAddress);
	FLASHAddress++;

	if((FLASHAddress%FLASH_BUFFER_SIZE) == 0) {
		WriteBufferToMainMemory(FLASHAddress-1);	
	}

	return XEE_SUCCESS;

#else
	*EEPROMBufferPtr++ = val;
	if( EEPROMBufferPtr == EEPROMBuffer + EEPROM_BUFFER_SIZE )
    {
		DoWrite();
    }

    return XEE_SUCCESS;
#endif
}



/*****************************************************************************
  Function:
    XEE_RESULT XEEWriteArray(BYTE *val, WORD wLen)

  Summary:
    Writes an array of bytes to the EEPROM part.

  Description:
    This function writes an array of bytes to the EEPROM at the address 
    specified when XEEBeginWrite() was called.  Page boundary crossing is 
    handled internally.
    
  Precondition:
    XEEInit() was called once and XEEBeginWrite() was called.

  Parameters:
    vData - The array to write to the next memory location
    wLen - The length of the data to be written

  Returns:
    None

  Remarks:
    The internal write cache is flushed at completion, so it is unnecessary 
    to call XEEEndWrite() after calling this function.  However, if you do 
    so, no harm will be done.
  ***************************************************************************/
void XEEWriteArray(BYTE *val, WORD wLen)
{
	while(wLen--)
		XEEWrite(*val++);
	
	XEEEndWrite();
}


/*********************************************************************
 * Function:        XEE_RESULT XEEEndWrite(void)
 *
 * PreCondition:    XEEInit() && XEEBeginWrite() are already called.
 *
 * Input:           None
 *
 * Output:          XEE_SUCCESS if successful
 *                  other value if failed.
 *
 * Side Effects:    None
 *
 * Overview:        Instructs EEPROM to begin write cycle.
 *
 * Note:            Call this function after either page full of bytes
 *                  written or no more bytes are left to load.
 *                  This function initiates the write cycle.
 *                  User must call for XEEIsBusy() to ensure that write
 *                  cycle is finished before calling any other
 *                  routine.
 ********************************************************************/
XEE_RESULT XEEEndWrite(void)
{
#if defined(USE_ATMEL_FLASH)

	FLASHReadyFlag = 0;
	if((FLASHAddress%FLASH_BUFFER_SIZE) != 0) {
		WriteBufferToMainMemory(FLASHAddress-1);		
	}    

	return XEE_SUCCESS;

#else
	if( EEPROMBufferPtr != EEPROMBuffer )
    {
		DoWrite();
    }

    return XEE_SUCCESS;
#endif
}

#if  !defined(USE_ATMEL_FLASH)
static void DoWrite(void)
{
	BYTE Dummy;
	BYTE BytesToWrite;
	#if defined(__18CXX)
	BYTE SPICON1Save;
	#else
	WORD SPICON1Save;
	#endif	

	// Save SPI state (clock speed)
	SPICON1Save = EEPROM_SPICON1;
	EEPROM_SPICON1 = PROPER_SPICON1;
	
	// Set the Write Enable latch
	EEPROM_CS_IO = 0;
	EEPROM_SSPBUF = WREN;
	while(!EEPROM_SPI_IF);
	Dummy = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	EEPROM_CS_IO = 1;
	
	// Send WRITE opcode
	EEPROM_CS_IO = 0;
	EEPROM_SSPBUF = WRITE;
	while(!EEPROM_SPI_IF);
	Dummy = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	
	// Send address
	EEPROM_SSPBUF = ((WORD_VAL*)&EEPROMAddress)->v[1];
	while(!EEPROM_SPI_IF);
	Dummy = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	EEPROM_SSPBUF = ((WORD_VAL*)&EEPROMAddress)->v[0];
	while(!EEPROM_SPI_IF);
	Dummy = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	
	BytesToWrite = (BYTE)(EEPROMBufferPtr - EEPROMBuffer);
	
	EEPROMAddress += BytesToWrite;
	EEPROMBufferPtr = EEPROMBuffer;

	while(BytesToWrite--)
	{
		// Send the byte to write
		EEPROM_SSPBUF = *EEPROMBufferPtr++;
		while(!EEPROM_SPI_IF);
		Dummy = EEPROM_SSPBUF;
		EEPROM_SPI_IF = 0;
	}

	// Begin the write
	EEPROM_CS_IO = 1;

	EEPROMBufferPtr = EEPROMBuffer;

	// Restore SPI State
	EEPROM_SPICON1 = SPICON1Save;

	// Wait for write to complete
	while( XEEIsBusy() );
}
#endif

/*********************************************************************
 * Function:        BOOL XEEIsBusy(void)
 *
 * PreCondition:    XEEInit() is already called.
 *
 * Input:           None
 *
 * Output:          FALSE if EEPROM is not busy
 *                  TRUE if EEPROM is busy
 *
 * Side Effects:    None
 *
 * Overview:        Reads the status register
 *
 * Note:            None
 ********************************************************************/
BOOL XEEIsBusy(void)
{
	BYTE_VAL result;
#if defined(USE_ATMEL_FLASH)

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 0; 	// Data transmitted on falling edge of SCK
	SSPCON1 = 0x30;			// perform SPI Mode 3

	SPISelectEEPROM();

	// Send RDSR - Read Status Register opcode
	//SSPBUF = READ_STATUS_REGISTER;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(READ_STATUS_REGISTER);

	// Get register contents
	//SSPBUF = 0;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(0);
	result.Val = SSPBUF;

	SPIUnselectEEPROM();

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 1; 	// Transmit data on rising edge of clock
	SSPCON1 = 0x20;			// perform SPI Mode 0

	if(result.Val&0x80) 
		return FALSE;
	else 
		return TRUE;

#else
	#if defined(__18CXX)
	BYTE SPICON1Save;
	#else
	WORD SPICON1Save;
	#endif	

	// Save SPI state (clock speed)
	SPICON1Save = EEPROM_SPICON1;
	EEPROM_SPICON1 = PROPER_SPICON1;

	EEPROM_CS_IO = 0;
	// Send RDSR - Read Status Register opcode
	EEPROM_SSPBUF = RDSR;
	while(!EEPROM_SPI_IF);
	result.Val = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	
	// Get register contents
	EEPROM_SSPBUF = 0;
	while(!EEPROM_SPI_IF);
	result.Val = EEPROM_SSPBUF;
	EEPROM_SPI_IF = 0;
	EEPROM_CS_IO = 1;

	// Restore SPI State
	EEPROM_SPICON1 = SPICON1Save;

	return result.bits.b0;
#endif
}

/*********************************************************************
 * Function:        EraseSector at specify address
 *
 * PreCondition:    XEEInit() is already called.
 *
 * Input:           Address to erase
 *
 * Side Effects:    None
 *
 * Overview:        Erase sector
 *
 * Note:            None
 ********************************************************************/
void EraseSector(unsigned int address) {

// WORK BUT NOT ENOUGHT SPACE

#if defined(USE_ATMEL_FLASH)

	unsigned int addr	= 0;
	unsigned int page	= 0;
		
	page = address/264;
	addr = address%264;	

	page<<=1;

	// Wait for write to complete
	while( XEEIsBusy() );

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 0; 	// Data transmitted on falling edge of SCK
	SSPCON1 = 0x30;			// perform SPI Mode 3

	SPISelectEEPROM();

	//command
	SSPBUF = PAGE_ERASE;
	while(!PIR1_SSPIF);
	PIR1_SSPIF = 0;	

	//6 reserved + 2 high address
	SSPBUF = (*((unsigned char*)&page+1));
	while(!PIR1_SSPIF);
	PIR1_SSPIF = 0;	

	//7 low address bits + 1 don't care
	SSPBUF = ((unsigned char)page);
	while(!PIR1_SSPIF);
	PIR1_SSPIF = 0;	

	//don't care 8 bits
	SSPBUF = 0;
	while(!PIR1_SSPIF);
	PIR1_SSPIF = 0;	
	
	SPIUnselectEEPROM();

	// Wait for write to complete
	while( XEEIsBusy() );

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 1; 	// Transmit data on rising edge of clock
	SSPCON1 = 0x20;			// perform SPI Mode 0


#endif

}



/*********************************************************************
 * Function:        Write buffer to main memory
 *
 * PreCondition:    XEEInit() is already called.
 *
 * Input:           Address which determine page to write
 *
 * Side Effects:    None
 *
 * Overview:        Write buffer to main memory
 *
 * Note:            None
 ********************************************************************/
void WriteBufferToMainMemory(DWORD address) {
	
#if defined(USE_ATMEL_FLASH)

	// unsigned int addr	= 0;
	unsigned int page	= 0;
		
	page = address/264;
	// addr = address%264;	

	page<<=1;

	// Wait for write to complete
	while( XEEIsBusy() );	

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 0; 	// Data transmitted on falling edge of SCK
	SSPCON1 = 0x30;			// perform SPI Mode 3

	SPISelectEEPROM();

	//command
	//SSPBUF = B1_TO_MM_PAGE_PROG_WITH_ERASE;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer(B1_TO_MM_PAGE_PROG_WITH_ERASE);

	//6 reserved + 2 high address
	//SSPBUF = (*((unsigned char*)&page+1));
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer((*((unsigned char*)&page+1)));

	//7 low address bits + 1 don't care
	//SSPBUF = ((unsigned char)page);
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer(((unsigned char)page));

	//don't care 8 bits
	//SSPBUF = 0;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer(0);
	
	SPIUnselectEEPROM();

	// Wait for write to complete
	while( XEEIsBusy() );

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 1; 	// Transmit data on rising edge of clock
	SSPCON1 = 0x20;			// perform SPI Mode 0

#endif

}


/*********************************************************************
 * Function:        Read buffer from main memory
 *
 * PreCondition:    XEEInit() is already called.
 *
 * Input:           Address which determine page to read
 *
 * Side Effects:    None
 *
 * Overview:        Read buffer to main memory
 *
 * Note:            None
 ********************************************************************/
void ReadBufferFromMainMemory(DWORD address) {

#if defined(USE_ATMEL_FLASH)	

	// unsigned int addr	= 0;
	unsigned int page	= 0;
		
	page = address/264;
	// addr = address%264;	

	page<<=1;

	// Wait for write to complete
	while( XEEIsBusy() );	

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 0; 	// Data transmitted on falling edge of SCK
	SSPCON1 = 0x30;			// perform SPI Mode 3

	SPISelectEEPROM();

	//command
	//SSPBUF = MM_PAGE_TO_B1_XFER;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer(MM_PAGE_TO_B1_XFER);
	
	//6 reserved + 2 high address
	//SSPBUF = (*((unsigned char*)&page+1));
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer((*((unsigned char*)&page+1)));

	//7 low address bits + 1 don't care
	//SSPBUF = ((unsigned char)page);
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer(((unsigned char)page));

	//don't care 8 bits
	//SSPBUF = 0;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;	
	SPITransfer(0);
	
	SPIUnselectEEPROM();

	// Wait for write to complete
	while( XEEIsBusy() );

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 1; 	// Transmit data on rising edge of clock
	SSPCON1 = 0x20;			// perform SPI Mode 0

#endif

}

/*********************************************************************
 * Function:        Program byte to buffer
 *
 * PreCondition:    XEEInit() is already called.
 *
 * Input:           Byte to program and address 
 *
 * Side Effects:    None
 *
 * Overview:        Program byte to buffer
 *
 * Note:            None
 ********************************************************************/
void ByteToBuffer(unsigned int byte, DWORD address) {
	
	unsigned int 	addr			= 0;
	//unsigned int 	page			= 0;

	//page = address/264;
	addr = address%264;	

	// Wait for write to complete
	while( XEEIsBusy() );	

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 0; 	// Data transmitted on falling edge of SCK
	SSPCON1 = 0x30;			// perform SPI Mode 3

	// Set the Write Enable latch
	SPISelectEEPROM();

	//SSPBUF = BUFFER_1_WRITE;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(BUFFER_1_WRITE);
	
	//SSPBUF = 0;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(0);
	
	//SSPBUF = (*((unsigned char*)&addr +1));
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer((*((unsigned char*)&addr +1)));
	
	//SSPBUF = ((unsigned char)addr);
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;
	SPITransfer(((unsigned char)addr));

	// Send the byte to write
	//SSPBUF = byte;
	//while(!PIR1_SSPIF);
	//PIR1_SSPIF = 0;		
	SPITransfer(byte);
	
	SPIUnselectEEPROM();

	// Wait for write to complete
	while( XEEIsBusy() );

	// perform to transfer
	EEPROM_SPISTATbits.CKE = 1; 	// Transmit data on rising edge of clock
	SSPCON1 = 0x20;			// perform SPI Mode 0
}


#endif //#if defined(MPFS_USE_EEPROM) && defined(EEPROM_CS_TRIS) && defined(STACK_USE_MPFS)
