#include "servo.h"
#include "task.h"

void blink(void *pdata)
{
	(void)pdata;
	ledInit(7);
	while (1) {
		ledOn(7);
		OSTimeDly(5);
		ledOff(7);
		OSTimeDly(495);
	}
}

void usbDemo(void *pdata)
{
	uint8 buf[4];

	(void)pdata;
	buf[0] = 0;
	buf[1] = 1;
	buf[2] = 1;
	buf[3] = 0;
	usbMouseConnect();
	while (1) {
		usbMouseInput(buf, 15);
	}
}

void nrfTxDemo(void *pdata)
{
	uint8 buf[PLOAD_WIDTH];

	(void)pdata;
	nrf24l01pInitFromTask(NRF24L01P_TX_MODE);
	buf[0] = 0;
	buf[1] = 0;
	while (1) {
		buf[0]++;
		buf[0] %= 10;
		buf[0] += '0';
		nrf24l01pWrite(buf, 250);
		buf[0] -= '0';
		uart0PendingLongInt(buf[0]);
		uart0PendingPrint("\r\n");
		OSTimeDly(150);
	}
}

void nrfRxDemo(void *pdata)
{
	uint8 buf[PLOAD_WIDTH];

	(void)pdata;
	nrf24l01pInitFromTask(NRF24L01P_RX_MODE);
	while (1) {
		nrf24l01pRead(buf, 0xFFFFFFFF);
		uart0PendingPrint((char *)buf);
		uart0PendingPrint("\r\n");
	}
}

void mpu6050RxDemo(void *pdata)
{
	uint8 buf[PLOAD_WIDTH];

	(void)pdata;
	ledInit(6);
	nrf24l01pInitFromTask(NRF24L01P_RX_MODE);
	while (1) {
		nrf24l01pRead(buf, 0xFFFFFFFF);
		uart0PendingByte(buf[0]);
		uart0PendingByte(buf[1]);
		uart0PendingByte(buf[2]);
		uart0PendingByte(buf[3]);
		uart0PendingByte(buf[4]);
		uart0PendingByte(buf[5]);
		//uart0PendingByte(buf[6]);
		//uart0PendingByte(buf[7]);
		uart0PendingByte(10);
		ledToggle(6);
	}
}
