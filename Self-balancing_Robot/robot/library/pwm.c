#include "pwm.h"

void pwmInit(void)
{
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	ICR1 = 499;
	TCCR1A = 0xA2;
	TCCR1B = 0x1A;
	TCCR1C = 0x00;
	TIFR1 = ex(ICF1);
	TIMSK1 = ex(ICIE1);
	DDRB |= ex(5) | ex(6);
}

void pwm1A(uint16 dutyCycle)
{
	OCR1A = 499 - dutyCycle;
}

void pwm1B(uint16 dutyCycle)
{
	OCR1B = 499 - dutyCycle;
}
