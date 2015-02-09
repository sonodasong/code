#ifndef __OLED_PORT_H__
#define __OLED_PORT_H__

#include "define.h"

void oledCmdW0(uint8 cmd);
void oledCmdW1(uint8 cmd, uint8 byte);
void oledDataByteW(uint8 byte);
void oledDataBufW(uint8 *buf, uint8 size);

#endif
