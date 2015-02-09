#include <math.h>
#include "core.h"
#include "geometry.h"
#include "servo.h"

#define SERVO_1_LOW_LIMIT		450.0
#define SERVO_1_MIDDLE			1090.0
#define SERVO_1_HIGH_LIMIT		1800.0

#define SERVO_2_LOW_LIMIT		570.0
#define SERVO_2_MIDDLE			1220.0
#define SERVO_2_HIGH_LIMIT		1940.0

#define SERVO_3_LOW_LIMIT		480.0
#define SERVO_3_MIDDLE			1120.0
#define SERVO_3_HIGH_LIMIT		1860.0

#define SERVO_4_LOW_LIMIT		500.0
#define SERVO_4_MIDDLE			1150.0
#define SERVO_4_HIGH_LIMIT		1880.0

#define SERVO_5_LOW_LIMIT		510.0
#define SERVO_5_MIDDLE			1170.0
#define SERVO_5_HIGH_LIMIT		1920.0

#define SERVO_6_LOW_LIMIT		550.0
#define SERVO_6_MIDDLE			1220.0
#define SERVO_6_HIGH_LIMIT		1960.0

static uint32 servoD0 = (uint32)(FRAME_SIZE_SONAR * 1.41421356);
static uint32 servoD1 = (uint32)(FRAME_SIZE_SONAR * 2);
static uint32 servoD2 = (uint32)(FRAME_SIZE_SONAR * 2);

static tPoint pDevice;

static void servo1Write(float angle);
static void servo2Write(float angle);
static void servo3Write(float angle);
static void servo4Write(float angle);
static void servo5Write(float angle);
static void servo6Write(float angle);
static void servoUpdate(void);

static uint32 servoGlitchFilter0(uint32 input, uint32 limit, uint16 width);
static uint32 servoGlitchFilter1(uint32 input, uint32 limit, uint16 width);
static uint32 servoGlitchFilter2(uint32 input, uint32 limit, uint16 width);
static float servoExponentialFilter0(uint32 input, float a);
static float servoExponentialFilter1(uint32 input, float a);
static float servoExponentialFilter2(uint32 input, float a);

tPoint servoDeviceCoordinate(void)
{
	OS_CPU_SR  cpu_sr;
	tPoint temp;

	OS_ENTER_CRITICAL();
	temp = pDevice;
	OS_EXIT_CRITICAL();
	return temp;
}

void servoTask(void *pdata)
{
	static tPoint p0 = {0.0, 0.0, 0.0};
	static tPoint p1 = {-FRAME_SIZE_SONAR, FRAME_SIZE_SONAR, 0.0};
	static tPoint p2 = {FRAME_SIZE_SONAR, FRAME_SIZE_SONAR, 0.0};
	OS_CPU_SR  cpu_sr;
	uint32 distance0;
	uint32 distance1;
	uint32 distance2;
	tSonarDistance sonarDistance;
	tPoint pOld;
	tPoint pNew;
	tServoAngle servoAngle0, servoAngle1, servoAngle2;
	
	(void)pdata;
	while (1) {
		coreSonarPend(0xFFFFFFFF);
		OS_ENTER_CRITICAL();
		distance0 = servoD0;
		distance1 = servoD1;
		distance2 = servoD2;
		OS_EXIT_CRITICAL();		
		distance0 = servoGlitchFilter0(distance0, 500, 100);
		distance1 = servoGlitchFilter1(distance1, 500, 100);
		distance2 = servoGlitchFilter2(distance2, 500, 100);
		sonarDistance.d0 = servoExponentialFilter0(distance0, 0.05);
		sonarDistance.d1 = servoExponentialFilter1(distance1, 0.05);
		sonarDistance.d2 = servoExponentialFilter2(distance2, 0.05);
		pOld = geoCoordinateFromDistance(sonarDistance, FRAME_SIZE_SONAR);
		pOld.px = constrain(pOld.px, -10000.0, 10000.0);
		pOld.py = constrain(pOld.py, -10000.0, 10000.0);
		pOld.pz = constrain(pOld.pz, 0.0, 10000.0);
#ifdef SERVO_DEBUG
		uart0PendingLongInt((uint32)sonarDistance.d2);
		uart0PendingPrint("\r\n");
		pOld.px = 0.0;
		pOld.py = 2400.0;
		pOld.pz = 0.0;
#endif
		pNew.px = -pOld.pz;
		pNew.py = -pOld.px;
		pNew.pz = pOld.py;
		OS_ENTER_CRITICAL();
		pDevice = pNew;
		OS_EXIT_CRITICAL();
		servoAngle0 = geoServoAngle(p0, pOld);
		servoAngle1 = geoServoAngle(p1, pOld);
		servoAngle2 = geoServoAngle(p2, pOld);
		servo1Write(servoAngle0.az);
		//servo1Write(90);
		servo2Write(servoAngle0.ax);
		//servo2Write(90);
		servo3Write(servoAngle1.az);
		//servo3Write(90);
		servo4Write(servoAngle1.ax);
		//servo4Write(90);
		servo5Write(servoAngle2.az);
		//servo5Write(90);
		servo6Write(servoAngle2.ax);
		//servo6Write(90);
		servoUpdate();
	}
}

