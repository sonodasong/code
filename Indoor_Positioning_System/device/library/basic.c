#include "pin.h"
#include "basic.h"

void ledInit(void)
{
	pinSel(0, 22, 0);
	pinMode(0, 22, 0);
	pinModeOD(0, 22, 0);
	LPC_GPIO0->FIOMASK &= rex(22);
	LPC_GPIO0->FIODIR |= ex(22);
}

void ledOn(void)
{
	LPC_GPIO0->FIOSET = ex(22);
}

void ledOff(void)
{
	LPC_GPIO0->FIOCLR = ex(22);
}

void ledToggle(void)
{
	if (LPC_GPIO0->FIOPIN & ex(22)) {
		LPC_GPIO0->FIOCLR = ex(22);
	} else {
		LPC_GPIO0->FIOSET = ex(22);
	}
}

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
	return toLow + (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow);
}

float constrain(float value, float low, float high)
{
	if (value < low) {
		value = low;
	} else if (value > high) {
		value = high;
	}
	return value;
}
