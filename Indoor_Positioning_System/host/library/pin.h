#ifndef __PIN_H__
#define __PIN_H__

#include "define.h"

void pinSel(uint8 port, uint8 pin, uint8 func);
void pinMode(uint8 port, uint8 pin, uint8 func);
void pinModeOD(uint8 port, uint8 pin, uint8 func);

#endif
