#include "filter.h"

int16 constraint16(int16 min, int16 max, int16 data)
{
	if (data < min) {
		return min;
	} else if (data > max) {
		return max;
	} else {
		return data;
	}
}

int32 constraint32(int32 min, int32 max, int32 data)
{
	if (data < min) {
		return min;
	} else if (data > max) {
		return max;
	} else {
		return data;
	}
}

int16 complementary(int16 x, int16 y)
{
	static int16 xn = 0;
	
	xn = (x - xn - y) / 16 + xn + y;
	return xn;
}

int16 aSpdExp(int16 x)
{
	static int16 xn = 0;
	
	xn = (x - xn) / 8 + xn;
	return xn;
}

int32 aItgExp(int32 x, boolean update)
{
	static int32 xn = 0;
	
	if (update == TRUE) {
		xn = x;
	} else {
		xn -= xn / 32;
	}
	return xn;
}

int32 vItgBnd(int32 x)
{
	if (x < -50) {
		return x + 50;
	} else if (x >= -50 && x <= 50) {
		return 0;
	} else {
		return x - 50;
	}
}

int16 vAglExp(int16 x)
{
	static int16 xn = 0;
	
	xn = (x - xn) / 8 + xn;
	return xn;
}
