#include "core.h"
#include "geometry.h"
#include "rgb.h"
#include "servo.h"

static OS_EVENT *coreSonarRdy;
static OS_EVENT *coreSonarD0Rdy;
static OS_EVENT *coreSonarD1Rdy;
static OS_EVENT *coreSonarD2Rdy;
static OS_EVENT *corePointerRdy;
static OS_EVENT *coreMouseRdy;

static uint8 coreRxBuf[PLOAD_WIDTH * 2];
static uint8 prevState = 0x00;
static float coreYawOffset = 0.0;

static tEulerAngle coreEulerAngle(void);
static void coreUSBMouseHandler(int16 curMouseX, int16 curMouseY);

void coreInit(void)
{
	coreSonarRdy = OSSemCreate(0);
	coreSonarD0Rdy = OSSemCreate(0);
	coreSonarD1Rdy = OSSemCreate(0);
	coreSonarD2Rdy = OSSemCreate(0);
	corePointerRdy = OSSemCreate(0);
	coreMouseRdy = OSSemCreate(0);
}

INT8U coreSonarPend(INT32U timeout)
{
	INT8U err;

	OSSemPend(coreSonarRdy, timeout, &err);
	return err;
}

INT8U coreSonarD0Pend(INT32U timeout)
{
	INT8U err;

	OSSemPend(coreSonarD0Rdy, timeout, &err);
	return err;
}

INT8U coreSonarD1Pend(INT32U timeout)
{
	INT8U err;

	OSSemPend(coreSonarD1Rdy, timeout, &err);
	return err;
}

INT8U coreSonarD2Pend(INT32U timeout)
{
	INT8U err;

	OSSemPend(coreSonarD2Rdy, timeout, &err);
	return err;
}

void coreTask(void *pdata)
{
	INT8U err;
	tEulerAngle eCore;
	uint8 sonarCnt;

	(void)pdata;
	ledInit(6);
	nrf24l01pInitFromTask(NRF24L01P_RX_MODE);
	sonarCnt = 0;
	while (1) {
		ledToggle(6);
		nrf24l01pRead(coreRxBuf, 0xFFFFFFFF);
		if ((coreRxBuf[0] & 0x80) == 0x00) {
			nrf24l01pRead(&coreRxBuf[PLOAD_WIDTH], 0xFFFFFFFF);
		}
		ledToggle(6);
		if (TRUE) {
			sonarRxTrigger(25);
			sonarRxReadReset();
			OSSemSet(coreSonarRdy, 0, &err);
			OSSemPost(coreSonarRdy);
			OSSemSet(coreSonarD0Rdy, 0, &err);
			OSSemPost(coreSonarD0Rdy);
			OSSemSet(coreSonarD1Rdy, 0, &err);
			OSSemPost(coreSonarD1Rdy);
			OSSemSet(coreSonarD2Rdy, 0, &err);
			OSSemPost(coreSonarD2Rdy);
		}
		sonarCnt++;
		switch (coreRxBuf[0]) {
		case 0x00:
			if (prevState != 0x00) {
				rgbUpdate(0x04);
				usbMouseConnect();
			}
			OSSemSet(corePointerRdy, 0, &err);
			OSSemPost(corePointerRdy);
			break;
		case 0x01:
			if (prevState != 0x01) {
				rgbUpdate(0x02);
			}
			if (prevState == 0x00) {
				usbMouseDisconnect();
			}
			OSSemSet(coreMouseRdy, 0, &err);
			OSSemPost(coreMouseRdy);
			break;
		case 0x02:
			if (prevState != 0x02) {
				rgbUpdate(0x01);
			}
			if (prevState == 0x00) {
				usbMouseDisconnect();
			}
			break;
		case 0x03:
			if (prevState != 0x03) {
				rgbUpdate(0x07);
			}
			break;
		case 0x13:
			eCore = coreEulerAngle();
			coreYawOffset = eCore.yaw;
			break;
		default:
			break;
		}
		prevState = coreRxBuf[0];
	}
}

void pointerTask(void *pdata)
{
	INT8U err;
	tPoint pPointer;
	tEulerAngle ePointer;
	tVector vPointer;
	float yLowConstrain, yHighConstrain;
	float zLowConstrain, zHighConstrain;
	int16 curMouseX, curMouseY;

	(void)pdata;
	yLowConstrain = -GEO_DISPLAY_WIDTH_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER / 2;
	yHighConstrain = GEO_DISPLAY_WIDTH_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER / 2;
	zLowConstrain = 0.0;
	zHighConstrain = GEO_DISPLAY_HEIGHT_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER;
	while (1) {
		OSSemPend(corePointerRdy, 0xFFFFFFFF, &err);
		pPointer = servoDeviceCoordinate();
		//pPointer.px = -FRAME_SIZE_SONAR * 1.41421356;
		//pPointer.py = 0.0;
		//pPointer.pz = 0.0;
		pPointer = geoNewFramePoint(pPointer);
		ePointer = coreEulerAngle();
		ePointer.yaw -= coreYawOffset;
		vPointer = geoVectorFromEulerAngle(ePointer);
		//vPointer.vx = 1.0;
		//vPointer.vy = 0.0;
		//vPointer.vz = 0.0;
		pPointer = geoLaserPoint(pPointer, vPointer);
		pPointer.py = constrain(pPointer.py, yLowConstrain, yHighConstrain);
		pPointer.pz = constrain(pPointer.pz, zLowConstrain, zHighConstrain);
		curMouseX = (int16)map(pPointer.py, yHighConstrain, yLowConstrain, 0.0, GEO_DISPLAY_RESOLUTION_HORIZONTAL);
		curMouseY = (int16)map(pPointer.pz, zHighConstrain, zLowConstrain, 0.0, GEO_DISPLAY_RESOLUTION_VERTICAL);
		coreUSBMouseHandler(curMouseX, curMouseY);
	}
}

