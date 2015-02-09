#include "pin.h"
#include "sonar_rx.h"

#define timer0Enable()					LPC_TIM0->TCR |= ex(0)
#define timer0Disable()					LPC_TIM0->TCR &= rex(0)
#define timer0IntClr()					LPC_TIM0->IR = ex(0)

#define triggerHigh()					LPC_GPIO2->FIOSET = ex(8)
#define triggerLow()					LPC_GPIO2->FIOCLR = ex(8)

#define timer1Enable()					LPC_TIM1->TCR |= ex(0)
#define timer1Cap1IntClr()				LPC_TIM1->IR = ex(5)

#define timer2Enable()					LPC_TIM2->TCR |= ex(0)
#define timer2Cap1IntClr()				LPC_TIM2->IR = ex(5)

#define timer3Enable()					LPC_TIM3->TCR |= ex(0)
#define timer3Cap1IntClr()				LPC_TIM3->IR = ex(5)

static uint32 sonarRxCap0Temp;
static uint32 sonarRxCap1Temp;
static uint32 sonarRxCap2Temp;

static OS_EVENT *sonarRxTrigRdy;
static OS_EVENT *sonarRxCap0Rdy;
static OS_EVENT *sonarRxCap1Rdy;
static OS_EVENT *sonarRxCap2Rdy;

static void timer0Setup(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(1);

	/* peripheral clock, 100 MHz */
	LPC_SC->PCLKSEL0 |= ex(2);
	LPC_SC->PCLKSEL0 &= rex(3);

	/* trigger pin configuration */
	pinSel(2, 8, 0);
	pinMode(2, 8, 0);
	pinModeOD(2, 8, 0);
	LPC_GPIO2->FIOMASK &= rex(8);
	LPC_GPIO2->FIODIR |= ex(8);

	/* timer0 setup */
	LPC_TIM0->TCR = 0x00;
	LPC_TIM0->CTCR = 0x00;
	LPC_TIM0->PR = 99;
	LPC_TIM0->MR0 = 9;
	LPC_TIM0->MCR = 0x07;

	/* semaphore */
	sonarRxTrigRdy = OSSemCreate(0);

	/* setup interrupt */
	timer0IntClr();
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);
}

static void timer1Setup(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(2);

	/* peripheral clock, 100 MHz */
	LPC_SC->PCLKSEL0 |= ex(4);
	LPC_SC->PCLKSEL0 &= rex(5);

	/* capture0 pin configuration */
	pinSel(1, 19, 3);
	pinMode(1, 19, 0);
	pinModeOD(1, 19, 0);

	/* timer1 setup */
	LPC_TIM1->TCR = 0x00;
	LPC_TIM1->CTCR = 0x00;
	LPC_TIM1->PR = 99;
	LPC_TIM1->PC = 0;
	LPC_TIM1->TC = 0;
	LPC_TIM1->CCR |= ex(3);
	LPC_TIM1->CCR &= rex(4);

	/* semaphore */
	sonarRxCap0Rdy = OSSemCreate(0);

	/* setup interrupt */
	timer1Cap1IntClr();
	LPC_TIM1->CCR |= ex(5);
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	NVIC_EnableIRQ(TIMER1_IRQn);

	/* enable timer 1 */
	timer1Enable();
}

static void timer2Setup(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(22);

	/* peripheral clock, 100 MHz */
	LPC_SC->PCLKSEL1 |= ex(12);
	LPC_SC->PCLKSEL1 &= rex(13);

	/* capture1 pin configuration */
	pinSel(0, 5, 3);
	pinMode(0, 5, 0);
	pinModeOD(0, 5, 0);

	/* timer2 setup */
	LPC_TIM2->TCR = 0x00;
	LPC_TIM2->CTCR = 0x00;
	LPC_TIM2->PR = 99;
	LPC_TIM2->PC = 0;
	LPC_TIM2->TC = 0;
	LPC_TIM2->CCR |= ex(3);
	LPC_TIM2->CCR &= rex(4);

	/* semaphore */
	sonarRxCap1Rdy = OSSemCreate(0);

	/* setup interrupt */
	timer2Cap1IntClr();
	LPC_TIM2->CCR |= ex(5);
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
	NVIC_EnableIRQ(TIMER2_IRQn);

	/* enable timer 2 */
	timer2Enable();
}

