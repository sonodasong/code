#ifndef __I2C0_H__
#define __I2C0_H__

#include "define.h"

#define I2C0_TIME_OUT		0xFFFFFFFF

void i2c0Init(void);
INT8U i2c0RegW(uint8 address, uint8 reg, uint8 *tx, uint8 txSize);
INT8U i2c0RegR(uint8 address, uint8 reg, uint8 *rx, uint8 rxSize);
INT8U i2c0RegWIgnoreNAck(uint8 address, uint8 reg, uint8 *tx, uint8 txSize);
uint8 i2c0ReadErrorCode(void);
uint8 i2c0WriteCount(void);
uint8 i2c0ReadCount(void);

#endif
