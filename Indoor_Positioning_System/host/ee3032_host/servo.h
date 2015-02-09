#ifndef __SERVO_H__
#define __SERVO_H__

#include <library.h>
#include "geometry.h"

//#define SERVO_DEBUG

tPoint servoDeviceCoordinate(void);
void servoTask(void *pdata);
void servoDistance0Task(void *pdata);
void servoDistance1Task(void *pdata);
void servoDistance2Task(void *pdata);

#endif
