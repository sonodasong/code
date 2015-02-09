#ifndef __FILTER_H__
#define __FILTER_H__

#include "define.h"

int16 constraint16(int16 min, int16 max, int16 data);
int32 constraint32(int32 min, int32 max, int32 data);
int16 complementary(int16 x, int16 y);
int16 aSpdExp(int16 x);
int32 aItgExp(int32 x, boolean update);
int32 vItgBnd(int32 x);
int16 vAglExp(int16 x);

#endif