void mouseTask(void *pdata)
{
	INT8U err;
	tEulerAngle eMouse;
	tPoint pMouse;
	float ratio;
	uint8 *tx;

	(void)pdata;
	ratio = GEO_DISPLAY_RESOLUTION_HORIZONTAL / (GEO_DISPLAY_WIDTH_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER);
	while (1) {
		OSSemPend(coreMouseRdy, 0xFFFFFFFF, &err);
		eMouse = coreEulerAngle();
		eMouse.yaw -= coreYawOffset;
		pMouse = servoDeviceCoordinate();
		pMouse = geoNewFramePoint(pMouse);
		pMouse.px *= ratio;
		pMouse.py *= ratio;
		pMouse.pz *= ratio;
		tx = (uint8 *)&eMouse;
		uart0PendingByte(tx[0]);
		uart0PendingByte(tx[1]);
		uart0PendingByte(tx[2]);
		uart0PendingByte(tx[3]);
		uart0PendingByte(tx[4]);
		uart0PendingByte(tx[5]);
		uart0PendingByte(tx[6]);
		uart0PendingByte(tx[7]);
		uart0PendingByte(tx[8]);
		uart0PendingByte(tx[9]);
		uart0PendingByte(tx[10]);
		uart0PendingByte(tx[11]);
		tx = (uint8 *)&pMouse;
		uart0PendingByte(tx[0]);
		uart0PendingByte(tx[1]);
		uart0PendingByte(tx[2]);
		uart0PendingByte(tx[3]);
		uart0PendingByte(tx[4]);
		uart0PendingByte(tx[5]);
		uart0PendingByte(tx[6]);
		uart0PendingByte(tx[7]);
		uart0PendingByte(tx[8]);
		uart0PendingByte(tx[9]);
		uart0PendingByte(tx[10]);
		uart0PendingByte(tx[11]);
		uart0PendingByte(10);
	}
}

static tEulerAngle coreEulerAngle(void)
{
	tEulerAngle eulerAngle;
	uint32 temp;
	
	temp = coreRxBuf[5];
	temp = temp << 8;
	temp |= coreRxBuf[4];
	temp = temp << 8;
	temp |= coreRxBuf[3];
	temp = temp << 8;
	temp |= coreRxBuf[2];
	eulerAngle.roll = *((float *)&temp);
	temp = coreRxBuf[11];
	temp = temp << 8;
	temp |= coreRxBuf[10];
	temp = temp << 8;
	temp |= coreRxBuf[7];
	temp = temp << 8;
	temp |= coreRxBuf[6];
	eulerAngle.pitch = *((float *)&temp);
	temp = coreRxBuf[15];
	temp = temp << 8;
	temp |= coreRxBuf[14];
	temp = temp << 8;
	temp |= coreRxBuf[13];
	temp = temp << 8;
	temp |= coreRxBuf[12];
	eulerAngle.yaw = *((float *)&temp);
	return eulerAngle;
}

static void coreUSBMouseHandler(int16 curMouseX, int16 curMouseY)
{
	static int16 prevMouseX, prevMouseY;
	int8 mouseBuf[4];

	if ((curMouseX - prevMouseX) > 127) {
		mouseBuf[1] = 127;
		prevMouseX += 127;
	} else if ((curMouseX - prevMouseX) < -128) {
		mouseBuf[1] = -128;
		prevMouseX -= 128;
	} else {
		mouseBuf[1] = curMouseX - prevMouseX;
		prevMouseX = curMouseX;
	}
	if ((curMouseY - prevMouseY) > 127) {
		mouseBuf[2] = 127;
		prevMouseY += 127;
	} else if ((curMouseY - prevMouseY) < -128) {
		mouseBuf[2] = -128;
		prevMouseY -= 128;
	} else {
		mouseBuf[2] = curMouseY - prevMouseY;
		prevMouseY = curMouseY;
	}
	mouseBuf[0] = coreRxBuf[1];
	mouseBuf[3] = coreRxBuf[9];
	usbMouseInput((uint8 *)mouseBuf, 15);
}
