#include "pin.h"
#include "sonar_tx.h"
#include "basic.h"

#define repetitiveTimerEnable()			LPC_RIT->RICTRL |= ex(3)
#define repetitiveTimerDisable()		LPC_RIT->RICTRL &= rex(3)
#define repetitiveTimerIntClr()			LPC_RIT->RICTRL |= ex(0)

#define timer3Enable()					LPC_TIM3->TCR |= ex(0)
#define timer3Disable()					LPC_TIM3->TCR &= rex(0)
#define timer3IntClr()					LPC_TIM3->IR = ex(0)

static uint8 sonarTxPulseCnt;

static OS_EVENT *sonarTxRdy;

static void repetitiveTimerSetup(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(16);

	/* peripheral clock, 100 MHz */
	LPC_SC->PCLKSEL1 |= ex(26);
	LPC_SC->PCLKSEL1 &= rex(27);

	/* repetitive timer setup */
	LPC_RIT->RICTRL = 0x00;
	LPC_RIT->RIMASK = 0x00;

	/* semaphore */
	sonarTxRdy = OSSemCreate(0);

	/* set up interrupt */
	repetitiveTimerIntClr();
	NVIC_ClearPendingIRQ(RIT_IRQn);
	NVIC_EnableIRQ(RIT_IRQn);
}

static void timer3Setup(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(23);

	/* peripheral clock, 100 MHz */
	LPC_SC->PCLKSEL1 |= ex(14);
	LPC_SC->PCLKSEL1 &= rex(15);

	/* MAT0 pin configuration */
	pinSel(0, 10, 3);
	pinMode(0, 10, 0);
	pinModeOD(0, 10, 0);

	/* MAT1 pin configuration */
	pinSel(0, 11, 3);
	pinMode(0, 11, 0);
	pinModeOD(0, 11, 0);

	/* timer3 setup */
	LPC_TIM3->TCR = 0x00;
	LPC_TIM3->CTCR = 0x00;
	LPC_TIM3->PR = 49;
	LPC_TIM3->MR0 = 24;
	LPC_TIM3->MR1 = 24;
	LPC_TIM3->MCR = 0x03;
	LPC_TIM3->EMR = 0xF0;

	/* setup interrupt */
	timer3IntClr();
	NVIC_ClearPendingIRQ(TIMER3_IRQn);
	NVIC_EnableIRQ(TIMER3_IRQn);
}

void sonarTxInit(void)
{
	repetitiveTimerSetup();
	timer3Setup();
}

INT8U sonarTxSendPulse(uint32 delay, INT32U timeout)
{
	INT8U err;

	LPC_RIT->RICOMPVAL = delay;
	LPC_RIT->RICOUNTER = 0x00;

	LPC_TIM3->PC = 0;
	LPC_TIM3->TC = 0;
	sonarTxPulseCnt = 0;

	repetitiveTimerEnable();
	OSSemPend(sonarTxRdy, timeout, &err);
	return err;
}

void RIT_IRQHandler(void)
{
	OSIntEnter();
	repetitiveTimerDisable();
	repetitiveTimerIntClr();
	LPC_TIM3->EMR = 0xF1;
	timer3Enable();
	OSIntExit();
}

void TIMER3_IRQHandler(void)
{
	OSIntEnter();
	if (sonarTxPulseCnt == 14) {
		LPC_TIM3->EMR = 0xC2;
	} else if (sonarTxPulseCnt == 15) {
		timer3Disable();
		OSSemPost(sonarTxRdy);
	}
	sonarTxPulseCnt++;
	timer3IntClr();
	OSIntExit();
}
