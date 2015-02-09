#include "pin.h"
#include "adc.h"

static uint32 adcGDR;
static OS_EVENT *adcAvl;
static OS_EVENT *adcRdy;

void adcInit(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(12);

	/* peripheral clock, 12.5 MHz */
	LPC_SC->PCLKSEL0 |= 0x03000000;

	/* ADC0 pin configuration */
	pinSel(0, 23, 1);
	pinMode(0, 23, 2);
	pinModeOD(0, 23, 0);

	/* ADC1 pin configuration */
	pinSel(0, 24, 1);
	pinMode(0, 24, 2);
	pinModeOD(0, 24, 0);

	/* ADC2 pin configuration */
	pinSel(0, 25, 1);
	pinMode(0, 25, 2);
	pinModeOD(0, 25, 0);

	/* ADC3 pin configuration */
	pinSel(0, 26, 1);
	pinMode(0, 26, 2);
	pinModeOD(0, 26, 0);

	/* ADC configuration */
	LPC_ADC->ADCR = 0x00;

	/* semaphore and queue */
	adcAvl = OSSemCreate(1);
	adcRdy = OSSemCreate(0);

	/* enable interrupt */
	LPC_ADC->ADINTEN = 0x0100;
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);
}

INT8U adcPend(void)
{
	INT8U err;;
	
	OSSemPend(adcAvl, ADC_AVL_TIMEOUT, &err);
	return err;
}

void adcPost(void)
{
	OSSemPost(adcAvl);
}

uint16 adcRead0(void)
{
	uint16 result;
	INT8U err;

	LPC_ADC->ADCR = 0x01200001;
	OSSemPend(adcRdy, ADC_TIMEOUT, &err);
	result = (adcGDR >> 4) & 0x0FFF;
	return result;
}

uint16 adcRead1(void)
{
	uint16 result;
	INT8U err;

	LPC_ADC->ADCR = 0x01200002;
	OSSemPend(adcRdy, ADC_TIMEOUT, &err);
	result = (adcGDR >> 4) & 0x0FFF;
	return result;
}

uint16 adcRead2(void)
{
	uint16 result;
	INT8U err;

	LPC_ADC->ADCR = 0x01200004;
	OSSemPend(adcRdy, ADC_TIMEOUT, &err);
	result = (adcGDR >> 4) & 0x0FFF;
	return result;
}

uint16 adcRead3(void)
{
	uint16 result;
	INT8U err;

	LPC_ADC->ADCR = 0x01200008;
	OSSemPend(adcRdy, ADC_TIMEOUT, &err);
	result = (adcGDR >> 4) & 0x0FFF;
	return result;
}

void ADC_IRQHandler(void)
{
	OSIntEnter();
	adcGDR = LPC_ADC->ADGDR;
	LPC_ADC->ADCR = 0x00000000;
	OSSemPost(adcRdy);
	OSIntExit();
}
