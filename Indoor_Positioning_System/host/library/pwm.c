#include "pin.h"
#include "pwm.h"

void pwmInit(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(6);

	/* peripheral clock, 100 MHz */
	LPC_SC->PCLKSEL0 &= rex(13);
	LPC_SC->PCLKSEL0 |= ex(12);

	/* PWM1 pin configuration */
	pinSel(2, 0, 1);
	pinMode(2, 0, 0);
	pinModeOD(2, 0, 0);

	/* PWM2 pin configuration */
	pinSel(2, 1, 1);
	pinMode(2, 1, 0);
	pinModeOD(2, 1, 0);

	/* PWM3 pin configuration */
	pinSel(2, 2, 1);
	pinMode(2, 2, 0);
	pinModeOD(2, 2, 0);

	/* PWM4 pin configuration */
	pinSel(2, 3, 1);
	pinMode(2, 3, 0);
	pinModeOD(2, 3, 0);

	/* PWM5 pin configuration */
	pinSel(2, 4, 1);
	pinMode(2, 4, 0);
	pinModeOD(2, 4, 0);

	/* PWM6 pin configuration */
	pinSel(2, 5, 1);
	pinMode(2, 5, 0);
	pinModeOD(2, 5, 0);

	/* 50 Hz, resolution 16000 */
	LPC_PWM1->PR = 125;
	LPC_PWM1->MR0 = 16000;
	LPC_PWM1->MR1 = 14910;
	LPC_PWM1->MR2 = 14780;
	LPC_PWM1->MR3 = 1120;
	LPC_PWM1->MR4 = 1150;
	LPC_PWM1->MR5 = 1170;
	LPC_PWM1->MR6 = 1220;
	LPC_PWM1->LER = 0x7F;

	/* PWM configuration */
	LPC_PWM1->CTCR = 0x00;
	LPC_PWM1->MCR = 0x02;
	LPC_PWM1->CCR = 0x00;
	LPC_PWM1->PCR = 0x7E00;

	/* clear interrupt */
	LPC_PWM1->IR = 0x073F;

	/* enable PWM */
	LPC_PWM1->TCR |= ex(3);

	/* reset counter */
	LPC_PWM1->TCR |= ex(1);
	LPC_PWM1->TCR &= rex(1);

	/* enable counter */
	LPC_PWM1->TCR |= ex(0);
}

void pwm1Write(uint16 value)
{
	LPC_PWM1->MR1 = value;
}

void pwm2Write(uint16 value)
{
	LPC_PWM1->MR2 = value;
}

void pwm3Write(uint16 value)
{
	LPC_PWM1->MR3 = value;
}

void pwm4Write(uint16 value)
{
	LPC_PWM1->MR4 = value;
}

void pwm5Write(uint16 value)
{
	LPC_PWM1->MR5 = value;
}

void pwm6Write(uint16 value)
{
	LPC_PWM1->MR6 = value;
}

void pwmLatchEnable(uint8 bitEnable)
{
	LPC_PWM1->LER = bitEnable;
}
