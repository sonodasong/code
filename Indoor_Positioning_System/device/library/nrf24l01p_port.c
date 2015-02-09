#include "pin.h"
#include "spi.h"
#include "nrf24l01p_port.h"

extern void nrf24l01pIRQHandler(void);

void nrf24l01pCEInit(void)
{
	pinSel(0, 21, 0);
	pinMode(0, 21, 0);
	pinModeOD(0, 21, 0);
	LPC_GPIO0->FIOMASK &= rex(21);
	LPC_GPIO0->FIODIR |= ex(21);
}

void nrf24l01pIRQInit(void)
{
	pinSel(2, 10, 1);
	pinMode(2, 10, 0);
	pinModeOD(2, 10, 0);
	LPC_SC->EXTMODE &= rex(0);
	LPC_SC->EXTPOLAR &= rex(0);
}

void nrf24l01pIRQEnable(void)
{
	LPC_SC->EXTINT = ex(0);
	NVIC_ClearPendingIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);
}

void nrf24l01pIRQDisable(void)
{
	NVIC_DisableIRQ(EINT0_IRQn);
}

uint8 nrf24l01CmdW(uint8 cmd)
{
	spiBufWR(&cmd, &cmd, 1);
	return cmd;
}

void nrf24l01pCmdByteW(uint8 cmd, uint8 value)
{
	spiRegW(cmd, &cmd, &value, 1);
}

uint8 nrf24l01pCmdByteR(uint8 cmd)
{
	uint8 temp;
	
	spiRegR(cmd, &cmd, &temp, 1, 0x00);
	return temp;
}

void nrf24l01pCmdBufW(uint8 cmd, uint8 *buf, uint8 size)
{
	spiRegW(cmd, &cmd, buf, size);
}

void nrf24l01pCmdBufR(uint8 cmd, uint8 *buf, uint8 size)
{
	spiRegR(cmd, &cmd, buf, size, 0x00);
}

void nrf24l01pRegByteW(uint8 reg, uint8 value)
{
	spiRegW(0x20 | reg, &reg, &value, 1);
}

uint8 nrf24l01pRegByteR(uint8 reg)
{
	uint8 temp;
	
	spiRegR(reg, &reg, &temp, 1, 0x00);
	return temp;
}

void nrf24l01pRegBufW(uint8 reg, uint8 *buf, uint8 size)
{
	spiRegW(0x20 | reg, &reg, buf, size);
}

void nrf24l01pRegBufR(uint8 reg, uint8 *buf, uint8 size)
{
	spiRegR(reg, &reg, buf, size, 0x00);
}

void EINT0_IRQHandler(void)
{
	OSIntEnter();
	nrf24l01pIRQHandler();
	OSIntExit();
}
