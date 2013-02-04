#line 1 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"
#line 1 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 38 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"
 




#line 1 "HardwareProfile.h"

#line 50 "HardwareProfile.h"
 







#line 59 "HardwareProfile.h"
#line 61 "HardwareProfile.h"
#line 64 "HardwareProfile.h"
	
#line 1 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

#line 50 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
 

#line 53 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

#line 1 "C:/mcc18/h/GenericTypeDefs.h"

#line 46 "C:/mcc18/h/GenericTypeDefs.h"
 


#line 50 "C:/mcc18/h/GenericTypeDefs.h"

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;	


#line 55 "C:/mcc18/h/GenericTypeDefs.h"
#line 56 "C:/mcc18/h/GenericTypeDefs.h"

#line 58 "C:/mcc18/h/GenericTypeDefs.h"
#line 59 "C:/mcc18/h/GenericTypeDefs.h"
#line 60 "C:/mcc18/h/GenericTypeDefs.h"

typedef unsigned char		BYTE;				
typedef unsigned short int	WORD;				
typedef unsigned long		DWORD;				
typedef unsigned long long	QWORD;				
typedef signed char			CHAR;				
typedef signed short int	SHORT;				
typedef signed long			LONG;				
typedef signed long long	LONGLONG;			

 
typedef void                VOID;

typedef char                CHAR8;
typedef unsigned char       UCHAR8;

 



typedef signed int          INT;
typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed long int     INT32;
typedef signed long long    INT64;

typedef unsigned int        UINT;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
typedef unsigned long int   UINT32;  
typedef unsigned long long  UINT64;

typedef union _BYTE_VAL
{
    BYTE Val;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union _WORD_VAL
{
    WORD Val;
    BYTE v[2];
    struct
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union _DWORD_VAL
{
    DWORD Val;
	WORD w[2];
    BYTE v[4];
    struct
    {
        WORD LW;
        WORD HW;
    } word;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
        unsigned char b16:1;
        unsigned char b17:1;
        unsigned char b18:1;
        unsigned char b19:1;
        unsigned char b20:1;
        unsigned char b21:1;
        unsigned char b22:1;
        unsigned char b23:1;
        unsigned char b24:1;
        unsigned char b25:1;
        unsigned char b26:1;
        unsigned char b27:1;
        unsigned char b28:1;
        unsigned char b29:1;
        unsigned char b30:1;
        unsigned char b31:1;
    } bits;
} DWORD_VAL;

typedef union _QWORD_VAL
{
    QWORD Val;
	DWORD d[2];
	WORD w[4];
    BYTE v[8];
    struct
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
        unsigned char b16:1;
        unsigned char b17:1;
        unsigned char b18:1;
        unsigned char b19:1;
        unsigned char b20:1;
        unsigned char b21:1;
        unsigned char b22:1;
        unsigned char b23:1;
        unsigned char b24:1;
        unsigned char b25:1;
        unsigned char b26:1;
        unsigned char b27:1;
        unsigned char b28:1;
        unsigned char b29:1;
        unsigned char b30:1;
        unsigned char b31:1;
        unsigned char b32:1;
        unsigned char b33:1;
        unsigned char b34:1;
        unsigned char b35:1;
        unsigned char b36:1;
        unsigned char b37:1;
        unsigned char b38:1;
        unsigned char b39:1;
        unsigned char b40:1;
        unsigned char b41:1;
        unsigned char b42:1;
        unsigned char b43:1;
        unsigned char b44:1;
        unsigned char b45:1;
        unsigned char b46:1;
        unsigned char b47:1;
        unsigned char b48:1;
        unsigned char b49:1;
        unsigned char b50:1;
        unsigned char b51:1;
        unsigned char b52:1;
        unsigned char b53:1;
        unsigned char b54:1;
        unsigned char b55:1;
        unsigned char b56:1;
        unsigned char b57:1;
        unsigned char b58:1;
        unsigned char b59:1;
        unsigned char b60:1;
        unsigned char b61:1;
        unsigned char b62:1;
        unsigned char b63:1;
    } bits;
} QWORD_VAL;

#line 285 "C:/mcc18/h/GenericTypeDefs.h"
#line 54 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

#line 1 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"

#line 54 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
 

#line 57 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"


#line 60 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
	
#line 62 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 1 "C:/mcc18/h/p18cxxx.h"

#line 3 "C:/mcc18/h/p18cxxx.h"

#line 5 "C:/mcc18/h/p18cxxx.h"
#line 7 "C:/mcc18/h/p18cxxx.h"
#line 9 "C:/mcc18/h/p18cxxx.h"
#line 11 "C:/mcc18/h/p18cxxx.h"
#line 13 "C:/mcc18/h/p18cxxx.h"
#line 15 "C:/mcc18/h/p18cxxx.h"
#line 17 "C:/mcc18/h/p18cxxx.h"
#line 19 "C:/mcc18/h/p18cxxx.h"
#line 21 "C:/mcc18/h/p18cxxx.h"
#line 23 "C:/mcc18/h/p18cxxx.h"
#line 25 "C:/mcc18/h/p18cxxx.h"
#line 27 "C:/mcc18/h/p18cxxx.h"
#line 29 "C:/mcc18/h/p18cxxx.h"
#line 31 "C:/mcc18/h/p18cxxx.h"
#line 33 "C:/mcc18/h/p18cxxx.h"
#line 35 "C:/mcc18/h/p18cxxx.h"
#line 37 "C:/mcc18/h/p18cxxx.h"
#line 39 "C:/mcc18/h/p18cxxx.h"
#line 41 "C:/mcc18/h/p18cxxx.h"
#line 43 "C:/mcc18/h/p18cxxx.h"
#line 45 "C:/mcc18/h/p18cxxx.h"
#line 47 "C:/mcc18/h/p18cxxx.h"
#line 49 "C:/mcc18/h/p18cxxx.h"
#line 51 "C:/mcc18/h/p18cxxx.h"
#line 53 "C:/mcc18/h/p18cxxx.h"
#line 55 "C:/mcc18/h/p18cxxx.h"
#line 57 "C:/mcc18/h/p18cxxx.h"
#line 59 "C:/mcc18/h/p18cxxx.h"
#line 61 "C:/mcc18/h/p18cxxx.h"
#line 63 "C:/mcc18/h/p18cxxx.h"
#line 65 "C:/mcc18/h/p18cxxx.h"
#line 67 "C:/mcc18/h/p18cxxx.h"
#line 69 "C:/mcc18/h/p18cxxx.h"
#line 71 "C:/mcc18/h/p18cxxx.h"
#line 73 "C:/mcc18/h/p18cxxx.h"
#line 75 "C:/mcc18/h/p18cxxx.h"
#line 77 "C:/mcc18/h/p18cxxx.h"
#line 79 "C:/mcc18/h/p18cxxx.h"
#line 81 "C:/mcc18/h/p18cxxx.h"
#line 83 "C:/mcc18/h/p18cxxx.h"
#line 85 "C:/mcc18/h/p18cxxx.h"
#line 87 "C:/mcc18/h/p18cxxx.h"
#line 89 "C:/mcc18/h/p18cxxx.h"
#line 91 "C:/mcc18/h/p18cxxx.h"
#line 93 "C:/mcc18/h/p18cxxx.h"
#line 95 "C:/mcc18/h/p18cxxx.h"
#line 97 "C:/mcc18/h/p18cxxx.h"
#line 99 "C:/mcc18/h/p18cxxx.h"
#line 101 "C:/mcc18/h/p18cxxx.h"
#line 103 "C:/mcc18/h/p18cxxx.h"
#line 105 "C:/mcc18/h/p18cxxx.h"
#line 107 "C:/mcc18/h/p18cxxx.h"
#line 109 "C:/mcc18/h/p18cxxx.h"
#line 111 "C:/mcc18/h/p18cxxx.h"
#line 113 "C:/mcc18/h/p18cxxx.h"
#line 115 "C:/mcc18/h/p18cxxx.h"
#line 117 "C:/mcc18/h/p18cxxx.h"
#line 119 "C:/mcc18/h/p18cxxx.h"
#line 121 "C:/mcc18/h/p18cxxx.h"
#line 123 "C:/mcc18/h/p18cxxx.h"
#line 125 "C:/mcc18/h/p18cxxx.h"
#line 127 "C:/mcc18/h/p18cxxx.h"
#line 129 "C:/mcc18/h/p18cxxx.h"
#line 131 "C:/mcc18/h/p18cxxx.h"
#line 133 "C:/mcc18/h/p18cxxx.h"
#line 135 "C:/mcc18/h/p18cxxx.h"
#line 137 "C:/mcc18/h/p18cxxx.h"
#line 139 "C:/mcc18/h/p18cxxx.h"
#line 141 "C:/mcc18/h/p18cxxx.h"
#line 143 "C:/mcc18/h/p18cxxx.h"
#line 145 "C:/mcc18/h/p18cxxx.h"
#line 147 "C:/mcc18/h/p18cxxx.h"
#line 149 "C:/mcc18/h/p18cxxx.h"
#line 151 "C:/mcc18/h/p18cxxx.h"
#line 153 "C:/mcc18/h/p18cxxx.h"
#line 155 "C:/mcc18/h/p18cxxx.h"
#line 157 "C:/mcc18/h/p18cxxx.h"
#line 159 "C:/mcc18/h/p18cxxx.h"
#line 161 "C:/mcc18/h/p18cxxx.h"
#line 163 "C:/mcc18/h/p18cxxx.h"
#line 165 "C:/mcc18/h/p18cxxx.h"
#line 167 "C:/mcc18/h/p18cxxx.h"
#line 169 "C:/mcc18/h/p18cxxx.h"
#line 171 "C:/mcc18/h/p18cxxx.h"
#line 173 "C:/mcc18/h/p18cxxx.h"
#line 175 "C:/mcc18/h/p18cxxx.h"
#line 177 "C:/mcc18/h/p18cxxx.h"
#line 179 "C:/mcc18/h/p18cxxx.h"
#line 181 "C:/mcc18/h/p18cxxx.h"
#line 183 "C:/mcc18/h/p18cxxx.h"
#line 185 "C:/mcc18/h/p18cxxx.h"
#line 187 "C:/mcc18/h/p18cxxx.h"
#line 189 "C:/mcc18/h/p18cxxx.h"
#line 191 "C:/mcc18/h/p18cxxx.h"
#line 193 "C:/mcc18/h/p18cxxx.h"
#line 195 "C:/mcc18/h/p18cxxx.h"
#line 197 "C:/mcc18/h/p18cxxx.h"
#line 199 "C:/mcc18/h/p18cxxx.h"
#line 201 "C:/mcc18/h/p18cxxx.h"
#line 203 "C:/mcc18/h/p18cxxx.h"
#line 205 "C:/mcc18/h/p18cxxx.h"
#line 207 "C:/mcc18/h/p18cxxx.h"
#line 209 "C:/mcc18/h/p18cxxx.h"
#line 211 "C:/mcc18/h/p18cxxx.h"
#line 213 "C:/mcc18/h/p18cxxx.h"
#line 215 "C:/mcc18/h/p18cxxx.h"
#line 217 "C:/mcc18/h/p18cxxx.h"
#line 219 "C:/mcc18/h/p18cxxx.h"
#line 221 "C:/mcc18/h/p18cxxx.h"
#line 223 "C:/mcc18/h/p18cxxx.h"
#line 225 "C:/mcc18/h/p18cxxx.h"
#line 227 "C:/mcc18/h/p18cxxx.h"
#line 229 "C:/mcc18/h/p18cxxx.h"
#line 231 "C:/mcc18/h/p18cxxx.h"
#line 233 "C:/mcc18/h/p18cxxx.h"
#line 235 "C:/mcc18/h/p18cxxx.h"
#line 237 "C:/mcc18/h/p18cxxx.h"
#line 239 "C:/mcc18/h/p18cxxx.h"
#line 241 "C:/mcc18/h/p18cxxx.h"
#line 243 "C:/mcc18/h/p18cxxx.h"
#line 245 "C:/mcc18/h/p18cxxx.h"
#line 247 "C:/mcc18/h/p18cxxx.h"
#line 249 "C:/mcc18/h/p18cxxx.h"
#line 251 "C:/mcc18/h/p18cxxx.h"
#line 253 "C:/mcc18/h/p18cxxx.h"
#line 255 "C:/mcc18/h/p18cxxx.h"
#line 257 "C:/mcc18/h/p18cxxx.h"
#line 259 "C:/mcc18/h/p18cxxx.h"
#line 261 "C:/mcc18/h/p18cxxx.h"
#line 263 "C:/mcc18/h/p18cxxx.h"
#line 265 "C:/mcc18/h/p18cxxx.h"
#line 267 "C:/mcc18/h/p18cxxx.h"
#line 269 "C:/mcc18/h/p18cxxx.h"
#line 271 "C:/mcc18/h/p18cxxx.h"
#line 273 "C:/mcc18/h/p18cxxx.h"
#line 275 "C:/mcc18/h/p18cxxx.h"
#line 277 "C:/mcc18/h/p18cxxx.h"
#line 279 "C:/mcc18/h/p18cxxx.h"
#line 281 "C:/mcc18/h/p18cxxx.h"
#line 283 "C:/mcc18/h/p18cxxx.h"
#line 285 "C:/mcc18/h/p18cxxx.h"
#line 287 "C:/mcc18/h/p18cxxx.h"
#line 289 "C:/mcc18/h/p18cxxx.h"
#line 291 "C:/mcc18/h/p18cxxx.h"
#line 293 "C:/mcc18/h/p18cxxx.h"
#line 295 "C:/mcc18/h/p18cxxx.h"
#line 297 "C:/mcc18/h/p18cxxx.h"
#line 299 "C:/mcc18/h/p18cxxx.h"
#line 301 "C:/mcc18/h/p18cxxx.h"
#line 303 "C:/mcc18/h/p18cxxx.h"
#line 305 "C:/mcc18/h/p18cxxx.h"
#line 307 "C:/mcc18/h/p18cxxx.h"
#line 309 "C:/mcc18/h/p18cxxx.h"
#line 311 "C:/mcc18/h/p18cxxx.h"
#line 313 "C:/mcc18/h/p18cxxx.h"
#line 315 "C:/mcc18/h/p18cxxx.h"
#line 317 "C:/mcc18/h/p18cxxx.h"
#line 319 "C:/mcc18/h/p18cxxx.h"
#line 321 "C:/mcc18/h/p18cxxx.h"
#line 323 "C:/mcc18/h/p18cxxx.h"
#line 325 "C:/mcc18/h/p18cxxx.h"
#line 327 "C:/mcc18/h/p18cxxx.h"
#line 329 "C:/mcc18/h/p18cxxx.h"
#line 331 "C:/mcc18/h/p18cxxx.h"
#line 333 "C:/mcc18/h/p18cxxx.h"
#line 335 "C:/mcc18/h/p18cxxx.h"
#line 337 "C:/mcc18/h/p18cxxx.h"
#line 339 "C:/mcc18/h/p18cxxx.h"
#line 341 "C:/mcc18/h/p18cxxx.h"
#line 343 "C:/mcc18/h/p18cxxx.h"
#line 345 "C:/mcc18/h/p18cxxx.h"
#line 347 "C:/mcc18/h/p18cxxx.h"
#line 349 "C:/mcc18/h/p18cxxx.h"
#line 351 "C:/mcc18/h/p18cxxx.h"
#line 353 "C:/mcc18/h/p18cxxx.h"
#line 355 "C:/mcc18/h/p18cxxx.h"
#line 357 "C:/mcc18/h/p18cxxx.h"
#line 359 "C:/mcc18/h/p18cxxx.h"
#line 361 "C:/mcc18/h/p18cxxx.h"
#line 363 "C:/mcc18/h/p18cxxx.h"
#line 365 "C:/mcc18/h/p18cxxx.h"
#line 367 "C:/mcc18/h/p18cxxx.h"
#line 369 "C:/mcc18/h/p18cxxx.h"
#line 371 "C:/mcc18/h/p18cxxx.h"
#line 373 "C:/mcc18/h/p18cxxx.h"
#line 375 "C:/mcc18/h/p18cxxx.h"
#line 377 "C:/mcc18/h/p18cxxx.h"
#line 379 "C:/mcc18/h/p18cxxx.h"
#line 381 "C:/mcc18/h/p18cxxx.h"
#line 383 "C:/mcc18/h/p18cxxx.h"
#line 385 "C:/mcc18/h/p18cxxx.h"
#line 387 "C:/mcc18/h/p18cxxx.h"
#line 389 "C:/mcc18/h/p18cxxx.h"
#line 391 "C:/mcc18/h/p18cxxx.h"
#line 393 "C:/mcc18/h/p18cxxx.h"
#line 395 "C:/mcc18/h/p18cxxx.h"
#line 397 "C:/mcc18/h/p18cxxx.h"
#line 399 "C:/mcc18/h/p18cxxx.h"
#line 401 "C:/mcc18/h/p18cxxx.h"
#line 403 "C:/mcc18/h/p18cxxx.h"
#line 405 "C:/mcc18/h/p18cxxx.h"
#line 407 "C:/mcc18/h/p18cxxx.h"
#line 409 "C:/mcc18/h/p18cxxx.h"
#line 411 "C:/mcc18/h/p18cxxx.h"
#line 413 "C:/mcc18/h/p18cxxx.h"
#line 415 "C:/mcc18/h/p18cxxx.h"
#line 417 "C:/mcc18/h/p18cxxx.h"
#line 419 "C:/mcc18/h/p18cxxx.h"
#line 421 "C:/mcc18/h/p18cxxx.h"
#line 423 "C:/mcc18/h/p18cxxx.h"
#line 425 "C:/mcc18/h/p18cxxx.h"
#line 427 "C:/mcc18/h/p18cxxx.h"
#line 429 "C:/mcc18/h/p18cxxx.h"
#line 431 "C:/mcc18/h/p18cxxx.h"
#line 433 "C:/mcc18/h/p18cxxx.h"
#line 435 "C:/mcc18/h/p18cxxx.h"
#line 437 "C:/mcc18/h/p18cxxx.h"
#line 439 "C:/mcc18/h/p18cxxx.h"
#line 441 "C:/mcc18/h/p18cxxx.h"
#line 443 "C:/mcc18/h/p18cxxx.h"
#line 445 "C:/mcc18/h/p18cxxx.h"
#line 447 "C:/mcc18/h/p18cxxx.h"
#line 1 "C:/mcc18/h/p18f97j60.h"

