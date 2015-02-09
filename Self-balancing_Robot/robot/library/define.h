#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <avr/io.h>
#include <avr/interrupt.h>

typedef signed char int8;
typedef unsigned char uint8;
typedef signed int int16;
typedef unsigned int uint16;
typedef signed long int32;
typedef unsigned long uint32;
typedef unsigned char boolean;

#define MCLK			16000000UL

#ifndef NULL
#define NULL			0
#endif

#ifndef TRUE
#define TRUE			1
#endif

#ifndef FALSE
#define FALSE			0
#endif

#define ex(n)			(0x01 << (n))
#define rex(n)			(~ex(n))

#define FIXED_DIV		16

#endif
