#include "filter.h"
#include "motor.h"
#include "pwm.h"

void motorInit(void)
{
	// left wheel
	DDRH |= ex(5) | ex(6);
	PORTH &= rex(5) & rex(6);
	// right wheel
	DDRB |= ex(4) | ex(7);
	PORTB &= rex(4) & rex(7);
}

void motorL(int16 pwm)
{
	pwm = constraint16(-499, 499, pwm);
	if (pwm > 0) {
		PORTH |= ex(5);
		PORTH &= rex(6);
		pwm1A(pwm);
	} else if (pwm < 0) {
		PORTH &= rex(5);
		PORTH |= ex(6);
		pwm1A(-pwm);
	} else {
		PORTH &= rex(5) & rex(6);
		pwm1A(0);
	}
}

void motorR(int16 pwm)
{
	pwm = constraint16(-499, 499, pwm);
	if (pwm > 0) {
		PORTB &= rex(4);
		PORTB |= ex(7);
		pwm1B(pwm);
	} else if (pwm < 0) {
		PORTB |= ex(4);
		PORTB &= rex(7);
		pwm1B(-pwm);
	} else {
		PORTB &= rex(4) & rex(7);
		pwm1B(0);
	}
}
