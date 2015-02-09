#ifndef __USART0_H__
#define __USART0_H__

#include "define.h"

#define USART0_RX_EOF			'\r'

/* queue size is 2 ^ UART0_RX_Q_SIZE */
#define USART0_RX_Q_SIZE		5
/* buffer size is 2 ^ UART0_RX_SIZE */
#define USART0_RX_SIZE			4

void usart0Init(void);
void usart0Print(char *str);
void usart0Bit8(uint8 bit8);
void usart0Bit16(uint16 bit16);
void usart0Bit32(uint32 bit32);
void usart0Hex8(uint8 hex8);
void usart0Hex16(uint16 hex16);
void usart0Hex32(uint32 hex32);
void usart0LongInt(uint32 x);
boolean usart0RxAvailable(void);
char *usart0Read(void);

#endif
