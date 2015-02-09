#include "i2c.h"

#define i2cIntFlagGet()		(TWCR & ex(TWINT))
#define i2cIntFlagClr()		TWCR = 0x84

#define i2cReset()			TWCR = 0x80

#define i2cStart()			TWCR = 0xA4
#define i2cStartClr()		TWCR = 0x84
#define i2cAck()			TWCR = 0xC4
#define i2cNAck()			TWCR = 0x84
#define i2cStop()			TWCR = 0x94

static uint8 i2cTxCnt;
static uint8 i2cRxCnt;
static uint8 i2cErrorCode;

void i2cInit(void)
{
	// enable SCL pull-up
	PORTD |= ex(0);
	// enable SDA pull-up
	PORTD |= ex(1);
	TWSR = 0x00;
	// 400 kHz
	TWBR = 0x0C;
	TWCR = 0x04;
}

uint8 i2cRegR(uint8 address, uint8 reg, uint8 *rx, uint8 rxSize)
{
	uint16 cnt;
	
	i2cRxCnt = 0;
	i2cStart();
	while (1) {
		cnt = 0;
		while (i2cIntFlagGet() == 0x00 && cnt < 1000) {
			cnt++;
		}
		if (cnt == 1000) {
			i2cReset();
			break;
		}
		i2cErrorCode = TWSR & 0xF8;
		if (i2cErrorCode == 0x08) {
			TWDR = address << 1;
			i2cStartClr();
		} else if (i2cErrorCode == 0x10) {
			TWDR = (address << 1) | 0x01;
			i2cStartClr();
		} else if (i2cErrorCode == 0x18) {
			TWDR = reg;
			i2cIntFlagClr();
		} else if (i2cErrorCode == 0x20) {
			i2cStop();
			break;
		} else if (i2cErrorCode == 0x28) {
			i2cStart();
		} else if (i2cErrorCode == 0x30) {
			i2cStop();
			break;
		} else if (i2cErrorCode == 0x38) {
			i2cIntFlagClr();
			break;
		} else if (i2cErrorCode == 0x40) {
			if (rxSize < 2) {
				i2cNAck();
			} else {
				i2cAck();
			}
		} else if (i2cErrorCode == 0x48) {
			i2cStop();
			break;
		} else if (i2cErrorCode == 0x50) {
			rx[i2cRxCnt] = TWDR;
			i2cRxCnt++;
			if (i2cRxCnt < (rxSize - 1)) {
				i2cAck();
			} else {
				i2cNAck();
			}
		} else if (i2cErrorCode == 0x58) {
			rx[i2cRxCnt] = TWDR;
			i2cStop();
			break;
		} else {
			i2cReset();
			break;
		}
	}
	return i2cErrorCode;
}

uint8 i2cRegW(uint8 address, uint8 reg, uint8 *tx, uint8 txSize)
{
	i2cTxCnt = 0;
	i2cStart();
	while (1) {
		while (i2cIntFlagGet() == 0x00);
		i2cErrorCode = TWSR & 0xF8;
		if (i2cErrorCode == 0x08) {
			TWDR = address << 1;
			i2cStartClr();
		} else if (i2cErrorCode == 0x10) {
			TWDR = address << 1;
			i2cStartClr();
		} else if (i2cErrorCode == 0x18) {
			TWDR = reg;
			i2cIntFlagClr();
		} else if (i2cErrorCode == 0x20) {
			i2cStop();
			break;
		} else if (i2cErrorCode == 0x28) {
			if (i2cTxCnt < txSize) {
				TWDR = tx[i2cTxCnt];
				i2cTxCnt++;
				i2cIntFlagClr();
			} else {
				i2cStop();
				break;
			}
		} else if (i2cErrorCode == 0x30) {
			i2cStop();
			break;
		} else if (i2cErrorCode == 0x38) {
			i2cIntFlagClr();
			break;
		}
	}
	return i2cErrorCode;
}

uint8 i2cReadCount(void)
{
	return i2cRxCnt + 1;
}

uint8 i2cWriteCount(void)
{
	return i2cTxCnt;
}
