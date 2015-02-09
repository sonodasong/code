#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "define.h"

extern volatile int32 rxBit32[2];

extern volatile boolean mpu6050DMPRdy;
extern volatile int32 sAngle;
extern volatile int32 fAngle;
extern volatile int16 gLSpd;
extern volatile int16 gRSpd;

extern volatile int16 gSpd;

#endif
