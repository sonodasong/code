#include "joystick.h"

/**
 * bit 4: button
 * bit 3: up
 * bit 2: down
 * bit 1: left
 * bit 0: right
 */
static uint8 joystickState = 0x00;

void joystickInit(void)
{
	pinSel(2, 1, 0);
	pinMode(2, 1, 0);
	pinModeOD(2, 1, 0);
	LPC_GPIO2->FIOMASK &= rex(1);
	LPC_GPIO2->FIODIR &= rex(1);
}

uint8 joystickRead(void)
{
	OS_CPU_SR  cpu_sr;
	uint8 temp;

	OS_ENTER_CRITICAL();
	temp = joystickState;
	joystickState = 0x00;
	OS_EXIT_CRITICAL();
	return temp;
}

void joystickTask(void *pdata)
{
	static uint16 adc0 = 0x0800;
	static uint16 adc1 = 0x0800;
	static uint8 prevJoystick = 0x00;
	OS_CPU_SR  cpu_sr;
	uint16 adcTemp0;
	uint16 adcTemp1;
	uint8 curJoystick;

	(void)pdata;
	curJoystick = 0x00;
	while (1) {
		adcPend();
		adcTemp0 = adcRead0();
		adcTemp1 = adcRead1();
		adcPost();
		adc0 += (adcTemp0 >> 2) - (adc0 >> 2);		//exponential filter
		adc1 += (adcTemp1 >> 2) - (adc1 >> 2);		//exponential filter
		if (adc0 > 0x0F00) {
			curJoystick |= JOYSTICK_RIGHT;
		} else if (adc0 < 0x0A00) {
			curJoystick &= ~JOYSTICK_RIGHT;
		}
		if (adc0 < 0x0100) {
			curJoystick |= JOYSTICK_LEFT;
		} else if (adc0 > 0x0600) {
			curJoystick &= ~JOYSTICK_LEFT;
		}
		if (adc1 > 0x0F00) {
			curJoystick |= JOYSTICK_DOWN;
		} else if (adc1 < 0x0A00) {
			curJoystick &= ~JOYSTICK_DOWN;
		}
		if (adc1 < 0x0100) {
			curJoystick |= JOYSTICK_UP;
		} else if (adc1 > 0x0600) {
			curJoystick &= ~JOYSTICK_UP;
		}
		if (LPC_GPIO2->FIOPIN & ex(1)) {
			curJoystick &= ~JOYSTICK_BUTTON;
		} else {
			curJoystick |= JOYSTICK_BUTTON;
		}
		OS_ENTER_CRITICAL();
		joystickState |= (~prevJoystick) & curJoystick;
		OS_EXIT_CRITICAL();
		prevJoystick = curJoystick;
		OSTimeDly(10);
	}
}
