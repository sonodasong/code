#include "rgb.h"

static uint8 rgbState = 0x01;

void rgbInit(void)
{
	/* red pin configuration */
	pinSel(0, 23, 0);
	pinMode(0, 23, 0);
	pinModeOD(0, 23, 0);
	LPC_GPIO0->FIOMASK &= rex(23);
	LPC_GPIO0->FIODIR |= ex(23);

	/* green pin configuration */
	pinSel(0, 25, 0);
	pinMode(0, 25, 0);
	pinModeOD(0, 25, 0);
	LPC_GPIO0->FIOMASK &= rex(25);
	LPC_GPIO0->FIODIR |= ex(25);

	/* green pin configuration */
	pinSel(0, 26, 0);
	pinMode(0, 26, 0);
	pinModeOD(0, 26, 0);
	LPC_GPIO0->FIOMASK &= rex(26);
	LPC_GPIO0->FIODIR |= ex(26);
}

void rgbUpdate(uint8 color)
{
	OS_CPU_SR  cpu_sr;

	OS_ENTER_CRITICAL();
	rgbState = color;
	OS_EXIT_CRITICAL();
}

void rgbTask(void *pdata)
{
	OS_CPU_SR  cpu_sr;
	uint8 temp;

	(void)pdata;
	while (1) {
		OS_ENTER_CRITICAL();
		temp = rgbState;
		OS_EXIT_CRITICAL();
		if (temp & ex(0)) {
			LPC_GPIO0->FIOSET = ex(23);
		}
		if (temp & ex(1)) {
			LPC_GPIO0->FIOSET = ex(25);
		}
		if (temp & ex(2)) {
			LPC_GPIO0->FIOSET = ex(26);
		}
		OSTimeDly(50);
		LPC_GPIO0->FIOCLR = ex(23) | ex(25) | ex(26);
		OSTimeDly(950);
	}
}
