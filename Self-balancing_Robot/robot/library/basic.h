#ifndef __BASIC_H__
#define __BASIC_H__

#include "define.h"

void enablePullup(void);
void disablePullup(void);
void delayms(uint16 x);
void ledInit(void);
void ledOn(void);
void ledOff(void);
void ledToggle(void);

#endif
