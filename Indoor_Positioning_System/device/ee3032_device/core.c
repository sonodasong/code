#include "core.h"
#include "display.h"
#include "geometry.h"
#include "joystick.h"
#include "laser.h"
#include "mouse.h"

static uint8 corePacketInfo;

static uint8 coreState = 0x02;
static uint8 corePrevState = 0x02;
static uint8 coreDotState = 0x02;

static void coreStateHandler(void);
static void coreNonCalibrationStateHandler(void);
static void coreCalibrationStateHandler(void);
static tQuaternion coreQuaternion(int16 *quaternion);
static tVector coreMagVectorBodyFrame(int16 *mag);
static float complementaryFilter(float yawCorrected, float yawDMP, int32 a);
static void coreRFTxHandler(tEulerAngle eulerAngle, uint8 *mouse);
static void coreBufCopy(uint8 *dst, uint8 *src, uint8 size);

void coreTask(void *pdata)
{
	uint8 mpuIntStatus;
	uint8 fifoBuffer[42];
	int16 quaternion[4];
	int16 magnetometer[3];
	tEulerAngle eulerAngle;
	float yawDMP;
	uint8 mouse[2];

	(void)pdata;
	ledInit();
	nrf24l01pInitFromTask(NRF24L01P_TX_MODE);
	while (mpu6050DMPInitFromTask());
	while (1) {
		mpu6050DMPSemPend();
		mpuIntStatus = MPU6050getIntStatus();
		if (mpuIntStatus & 0x02) {
			MPU6050getFIFOBytes(fifoBuffer, 48);
			MPU6050resetFIFO();
			MPU6050dmpGetQuaternion(quaternion, fifoBuffer);
			MPU6050dmpGetMag(magnetometer, fifoBuffer);
			coreStateHandler();
			eulerAngle = geoEulerAngleFromQuaternion(coreQuaternion(quaternion));
			yawDMP = eulerAngle.yaw;
			eulerAngle = geoEulerAngleCorrected(eulerAngle, coreMagVectorBodyFrame(magnetometer));
			eulerAngle.yaw = complementaryFilter(eulerAngle.yaw, yawDMP, 2);
			mouseRead(mouse);
			ledToggle();
			coreRFTxHandler(eulerAngle, mouse);
			ledToggle();
			sonarTxSendPulse(6000, 15);
		} else if (mpuIntStatus & 0x10) {
			MPU6050resetFIFO();
		}
	}
}

static void coreStateHandler(void)
{
	if (coreState < 0x03) {
		coreNonCalibrationStateHandler();
	} else if (coreState == 0x03) {
		coreCalibrationStateHandler();
	}
}

static void coreNonCalibrationStateHandler(void)
{
	uint8 joystick;

	joystick = joystickRead();
	if (joystick & JOYSTICK_UP) {
		coreDotState -= 1;
		coreDotState %= 4;
		displayDotUpdate(coreDotState);
	}
	if (joystick & JOYSTICK_DOWN) {
		coreDotState += 1;
		coreDotState %= 4;
		displayDotUpdate(coreDotState);
	}
	if (joystick & JOYSTICK_BUTTON) {
		corePrevState = coreState;
		coreState = coreDotState;
		displayStateUpdate(coreState);
	}
	corePacketInfo = coreState;
}

static void coreCalibrationStateHandler(void)
{
	uint8 joystick;
	uint8 prevState;

	joystick = joystickRead();
	if (joystick & JOYSTICK_BUTTON) {
		prevState = corePrevState;
		coreState = prevState;
		coreDotState = prevState;
		displayStateUpdate(prevState);
		displayDotUpdate(prevState);
		corePacketInfo = 0x13;
	} else {
		corePacketInfo = 0x03;
	}
}

static tQuaternion coreQuaternion(int16 *quaternion)
{
	tQuaternion q;

	q.q0 = quaternion[0] / 16384.0;
	q.q1 = quaternion[1] / 16384.0;
	q.q2 = quaternion[2] / 16384.0;
	q.q3 = quaternion[3] / 16384.0;
	return q;
}

static tVector coreMagVectorBodyFrame(int16 *mag)
{
	tVector vMag;

	vMag.vx = (float)mag[1];
	vMag.vy = (float)mag[0];
	vMag.vz = -(float)mag[2];
	return vMag;
}

static float complementaryFilter(float yawCorrected, float yawDMP, int32 a)
{
	static float prevYawCorrected = 0.0;
	static float prevYawDMP = 0.0;
	static int32 out = 0;
	int32 intYawCorrected;
	int32 intYawDMPDelta;
	float output;

	if ((prevYawCorrected > PI / 2.0) && (prevYawCorrected < PI)) {
		if ((yawCorrected < -PI / 2.0) && (yawCorrected > -PI)) {
			out -= 628318;
		}
	} else if ((prevYawCorrected < -PI / 2.0) && (prevYawCorrected > -PI)) {
		if ((yawCorrected > PI / 2.0) && (yawCorrected < PI)) {
			out += 628318;
		}
	}
	if ((prevYawDMP > PI / 2.0) && (prevYawDMP < PI)) {
		if ((yawDMP < -PI / 2.0) && (yawDMP > -PI)) {
			prevYawDMP -= PI * 2;
		}
	} else if ((prevYawDMP < -PI / 2.0) && (prevYawDMP > -PI)) {
		if ((yawDMP > PI / 2.0) && (yawDMP < PI)) {
			prevYawDMP += PI * 2;
		}
	}
	intYawCorrected = (int32)(yawCorrected * 100000.0);
	intYawDMPDelta = (int32)((yawDMP - prevYawDMP) * 100000.0);
	out = (100 - a) * (out + intYawDMPDelta) + a * intYawCorrected;
	prevYawCorrected = yawCorrected;
	prevYawDMP = yawDMP;
	out /= 100;
	output = (float)out;
	output /= 100000.0;
	return output;
}

static void coreRFTxHandler(tEulerAngle eulerAngle, uint8 *mouse)
{
	uint8 buf[PLOAD_WIDTH];

	coreBufCopy(&buf[2], (uint8 *)&eulerAngle.roll, 6);
	buf[0] = corePacketInfo;
	buf[1] = mouse[0];
	nrf24l01pWrite(buf, 15);
	coreBufCopy(&buf[0], (uint8 *)&eulerAngle.pitch, 8);
	buf[0] = corePacketInfo | 0x80;
	buf[1] = mouse[1];
	nrf24l01pWrite(buf, 15);
}

static void coreBufCopy(uint8 *dst, uint8 *src, uint8 size)
{
	uint8 i;
	for (i = 0; i < size; i++) {
		dst[i] = src[i];
	}
}