#line 5 "C:/mcc18/h/p18f97j60.h"
 


#line 9 "C:/mcc18/h/p18f97j60.h"

extern volatile far  unsigned char       MAADR5;
extern volatile far  unsigned char       MAADR6;
extern volatile far  unsigned char       MAADR3;
extern volatile far  unsigned char       MAADR4;
extern volatile far  unsigned char       MAADR1;
extern volatile far  unsigned char       MAADR2;
extern volatile far  unsigned char       MISTAT;
extern volatile far  struct {
  unsigned BUSY:1;
  unsigned SCAN:1;
  unsigned NVALID:1;
} MISTATbits;
extern volatile far  unsigned char       EFLOCON;
extern volatile far  struct {
  unsigned FCEN0:1;
  unsigned FCEN1:1;
  unsigned FULDPXS:1;
} EFLOCONbits;
extern volatile far  unsigned            EPAUS;
extern volatile far  unsigned char       EPAUSL;
extern volatile far  unsigned char       EPAUSH;
extern volatile far  unsigned char       MACON1;
extern volatile far  struct {
  unsigned MARXEN:1;
  unsigned PASSALL:1;
  unsigned RXPAUS:1;
  unsigned TXPAUS:1;
} MACON1bits;
extern volatile far  unsigned char       MACON3;
extern volatile far  union {
  struct {
    unsigned FULDPX:1;
    unsigned FRMLNEN:1;
    unsigned HFRMEN:1;
    unsigned PHDREN:1;
    unsigned TXCRCEN:1;
    unsigned PADCFG0:1;
    unsigned PADCFG1:1;
    unsigned PADCFG2:1;
  };
  struct {
    unsigned :5;
    unsigned PADCFG:3;
  };
} MACON3bits;
extern volatile far  unsigned char       MACON4;
extern volatile far  struct {
  unsigned :6;
  unsigned DEFER:1;
} MACON4bits;
extern volatile far  unsigned char       MABBIPG;
extern volatile far  unsigned            MAIPG;
extern volatile far  unsigned char       MAIPGL;
extern volatile far  unsigned char       MAIPGH;
extern volatile far  unsigned            MAMXFL;
extern volatile far  unsigned char       MAMXFLL;
extern volatile far  unsigned char       MAMXFLH;
extern volatile far  unsigned char       MICMD;
extern volatile far  struct {
  unsigned MIIRD:1;
  unsigned MIISCAN:1;
} MICMDbits;
extern volatile far  unsigned char       MIREGADR;
extern volatile far  unsigned            MIWR;
extern volatile far  unsigned char       MIWRL;
extern volatile far  unsigned char       MIWRH;
extern volatile far  unsigned            MIRD;
extern volatile far  unsigned char       MIRDL;
extern volatile far  unsigned char       MIRDH;
extern volatile far  unsigned char       EHT0;
extern volatile far  unsigned char       EHT1;
extern volatile far  unsigned char       EHT2;
extern volatile far  unsigned char       EHT3;
extern volatile far  unsigned char       EHT4;
extern volatile far  unsigned char       EHT5;
extern volatile far  unsigned char       EHT6;
extern volatile far  unsigned char       EHT7;
extern volatile far  unsigned char       EPMM0;
extern volatile far  unsigned char       EPMM1;
extern volatile far  unsigned char       EPMM2;
extern volatile far  unsigned char       EPMM3;
extern volatile far  unsigned char       EPMM4;
extern volatile far  unsigned char       EPMM5;
extern volatile far  unsigned char       EPMM6;
extern volatile far  unsigned char       EPMM7;
extern volatile far  unsigned            EPMCS;
extern volatile far  unsigned char       EPMCSL;
extern volatile far  unsigned char       EPMCSH;
extern volatile far  unsigned            EPMO;
extern volatile far  unsigned char       EPMOL;
extern volatile far  unsigned char       EPMOH;
extern volatile far  unsigned char       ERXFCON;
extern volatile far  struct {
  unsigned BCEN:1;
  unsigned MCEN:1;
  unsigned HTEN:1;
  unsigned MPEN:1;
  unsigned PMEN:1;
  unsigned CRCEN:1;
  unsigned ANDOR:1;
  unsigned UCEN:1;
} ERXFCONbits;
extern volatile far  unsigned char       EPKTCNT;
extern volatile far  unsigned            EWRPT;
extern volatile far  unsigned char       EWRPTL;
extern volatile far  unsigned char       EWRPTH;
extern volatile far  unsigned            ETXST;
extern volatile far  unsigned char       ETXSTL;
extern volatile far  unsigned char       ETXSTH;
extern volatile far  unsigned            ETXND;
extern volatile far  unsigned char       ETXNDL;
extern volatile far  unsigned char       ETXNDH;
extern volatile far  unsigned            ERXST;
extern volatile far  unsigned char       ERXSTL;
extern volatile far  unsigned char       ERXSTH;
extern volatile far  unsigned            ERXND;
extern volatile far  unsigned char       ERXNDL;
extern volatile far  unsigned char       ERXNDH;
extern volatile far  unsigned            ERXRDPT;
extern volatile far  unsigned char       ERXRDPTL;
extern volatile far  unsigned char       ERXRDPTH;
extern volatile far  unsigned            ERXWRPT;
extern volatile far  unsigned char       ERXWRPTL;
extern volatile far  unsigned char       ERXWRPTH;
extern volatile far  unsigned            EDMAST;
extern volatile far  unsigned char       EDMASTL;
extern volatile far  unsigned char       EDMASTH;
extern volatile far  unsigned            EDMAND;
extern volatile far  unsigned char       EDMANDL;
extern volatile far  unsigned char       EDMANDH;
extern volatile far  unsigned            EDMADST;
extern volatile far  unsigned char       EDMADSTL;
extern volatile far  unsigned char       EDMADSTH;
extern volatile far  unsigned            EDMACS;
extern volatile far  unsigned char       EDMACSL;
extern volatile far  unsigned char       EDMACSH;
extern volatile far  unsigned char       EIE;
extern volatile far  struct {
  unsigned RXERIE:1;
  unsigned TXERIE:1;
  unsigned :1;
  unsigned TXIE:1;
  unsigned LINKIE:1;
  unsigned DMAIE:1;
  unsigned PKTIE:1;
} EIEbits;
extern volatile far  unsigned char       ESTAT;
extern volatile far  struct {
  unsigned PHYRDY:1;
  unsigned TXABRT:1;
  unsigned RXBUSY:1;
  unsigned :3;
  unsigned BUFER:1;
} ESTATbits;
extern volatile far  unsigned char       ECON2;
extern volatile far  struct {
  unsigned :5;
  unsigned ETHEN:1;
  unsigned PKTDEC:1;
  unsigned AUTOINC:1;
} ECON2bits;
extern volatile near unsigned char       EIR;
extern volatile near struct {
  unsigned RXERIF:1;
  unsigned TXERIF:1;
  unsigned :1;
  unsigned TXIF:1;
  unsigned LINKIF:1;
  unsigned DMAIF:1;
  unsigned PKTIF:1;
} EIRbits;
extern volatile near unsigned char       EDATA;
extern volatile near struct {
  unsigned EDATA0:1;
  unsigned EDATA1:1;
  unsigned EDATA2:1;
  unsigned EDATA3:1;
  unsigned EDATA4:1;
  unsigned EDATA5:1;
  unsigned EDATA6:1;
  unsigned EDATA7:1;
} EDATAbits;
extern volatile near unsigned char       SSP2CON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK:5;
  };
} SSP2CON2bits;
extern volatile near unsigned char       SSP2CON1;
extern volatile near struct {
  unsigned SSPM0:1;
  unsigned SSPM1:1;
  unsigned SSPM2:1;
  unsigned SSPM3:1;
  unsigned CKP:1;
  unsigned SSPEN:1;
  unsigned SSPOV:1;
  unsigned WCOL:1;
} SSP2CON1bits;
extern volatile near unsigned char       SSP2STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSP2STATbits;
extern volatile near unsigned char       SSP2ADD;
extern volatile near unsigned char       SSP2BUF;
extern volatile near unsigned char       ECCP2DEL;
extern volatile near union {
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
    unsigned PRSEN:1;
  };
  struct {
    unsigned P2DC0:1;
    unsigned P2DC1:1;
    unsigned P2DC2:1;
    unsigned P2DC3:1;
    unsigned P2DC4:1;
    unsigned P2DC5:1;
    unsigned P2DC6:1;
    unsigned P2RSEN:1;
  };
} ECCP2DELbits;
extern volatile near unsigned char       ECCP2AS;
extern volatile near union {
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSS2BD0:1;
    unsigned PSS2BD1:1;
    unsigned PSS2AC0:1;
    unsigned PSS2AC1:1;
    unsigned ECCP2AS0:1;
    unsigned ECCP2AS1:1;
    unsigned ECCP2AS2:1;
    unsigned ECCP2ASE:1;
  };
} ECCP2ASbits;
extern volatile near unsigned char       ECCP3DEL;
extern volatile near union {
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
    unsigned PRSEN:1;
  };
  struct {
    unsigned P3DC0:1;
    unsigned P3DC1:1;
    unsigned P3DC2:1;
    unsigned P3DC3:1;
    unsigned P3DC4:1;
    unsigned P3DC5:1;
    unsigned P3DC6:1;
    unsigned P3RSEN:1;
  };
} ECCP3DELbits;
extern volatile near unsigned char       ECCP3AS;
extern volatile near union {
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSS3BD0:1;
    unsigned PSS3BD1:1;
    unsigned PSS3AC0:1;
    unsigned PSS3AC1:1;
    unsigned ECCP3AS0:1;
    unsigned ECCP3AS1:1;
    unsigned ECCP3AS2:1;
    unsigned ECCP3ASE:1;
  };
} ECCP3ASbits;
extern volatile near unsigned char       RCSTA2;
extern volatile near union {
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
} RCSTA2bits;
extern volatile near unsigned char       TXSTA2;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
} TXSTA2bits;
extern volatile near unsigned char       TXREG2;
extern volatile near unsigned char       RCREG2;
extern volatile near unsigned char       SPBRG2;
extern volatile near unsigned char       CCP5CON;
extern volatile near union {
  struct {
    unsigned CCP5M0:1;
    unsigned CCP5M1:1;
    unsigned CCP5M2:1;
    unsigned CCP5M3:1;
    unsigned CCP5Y:1;
    unsigned CCP5X:1;
  };
  struct {
    unsigned :4;
    unsigned DC5B0:1;
    unsigned DC5B1:1;
  };
} CCP5CONbits;
extern volatile near unsigned            CCPR5;
extern volatile near unsigned char       CCPR5L;
extern volatile near unsigned char       CCPR5H;
extern volatile near unsigned char       CCP4CON;
extern volatile near union {
  struct {
    unsigned CCP4M0:1;
    unsigned CCP4M1:1;
    unsigned CCP4M2:1;
    unsigned CCP4M3:1;
    unsigned CCP4Y:1;
    unsigned CCP4X:1;
  };
  struct {
    unsigned :4;
    unsigned DC4B0:1;
    unsigned DC4B1:1;
  };
} CCP4CONbits;
extern volatile near unsigned            CCPR4;
extern volatile near unsigned char       CCPR4L;
extern volatile near unsigned char       CCPR4H;
extern volatile near unsigned char       T4CON;
extern volatile near struct {
  unsigned T4CKPS0:1;
  unsigned T4CKPS1:1;
  unsigned TMR4ON:1;
  unsigned T4OUTPS0:1;
  unsigned T4OUTPS1:1;
  unsigned T4OUTPS2:1;
  unsigned T4OUTPS3:1;
} T4CONbits;
extern volatile near unsigned char       PR4;
extern volatile near unsigned char       TMR4;
extern volatile near unsigned char       ECCP1DEL;
extern volatile near union {
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
    unsigned PRSEN:1;
  };
  struct {
    unsigned P1DC0:1;
    unsigned P1DC1:1;
    unsigned P1DC2:1;
    unsigned P1DC3:1;
    unsigned P1DC4:1;
    unsigned P1DC5:1;
    unsigned P1DC6:1;
    unsigned P1RSEN:1;
  };
} ECCP1DELbits;
extern volatile near unsigned            ERDPT;
extern volatile near unsigned char       ERDPTL;
extern volatile near unsigned char       ERDPTH;
extern volatile near unsigned char       BAUDCON2;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
  };
} BAUDCON2bits;
extern volatile near unsigned char       BAUDCTL2;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
  };
} BAUDCTL2bits;
extern volatile near unsigned char       SPBRGH2;
extern volatile near unsigned char       BAUDCON;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
  };
} BAUDCONbits;
extern volatile near unsigned char       BAUDCON1;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
  };
} BAUDCON1bits;
extern volatile near unsigned char       BAUDCTL;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
  };
} BAUDCTLbits;
extern volatile near unsigned char       BAUDCTL1;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
  };
} BAUDCTL1bits;
extern volatile near unsigned char       SPBRGH;
extern volatile near unsigned char       SPBRGH1;
extern volatile near unsigned char       PORTA;
extern volatile near union {
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned :1;
    unsigned RJPU:1;
  };
  struct {
    unsigned AN0:1;
    unsigned AN1:1;
    unsigned AN2:1;
    unsigned AN3:1;
    unsigned T0CKI:1;
    unsigned AN4:1;
  };
  struct {
    unsigned LEDA:1;
    unsigned LEDB:1;
    unsigned VREFM:1;
    unsigned VREFP:1;
  };
} PORTAbits;
extern volatile near unsigned char       PORTB;
extern volatile near union {
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
  struct {
    unsigned INT0:1;
    unsigned INT1:1;
    unsigned INT2:1;
    unsigned INT3:1;
    unsigned KBI0:1;
    unsigned KBI1:1;
    unsigned KBI2:1;
    unsigned KBI3:1;
  };
  struct {
    unsigned FLT0:1;
    unsigned :2;
    unsigned CCP2:1;
    unsigned :2;
    unsigned PGC:1;
    unsigned PGD:1;
  };
  struct {
    unsigned :3;
    unsigned ECCP2:1;
  };
} PORTBbits;
extern volatile near unsigned char       PORTC;
extern volatile near union {
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
  struct {
    unsigned T1OSO:1;
    unsigned T1OSI:1;
    unsigned CCP1:1;
    unsigned SCK:1;
    unsigned SDI:1;
    unsigned SDO:1;
    unsigned TX:1;
    unsigned RX:1;
  };
  struct {
    unsigned T13CKI:1;
    unsigned CCP2:1;
    unsigned :1;
    unsigned SCL:1;
    unsigned SDA:1;
    unsigned :1;
    unsigned CK:1;
    unsigned DT:1;
  };
  struct {
    unsigned :1;
    unsigned ECCP2:1;
    unsigned ECCP1:1;
    unsigned SCK1:1;
    unsigned SDI1:1;
    unsigned SDO1:1;
    unsigned TX1:1;
    unsigned RX1:1;
  };
  struct {
    unsigned :3;
    unsigned SCL1:1;
    unsigned SDA1:1;
    unsigned :1;
    unsigned CK1:1;
    unsigned DT1:1;
  };
} PORTCbits;
extern volatile near unsigned char       PORTD;
extern volatile near union {
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
  struct {
    unsigned PSP0:1;
    unsigned PSP1:1;
    unsigned PSP2:1;
    unsigned PSP3:1;
    unsigned PSP4:1;
    unsigned PSP5:1;
    unsigned PSP6:1;
    unsigned PSP7:1;
  };
  struct {
    unsigned AD0:1;
    unsigned AD1:1;
    unsigned AD2:1;
    unsigned AD3:1;
    unsigned AD4:1;
    unsigned AD5:1;
    unsigned AD6:1;
    unsigned AD7:1;
  };
  struct {
    unsigned :5;
    unsigned SDA2:1;
    unsigned SCL2:1;
    unsigned SS2:1;
  };
  struct {
    unsigned :4;
    unsigned SDO2:1;
    unsigned SDI2:1;
    unsigned SCK2:1;
    unsigned NOT_SS2:1;
  };
} PORTDbits;
extern volatile near unsigned char       PORTE;
extern volatile near union {
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
    unsigned RE3:1;
    unsigned RE4:1;
    unsigned RE5:1;
    unsigned RE6:1;
    unsigned RE7:1;
  };
  struct {
    unsigned RD:1;
    unsigned WR:1;
    unsigned CS:1;
    unsigned :4;
    unsigned CCP2:1;
  };
  struct {
    unsigned NOT_RD:1;
    unsigned NOT_WR:1;
    unsigned NOT_CS:1;
    unsigned :4;
    unsigned ECCP2:1;
  };
  struct {
    unsigned AD8:1;
    unsigned AD9:1;
    unsigned AD10:1;
    unsigned AD11:1;
    unsigned AD12:1;
    unsigned AD13:1;
    unsigned AD14:1;
    unsigned AD15:1;
  };
} PORTEbits;
extern volatile near unsigned char       PORTF;
extern volatile near union {
  struct {
    unsigned RF0:1;
    unsigned RF1:1;
    unsigned RF2:1;
    unsigned RF3:1;
    unsigned RF4:1;
    unsigned RF5:1;
    unsigned RF6:1;
    unsigned RF7:1;
  };
  struct {
    unsigned AN5:1;
    unsigned AN6:1;
    unsigned AN7:1;
    unsigned AN8:1;
    unsigned AN9:1;
    unsigned AN10:1;
    unsigned AN11:1;
    unsigned SS:1;
  };
  struct {
    unsigned :5;
    unsigned CVREF:1;
    unsigned :1;
    unsigned NOT_SS:1;
  };
  struct {
    unsigned :7;
    unsigned SS1:1;
  };
  struct {
    unsigned :7;
    unsigned NOT_SS1:1;
  };
} PORTFbits;
extern volatile near unsigned char       PORTG;
extern volatile near union {
  struct {
    unsigned RG0:1;
    unsigned RG1:1;
    unsigned RG2:1;
    unsigned RG3:1;
    unsigned RG4:1;
    unsigned RG5:1;
    unsigned RG6:1;
    unsigned RG7:1;
  };
  struct {
    unsigned CCP3:1;
    unsigned TX2:1;
    unsigned RX2:1;
    unsigned CCP4:1;
    unsigned CCP5:1;
  };
  struct {
    unsigned ECCP3:1;
    unsigned CK2:1;
    unsigned DT2:1;
  };
} PORTGbits;
extern volatile near unsigned char       PORTH;
extern volatile near union {
  struct {
    unsigned RH0:1;
    unsigned RH1:1;
    unsigned RH2:1;
    unsigned RH3:1;
    unsigned RH4:1;
    unsigned RH5:1;
    unsigned RH6:1;
    unsigned RH7:1;
  };
  struct {
    unsigned AD16:1;
    unsigned AD17:1;
    unsigned AD18:1;
    unsigned AD19:1;
    unsigned AN12:1;
    unsigned AN13:1;
    unsigned AN14:1;
    unsigned AN15:1;
  };
} PORTHbits;
extern volatile near unsigned char       PORTJ;
extern volatile near union {
  struct {
    unsigned RJ0:1;
    unsigned RJ1:1;
    unsigned RJ2:1;
    unsigned RJ3:1;
    unsigned RJ4:1;
    unsigned RJ5:1;
    unsigned RJ6:1;
    unsigned RJ7:1;
  };
  struct {
    unsigned ALE:1;
    unsigned OE:1;
    unsigned WRL:1;
    unsigned WRH:1;
    unsigned BA0:1;
    unsigned CE:1;
    unsigned LB:1;
    unsigned UB:1;
  };
  struct {
    unsigned :1;
    unsigned NOT_OE:1;
    unsigned NOT_WRL:1;
    unsigned NOT_WRH:1;
    unsigned :1;
    unsigned NOT_CE:1;
    unsigned NOT_LB:1;
    unsigned NOT_UB:1;
  };
} PORTJbits;
extern volatile near unsigned char       LATA;
extern volatile near struct {
  unsigned LATA0:1;
  unsigned LATA1:1;
  unsigned LATA2:1;
  unsigned LATA3:1;
  unsigned LATA4:1;
  unsigned LATA5:1;
  unsigned REPU:1;
  unsigned RDPU:1;
} LATAbits;
extern volatile near unsigned char       LATB;
extern volatile near struct {
  unsigned LATB0:1;
  unsigned LATB1:1;
  unsigned LATB2:1;
  unsigned LATB3:1;
  unsigned LATB4:1;
  unsigned LATB5:1;
  unsigned LATB6:1;
  unsigned LATB7:1;
} LATBbits;
extern volatile near unsigned char       LATC;
extern volatile near struct {
  unsigned LATC0:1;
  unsigned LATC1:1;
  unsigned LATC2:1;
  unsigned LATC3:1;
  unsigned LATC4:1;
  unsigned LATC5:1;
  unsigned LATC6:1;
  unsigned LATC7:1;
} LATCbits;
extern volatile near unsigned char       LATD;
extern volatile near struct {
  unsigned LATD0:1;
  unsigned LATD1:1;
  unsigned LATD2:1;
  unsigned LATD3:1;
  unsigned LATD4:1;
  unsigned LATD5:1;
  unsigned LATD6:1;
  unsigned LATD7:1;
} LATDbits;
extern volatile near unsigned char       LATE;
extern volatile near struct {
  unsigned LATE0:1;
  unsigned LATE1:1;
  unsigned LATE2:1;
  unsigned LATE3:1;
  unsigned LATE4:1;
  unsigned LATE5:1;
  unsigned LATE6:1;
  unsigned LATE7:1;
} LATEbits;
extern volatile near unsigned char       LATF;
extern volatile near struct {
  unsigned LATF0:1;
  unsigned LATF1:1;
  unsigned LATF2:1;
  unsigned LATF3:1;
  unsigned LATF4:1;
  unsigned LATF5:1;
  unsigned LATF6:1;
  unsigned LATF7:1;
} LATFbits;
extern volatile near unsigned char       LATG;
extern volatile near struct {
  unsigned LATG0:1;
  unsigned LATG1:1;
  unsigned LATG2:1;
  unsigned LATG3:1;
  unsigned LATG4:1;
  unsigned LATG5:1;
  unsigned LATG6:1;
  unsigned LATG7:1;
} LATGbits;
extern volatile near unsigned char       LATH;
extern volatile near struct {
  unsigned LATH0:1;
  unsigned LATH1:1;
  unsigned LATH2:1;
  unsigned LATH3:1;
  unsigned LATH4:1;
  unsigned LATH5:1;
  unsigned LATH6:1;
  unsigned LATH7:1;
} LATHbits;
extern volatile near unsigned char       LATJ;
extern volatile near struct {
  unsigned LATJ0:1;
  unsigned LATJ1:1;
  unsigned LATJ2:1;
  unsigned LATJ3:1;
  unsigned LATJ4:1;
  unsigned LATJ5:1;
  unsigned LATJ6:1;
  unsigned LATJ7:1;
} LATJbits;
extern volatile near unsigned char       DDRA;
extern volatile near struct {
  unsigned RA0:1;
  unsigned RA1:1;
  unsigned RA2:1;
  unsigned RA3:1;
  unsigned RA4:1;
  unsigned RA5:1;
} DDRAbits;
extern volatile near unsigned char       TRISA;
extern volatile near struct {
  unsigned TRISA0:1;
  unsigned TRISA1:1;
  unsigned TRISA2:1;
  unsigned TRISA3:1;
  unsigned TRISA4:1;
  unsigned TRISA5:1;
} TRISAbits;
extern volatile near unsigned char       DDRB;
extern volatile near struct {
  unsigned RB0:1;
  unsigned RB1:1;
  unsigned RB2:1;
  unsigned RB3:1;
  unsigned RB4:1;
  unsigned RB5:1;
  unsigned RB6:1;
  unsigned RB7:1;
} DDRBbits;
extern volatile near unsigned char       TRISB;
extern volatile near struct {
  unsigned TRISB0:1;
  unsigned TRISB1:1;
  unsigned TRISB2:1;
  unsigned TRISB3:1;
  unsigned TRISB4:1;
  unsigned TRISB5:1;
  unsigned TRISB6:1;
  unsigned TRISB7:1;
} TRISBbits;
extern volatile near unsigned char       DDRC;
extern volatile near struct {
  unsigned RC0:1;
  unsigned RC1:1;
  unsigned RC2:1;
  unsigned RC3:1;
  unsigned RC4:1;
  unsigned RC5:1;
  unsigned RC6:1;
  unsigned RC7:1;
} DDRCbits;
extern volatile near unsigned char       TRISC;
extern volatile near struct {
  unsigned TRISC0:1;
  unsigned TRISC1:1;
  unsigned TRISC2:1;
  unsigned TRISC3:1;
  unsigned TRISC4:1;
  unsigned TRISC5:1;
  unsigned TRISC6:1;
  unsigned TRISC7:1;
} TRISCbits;
extern volatile near unsigned char       DDRD;
extern volatile near struct {
  unsigned RD0:1;
  unsigned RD1:1;
  unsigned RD2:1;
  unsigned RD3:1;
  unsigned RD4:1;
  unsigned RD5:1;
  unsigned RD6:1;
  unsigned RD7:1;
} DDRDbits;
extern volatile near unsigned char       TRISD;
extern volatile near struct {
  unsigned TRISD0:1;
  unsigned TRISD1:1;
  unsigned TRISD2:1;
  unsigned TRISD3:1;
  unsigned TRISD4:1;
  unsigned TRISD5:1;
  unsigned TRISD6:1;
  unsigned TRISD7:1;
} TRISDbits;
extern volatile near unsigned char       DDRE;
extern volatile near struct {
  unsigned RE0:1;
  unsigned RE1:1;
  unsigned RE2:1;
  unsigned RE3:1;
  unsigned RE4:1;
  unsigned RE5:1;
  unsigned RE6:1;
  unsigned RE7:1;
} DDREbits;
extern volatile near unsigned char       TRISE;
extern volatile near struct {
  unsigned TRISE0:1;
  unsigned TRISE1:1;
  unsigned TRISE2:1;
  unsigned TRISE3:1;
  unsigned TRISE4:1;
  unsigned TRISE5:1;
  unsigned TRISE6:1;
  unsigned TRISE7:1;
} TRISEbits;
extern volatile near unsigned char       DDRF;
extern volatile near struct {
  unsigned RF0:1;
  unsigned RF1:1;
  unsigned RF2:1;
  unsigned RF3:1;
  unsigned RF4:1;
  unsigned RF5:1;
  unsigned RF6:1;
  unsigned RF7:1;
} DDRFbits;
extern volatile near unsigned char       TRISF;
extern volatile near struct {
  unsigned TRISF0:1;
  unsigned TRISF1:1;
  unsigned TRISF2:1;
  unsigned TRISF3:1;
  unsigned TRISF4:1;
  unsigned TRISF5:1;
  unsigned TRISF6:1;
  unsigned TRISF7:1;
} TRISFbits;
extern volatile near unsigned char       DDRG;
extern volatile near struct {
  unsigned RG0:1;
  unsigned RG1:1;
  unsigned RG2:1;
  unsigned RG3:1;
  unsigned RG4:1;
  unsigned RG5:1;
  unsigned RG6:1;
  unsigned RG7:1;
} DDRGbits;
extern volatile near unsigned char       TRISG;
extern volatile near struct {
  unsigned TRISG0:1;
  unsigned TRISG1:1;
  unsigned TRISG2:1;
  unsigned TRISG3:1;
  unsigned TRISG4:1;
  unsigned TRISG5:1;
  unsigned TRISG6:1;
  unsigned TRISG7:1;
} TRISGbits;
extern volatile near unsigned char       DDRH;
extern volatile near struct {
  unsigned RH0:1;
  unsigned RH1:1;
  unsigned RH2:1;
  unsigned RH3:1;
  unsigned RH4:1;
  unsigned RH5:1;
  unsigned RH6:1;
  unsigned RH7:1;
} DDRHbits;
extern volatile near unsigned char       TRISH;
extern volatile near struct {
  unsigned TRISH0:1;
  unsigned TRISH1:1;
  unsigned TRISH2:1;
  unsigned TRISH3:1;
  unsigned TRISH4:1;
  unsigned TRISH5:1;
  unsigned TRISH6:1;
  unsigned TRISH7:1;
} TRISHbits;
extern volatile near unsigned char       DDRJ;
extern volatile near struct {
  unsigned RJ0:1;
  unsigned RJ1:1;
  unsigned RJ2:1;
  unsigned RJ3:1;
  unsigned RJ4:1;
  unsigned RJ5:1;
  unsigned RJ6:1;
  unsigned RJ7:1;
} DDRJbits;
extern volatile near unsigned char       TRISJ;
extern volatile near struct {
  unsigned TRISJ0:1;
  unsigned TRISJ1:1;
  unsigned TRISJ2:1;
  unsigned TRISJ3:1;
  unsigned TRISJ4:1;
  unsigned TRISJ5:1;
  unsigned TRISJ6:1;
  unsigned TRISJ7:1;
} TRISJbits;
extern volatile near unsigned char       OSCTUNE;
extern volatile near struct {
  unsigned :4;
  unsigned PPRE:1;
  unsigned PPST0:1;
  unsigned PLLEN:1;
  unsigned PPST1:1;
} OSCTUNEbits;
extern volatile near unsigned char       MEMCON;
extern volatile near struct {
  unsigned WM0:1;
  unsigned WM1:1;
  unsigned :2;
  unsigned WAIT0:1;
  unsigned WAIT1:1;
  unsigned :1;
  unsigned EBDIS:1;
} MEMCONbits;
extern volatile near unsigned char       PIE1;
extern volatile near union {
  struct {
    unsigned TMR1IE:1;
    unsigned TMR2IE:1;
    unsigned CCP1IE:1;
    unsigned SSPIE:1;
    unsigned TXIE:1;
    unsigned RCIE:1;
    unsigned ADIE:1;
    unsigned PSPIE:1;
  };
  struct {
    unsigned :3;
    unsigned SSP1IE:1;
    unsigned TX1IE:1;
    unsigned RC1IE:1;
  };
} PIE1bits;
extern volatile near unsigned char       PIR1;
extern volatile near union {
  struct {
    unsigned TMR1IF:1;
    unsigned TMR2IF:1;
    unsigned CCP1IF:1;
    unsigned SSPIF:1;
    unsigned TXIF:1;
    unsigned RCIF:1;
    unsigned ADIF:1;
    unsigned PSPIF:1;
  };
  struct {
    unsigned :3;
    unsigned SSP1IF:1;
    unsigned TX1IF:1;
    unsigned RC1IF:1;
  };
} PIR1bits;
extern volatile near unsigned char       IPR1;
extern volatile near union {
  struct {
    unsigned TMR1IP:1;
    unsigned TMR2IP:1;
    unsigned CCP1IP:1;
    unsigned SSPIP:1;
    unsigned TXIP:1;
    unsigned RCIP:1;
    unsigned ADIP:1;
    unsigned PSPIP:1;
  };
  struct {
    unsigned :3;
    unsigned SSP1IP:1;
    unsigned TX1IP:1;
    unsigned RC1IP:1;
  };
} IPR1bits;
extern volatile near unsigned char       PIE2;
extern volatile near union {
  struct {
    unsigned CCP2IE:1;
    unsigned TMR3IE:1;
    unsigned :1;
    unsigned BCLIE:1;
    unsigned :1;
    unsigned ETHIE:1;
    unsigned CMIE:1;
    unsigned OSCFIE:1;
  };
  struct {
    unsigned :3;
    unsigned BCL1IE:1;
  };
} PIE2bits;
extern volatile near unsigned char       PIR2;
extern volatile near union {
  struct {
    unsigned CCP2IF:1;
    unsigned TMR3IF:1;
    unsigned :1;
    unsigned BCLIF:1;
    unsigned :1;
    unsigned ETHIF:1;
    unsigned CMIF:1;
    unsigned OSCFIF:1;
  };
  struct {
    unsigned :3;
    unsigned BCL1IF:1;
  };
} PIR2bits;
extern volatile near unsigned char       IPR2;
extern volatile near union {
  struct {
    unsigned CCP2IP:1;
    unsigned TMR3IP:1;
    unsigned :1;
    unsigned BCLIP:1;
    unsigned :1;
    unsigned ETHIP:1;
    unsigned CMIP:1;
    unsigned OSCFIP:1;
  };
  struct {
    unsigned :3;
    unsigned BCL1IP:1;
  };
} IPR2bits;
extern volatile near unsigned char       PIE3;
extern volatile near struct {
  unsigned CCP3IE:1;
  unsigned CCP4IE:1;
  unsigned CCP5IE:1;
  unsigned TMR4IE:1;
  unsigned TX2IE:1;
  unsigned RC2IE:1;
  unsigned BCL2IE:1;
  unsigned SSP2IE:1;
} PIE3bits;
extern volatile near unsigned char       PIR3;
extern volatile near struct {
  unsigned CCP3IF:1;
  unsigned CCP4IF:1;
  unsigned CCP5IF:1;
  unsigned TMR4IF:1;
  unsigned TX2IF:1;
  unsigned RC2IF:1;
  unsigned BCL2IF:1;
  unsigned SSP2IF:1;
} PIR3bits;
extern volatile near unsigned char       IPR3;
extern volatile near struct {
  unsigned CCP3IP:1;
  unsigned CCP4IP:1;
  unsigned CCP5IP:1;
  unsigned TMR4IP:1;
  unsigned TX2IP:1;
  unsigned RC2IP:1;
  unsigned BCL2IP:1;
  unsigned SSP2IP:1;
} IPR3bits;
extern volatile near unsigned char       EECON1;
extern volatile near struct {
  unsigned :1;
  unsigned WR:1;
  unsigned WREN:1;
  unsigned WRERR:1;
  unsigned FREE:1;
} EECON1bits;
extern volatile near unsigned char       EECON2;
extern volatile near unsigned char       RCSTA;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
} RCSTAbits;
extern volatile near unsigned char       RCSTA1;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
} RCSTA1bits;
extern volatile near unsigned char       TXSTA;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
} TXSTAbits;
extern volatile near unsigned char       TXSTA1;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
} TXSTA1bits;
extern volatile near unsigned char       TXREG;
extern volatile near unsigned char       TXREG1;
extern volatile near unsigned char       RCREG;
extern volatile near unsigned char       RCREG1;
extern volatile near unsigned char       SPBRG;
extern volatile near unsigned char       SPBRG1;
extern volatile near unsigned char       PSPCON;
extern volatile near struct {
  unsigned :4;
  unsigned PSPMODE:1;
  unsigned IBOV:1;
  unsigned OBF:1;
  unsigned IBF:1;
} PSPCONbits;
extern volatile near unsigned char       T3CON;
extern volatile near union {
  struct {
    unsigned TMR3ON:1;
    unsigned TMR3CS:1;
    unsigned T3SYNC:1;
    unsigned T3CCP1:1;
    unsigned T3CKPS0:1;
    unsigned T3CKPS1:1;
    unsigned T3CCP2:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T3INSYNC:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_T3SYNC:1;
  };
} T3CONbits;
extern volatile near unsigned char       TMR3L;
extern volatile near unsigned char       TMR3H;
extern volatile near unsigned char       CMCON;
extern volatile near struct {
  unsigned CM0:1;
  unsigned CM1:1;
  unsigned CM2:1;
  unsigned CIS:1;
  unsigned C1INV:1;
  unsigned C2INV:1;
  unsigned C1OUT:1;
  unsigned C2OUT:1;
} CMCONbits;
extern volatile near unsigned char       CVRCON;
extern volatile near struct {
  unsigned CVR0:1;
  unsigned CVR1:1;
  unsigned CVR2:1;
  unsigned CVR3:1;
  unsigned CVRSS:1;
  unsigned CVRR:1;
  unsigned CVROE:1;
  unsigned CVREN:1;
} CVRCONbits;
extern volatile near unsigned char       ECCP1AS;
extern volatile near union {
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSS1BD0:1;
    unsigned PSS1BD1:1;
    unsigned PSS1AC0:1;
    unsigned PSS1AC1:1;
    unsigned ECCP1AS0:1;
    unsigned ECCP1AS1:1;
    unsigned ECCP1AS2:1;
    unsigned ECCP1ASE:1;
  };
} ECCP1ASbits;
extern volatile near unsigned char       CCP3CON;
extern volatile near union {
  struct {
    unsigned CCP3M0:1;
    unsigned CCP3M1:1;
    unsigned CCP3M2:1;
    unsigned CCP3M3:1;
    unsigned DC3B0:1;
    unsigned DC3B1:1;
    unsigned P3M0:1;
    unsigned P3M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP3Y:1;
    unsigned CCP3X:1;
  };
} CCP3CONbits;
extern volatile near unsigned char       ECCP3CON;
extern volatile near union {
  struct {
    unsigned CCP3M0:1;
    unsigned CCP3M1:1;
    unsigned CCP3M2:1;
    unsigned CCP3M3:1;
    unsigned DC3B0:1;
    unsigned DC3B1:1;
    unsigned P3M0:1;
    unsigned P3M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP3Y:1;
    unsigned CCP3X:1;
  };
} ECCP3CONbits;
extern volatile near unsigned            CCPR3;
extern volatile near unsigned char       CCPR3L;
extern volatile near unsigned char       CCPR3H;
extern volatile near unsigned char       CCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP2Y:1;
    unsigned CCP2X:1;
  };
} CCP2CONbits;
extern volatile near unsigned char       ECCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP2Y:1;
    unsigned CCP2X:1;
  };
} ECCP2CONbits;
extern volatile near unsigned            CCPR2;
extern volatile near unsigned char       CCPR2L;
extern volatile near unsigned char       CCPR2H;
extern volatile near unsigned char       CCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP1Y:1;
    unsigned CCP1X:1;
  };
} CCP1CONbits;
extern volatile near unsigned char       ECCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP1Y:1;
    unsigned CCP1X:1;
  };
} ECCP1CONbits;
extern volatile near unsigned            CCPR1;
extern volatile near unsigned char       CCPR1L;
extern volatile near unsigned char       CCPR1H;
extern volatile near unsigned char       ADCON2;
extern volatile near struct {
  unsigned ADCS0:1;
  unsigned ADCS1:1;
  unsigned ADCS2:1;
  unsigned ACQT0:1;
  unsigned ACQT1:1;
  unsigned ACQT2:1;
  unsigned :1;
  unsigned ADFM:1;
} ADCON2bits;
extern volatile near unsigned char       ADCON1;
extern volatile near struct {
  unsigned PCFG0:1;
  unsigned PCFG1:1;
  unsigned PCFG2:1;
  unsigned PCFG3:1;
  unsigned VCFG0:1;
  unsigned VCFG1:1;
} ADCON1bits;
extern volatile near unsigned char       ADCON0;
extern volatile near union {
  struct {
    unsigned :1;
    unsigned DONE:1;
    unsigned :5;
    unsigned ADCAL:1;
  };
  struct {
    unsigned :1;
    unsigned GO_DONE:1;
  };
  struct {
    unsigned ADON:1;
    unsigned GO:1;
    unsigned CHS0:1;
    unsigned CHS1:1;
    unsigned CHS2:1;
    unsigned CHS3:1;
  };
  struct {
    unsigned :1;
    unsigned NOT_DONE:1;
  };
} ADCON0bits;
extern volatile near unsigned            ADRES;
extern volatile near unsigned char       ADRESL;
extern volatile near unsigned char       ADRESH;
extern volatile near unsigned char       SSP1CON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK:5;
  };
} SSP1CON2bits;
extern volatile near unsigned char       SSPCON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK:5;
  };
} SSPCON2bits;
extern volatile near unsigned char       SSP1CON1;
extern volatile near struct {
  unsigned SSPM0:1;
  unsigned SSPM1:1;
  unsigned SSPM2:1;
  unsigned SSPM3:1;
  unsigned CKP:1;
  unsigned SSPEN:1;
  unsigned SSPOV:1;
  unsigned WCOL:1;
} SSP1CON1bits;
extern volatile near unsigned char       SSPCON1;
extern volatile near struct {
  unsigned SSPM0:1;
  unsigned SSPM1:1;
  unsigned SSPM2:1;
  unsigned SSPM3:1;
  unsigned CKP:1;
  unsigned SSPEN:1;
  unsigned SSPOV:1;
  unsigned WCOL:1;
} SSPCON1bits;
extern volatile near unsigned char       SSP1STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSP1STATbits;
extern volatile near unsigned char       SSPSTAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSPSTATbits;
extern volatile near unsigned char       SSP1ADD;
extern volatile near unsigned char       SSPADD;
extern volatile near unsigned char       SSP1BUF;
extern volatile near unsigned char       SSPBUF;
extern volatile near unsigned char       T2CON;
extern volatile near struct {
  unsigned T2CKPS0:1;
  unsigned T2CKPS1:1;
  unsigned TMR2ON:1;
  unsigned T2OUTPS0:1;
  unsigned T2OUTPS1:1;
  unsigned T2OUTPS2:1;
  unsigned T2OUTPS3:1;
} T2CONbits;
extern volatile near unsigned char       PR2;
extern volatile near unsigned char       TMR2;
extern volatile near unsigned char       T1CON;
extern volatile near union {
  struct {
    unsigned TMR1ON:1;
    unsigned TMR1CS:1;
    unsigned T1SYNC:1;
    unsigned T1OSCEN:1;
    unsigned T1CKPS0:1;
    unsigned T1CKPS1:1;
    unsigned T1RUN:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T1INSYNC:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_T1SYNC:1;
  };
} T1CONbits;
extern volatile near unsigned char       TMR1L;
extern volatile near unsigned char       TMR1H;
extern volatile near unsigned char       RCON;
extern volatile near union {
  struct {
    unsigned NOT_BOR:1;
    unsigned NOT_POR:1;
    unsigned NOT_PD:1;
    unsigned NOT_TO:1;
    unsigned NOT_RI:1;
    unsigned :2;
    unsigned IPEN:1;
  };
  struct {
    unsigned BOR:1;
    unsigned POR:1;
    unsigned PD:1;
    unsigned TO:1;
    unsigned RI:1;
  };
} RCONbits;
extern volatile near unsigned char       WDTCON;
extern volatile near union {
  struct {
    unsigned SWDTE:1;
  };
  struct {
    unsigned SWDTEN:1;
  };
} WDTCONbits;
extern volatile near unsigned char       ECON1;
extern volatile near struct {
  unsigned :2;
  unsigned RXEN:1;
  unsigned TXRTS:1;
  unsigned CSUMEN:1;
  unsigned DMAST:1;
  unsigned RXRST:1;
  unsigned TXRST:1;
} ECON1bits;
extern volatile near unsigned char       OSCCON;
extern volatile near struct {
  unsigned SCS0:1;
  unsigned SCS1:1;
  unsigned :1;
  unsigned OSTS:1;
  unsigned :3;
  unsigned IDLEN:1;
} OSCCONbits;
extern volatile near unsigned char       T0CON;
extern volatile near struct {
  unsigned T0PS0:1;
  unsigned T0PS1:1;
  unsigned T0PS2:1;
  unsigned PSA:1;
  unsigned T0SE:1;
  unsigned T0CS:1;
  unsigned T08BIT:1;
  unsigned TMR0ON:1;
} T0CONbits;
extern volatile near unsigned char       TMR0L;
extern volatile near unsigned char       TMR0H;
extern          near unsigned char       STATUS;
extern          near struct {
  unsigned C:1;
  unsigned DC:1;
  unsigned Z:1;
  unsigned OV:1;
  unsigned N:1;
} STATUSbits;
extern          near unsigned            FSR2;
extern          near unsigned char       FSR2L;
extern          near unsigned char       FSR2H;
extern volatile near unsigned char       PLUSW2;
extern volatile near unsigned char       PREINC2;
extern volatile near unsigned char       POSTDEC2;
extern volatile near unsigned char       POSTINC2;
extern          near unsigned char       INDF2;
extern          near unsigned char       BSR;
extern          near unsigned            FSR1;
extern          near unsigned char       FSR1L;
extern          near unsigned char       FSR1H;
extern volatile near unsigned char       PLUSW1;
extern volatile near unsigned char       PREINC1;
extern volatile near unsigned char       POSTDEC1;
extern volatile near unsigned char       POSTINC1;
extern          near unsigned char       INDF1;
extern          near unsigned char       WREG;
extern          near unsigned            FSR0;
extern          near unsigned char       FSR0L;
extern          near unsigned char       FSR0H;
extern volatile near unsigned char       PLUSW0;
extern volatile near unsigned char       PREINC0;
extern volatile near unsigned char       POSTDEC0;
extern volatile near unsigned char       POSTINC0;
extern          near unsigned char       INDF0;
extern volatile near unsigned char       INTCON3;
extern volatile near union {
  struct {
    unsigned INT1F:1;
    unsigned INT2F:1;
    unsigned INT3F:1;
    unsigned INT1E:1;
    unsigned INT2E:1;
    unsigned INT3E:1;
    unsigned INT1P:1;
    unsigned INT2P:1;
  };
  struct {
    unsigned INT1IF:1;
    unsigned INT2IF:1;
    unsigned INT3IF:1;
    unsigned INT1IE:1;
    unsigned INT2IE:1;
    unsigned INT3IE:1;
    unsigned INT1IP:1;
    unsigned INT2IP:1;
  };
} INTCON3bits;
extern volatile near unsigned char       INTCON2;
extern volatile near union {
  struct {
    unsigned RBIP:1;
    unsigned INT3IP:1;
    unsigned T0IP:1;
    unsigned INTEDG3:1;
    unsigned INTEDG2:1;
    unsigned INTEDG1:1;
    unsigned INTEDG0:1;
    unsigned NOT_RBPU:1;
  };
  struct {
    unsigned :2;
    unsigned TMR0IP:1;
    unsigned :4;
    unsigned RBPU:1;
  };
} INTCON2bits;
extern volatile near unsigned char       INTCON;
extern volatile near union {
  struct {
    unsigned RBIF:1;
    unsigned INT0F:1;
    unsigned T0IF:1;
    unsigned RBIE:1;
    unsigned INT0E:1;
    unsigned T0IE:1;
    unsigned PEIE:1;
    unsigned GIE:1;
  };
  struct {
    unsigned :1;
    unsigned INT0IF:1;
    unsigned TMR0IF:1;
    unsigned :1;
    unsigned INT0IE:1;
    unsigned TMR0IE:1;
    unsigned GIEL:1;
    unsigned GIEH:1;
  };
} INTCONbits;
extern          near unsigned            PROD;
extern          near unsigned char       PRODL;
extern          near unsigned char       PRODH;
extern volatile near unsigned char       TABLAT;
extern volatile near unsigned short long TBLPTR;
extern volatile near unsigned char       TBLPTRL;
extern volatile near unsigned char       TBLPTRH;
extern volatile near unsigned char       TBLPTRU;
extern volatile near unsigned short long PC;
extern volatile near unsigned char       PCL;
extern volatile near unsigned char       PCLATH;
extern volatile near unsigned char       PCLATU;
extern volatile near unsigned char       STKPTR;
extern volatile near union {
  struct {
    unsigned STKPTR0:1;
    unsigned STKPTR1:1;
    unsigned STKPTR2:1;
    unsigned STKPTR3:1;
    unsigned STKPTR4:1;
    unsigned :1;
    unsigned STKUNF:1;
    unsigned STKOVF:1;
  };
  struct {
    unsigned SP0:1;
    unsigned SP1:1;
    unsigned SP2:1;
    unsigned SP3:1;
    unsigned SP4:1;
    unsigned :2;
    unsigned STKFUL:1;
  };
} STKPTRbits;
extern          near unsigned short long TOS;
extern          near unsigned char       TOSL;
extern          near unsigned char       TOSH;
extern          near unsigned char       TOSU;

