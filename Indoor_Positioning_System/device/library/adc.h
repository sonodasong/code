#ifndef __ADC_H__
#define __ADC_H__

#include "define.h"

#define ADC_AVL_TIMEOUT		0xFFFFFFFF
#define ADC_TIMEOUT			15

void adcInit(void);
INT8U adcPend(void);
void adcPost(void);
uint16 adcRead0(void);
uint16 adcRead1(void);
uint16 adcRead2(void);
uint16 adcRead3(void);

#endif
