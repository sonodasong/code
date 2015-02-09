#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <library.h>

#define JOYSTICK_BUTTON		0x10
#define JOYSTICK_UP			0x08
#define JOYSTICK_DOWN		0x04
#define JOYSTICK_LEFT		0x02
#define JOYSTICK_RIGHT		0x01

void joystickInit(void);
uint8 joystickRead(void);
void joystickTask(void *pdata);

#endif
