#include "pin.h"

void pinSel(uint8 port, uint8 pin, uint8 func)
{
	uint32 address;
	uint32 mask;

	address = 0x4002C000 + (port << 3) + ((pin & 0x10) >> 2);
	pin &= 0x0F;
	mask = 0x03;
	mask = ~(mask << (pin << 1));
	*((uint32 *)address) &= mask;
	mask = (uint32)func;
	mask = mask << (pin << 1);
	*((uint32 *)address) |= mask;
}

void pinMode(uint8 port, uint8 pin, uint8 func)
{
	uint32 address;
	uint32 mask;

	address = 0x4002C040 + (port << 3) + ((pin & 0x10) >> 2);
	pin &= 0x0F;
	mask = 0x03;
	mask = ~(mask << (pin << 1));
	*((uint32 *)address) &= mask;
	mask = (uint32)func;
	mask = mask << (pin << 1);
	*((uint32 *)address) |= mask;
}

void pinModeOD(uint8 port, uint8 pin, uint8 func)
{
	uint32 address;

	address = 0x4002C068 + (port << 2);
	if (func == 0x00) {
		*((uint32 *)address) &= rex(pin);
	} else {
		*((uint32 *)address) |= ex(pin);
	}
}
