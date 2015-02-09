#include "nrf24l01p_port.h"
#include "nrf24l01p.h"

static OS_EVENT *nrf24l01pRdy;

void nrf24l01pInit(void)
{
	nrf24l01pCELow();
	nrf24l01pCEInit();
	nrf24l01pIRQInit();
	nrf24l01pIRQDisable();
	nrf24l01pRdy = OSSemCreate(0);
}

void nrf24l01pInitFromTask(uint8 mode)
{
	uint8 nrf24l01pAddress[ADDRESS_WIDTH];
	
	nrf24l01pAddress[0] = 0x34;
	nrf24l01pAddress[1] = 0x43;
	nrf24l01pAddress[2] = 0x10;
	nrf24l01pAddress[3] = 0x10;
	nrf24l01pAddress[4] = 0x01;
	
	OSTimeDly(OS_TICKS_PER_SEC / 10 + 1);	//power on reset 100 ms

	nrf24l01pCELow();
	nrf24l01pRegByteW(CONFIG, 0x0D);
	nrf24l01pCEHigh();
	OSTimeDly(2);

	nrf24l01pCELow();
	nrf24l01pRegByteW(EN_AA, 0x01);
	nrf24l01pRegByteW(EN_RXADDR, 0x01);
	nrf24l01pRegByteW(SETUP_AW, 0x03);
	nrf24l01pRegByteW(SETUP_RETR, 0x1F);
	nrf24l01pRegByteW(RF_CH, 120);
	nrf24l01pRegByteW(RF_SETUP, 0x26);
	nrf24l01pRegBufW(RX_ADDR_P0, nrf24l01pAddress, ADDRESS_WIDTH);
	nrf24l01pRegBufW(TX_ADDR, nrf24l01pAddress, ADDRESS_WIDTH);
	nrf24l01pRegByteW(RX_PW_P0, PLOAD_WIDTH);
	nrf24l01CmdW(FLUSH_TX);
	nrf24l01CmdW(FLUSH_RX);
	nrf24l01pRegByteW(STATUS, 0x70);
	if (mode == NRF24L01P_RX_MODE) {
		nrf24l01pRegByteW(CONFIG, 0x0F);
	} else {
		nrf24l01pRegByteW(CONFIG, 0x0E);
	}
	nrf24l01pCEHigh();
	OSTimeDly(2);
}

uint8 nrf24l01pWrite(uint8 *buf, uint32 timeout)
{
	INT8U err;
	uint8 status;
	
	nrf24l01pCmdBufW(WRTX_PAYLOAD, buf, PLOAD_WIDTH);
	nrf24l01pIRQEnable();
	OSSemPend(nrf24l01pRdy, timeout, &err);
	if (err == OS_ERR_NONE) {
		status = nrf24l01CmdW(NOP);
		nrf24l01pRegByteW(STATUS, 0x70);
		if (status & TX_DS) {
			return 0;
		} else if (status & MAX_RT) {
			nrf24l01CmdW(FLUSH_TX);
			return 1;
		} else {
			nrf24l01CmdW(FLUSH_TX);
			return 3;
		}
	} else {
		nrf24l01pIRQDisable();
		nrf24l01CmdW(FLUSH_TX);
		return 2;
	}
}

uint8 nrf24l01pRead(uint8 *buf, uint32 timeout)
{
	INT8U err;
	uint8 status;
	
	nrf24l01CmdW(FLUSH_RX);
	nrf24l01pRegByteW(STATUS, 0x70);
	OSSemSet(nrf24l01pRdy, 0, &err);
	nrf24l01pIRQEnable();
	OSSemPend(nrf24l01pRdy, timeout, &err);
	if (err == OS_ERR_NONE) {
		status = nrf24l01CmdW(NOP);
		nrf24l01pRegByteW(STATUS, 0x70);
		if (status & RX_DR) {
			nrf24l01pCmdBufR(R_RX_PAYLOAD, buf, PLOAD_WIDTH);
			return 0;
		} else {
			return 2;
		}
	} else {
		nrf24l01pIRQDisable();
		return 1;
	}
}

void nrf24l01pIRQHandler(void)
{
	nrf24l01pIRQDisable();
	OSSemPost(nrf24l01pRdy);
}
