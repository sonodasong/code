#ifndef __I2C1_H__
#define __I2C1_H__

#include "define.h"

#define I2C1_TIME_OUT		0xFFFFFFFF

void i2c1Init(void);
INT8U i2c1RegWIgnoreNAck(uint8 address, uint8 reg, uint8 *tx, uint8 txSize);
uint8 i2c1ReadErrorCode(void);
uint8 i2c1WriteCount(void);

#endif