#pragma varlocate 14 MAADR5
#pragma varlocate 14 MAADR6
#pragma varlocate 14 MAADR3
#pragma varlocate 14 MAADR4
#pragma varlocate 14 MAADR1
#pragma varlocate 14 MAADR2
#pragma varlocate 14 MISTAT
#pragma varlocate 14 MISTATbits
#pragma varlocate 14 EFLOCON
#pragma varlocate 14 EFLOCONbits
#pragma varlocate 14 EPAUS
#pragma varlocate 14 EPAUSL
#pragma varlocate 14 EPAUSH
#pragma varlocate 14 MACON1
#pragma varlocate 14 MACON1bits
#pragma varlocate 14 MACON3
#pragma varlocate 14 MACON3bits
#pragma varlocate 14 MACON4
#pragma varlocate 14 MACON4bits
#pragma varlocate 14 MABBIPG
#pragma varlocate 14 MAIPG
#pragma varlocate 14 MAIPGL
#pragma varlocate 14 MAIPGH
#pragma varlocate 14 MAMXFL
#pragma varlocate 14 MAMXFLL
#pragma varlocate 14 MAMXFLH
#pragma varlocate 14 MICMD
#pragma varlocate 14 MICMDbits
#pragma varlocate 14 MIREGADR
#pragma varlocate 14 MIWR
#pragma varlocate 14 MIWRL
#pragma varlocate 14 MIWRH
#pragma varlocate 14 MIRD
#pragma varlocate 14 MIRDL
#pragma varlocate 14 MIRDH
#pragma varlocate 14 EHT0
#pragma varlocate 14 EHT1
#pragma varlocate 14 EHT2
#pragma varlocate 14 EHT3
#pragma varlocate 14 EHT4
#pragma varlocate 14 EHT5
#pragma varlocate 14 EHT6
#pragma varlocate 14 EHT7
#pragma varlocate 14 EPMM0
#pragma varlocate 14 EPMM1
#pragma varlocate 14 EPMM2
#pragma varlocate 14 EPMM3
#pragma varlocate 14 EPMM4
#pragma varlocate 14 EPMM5
#pragma varlocate 14 EPMM6
#pragma varlocate 14 EPMM7
#pragma varlocate 14 EPMCS
#pragma varlocate 14 EPMCSL
#pragma varlocate 14 EPMCSH
#pragma varlocate 14 EPMO
#pragma varlocate 14 EPMOL
#pragma varlocate 14 EPMOH
#pragma varlocate 14 ERXFCON
#pragma varlocate 14 ERXFCONbits
#pragma varlocate 14 EPKTCNT
#pragma varlocate 14 EWRPT
#pragma varlocate 14 EWRPTL
#pragma varlocate 14 EWRPTH
#pragma varlocate 14 ETXST
#pragma varlocate 14 ETXSTL
#pragma varlocate 14 ETXSTH
#pragma varlocate 14 ETXND
#pragma varlocate 14 ETXNDL
#pragma varlocate 14 ETXNDH
#pragma varlocate 14 ERXST
#pragma varlocate 14 ERXSTL
#pragma varlocate 14 ERXSTH
#pragma varlocate 14 ERXND
#pragma varlocate 14 ERXNDL
#pragma varlocate 14 ERXNDH
#pragma varlocate 14 ERXRDPT
#pragma varlocate 14 ERXRDPTL
#pragma varlocate 14 ERXRDPTH
#pragma varlocate 14 ERXWRPT
#pragma varlocate 14 ERXWRPTL
#pragma varlocate 14 ERXWRPTH
#pragma varlocate 14 EDMAST
#pragma varlocate 14 EDMASTL
#pragma varlocate 14 EDMASTH
#pragma varlocate 14 EDMAND
#pragma varlocate 14 EDMANDL
#pragma varlocate 14 EDMANDH
#pragma varlocate 14 EDMADST
#pragma varlocate 14 EDMADSTL
#pragma varlocate 14 EDMADSTH
#pragma varlocate 14 EDMACS
#pragma varlocate 14 EDMACSL
#pragma varlocate 14 EDMACSH
#pragma varlocate 14 EIE
#pragma varlocate 14 EIEbits
#pragma varlocate 14 ESTAT
#pragma varlocate 14 ESTATbits
#pragma varlocate 14 ECON2
#pragma varlocate 14 ECON2bits


