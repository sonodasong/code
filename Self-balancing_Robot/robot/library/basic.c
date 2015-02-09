#include "basic.h"

void enablePullup(void)
{
	MCUCR &= rex(PUD);
}

void disablePullup(void)
{
	MCUCR |= ex(PUD);
}

void delayms(uint16 x)
{
	uint16 i, j;
	
	for (i = x; i > 0; i--) {
		for (j = 0; j < 3994; j++);
	}
}

void ledInit(void)
{
	DDRH |= ex(4);
}

void ledOn(void)
{
	PORTH |= ex(4);
}

void ledOff(void)
{
	PORTH &= rex(4);
}

void ledToggle(void)
{
	if (PINH & ex(4)) {
		PORTH &= rex(4);
	} else {
		PORTH |= ex(4);
	}
}
