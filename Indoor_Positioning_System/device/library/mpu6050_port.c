#include "pin.h"
#include "i2c0.h"
#include "mpu6050_port.h"

extern void mpu6050DMPIRQHandler(void);

static uint16 mpu6050ReverseWord(uint16 data)
{
	uint8 temp;
	
	temp = (uint8)data;
	data = data >> 8;
	data |= temp << 8;
	return data;
}

int8 readBit(uint8 devAddr, uint8 regAddr, uint8 bitNum, uint8 *data)
{
	uint8 b;
	int8 count;
	
	count = readByte(devAddr, regAddr, &b);
	*data = b & (1 << bitNum);
	return count;
}

int8 readBitW(uint8 devAddr, uint8 regAddr, uint8 bitNum, uint16 *data)
{
	uint16 b;
	int8 count;
	
	count = readWord(devAddr, regAddr, &b);
	*data = b & (1 << bitNum);
	return count;
}

int8 readBits(uint8 devAddr, uint8 regAddr, uint8 bitStart, uint8 length, uint8 *data)
{
	uint8 b;
	int8 count;
	uint8 mask;
	
	if ((count = readByte(devAddr, regAddr, &b)) != 0) {
		mask = ((1 << length) - 1) << (bitStart - length + 1);
		b &= mask;
		b >>= (bitStart - length + 1);
		*data = b;
	}
	return count;
}

int8 readBitsW(uint8 devAddr, uint8 regAddr, uint8 bitStart, uint8 length, uint16 *data)
{
	uint16 w;
	int8 count;
	uint16 mask;
	
	if ((count = readWord(devAddr, regAddr, &w)) != 0) {
		mask = ((1 << length) - 1) << (bitStart - length + 1);
		w &= mask;
		w >>= (bitStart - length + 1);
		*data = w;
	}
	return count;
}

int8 readByte(uint8 devAddr, uint8 regAddr, uint8 *data)
{
	return readBytes(devAddr, regAddr, 1, data);
}

int8 readWord(uint8 devAddr, uint8 regAddr, uint16 *data)
{
	return readWords(devAddr, regAddr, 1, data);
}

int8 readBytes(uint8 devAddr, uint8 regAddr, uint8 length, uint8 *data)
{
	int8 count;
	
	i2c0RegR(devAddr, regAddr, data, length);
	if (i2c0ReadCount() == length) {
		count = length & 0x7F;
	} else {
		count = -1;
	}
	return count;
}

int8 readWords(uint8 devAddr, uint8 regAddr, uint8 length, uint16 *data)
{
	int8 count;
	uint8 i;
	
	i2c0RegR(devAddr, regAddr, (uint8 *)data, length * 2);
	if (i2c0ReadCount() == length * 2) {
		count = length & 0x7F;
		for (i = 0; i < length; i++) {
			data[i] = mpu6050ReverseWord(data[i]);
		}
	} else {
		count = -1;
	}
	return count;
}

boolean writeBit(uint8 devAddr, uint8 regAddr, uint8 bitNum, uint8 data)
{
	uint8 b;
	
	readByte(devAddr, regAddr, &b);
	b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	return writeByte(devAddr, regAddr, b);
}

boolean writeBitW(uint8 devAddr, uint8 regAddr, uint8 bitNum, uint16 data)
{
	uint16 w;
	
	readWord(devAddr, regAddr, &w);
	w = (data != 0) ? (w | (1 << bitNum)) : (w & ~(1 << bitNum));
	return writeWord(devAddr, regAddr, w);
}

boolean writeBits(uint8 devAddr, uint8 regAddr, uint8 bitStart, uint8 length, uint8 data)
{
	uint8 b;
	
	if (readByte(devAddr, regAddr, &b) != 0) {
		uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
		data <<= (bitStart - length + 1);
		data &= mask;
		b &= ~(mask);
		b |= data;
		return writeByte(devAddr, regAddr, b);
	} else {
		return FALSE;
	}
}

boolean writeBitsW(uint8 devAddr, uint8 regAddr, uint8 bitStart, uint8 length, uint16 data)
{
	uint16 w;
	
	if (readWord(devAddr, regAddr, &w) != 0) {
		uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
		data <<= (bitStart - length + 1);
		data &= mask;
		w &= ~(mask);
		w |= data;
		return writeWord(devAddr, regAddr, w);
	} else {
		return FALSE;
	}
}

boolean writeByte(uint8 devAddr, uint8 regAddr, uint8 data)
{
	return writeBytes(devAddr, regAddr, 1, &data);
}

boolean writeWord(uint8 devAddr, uint8 regAddr, uint16 data)
{
	return writeWords(devAddr, regAddr, 1, &data);
}

boolean writeBytes(uint8 devAddr, uint8 regAddr, uint8 length, uint8 *data)
{
	boolean b;
	
	i2c0RegW(devAddr, regAddr, data, length);
	if (i2c0WriteCount() == length) {
		b = TRUE;
	} else {
		b = FALSE;
	}
	return b;
}

boolean writeWords(uint8 devAddr, uint8 regAddr, uint8 length, uint16 *data)
{
	boolean b;
	uint8 i;
	
	for (i = 0; i < length; i++) {
		data[i] = mpu6050ReverseWord(data[i]);
	}
	i2c0RegW(devAddr, regAddr, (uint8 *)data, length * 2);
	if (i2c0WriteCount() == length * 2) {
		b = TRUE;
	} else {
		b = FALSE;
	}
	return b;
}

void mpu6050IRQInit(void)
{
	pinSel(2, 12, 1);
	pinMode(2, 12, 0);
	pinModeOD(2, 12, 0);
	LPC_SC->EXTMODE |= ex(2);
	LPC_SC->EXTPOLAR |= ex(2);
}

void mpu6050IRQEnable(void)
{
	NVIC_EnableIRQ(EINT2_IRQn);
}
void mpu6050IRQDisable(void)
{
	NVIC_DisableIRQ(EINT2_IRQn);
}

void mpu6050IRQClear(void)
{
	LPC_SC->EXTINT = ex(2);
	NVIC_ClearPendingIRQ(EINT2_IRQn);
}

void EINT2_IRQHandler(void)
{
	OSIntEnter();
	mpu6050IRQClear();
	mpu6050DMPIRQHandler();
	OSIntExit();
}