#line 2227 "C:/mcc18/h/p18f97j60.h"
 
#line 2229 "C:/mcc18/h/p18f97j60.h"
#line 2230 "C:/mcc18/h/p18f97j60.h"


#line 2233 "C:/mcc18/h/p18f97j60.h"
 
#line 2235 "C:/mcc18/h/p18f97j60.h"
#line 2236 "C:/mcc18/h/p18f97j60.h"
#line 2237 "C:/mcc18/h/p18f97j60.h"
#line 2238 "C:/mcc18/h/p18f97j60.h"

#line 2240 "C:/mcc18/h/p18f97j60.h"
#line 2241 "C:/mcc18/h/p18f97j60.h"
#line 2242 "C:/mcc18/h/p18f97j60.h"
#line 2243 "C:/mcc18/h/p18f97j60.h"
#line 2244 "C:/mcc18/h/p18f97j60.h"


#line 2248 "C:/mcc18/h/p18f97j60.h"
 
#line 2250 "C:/mcc18/h/p18f97j60.h"


#line 2253 "C:/mcc18/h/p18f97j60.h"
#line 447 "C:/mcc18/h/p18cxxx.h"

#line 449 "C:/mcc18/h/p18cxxx.h"
#line 451 "C:/mcc18/h/p18cxxx.h"
#line 453 "C:/mcc18/h/p18cxxx.h"
#line 455 "C:/mcc18/h/p18cxxx.h"
#line 457 "C:/mcc18/h/p18cxxx.h"
#line 459 "C:/mcc18/h/p18cxxx.h"
#line 461 "C:/mcc18/h/p18cxxx.h"
#line 463 "C:/mcc18/h/p18cxxx.h"
#line 465 "C:/mcc18/h/p18cxxx.h"
#line 467 "C:/mcc18/h/p18cxxx.h"
#line 469 "C:/mcc18/h/p18cxxx.h"
#line 471 "C:/mcc18/h/p18cxxx.h"
#line 473 "C:/mcc18/h/p18cxxx.h"
#line 475 "C:/mcc18/h/p18cxxx.h"
#line 477 "C:/mcc18/h/p18cxxx.h"
#line 479 "C:/mcc18/h/p18cxxx.h"
#line 481 "C:/mcc18/h/p18cxxx.h"
#line 483 "C:/mcc18/h/p18cxxx.h"
#line 485 "C:/mcc18/h/p18cxxx.h"
#line 487 "C:/mcc18/h/p18cxxx.h"
#line 489 "C:/mcc18/h/p18cxxx.h"
#line 491 "C:/mcc18/h/p18cxxx.h"
#line 493 "C:/mcc18/h/p18cxxx.h"
#line 495 "C:/mcc18/h/p18cxxx.h"
#line 497 "C:/mcc18/h/p18cxxx.h"
#line 499 "C:/mcc18/h/p18cxxx.h"
#line 501 "C:/mcc18/h/p18cxxx.h"
#line 503 "C:/mcc18/h/p18cxxx.h"
#line 505 "C:/mcc18/h/p18cxxx.h"

