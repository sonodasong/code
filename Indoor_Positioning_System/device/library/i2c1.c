#include "pin.h"
#include "i2c1.h"

#define i2c1IntFlagClr()		LPC_I2C1->I2CONCLR = ex(3)

#define i2c1Start()				LPC_I2C1->I2CONSET = ex(5)
#define i2c1StartClr()			LPC_I2C1->I2CONCLR = ex(5)
#define i2c1Ack()				LPC_I2C1->I2CONSET = ex(2)
#define i2c1NAck()				LPC_I2C1->I2CONCLR = ex(2)
#define i2c1Stop()				LPC_I2C1->I2CONSET = ex(4)

static uint8 i2c1Address;
static uint8 i2c1Reg;
static uint8 i2c1ErrorCode;

static uint8 *i2c1TxPtr;
static uint8 i2c1TxCnt;
static uint8 i2c1TxSize;

static OS_EVENT *i2c1Ready;

static void (*i2c1HandlerPtr)(void);
static void i2c1RegWIgnoreNAckHandler(void);

void i2c1Init(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(19);

	/* peripheral clock, 50 MHz */
	LPC_SC->PCLKSEL1 &= 0xFFFFFF3F;
	LPC_SC->PCLKSEL1 |= 0x80;

	/* SDA1 pin configuration */
	pinSel(0, 0, 3);
	pinMode(0 ,0, 2);
	pinModeOD(0, 0, 1);

	/* SCL1 pin configuration */
	pinSel(0, 1, 3);
	pinMode(0, 1, 2);
	pinModeOD(0, 1, 1);

	/* 400 kHz */
	LPC_I2C1->I2CONCLR = 0x64;
	LPC_I2C1->MMCTRL = 0x00;
	LPC_I2C1->I2SCLH = 62;
	LPC_I2C1->I2SCLL = 63;

	/* semaphore */
	i2c1Ready = OSSemCreate(0);

	/* interrupt */
	i2c1IntFlagClr();
	NVIC_ClearPendingIRQ(I2C1_IRQn);
	NVIC_EnableIRQ(I2C1_IRQn);

	/* enable I2C0 */
	LPC_I2C1->I2CONSET = ex(6);
}

INT8U i2c1RegWIgnoreNAck(uint8 address, uint8 reg, uint8 *tx, uint8 txSize)
{
	INT8U err;
	
	i2c1Address = address;
	i2c1Reg = reg;
	i2c1TxPtr = tx;
	i2c1TxCnt = 0;
	i2c1TxSize = txSize;
	i2c1HandlerPtr = i2c1RegWIgnoreNAckHandler;
	i2c1Start();
	OSSemPend(i2c1Ready, I2C1_TIME_OUT, &err);
	return err;
}

uint8 i2c1ReadErrorCode(void)
{
	return i2c1ErrorCode;
}

uint8 i2c1WriteCount(void)
{
	return i2c1TxCnt;
}

static void i2c1RegWIgnoreNAckHandler(void)
{
	i2c1ErrorCode = LPC_I2C1->I2STAT & 0xF8;
	if (i2c1ErrorCode == 0x08) {
		i2c1StartClr();
		LPC_I2C1->I2DAT = i2c1Address << 1;
	} else if (i2c1ErrorCode == 0x10) {
		i2c1StartClr();
		LPC_I2C1->I2DAT = i2c1Address << 1;
	} else if ((i2c1ErrorCode == 0x18) || (i2c1ErrorCode == 0x20)) {
		LPC_I2C1->I2DAT = i2c1Reg;
	} else if ((i2c1ErrorCode == 0x28) || (i2c1ErrorCode == 0x30)) {
		if (i2c1TxCnt < i2c1TxSize) {
			LPC_I2C1->I2DAT = *(i2c1TxPtr + i2c1TxCnt);
			i2c1TxCnt++;
		} else {
			i2c1Stop();
			OSSemPost(i2c1Ready);
		}
	} else if (i2c1ErrorCode == 0x38) {
		OSSemPost(i2c1Ready);
	}
	i2c1IntFlagClr();
}

void I2C1_IRQHandler(void)
{
	OSIntEnter();
	(*i2c1HandlerPtr)();
	OSIntExit();
}
