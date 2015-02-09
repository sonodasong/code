#include "i2c1.h"
#include "oled_port.h"

#define OLED_ADDRESS		0x3C

void oledCmdW0(uint8 cmd)
{
	i2c1RegWIgnoreNAck(OLED_ADDRESS, 0x00, &cmd, 1);
}

void oledCmdW1(uint8 cmd, uint8 byte)
{
	uint8 buf[2];
	
	buf[0] = cmd;
	buf[1] = byte;
	i2c1RegWIgnoreNAck(OLED_ADDRESS, 0x00, buf, 2);
}

void oledDataByteW(uint8 byte)
{
	i2c1RegWIgnoreNAck(OLED_ADDRESS, 0x40, &byte, 1);
}

void oledDataBufW(uint8 *buf, uint8 size)
{
	i2c1RegWIgnoreNAck(OLED_ADDRESS, 0x40, buf, size);
}
