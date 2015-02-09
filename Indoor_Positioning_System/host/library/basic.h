#ifndef __BASIC_H__
#define __BASIC_H__

#include "define.h"

void ledInit(uint8 num);
void ledOn(uint8 num);
void ledOff(uint8 num);
void ledToggle(uint8 num);
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
float constrain(float value, float low, float high);
boolean floatEqual(float x, float y);

#endif
