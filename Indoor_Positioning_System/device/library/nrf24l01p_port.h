#ifndef __NRF24L01P_PORT_H__
#define __NRF24L01P_PORT_H__

#include "define.h"

void nrf24l01pCEInit(void);
#define nrf24l01pCEHigh()			LPC_GPIO0->FIOSET = ex(21)
#define nrf24l01pCELow()			LPC_GPIO0->FIOCLR = ex(21)

void nrf24l01pIRQInit(void);
void nrf24l01pIRQEnable(void);
void nrf24l01pIRQDisable(void);

uint8 nrf24l01CmdW(uint8 cmd);
void nrf24l01pCmdByteW(uint8 cmd, uint8 value);
uint8 nrf24l01pCmdByteR(uint8 cmd);
void nrf24l01pCmdBufW(uint8 cmd, uint8 *buf, uint8 size);
void nrf24l01pCmdBufR(uint8 cmd, uint8 *buf, uint8 size);
void nrf24l01pRegByteW(uint8 reg, uint8 value);
uint8 nrf24l01pRegByteR(uint8 reg);
void nrf24l01pRegBufW(uint8 reg, uint8 *buf, uint8 size);
void nrf24l01pRegBufR(uint8 reg, uint8 *buf, uint8 size);

#endif