static void timer3Setup(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(23);

	/* peripheral clock, 100 MHz */
	LPC_SC->PCLKSEL1 |= ex(14);
	LPC_SC->PCLKSEL1 &= rex(15);

	/* capture2 pin configuration */
	pinSel(0, 24, 3);
	pinMode(0, 24, 0);
	pinModeOD(0, 24, 0);

	/* timer3 setup */
	LPC_TIM3->TCR = 0x00;
	LPC_TIM3->CTCR = 0x00;
	LPC_TIM3->PR = 99;
	LPC_TIM3->PC = 0;
	LPC_TIM3->TC = 0;
	LPC_TIM3->CCR |= ex(3);
	LPC_TIM3->CCR &= rex(4);

	/* semaphore */
	sonarRxCap2Rdy = OSSemCreate(0);

	/* setup interrupt */
	timer3Cap1IntClr();
	LPC_TIM3->CCR |= ex(5);
	NVIC_ClearPendingIRQ(TIMER3_IRQn);
	NVIC_EnableIRQ(TIMER3_IRQn);

	/* enable timer 3 */
	timer3Enable();
}

void sonarRxInit(void)
{
	timer0Setup();
	timer1Setup();
	timer2Setup();
	timer3Setup();
}

INT8U sonarRxTrigger(INT32U timeout)
{
	INT8U err;

	LPC_TIM0->PC = 0;
	LPC_TIM0->TC = 0;
	triggerHigh();
	timer0Enable();
	OSSemPend(sonarRxTrigRdy, timeout, &err);
	return err;
}

void sonarRxReadReset(void)
{
	INT8U err;

	LPC_TIM1->CCR |= ex(3);
	LPC_TIM1->CCR &= rex(4);
	OSSemSet(sonarRxCap0Rdy, 0, &err);
	LPC_TIM2->CCR |= ex(3);
	LPC_TIM2->CCR &= rex(4);
	OSSemSet(sonarRxCap1Rdy, 0, &err);
	LPC_TIM3->CCR |= ex(3);
	LPC_TIM3->CCR &= rex(4);
	OSSemSet(sonarRxCap2Rdy, 0, &err);
}

INT8U sonarRxRead0(uint32 *distance, INT32U timeout)
{
	INT8U err;

	OSSemPend(sonarRxCap0Rdy, timeout, &err);
	if (err == OS_ERR_NONE) {
		*distance = sonarRxCap0Temp;
	}
	return err;
}

INT8U sonarRxRead1(uint32 *distance, INT32U timeout)
{
	INT8U err;

	OSSemPend(sonarRxCap1Rdy, timeout, &err);
	if (err == OS_ERR_NONE) {
		*distance = sonarRxCap1Temp;
	}
	return err;
}

INT8U sonarRxRead2(uint32 *distance, INT32U timeout)
{
	INT8U err;

	OSSemPend(sonarRxCap2Rdy, timeout, &err);
	if (err == OS_ERR_NONE) {
		*distance = sonarRxCap2Temp;
	}
	return err;
}

void TIMER0_IRQHandler(void)
{
	OSIntEnter();
	triggerLow();
	OSSemPost(sonarRxTrigRdy);
	timer0IntClr();
	OSIntExit();
}

static void timer1IRQHandler(void)
{
	if (LPC_TIM1->CCR & ex(3)) {
		sonarRxCap0Temp = LPC_TIM1->CR1;
		LPC_TIM1->CCR &= rex(3);
		LPC_TIM1->CCR |= ex(4);
	} else if (LPC_TIM1->CCR & ex(4)) {
		sonarRxCap0Temp = LPC_TIM1->CR1 - sonarRxCap0Temp;
		OSSemPost(sonarRxCap0Rdy);
	}
	timer1Cap1IntClr();
}

static void timer2IRQHandler(void)
{
	if (LPC_TIM2->CCR & ex(3)) {
		sonarRxCap1Temp = LPC_TIM2->CR1;
		LPC_TIM2->CCR &= rex(3);
		LPC_TIM2->CCR |= ex(4);
	} else if (LPC_TIM2->CCR & ex(4)) {
		sonarRxCap1Temp = LPC_TIM2->CR1 - sonarRxCap1Temp;
		OSSemPost(sonarRxCap1Rdy);
	}
	timer2Cap1IntClr();
}

static void timer3IRQHandler(void)
{
	if (LPC_TIM3->CCR & ex(3)) {
		sonarRxCap2Temp = LPC_TIM3->CR1;
		LPC_TIM3->CCR &= rex(3);
		LPC_TIM3->CCR |= ex(4);
	} else if (LPC_TIM3->CCR & ex(4)) {
		sonarRxCap2Temp = LPC_TIM3->CR1 - sonarRxCap2Temp;
		OSSemPost(sonarRxCap2Rdy);
	}
	timer3Cap1IntClr();
}

void TIMER1_IRQHandler(void)
{
	OSIntEnter();
	timer1IRQHandler();
	OSIntExit();
}

void TIMER2_IRQHandler(void)
{
	OSIntEnter();
	timer2IRQHandler();
	OSIntExit();
}

void TIMER3_IRQHandler(void)
{
	OSIntEnter();
	timer3IRQHandler();
	OSIntExit();
}
