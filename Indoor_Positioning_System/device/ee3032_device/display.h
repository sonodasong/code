#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <library.h>

void displayStateUpdate(uint8 desktop);
void displayDotUpdate(uint8 dot);
void displayPowerUpdate(uint8 power);
void displayTemperatureUpdate(uint16 temperature);
void displayTask(void *pdata);

#endif