#line 507 "C:/mcc18/h/p18cxxx.h"
#line 62 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"

#line 64 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 66 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 68 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 71 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 75 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 79 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 83 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 87 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 91 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 95 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 100 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 105 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 106 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 107 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 109 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 113 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 115 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"

#line 1 "C:/mcc18/h/stdio.h"

#line 3 "C:/mcc18/h/stdio.h"

#line 1 "C:/mcc18/h/stdarg.h"
 


#line 5 "C:/mcc18/h/stdarg.h"

typedef void* va_list;
#line 8 "C:/mcc18/h/stdarg.h"
#line 9 "C:/mcc18/h/stdarg.h"
#line 10 "C:/mcc18/h/stdarg.h"
#line 11 "C:/mcc18/h/stdarg.h"
#line 12 "C:/mcc18/h/stdarg.h"
#line 4 "C:/mcc18/h/stdio.h"

#line 1 "C:/mcc18/h/stddef.h"
 

#line 4 "C:/mcc18/h/stddef.h"

typedef unsigned char wchar_t;


#line 10 "C:/mcc18/h/stddef.h"
 
typedef signed short int ptrdiff_t;
typedef signed short int ptrdiffram_t;
typedef signed short long int ptrdiffrom_t;


#line 20 "C:/mcc18/h/stddef.h"
 
