#include "mouse.h"

static uint8 mouseButton;

void mouseInit(void)
{
	/* right pin configuration */
	pinSel(2, 2, 0);
	pinMode(2, 2, 0);
	pinModeOD(2, 2, 0);
	LPC_GPIO2->FIOMASK &= rex(2);
	LPC_GPIO2->FIODIR &= rex(2);

	/* left pin configuration */
	pinSel(2, 5, 0);
	pinMode(2, 5, 0);
	pinModeOD(2, 5, 0);
	LPC_GPIO2->FIOMASK &= rex(5);
	LPC_GPIO2->FIODIR &= rex(5);
}

void mouseRead(uint8 *buf)
{
	OS_CPU_SR  cpu_sr;
	uint8 temp;

	OS_ENTER_CRITICAL();
	temp = mouseButton;
	OS_EXIT_CRITICAL();
	buf[0] = temp;
	buf[1] = 0;
}

void mouseTask(void *pdata)
{
	OS_CPU_SR  cpu_sr;
	uint8 temp;

	(void)pdata;
	temp = 0x00;
	while (1) {
		if (LPC_GPIO2->FIOPIN & ex(2)) {
			temp &= rex(1);
		} else {
			temp |= ex(1);
		}
		if (LPC_GPIO2->FIOPIN & ex(5)) {
			temp &= rex(0);
		} else {
			temp |= ex(0);
		}
		OS_ENTER_CRITICAL();
		mouseButton = temp;
		OS_EXIT_CRITICAL();
		OSTimeDly(10);
	}
}
