#include "pin.h"
#include "spi.h"

#define spiSSHigh()		LPC_GPIO0->FIOSET = ex(16)
#define spiSSLow()		LPC_GPIO0->FIOCLR = ex(16)

static uint8 *spiTxBuf;
static uint8 *spiRxBuf;
static uint8 spiSize;
static uint8 spiCnt;
static uint8 spiFill;
static uint8 spiFirstByte;

static OS_EVENT *spiRdy;

static void (*spiHandlerPtr)(void);
static void spiBufWHandler(void);
static void spiBufRHandler(void);
static void spiBufWRHandler(void);
static void spiRegWHandler(void);
static void spiRegRHandler(void);
static void spiRegWRHandler(void);

void spiInit(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(8);

	/* peripheral clock, 50 MHz */
	LPC_SC->PCLKSEL0 |= ex(17);
	LPC_SC->PCLKSEL0 &= rex(16);

	/* MOSI pin configuration */
	pinSel(0, 18, 3);
	pinMode(0, 18, 0);
	pinModeOD(0, 18 ,0);

	/* MISO pin configuration */
	pinSel(0, 17, 3);
	pinMode(0, 17, 0);
	pinModeOD(0, 17 ,0);

	/* SCK pin configuration */
	pinSel(0, 15, 3);
	pinMode(0, 15, 0);
	pinModeOD(0, 15 ,0);

	/* chip select pin configuration */
	pinSel(0, 16, 0);
	pinMode(0, 16, 0);
	pinModeOD(0, 16 ,0);
	LPC_GPIO0->FIOMASK &= rex(16);
	LPC_GPIO0->FIODIR |= ex(16);
	spiSSHigh();

	/* 8-bit, CPHA = 0, CPOL = 0 */
	LPC_SPI->SPCR = 0x0820;

	/* 1 Mbps */
	LPC_SPI->SPCCR = 50;

	/* semaphore */
	spiRdy = OSSemCreate(0);

	/* setup interrupt */
	LPC_SPI->SPCR |= ex(7);
	NVIC_ClearPendingIRQ(SPI_IRQn);
	NVIC_EnableIRQ(SPI_IRQn);
}

INT8U spiBufW(uint8 *buf, uint8 size)
{
	INT8U err;

	spiTxBuf = buf;
	spiSize = size;
	spiCnt = 1;
	spiHandlerPtr = spiBufWHandler;
	spiSSLow();
	LPC_SPI->SPDR = buf[0];
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	return err;
}

INT8U spiBufR(uint8 *buf, uint8 size, uint8 fill)
{
	INT8U err;

	spiRxBuf = buf;
	spiSize = size;
	spiCnt = 0;
	spiFill = fill;
	spiHandlerPtr = spiBufRHandler;
	spiSSLow();
	LPC_SPI->SPDR = fill;
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	return err;
}

INT8U spiBufWR(uint8 *txBuf, uint8 *rxBuf, uint8 size)
{
	INT8U err;

	spiTxBuf = txBuf;
	spiRxBuf = rxBuf;
	spiSize = size;
	spiCnt = 0;
	spiHandlerPtr = spiBufWRHandler;
	spiSSLow();
	LPC_SPI->SPDR = txBuf[0];
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	return err;
}

INT8U spiRegW(uint8 reg, uint8 *firstByte, uint8 *buf, uint8 size)
{
	INT8U err;

	spiTxBuf = buf;
	spiSize = size;
	spiCnt = 0xFF;
	spiHandlerPtr = spiRegWHandler;
	spiSSLow();
	LPC_SPI->SPDR = reg;
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	*firstByte = spiFirstByte;
	return err;
}

INT8U spiRegR(uint8 reg, uint8 *firstByte, uint8 *buf, uint8 size, uint8 fill)
{
	INT8U err;

	spiRxBuf = buf;
	spiSize = size;
	spiCnt = 0xFF;
	spiFill = fill;
	spiHandlerPtr = spiRegRHandler;
	spiSSLow();
	LPC_SPI->SPDR = reg;
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	*firstByte = spiFirstByte;
	return err;
}

