#ifndef __I2C_H__
#define __I2C_H__

#include "define.h"

void i2cInit(void);
uint8 i2cRegR(uint8 address, uint8 reg, uint8 *rx, uint8 rxSize);
uint8 i2cRegW(uint8 address, uint8 reg, uint8 *tx, uint8 txSize);
uint8 i2cReadCount(void);
uint8 i2cWriteCount(void);

#endif