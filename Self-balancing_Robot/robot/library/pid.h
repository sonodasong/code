#ifndef __PID_H__
#define __PID_H__

#include "define.h"

int16 pidLSpd(int16 setPoint, int16 feedback);
int16 pidRSpd(int16 setPoint, int16 feedback);
int16 pidAngle(int32 setPoint, int32 feedback);
int16 pidVelocity(int32 setPoint, int32 feedback);

#endif