void servoDistance0Task(void *pdata)
{
	static uint32 distance0 = (uint32)(FRAME_SIZE_SONAR * 1.41421356);
	OS_CPU_SR  cpu_sr;

	(void)pdata;
	while (1) {
		coreSonarD0Pend(0xFFFFFFFF);
		sonarRxRead0(&distance0, 0xFFFFFFFF);
		OS_ENTER_CRITICAL();
		servoD0 = distance0;
		OS_EXIT_CRITICAL();
	}
}

void servoDistance1Task(void *pdata)
{
	static uint32 distance1 = (uint32)(FRAME_SIZE_SONAR * 2);
	OS_CPU_SR  cpu_sr;

	(void)pdata;
	while (1) {
		coreSonarD1Pend(0xFFFFFFFF);
		sonarRxRead1(&distance1, 0xFFFFFFFF);
		OS_ENTER_CRITICAL();
		servoD1 = distance1;
		OS_EXIT_CRITICAL();
	}
}

void servoDistance2Task(void *pdata)
{
	static uint32 distance2 = (uint32)(FRAME_SIZE_SONAR * 2);
	OS_CPU_SR  cpu_sr;

	(void)pdata;
	while (1) {
		coreSonarD2Pend(0xFFFFFFFF);
		sonarRxRead2(&distance2, 0xFFFFFFFF);
		OS_ENTER_CRITICAL();
		servoD2 = distance2;
		OS_EXIT_CRITICAL();
	}
}

static void servo1Write(float angle)
{
	uint16 pwm;

	if (floatEqual(angle, 90.0)) {
		pwm = (uint16)SERVO_1_MIDDLE;
	} else if (angle < 90.0) {
		pwm = (uint16)map(angle, 0.0, 90.0, SERVO_1_LOW_LIMIT, SERVO_1_MIDDLE);
	} else {
		pwm = (uint16)map(angle, 90.0, 180.0, SERVO_1_MIDDLE, SERVO_1_HIGH_LIMIT);
	}
	pwm = 16000 - pwm;
	pwm1Write(pwm);
}

static void servo2Write(float angle)
{
	uint16 pwm;

	if (floatEqual(angle, 90.0)) {
		pwm = (uint16)SERVO_2_MIDDLE;
	} else if (angle < 90.0) {
		pwm = (uint16)map(angle, 0.0, 90.0, SERVO_2_LOW_LIMIT, SERVO_2_MIDDLE);
	} else {
		pwm = (uint16)map(angle, 90.0, 180.0, SERVO_2_MIDDLE, SERVO_2_HIGH_LIMIT);
	}
	pwm = 16000 - pwm;
	pwm2Write(pwm);
}

