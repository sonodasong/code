#ifndef __UART0_PENDING_H__
#define __UART0_PENDING_H__

#include "define.h"

extern char hexTable[];

void uart0PendingInit(void);
void uart0PendingPrint(char *str);
void uart0PendingByte(uint8 byte);
void uart0PendingHex8(uint8 hex8);
void uart0PendingHex16(uint16 hex16);
void uart0PendingHex32(uint32 hex32);
void uart0PendingLongInt(uint32 x);

#endif
