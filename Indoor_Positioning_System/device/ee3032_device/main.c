#include "ee3032_device.h"

static OS_STK stack0[512];
static OS_STK stack1[512];
static OS_STK stack2[512];
static OS_STK stack3[512];
static OS_STK stack4[512];
static OS_STK stack5[512];
static OS_STK stack6[512];
//static OS_STK stack7[512];

int main(void)
{
	SystemInit();
	__disable_irq();
	SysTick_Config(SystemCoreClock / 1000 - 1);
	OSInit();

	adcInit();
	i2c0Init();
	i2c1Init();
	spiInit();
	uart0PendingInit();
	nrf24l01pInit();
	mpu6050DMPInit();
	sonarTxInit();
	joystickInit();
	laserInit();
	mouseInit();

	OSTaskCreate(coreTask, (void*)0, &stack0[511], 0);
	OSTaskCreate(mouseTask, (void*)0, &stack1[511], 1);
	OSTaskCreate(laserTask, (void*)0, &stack2[511], 2);
	OSTaskCreate(joystickTask, (void*)0, &stack3[511], 3);
	OSTaskCreate(temperatureTask, (void*)0, &stack4[511], 4);
	OSTaskCreate(powerTask, (void*)0, &stack5[511], 5);
	OSTaskCreate(displayTask, (void*)0, &stack6[511], 6);
	//OSTaskCreate(blink, (void*)0, &stack7[511], 7);

	OSStart();

	return 0;
}
