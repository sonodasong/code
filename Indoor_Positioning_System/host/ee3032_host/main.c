#include "ee3032_host.h"

//static OS_STK stack0[256];
static OS_STK stack1[256];
static OS_STK stack2[256];
static OS_STK stack3[256];
static OS_STK stack4[256];
static OS_STK stack5[256];
static OS_STK stack6[256];
static OS_STK stack7[256];
static OS_STK stack8[256];

int main(void)
{																    
	SystemInit();
	__disable_irq();
	SysTick_Config(SystemCoreClock / 1000 - 1);
	OSInit();

	pwmInit();
	spiInit();
	uart0PendingInit();
	usbMouseInit();
	nrf24l01pInit();
	sonarRxInit();
	coreInit();
	rgbInit();

	//OSTaskCreate(usbDemo, (void*)0, &stack0[255], 0);
	OSTaskCreate(coreTask, (void*)0, &stack1[255], 1);
	OSTaskCreate(servoTask, (void*)0, &stack2[255], 2);
	OSTaskCreate(servoDistance0Task, (void*)0, &stack3[255], 3);
	OSTaskCreate(servoDistance1Task, (void*)0, &stack4[255], 4);
	OSTaskCreate(servoDistance2Task, (void*)0, &stack5[255], 5);
	OSTaskCreate(pointerTask, (void*)0, &stack6[255], 6);
	OSTaskCreate(mouseTask, (void*)0, &stack7[255], 7);
	OSTaskCreate(rgbTask, (void*)0, &stack8[255], 8);
	
	OSStart();

	return 0;
}
