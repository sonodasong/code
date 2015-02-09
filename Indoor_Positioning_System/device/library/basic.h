#ifndef __BASIC_H__
#define __BASIC_H__

#include "define.h"

void ledInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
float constrain(float value, float low, float high);

#endif
