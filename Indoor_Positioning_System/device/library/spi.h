#ifndef __SPI_H__
#define __SPI_H__

#include "define.h"

#define SPI_TIMEOUT		0xFFFFFFFF

void spiInit(void);
INT8U spiTransfer(uint8 *buf, uint8 size);
INT8U spiRegTransfer(uint8 reg, uint8 *firstByte, uint8 *buf, uint8 size);
INT8U spiBufW(uint8 *buf, uint8 size);
INT8U spiBufR(uint8 *buf, uint8 size, uint8 fill);
INT8U spiBufWR(uint8 *txBuf, uint8 *rxBuf, uint8 size);
INT8U spiRegW(uint8 reg, uint8 *firstByte, uint8 *buf, uint8 size);
INT8U spiRegR(uint8 reg, uint8 *firstByte, uint8 *buf, uint8 size, uint8 fill);
INT8U spiRegWR(uint8 reg, uint8 *firstByte, uint8 *txBuf, uint8 *rxBuf, uint8 size);

#endif