typedef unsigned short int size_t;
typedef unsigned short int sizeram_t;
typedef unsigned short long int sizerom_t;


#line 34 "C:/mcc18/h/stddef.h"
 
#line 36 "C:/mcc18/h/stddef.h"


#line 41 "C:/mcc18/h/stddef.h"
 
#line 43 "C:/mcc18/h/stddef.h"

#line 45 "C:/mcc18/h/stddef.h"
#line 5 "C:/mcc18/h/stdio.h"



#line 9 "C:/mcc18/h/stdio.h"
 
#line 11 "C:/mcc18/h/stdio.h"

#line 13 "C:/mcc18/h/stdio.h"


typedef unsigned char FILE;

 
#line 19 "C:/mcc18/h/stdio.h"
#line 20 "C:/mcc18/h/stdio.h"

extern FILE *stderr;
extern FILE *stdout;


int putc (auto char c, auto FILE *f);
int vsprintf (auto char *buf, auto const far  rom char *fmt, auto va_list ap);
int vprintf (auto const far  rom char *fmt, auto va_list ap);
int sprintf (auto char *buf, auto const far  rom char *fmt, ...);
int printf (auto const far  rom char *fmt, ...);
int fprintf (auto FILE *f, auto const far  rom char *fmt, ...);
int vfprintf (auto FILE *f, auto const far  rom char *fmt, auto va_list ap);
int puts (auto const far  rom char *s);
int fputs (auto const far  rom char *s, auto FILE *f);

