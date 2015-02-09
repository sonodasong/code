#include "basic.h"
#include "pin.h"

static uint8 ledState;

void ledInit(uint8 num)
{
	pinSel(2, num, 0);
	pinMode(2, num, 0);
	pinModeOD(2, num, 0);
	LPC_GPIO2->FIOMASK &= rex(num);
	LPC_GPIO2->FIODIR |= ex(num);
	LPC_GPIO2->FIOSET = ex(num);
	ledState |= ex(num);
}

void ledOn(uint8 num)
{
	LPC_GPIO2->FIOSET = ex(num);
	ledState |= ex(num);
}

void ledOff(uint8 num)
{
	LPC_GPIO2->FIOCLR = ex(num);
	ledState &= rex(num);
}

void ledToggle(uint8 num)
{
	if (ledState & ex(num)) {
		ledOff(num);
	} else {
		ledOn(num);
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

boolean floatEqual(float x, float y)
{
	if ((x < y + 0.00000001) && (y < x + 0.00000001)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
