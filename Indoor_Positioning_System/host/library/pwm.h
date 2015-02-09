#ifndef __PWM_H__
#define __PWM_H__

#include "define.h"

void pwmInit(void);
void pwm1Write(uint16 value);
void pwm2Write(uint16 value);
void pwm3Write(uint16 value);
void pwm4Write(uint16 value);
void pwm5Write(uint16 value);
void pwm6Write(uint16 value);
void pwmLatchEnable(uint8 bitEnable);

#endif