#line 36 "C:/mcc18/h/stdio.h"
#line 116 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"

#line 1 "C:/mcc18/h/stdlib.h"
 

#line 4 "C:/mcc18/h/stdlib.h"

#line 6 "C:/mcc18/h/stdlib.h"

#line 9 "C:/mcc18/h/stdlib.h"
 
 

#line 16 "C:/mcc18/h/stdlib.h"
 
double atof (const auto char *s);

#line 28 "C:/mcc18/h/stdlib.h"
 
signed char atob (const auto char *s);


#line 39 "C:/mcc18/h/stdlib.h"
 
int atoi (const auto char *s);

#line 47 "C:/mcc18/h/stdlib.h"
 
long atol (const auto char *s);

#line 58 "C:/mcc18/h/stdlib.h"
 
unsigned long atoul (const auto char *s);


#line 71 "C:/mcc18/h/stdlib.h"
 
char *btoa (auto signed char value, auto char *s);

#line 83 "C:/mcc18/h/stdlib.h"
 
char *itoa (auto int value, auto char *s);

#line 95 "C:/mcc18/h/stdlib.h"
 
char *ltoa (auto long value, auto char *s);

#line 107 "C:/mcc18/h/stdlib.h"
 
char *ultoa (auto unsigned long value, auto char *s);
 


#line 112 "C:/mcc18/h/stdlib.h"
 
 

#line 116 "C:/mcc18/h/stdlib.h"
 
#line 118 "C:/mcc18/h/stdlib.h"


#line 124 "C:/mcc18/h/stdlib.h"
 
int rand (void);

#line 136 "C:/mcc18/h/stdlib.h"
 
void srand (auto unsigned int seed);
 
#line 140 "C:/mcc18/h/stdlib.h"
#line 149 "C:/mcc18/h/stdlib.h"

#line 151 "C:/mcc18/h/stdlib.h"
#line 117 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"

#line 1 "C:/mcc18/h/string.h"

#line 3 "C:/mcc18/h/string.h"

#line 7 "C:/mcc18/h/string.h"


#line 20 "C:/mcc18/h/string.h"
 
#line 22 "C:/mcc18/h/string.h"


#line 25 "C:/mcc18/h/string.h"
 
#line 27 "C:/mcc18/h/string.h"

 

#line 39 "C:/mcc18/h/string.h"
 
void *memcpy (auto void *s1, auto const void *s2, auto size_t n);


#line 55 "C:/mcc18/h/string.h"
 
void *memmove (auto void *s1, auto const void *s2, auto size_t n);


#line 67 "C:/mcc18/h/string.h"
 
char *strcpy (auto char *s1, auto const char *s2);


#line 83 "C:/mcc18/h/string.h"
 
char *strncpy (auto char *s1, auto const char *s2, auto size_t n);


#line 97 "C:/mcc18/h/string.h"
 
char *strcat (auto char *s1, auto const char *s2);


#line 113 "C:/mcc18/h/string.h"
 
char *strncat (auto char *s1, auto const char *s2, auto size_t n);


#line 128 "C:/mcc18/h/string.h"
 
signed char memcmp (auto const void *s1, auto const void *s2, auto size_t n);


#line 141 "C:/mcc18/h/string.h"
 
signed char strcmp (auto const char *s1, auto const char *s2);


#line 147 "C:/mcc18/h/string.h"
 


#line 161 "C:/mcc18/h/string.h"
 
signed char strncmp (auto const char *s1, auto const char *s2, auto size_t n);


#line 167 "C:/mcc18/h/string.h"
 


#line 183 "C:/mcc18/h/string.h"
 
void *memchr (auto const void *s, auto unsigned char c, auto size_t n);


#line 199 "C:/mcc18/h/string.h"
 
char *strchr (auto const char *s, auto unsigned char c);


#line 210 "C:/mcc18/h/string.h"
 
size_t strcspn (auto const char *s1, auto const char *s2);


#line 222 "C:/mcc18/h/string.h"
 
char *strpbrk (auto const char *s1, auto const char *s2);


#line 238 "C:/mcc18/h/string.h"
 
char *strrchr (auto const char *s, auto unsigned char c);


#line 249 "C:/mcc18/h/string.h"
 
size_t strspn (auto const char *s1, auto const char *s2);


#line 262 "C:/mcc18/h/string.h"
 
char *strstr (auto const char *s1, auto const char *s2);


#line 305 "C:/mcc18/h/string.h"
 
char *strtok (auto char *s1, auto const char *s2);


#line 321 "C:/mcc18/h/string.h"
 
