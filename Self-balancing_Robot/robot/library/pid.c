#include "filter.h"
#include "pid.h"

static boolean vItgOn = FALSE;

int16 pidLSpd(int16 setPoint, int16 feedback)
{
	static int16 integration = 0;
	int16 e;
	int16 result;
	
	e = (setPoint - feedback);
	integration += e;
	integration = constraint16(-666, 666, integration);
	result = 75 * e + 12 * integration;
	return constraint16(-499, 499, result / FIXED_DIV);
}

int16 pidRSpd(int16 setPoint, int16 feedback)
{
	static int16 integration = 0;
	int16 e;
	int16 result;
	
	e = (setPoint - feedback);
	integration += e;
	integration = constraint16(-666, 666, integration);
	result = 75 * e + 12 * integration;
	return constraint16(-499, 499, result / FIXED_DIV);
}

int16 pidAngle(int32 setPoint, int32 feedback)
{
	static int32 itg = 0;
	int32 e;
	int32 result;
	
	e = (setPoint - feedback);
	if (e < -400) {
		itg += e;
		itg = constraint32(-21504, 21504, itg);
		aItgExp(itg, TRUE);
		result = 30 * e + 4 * itg - 2000;
		vItgOn = FALSE;
	} else if (e >= -400 && e < -100) {
		itg = aItgExp(0, FALSE);
		result = 20 * e + 4 * itg - 6000;
		vItgOn = TRUE;
	} else if (e >= -100 && e <= 100) {
		itg = aItgExp(0, FALSE);
		result = 80 * e + 4 * itg;
		vItgOn = TRUE;
	} else if (e > 100 && e <= 400) {
		itg = aItgExp(0, FALSE);
		result = 20 * e + 4 * itg + 6000;
		vItgOn = TRUE;
	} else {
		itg += e;
		itg = constraint32(-21504, 21504, itg);
		aItgExp(itg, TRUE);
		result = 30 * e + 4 * itg + 2000;
		vItgOn = FALSE;
	}
	return constraint32(-336, 336, result / FIXED_DIV / FIXED_DIV);
}

int16 pidVelocity(int32 setPoint, int32 feedback)
{
	static int32 integration = 0;
	int32 e;
	int32 result;
	
	e = (setPoint - feedback);
	if (vItgOn == TRUE) {
		integration += vItgBnd(e);
	}
	integration = constraint32(-51200, 51200, integration);
	result = 5 * e + 5 * integration / 128;
	return constraint32(-2000, 2000, result);
}
