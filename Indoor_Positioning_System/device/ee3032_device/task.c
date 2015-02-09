#include "display.h"
#include "joystick.h"
#include "laser.h"
#include "task.h"

void blink(void *pdata)
{
	(void)pdata;
	ledInit();
	while (1) {
		ledOn();
		OSTimeDly(5);
		ledOff();
		OSTimeDly(495);
	}
}

void nrfTxDemo(void *pdata)
{
	uint8 buf[PLOAD_WIDTH];

	(void)pdata;
	nrf24l01pInitFromTask(NRF24L01P_TX_MODE);
	oledInitFromTask();
	OSTimeDly(2);
	oledClearScreen();
	buf[0] = 0;
	buf[1] = 0;
	while (1) {
		buf[0]++;
		buf[0] %= 10;
		buf[0] += '0';
		nrf24l01pWrite(buf, 250);
		buf[0] -= '0';
		oledPrint(0, 0, "        ");
		oledLongInt(0, 0, buf[0]);
		OSTimeDly(15);
	}
}

void nrfRxDemo(void *pdata)
{
	uint8 buf[PLOAD_WIDTH];

	(void)pdata;
	nrf24l01pInitFromTask(NRF24L01P_RX_MODE);
	oledInitFromTask();
	OSTimeDly(2);
	oledClearScreen();
	while (1) {
		nrf24l01pRead(buf, 0xFFFFFFFF);
		oledPrint(0, 0, "        ");
		oledPrint(0, 0, (char *)buf);
	}
}

void mpu6050Demo(void *pdata)
{
	uint8 mpuIntStatus;
	uint8 fifoBuffer[42];
	int16 quaternion[4];

	(void)pdata;
	oledInitFromTask();
	OSTimeDly(2);
	oledClearScreen();
	while (mpu6050DMPInitFromTask());
	while (1) {
		mpu6050DMPSemPend();
		mpuIntStatus = MPU6050getIntStatus();
		if (mpuIntStatus & 0x02) {
			MPU6050getFIFOBytes(fifoBuffer, 48);
			MPU6050dmpGetQuaternion(quaternion, fifoBuffer);
			oledHex16(0, 0, quaternion[0]);
			oledHex16(1, 0, quaternion[1]);
			oledHex16(2, 0, quaternion[2]);
			oledHex16(3, 0, quaternion[3]);
		} else if (mpuIntStatus & 0x10) {
			MPU6050resetFIFO();
		}
	}
}

void mpu6050TxDemo(void *pdata)
{
	uint8 buf[PLOAD_WIDTH];
	uint8 mpuIntStatus;
	uint8 fifoBuffer[42];
	int16 quaternion[4];
	uint8 temp;

	(void)pdata;
	//oledInitFromTask();
	//OSTimeDly(2);
	//oledClearScreen();
	nrf24l01pInitFromTask(NRF24L01P_TX_MODE);
	while (mpu6050DMPInitFromTask());
	while (1) {
		mpu6050DMPSemPend();
		mpuIntStatus = MPU6050getIntStatus();
		if (mpuIntStatus & 0x02) {
			MPU6050getFIFOBytes(fifoBuffer, 48);
			MPU6050dmpGetQuaternion(quaternion, fifoBuffer);
			temp = quaternion[0] & 0xFF;
			buf[0] = temp;
			temp = (quaternion[0] >> 8) & 0xFF;
			buf[1] = temp;
			temp = quaternion[1] & 0xFF;
			buf[2] = temp;
			temp = (quaternion[1] >> 8) & 0xFF;
			buf[3] = temp;
			temp = quaternion[2] & 0xFF;
			buf[4] = temp;
			temp = (quaternion[2] >> 8) & 0xFF;
			buf[5] = temp;
			nrf24l01pWrite(buf, 10);
			/*
			oledHex16(0, 0, quaternion[0]);
			oledHex16(1, 0, quaternion[1]);
			oledHex16(2, 0, quaternion[2]);
			oledHex16(3, 0, quaternion[3]);
			*/
		} else if (mpuIntStatus & 0x10) {
			MPU6050resetFIFO();
		}
	}
}

void sonarTxDemo(void *pdata)
{
	uint8 buf[PLOAD_WIDTH];

	(void)pdata;
	ledInit();//
	nrf24l01pInitFromTask(NRF24L01P_TX_MODE);
	while (1) {
		buf[0] = 0x01;
		ledToggle();//
		nrf24l01pWrite(buf, 10);
		ledToggle();//
		sonarTxSendPulse(16400, 50);
		OSTimeDly(9);
	}
}