void *memset (auto void *s, auto unsigned char c, auto size_t n);


#line 339 "C:/mcc18/h/string.h"
 
#line 341 "C:/mcc18/h/string.h"


#line 349 "C:/mcc18/h/string.h"
 
size_t strlen (auto const char *s);


#line 358 "C:/mcc18/h/string.h"
 
char *strupr (auto char *s);


#line 367 "C:/mcc18/h/string.h"
 
char *strlwr (auto char *s);



 

#line 379 "C:/mcc18/h/string.h"
 
far  rom void *memcpypgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 389 "C:/mcc18/h/string.h"
 
void *memcpypgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 398 "C:/mcc18/h/string.h"
 
far  rom void *memcpyram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 407 "C:/mcc18/h/string.h"
 
far  rom void *memmovepgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 417 "C:/mcc18/h/string.h"
 
void *memmovepgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 426 "C:/mcc18/h/string.h"
 
far  rom void *memmoveram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 434 "C:/mcc18/h/string.h"
 
far  rom char *strcpypgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 443 "C:/mcc18/h/string.h"
 
char *strcpypgm2ram (auto char *s1, auto const far  rom char *s2);


#line 451 "C:/mcc18/h/string.h"
 
far  rom char *strcpyram2pgm (auto far  rom char *s1, auto const char *s2);


#line 460 "C:/mcc18/h/string.h"
 
far  rom char *strncpypgm (auto far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 470 "C:/mcc18/h/string.h"
 
char *strncpypgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 479 "C:/mcc18/h/string.h"
 
far  rom char *strncpyram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 487 "C:/mcc18/h/string.h"
 
far  rom char *strcatpgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 496 "C:/mcc18/h/string.h"
 
char *strcatpgm2ram (auto char *s1, auto const far  rom char *s2);


#line 504 "C:/mcc18/h/string.h"
 
far  rom char *strcatram2pgm (auto far  rom char *s1, auto const char *s2);


#line 513 "C:/mcc18/h/string.h"
 
far  rom char *strncatpgm (auto far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 523 "C:/mcc18/h/string.h"
 
char *strncatpgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 532 "C:/mcc18/h/string.h"
 
far  rom char *strncatram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 541 "C:/mcc18/h/string.h"
 
signed char memcmppgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 551 "C:/mcc18/h/string.h"
 
signed char memcmppgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 560 "C:/mcc18/h/string.h"
 
signed char memcmpram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 568 "C:/mcc18/h/string.h"
 
signed char strcmppgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 577 "C:/mcc18/h/string.h"
 
signed char strcmppgm2ram (auto const char *s1, auto const far  rom char *s2);


#line 585 "C:/mcc18/h/string.h"
 
signed char strcmpram2pgm (auto const far  rom char *s1, auto const char *s2);


#line 594 "C:/mcc18/h/string.h"
 
signed char strncmppgm (auto const far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 604 "C:/mcc18/h/string.h"
 
signed char strncmppgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 613 "C:/mcc18/h/string.h"
 
signed char strncmpram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 622 "C:/mcc18/h/string.h"
 
far  rom char *memchrpgm (auto const far  rom char *s, auto const unsigned char c, auto sizerom_t n);


#line 631 "C:/mcc18/h/string.h"
 
far  rom char *strchrpgm (auto const far  rom char *s, auto unsigned char c);


#line 639 "C:/mcc18/h/string.h"
 
sizerom_t strcspnpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 647 "C:/mcc18/h/string.h"
 
sizerom_t strcspnpgmram (auto const far  rom char *s1, auto const char *s2);


#line 655 "C:/mcc18/h/string.h"
 
sizeram_t strcspnrampgm (auto const char *s1, auto const far  rom char *s2);


#line 663 "C:/mcc18/h/string.h"
 
far  rom char *strpbrkpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 671 "C:/mcc18/h/string.h"
 
far  rom char *strpbrkpgmram (auto const far  rom char *s1, auto const char *s2);


#line 679 "C:/mcc18/h/string.h"
 
char *strpbrkrampgm (auto const char *s1, auto const far  rom char *s2);


#line 688 "C:/mcc18/h/string.h"
 
 


#line 696 "C:/mcc18/h/string.h"
 
sizerom_t strspnpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 704 "C:/mcc18/h/string.h"
 
sizerom_t strspnpgmram (auto const far  rom char *s1, auto const char *s2);


#line 712 "C:/mcc18/h/string.h"
 
sizeram_t strspnrampgm (auto const char *s1, auto const far  rom char *s2);


#line 720 "C:/mcc18/h/string.h"
 
far  rom char *strstrpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 729 "C:/mcc18/h/string.h"
 
far  rom char *strstrpgmram (auto const far  rom char *s1, auto const char *s2);


#line 737 "C:/mcc18/h/string.h"
 
char *strstrrampgm (auto const char *s1, auto const far  rom char *s2);


#line 745 "C:/mcc18/h/string.h"
 
far  rom char *strtokpgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 754 "C:/mcc18/h/string.h"
 
char *strtokpgmram (auto char *s1, auto const far  rom char *s2);


#line 762 "C:/mcc18/h/string.h"
 
far  rom char *strtokrampgm (auto far  rom char *s1, auto const char *s2);


#line 771 "C:/mcc18/h/string.h"
 
far  rom void *memsetpgm (auto far  rom void *s, auto unsigned char c, auto sizerom_t n);


#line 778 "C:/mcc18/h/string.h"
 
far  rom char *struprpgm (auto far  rom char *s);


#line 785 "C:/mcc18/h/string.h"
 
far  rom char *strlwrpgm (auto far  rom char *s);


#line 792 "C:/mcc18/h/string.h"
 
sizerom_t strlenpgm (auto const far  rom char *s);

#line 796 "C:/mcc18/h/string.h"

#line 798 "C:/mcc18/h/string.h"

#line 805 "C:/mcc18/h/string.h"
#line 814 "C:/mcc18/h/string.h"

#line 816 "C:/mcc18/h/string.h"
#line 118 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"




#line 123 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 126 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 129 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 130 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 131 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 132 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 135 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"



#line 139 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 149 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"




#line 154 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 155 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"

#line 157 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"

	
#line 160 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 161 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 162 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
	
	
#line 165 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 171 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
    


#line 175 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 179 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 182 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 185 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 194 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 196 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 197 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 198 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"



#line 202 "D:/Work/datakrat/PIC-MAXI-WEB/PIC-MAXI-WEB_5_31/Microchip/Include/Compiler.h"
#line 55 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"



#line 59 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 60 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"









#line 70 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"






#line 76 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 77 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 78 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 79 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
	




#line 85 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 86 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 89 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 91 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 94 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 96 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 98 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 100 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 101 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"


#line 104 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 105 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 106 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 108 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 110 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 112 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 115 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 121 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 124 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 127 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 130 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 133 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 138 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 140 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 141 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 145 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 151 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 156 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 158 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 159 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"



#line 163 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
	
#line 165 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 166 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 167 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 168 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 169 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 173 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 177 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 178 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 183 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 188 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 193 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 198 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 203 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"


#line 206 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 344 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 346 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 348 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 458 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 460 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 462 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 562 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 564 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 566 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 634 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 746 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 792 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 800 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 807 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 848 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 850 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 852 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 865 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 868 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 871 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 872 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 884 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 895 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 906 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 907 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

#line 914 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 916 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 921 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 928 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 929 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 934 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 935 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 941 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 954 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 966 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 975 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 983 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 991 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 998 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1007 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1071 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1084 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1088 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1101 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1103 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1108 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1115 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1123 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1125 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1127 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1140 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1144 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1157 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1159 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1164 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1171 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1182 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1185 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1186 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1188 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1273 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1449 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1595 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1684 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1686 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

	
#line 1689 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
	
	
#line 1692 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1693 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1694 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1695 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1696 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1697 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1698 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1699 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1700 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1701 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1702 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1703 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1704 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1705 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

	 
#line 1708 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1709 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1710 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1711 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

#line 1713 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1714 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1715 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1716 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1717 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1718 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1719 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1720 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1721 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1722 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1723 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1724 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"


	
#line 1728 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1729 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

#line 1731 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1732 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1733 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1734 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1735 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1736 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1737 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1738 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1739 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1740 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1741 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

	
#line 1744 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1745 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1746 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1747 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1748 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1749 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1750 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1751 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1752 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1753 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1754 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1755 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

	
#line 1758 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1759 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1760 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1761 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1762 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1763 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1764 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1765 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

	



























#line 1795 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1798 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1800 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"


#line 1803 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
	
	
	
#line 1807 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1808 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1809 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1810 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1811 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1812 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1813 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1814 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1815 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1816 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1817 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1818 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"

#line 1820 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1823 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1834 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1850 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1852 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1854 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 1858 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"


#line 1861 "Alternative Configurations/HardwareProfile PICDEMNET2_INTERNAL_ETHERNET.h"
#line 65 "HardwareProfile.h"

#line 67 "HardwareProfile.h"
#line 70 "HardwareProfile.h"
#line 73 "HardwareProfile.h"
#line 76 "HardwareProfile.h"
#line 79 "HardwareProfile.h"
#line 82 "HardwareProfile.h"
#line 85 "HardwareProfile.h"
#line 89 "HardwareProfile.h"
#line 90 "HardwareProfile.h"
#line 93 "HardwareProfile.h"
#line 96 "HardwareProfile.h"
#line 97 "HardwareProfile.h"
#line 100 "HardwareProfile.h"
#line 102 "HardwareProfile.h"
#line 104 "HardwareProfile.h"
#line 106 "HardwareProfile.h"
#line 107 "HardwareProfile.h"
#line 109 "HardwareProfile.h"
#line 110 "HardwareProfile.h"
#line 113 "HardwareProfile.h"
#line 116 "HardwareProfile.h"
#line 119 "HardwareProfile.h"
#line 122 "HardwareProfile.h"
#line 123 "HardwareProfile.h"
#line 124 "HardwareProfile.h"
#line 127 "HardwareProfile.h"
#line 130 "HardwareProfile.h"
#line 133 "HardwareProfile.h"
#line 134 "HardwareProfile.h"
#line 135 "HardwareProfile.h"
#line 137 "HardwareProfile.h"
#line 139 "HardwareProfile.h"
#line 141 "HardwareProfile.h"
#line 142 "HardwareProfile.h"
#line 145 "HardwareProfile.h"
#line 148 "HardwareProfile.h"
#line 150 "HardwareProfile.h"
#line 153 "HardwareProfile.h"
#line 156 "HardwareProfile.h"
#line 159 "HardwareProfile.h"
#line 160 "HardwareProfile.h"
#line 163 "HardwareProfile.h"
#line 166 "HardwareProfile.h"
#line 168 "HardwareProfile.h"
#line 171 "HardwareProfile.h"
#line 174 "HardwareProfile.h"
#line 177 "HardwareProfile.h"
#line 178 "HardwareProfile.h"
#line 181 "HardwareProfile.h"
#line 184 "HardwareProfile.h"
#line 186 "HardwareProfile.h"
#line 189 "HardwareProfile.h"
#line 192 "HardwareProfile.h"
#line 195 "HardwareProfile.h"
#line 196 "HardwareProfile.h"
#line 199 "HardwareProfile.h"
#line 201 "HardwareProfile.h"

#line 43 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"



#line 47 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 100 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 120 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 157 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 189 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 405 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 480 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 623 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 656 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 705 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 729 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 758 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 769 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 786 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

#line 871 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"
#line 919 "D:\Work\datakrat\PIC-MAXI-WEB\PIC-MAXI-WEB_5_31\Microchip\TCPIP Stack\ETHPIC32ExtPhy.c"