INT8U spiRegWR(uint8 reg, uint8 *firstByte, uint8 *txBuf, uint8 *rxBuf, uint8 size)
{
	INT8U err;

	spiTxBuf = txBuf;
	spiRxBuf = rxBuf;
	spiSize = size;
	spiCnt = 0xFF;
	spiHandlerPtr = spiRegWRHandler;
	spiSSLow();
	LPC_SPI->SPDR = reg;
	OSSemPend(spiRdy, SPI_TIMEOUT, &err);
	*firstByte = spiFirstByte;
	return err;
}

static void spiBufWHandler(void)
{
	uint32 status;

	status = LPC_SPI->SPSR;
	if (status & 0x80) {
		if (spiCnt < spiSize) {
			LPC_SPI->SPDR = spiTxBuf[spiCnt];
			spiCnt++;
		} else {
			spiSSHigh();
			OSSemPost(spiRdy);
		}
	}
	LPC_SPI->SPINT = ex(0);
}

static void spiBufRHandler(void)
{
	uint32 status;

	status = LPC_SPI->SPSR;
	if (status & 0x80) {
		spiRxBuf[spiCnt] = LPC_SPI->SPDR;
		spiCnt++;
		if (spiCnt < spiSize) {
			LPC_SPI->SPDR = spiFill;
		} else {
			spiSSHigh();
			OSSemPost(spiRdy);
		}
	}
	LPC_SPI->SPINT = ex(0);
}

static void spiBufWRHandler(void)
{
	uint32 status;

	status = LPC_SPI->SPSR;
	if (status & 0x80) {
		spiRxBuf[spiCnt] = LPC_SPI->SPDR;
		spiCnt++;
		if (spiCnt < spiSize) {
			LPC_SPI->SPDR = spiTxBuf[spiCnt];
		} else {
			spiSSHigh();
			OSSemPost(spiRdy);
		}
	}
	LPC_SPI->SPINT = ex(0);
}

static void spiRegWHandler(void)
{
	uint32 status;

	status = LPC_SPI->SPSR;
	if (status & 0x80) {
		if (spiCnt == 0xFF) {
			spiFirstByte = LPC_SPI->SPDR;
			LPC_SPI->SPDR = spiTxBuf[0];
			spiCnt = 1;
		} else {
			if (spiCnt < spiSize) {
				LPC_SPI->SPDR = spiTxBuf[spiCnt];
				spiCnt++;
			} else {
				spiSSHigh();
				OSSemPost(spiRdy);
			}
		}
	}
	LPC_SPI->SPINT = ex(0);
}

static void spiRegRHandler(void)
{
	uint32 status;

	status = LPC_SPI->SPSR;
	if (status & 0x80) {
		if (spiCnt == 0xFF) {
			spiFirstByte = LPC_SPI->SPDR;
			LPC_SPI->SPDR = spiFill;
			spiCnt = 0;
		} else {
			spiRxBuf[spiCnt] = LPC_SPI->SPDR;
			spiCnt++;
			if (spiCnt < spiSize) {
				LPC_SPI->SPDR = spiFill;
			} else {
				spiSSHigh();
				OSSemPost(spiRdy);
			}
		}
	}
	LPC_SPI->SPINT = ex(0);
}

static void spiRegWRHandler(void)
{
	uint32 status;

	status = LPC_SPI->SPSR;
	if (status & 0x80) {
		if (spiCnt == 0xFF) {
			spiFirstByte = LPC_SPI->SPDR;
			LPC_SPI->SPDR = spiTxBuf[0];
			spiCnt = 0;
		} else {
			spiRxBuf[spiCnt] = LPC_SPI->SPDR;
			spiCnt++;
			if (spiCnt < spiSize) {
				LPC_SPI->SPDR = spiTxBuf[spiCnt];
			} else {
				spiSSHigh();
				OSSemPost(spiRdy);
			}
		}
	}
	LPC_SPI->SPINT = ex(0);
}

void SPI_IRQHandler(void)
{
	OSIntEnter();
	spiHandlerPtr();
	OSIntExit();
}