static void servo3Write(float angle)
{
	uint16 pwm;

	if (floatEqual(angle, 90.0)) {
		pwm = (uint16)SERVO_3_MIDDLE;
	} else if (angle < 90.0) {
		pwm = (uint16)map(angle, 0.0, 90.0, SERVO_3_LOW_LIMIT, SERVO_3_MIDDLE);
	} else {
		pwm = (uint16)map(angle, 90.0, 180.0, SERVO_3_MIDDLE, SERVO_3_HIGH_LIMIT);
	}
	pwm3Write(pwm);
}

static void servo4Write(float angle)
{
	uint16 pwm;

	if (floatEqual(angle, 90.0)) {
		pwm = (uint16)SERVO_4_MIDDLE;
	} else if (angle < 90.0) {
		pwm = (uint16)map(angle, 0.0, 90.0, SERVO_4_LOW_LIMIT, SERVO_4_MIDDLE);
	} else {
		pwm = (uint16)map(angle, 90.0, 180.0, SERVO_4_MIDDLE, SERVO_4_HIGH_LIMIT);
	}
	pwm4Write(pwm);
}

static void servo5Write(float angle)
{
	uint16 pwm;

	if (floatEqual(angle, 90.0)) {
		pwm = (uint16)SERVO_5_MIDDLE;
	} else if (angle < 90.0) {
		pwm = (uint16)map(angle, 0.0, 90.0, SERVO_5_LOW_LIMIT, SERVO_5_MIDDLE);
	} else {
		pwm = (uint16)map(angle, 90.0, 180.0, SERVO_5_MIDDLE, SERVO_5_HIGH_LIMIT);
	}
	pwm5Write(pwm);
}

static void servo6Write(float angle)
{
	uint16 pwm;

	if (floatEqual(angle, 90.0)) {
		pwm = (uint16)SERVO_6_MIDDLE;
	} else if (angle < 90.0) {
		pwm = (uint16)map(angle, 0.0, 90.0, SERVO_6_LOW_LIMIT, SERVO_6_MIDDLE);
	} else {
		pwm = (uint16)map(angle, 90.0, 180.0, SERVO_6_MIDDLE, SERVO_6_HIGH_LIMIT);
	}
	pwm6Write(pwm);
}

static void servoUpdate(void)
{
	pwmLatchEnable(0x7E);
}

static uint32 servoGlitchFilter0(uint32 input, uint32 limit, uint16 width)
{
	static uint32 output = (uint32)(FRAME_SIZE_SONAR * 1.41421356);
	static uint16 cnt = 0;

	if (((input + limit) > output) && ((output + limit) > input)) {
		output = input;
		cnt = 0;
	} else {
		cnt++;
		if (cnt == width) {
			output = input;
			cnt = 0;
		}
	}
	return output;
}

static uint32 servoGlitchFilter1(uint32 input, uint32 limit, uint16 width)
{
	static uint32 output = (uint32)(FRAME_SIZE_SONAR * 2);
	static uint16 cnt = 0;

	if (((input + limit) > output) && ((output + limit) > input)) {
		output = input;
		cnt = 0;
	} else {
		cnt++;
		if (cnt == width) {
			output = input;
			cnt = 0;
		}
	}
	return output;
}

static uint32 servoGlitchFilter2(uint32 input, uint32 limit, uint16 width)
{
	static uint32 output = (uint32)(FRAME_SIZE_SONAR * 2);
	static uint16 cnt = 0;

	if (((input + limit) > output) && ((output + limit) > input)) {
		output = input;
		cnt = 0;
	} else {
		cnt++;
		if (cnt == width) {
			output = input;
			cnt = 0;
		}
	}
	return output;
}

static float servoExponentialFilter0(uint32 input, float a)
{
	static float output = FRAME_SIZE_SONAR * 1.41421356;

	output = (1 - a) * output + a * (float)input;
	return output;
}

static float servoExponentialFilter1(uint32 input, float a)
{
	static float output = FRAME_SIZE_SONAR * 2;

	output = (1 - a) * output + a * (float)input;
	return output;
}

static float servoExponentialFilter2(uint32 input, float a)
{
	static float output = FRAME_SIZE_SONAR * 2;

	output = (1 - a) * output + a * (float)input;
	return output;
}
