#include <string.h>
#include <avr/pgmspace.h>
#include "mpu6050_port.h"
#include "mpu6050.h"

static uint8 buffer[14];

void MPU6050initialize(void)
{
	MPU6050setClockSource(MPU6050_CLOCK_PLL_XGYRO);
	MPU6050setFullScaleGyroRange(MPU6050_GYRO_FS_250);
	MPU6050setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
	MPU6050setSleepEnabled(FALSE);
}

void MPU6050setRate(uint8 rate)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, rate);
}

void MPU6050setExternalFrameSync(uint8 sync)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_CONFIG, MPU6050_CFG_EXT_SYNC_SET_BIT, MPU6050_CFG_EXT_SYNC_SET_LENGTH, sync);
}

void MPU6050setDLPFMode(uint8 mode)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, mode);
}

void MPU6050setFullScaleGyroRange(uint8 range)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

void MPU6050setFullScaleAccelRange(uint8 range)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

void MPU6050setMotionDetectionThreshold(uint8 threshold)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_MOT_THR, threshold);
}

void MPU6050setMotionDetectionDuration(uint8 duration)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, duration);
}

void MPU6050setZeroMotionDetectionThreshold(uint8 threshold)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, threshold);
}

void MPU6050setZeroMotionDetectionDuration(uint8 duration)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, duration);
}

void MPU6050setSlaveAddress(uint8 num, uint8 address)
{
	if (num > 3) return;
	writeByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR + num*3, address);
}

void MPU6050setIntEnabled(uint8 enabled)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, enabled);
}

uint8 MPU6050getIntStatus(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, buffer);
	return buffer[0];
}

void MPU6050setFIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_EN_BIT, enabled);
}

void MPU6050setI2CMasterModeEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, enabled);
}

void MPU6050resetFIFO(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_RESET_BIT, TRUE);
}

void MPU6050resetI2CMaster(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_RESET_BIT, TRUE);
}

void MPU6050reset(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT, TRUE);
}

void MPU6050setSleepEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

void MPU6050setClockSource(uint8 source)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

void MPU6050getFIFOBytes(uint8 *data, uint8 length)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, length, data);
}

/* ======== UNDOCUMENTED/DMP REGISTERS/METHODS ======== */

void MPU6050setOTPBankValid(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_XG_OFFS_TC, MPU6050_TC_OTP_BNK_VLD_BIT, enabled);
}

int8 MPU6050getXGyroOffsetTC(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_XG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setXGyroOffsetTC(int8 offset)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_XG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, offset);
}

int8 MPU6050getYGyroOffsetTC(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_YG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setYGyroOffsetTC(int8 offset)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_YG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, offset);
}

int8 MPU6050getZGyroOffsetTC(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_ZG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setZGyroOffsetTC(int8 offset)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_ZG_OFFS_TC, MPU6050_TC_OFFSET_BIT, MPU6050_TC_OFFSET_LENGTH, offset);
}

int16 MPU6050getXAccelOffset(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_XA_OFFS_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

void MPU6050setXAccelOffset(int16 offset)
{
	writeWord(MPU6050_ADDRESS, MPU6050_RA_XA_OFFS_H, offset);
}

int16 MPU6050getYAccelOffset(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_YA_OFFS_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

void MPU6050setYAccelOffset(int16 offset)
{
	writeWord(MPU6050_ADDRESS, MPU6050_RA_YA_OFFS_H, offset);
}

int16 MPU6050getZAccelOffset(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_ZA_OFFS_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

void MPU6050setZAccelOffset(int16 offset)
{
	writeWord(MPU6050_ADDRESS, MPU6050_RA_ZA_OFFS_H, offset);
}

int16 MPU6050getXGyroOffset(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_XG_OFFS_USRH, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

void MPU6050setXGyroOffset(int16 offset)
{
	writeWord(MPU6050_ADDRESS, MPU6050_RA_XG_OFFS_USRH, offset);
}

int16 MPU6050getYGyroOffset(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_YG_OFFS_USRH, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

void MPU6050setYGyroOffset(int16 offset)
{
	writeWord(MPU6050_ADDRESS, MPU6050_RA_YG_OFFS_USRH, offset);
}

int16 MPU6050getZGyroOffset(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_ZG_OFFS_USRH, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

void MPU6050setZGyroOffset(int16 offset)
{
	writeWord(MPU6050_ADDRESS, MPU6050_RA_ZG_OFFS_USRH, offset);
}

void MPU6050setDMPEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_DMP_EN_BIT, enabled);
}

void MPU6050resetDMP(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_DMP_RESET_BIT, TRUE);
}

void MPU6050setMemoryBank(uint8 bank, boolean prefetchEnabled, boolean userBank)
{
	bank &= 0x1F;
	if (userBank) {
		bank |= 0x20;
	}
	if (prefetchEnabled) {
		bank |= 0x40;
	}
	writeByte(MPU6050_ADDRESS, MPU6050_RA_BANK_SEL, bank);
}

void MPU6050setMemoryStartAddress(uint8 address)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_MEM_START_ADDR, address);
}

void MPU6050readMemoryBlock(uint8 *data, uint16 dataSize, uint8 bank, uint8 address)
{
	uint8 chunkSize;
	uint16 i;
	
	MPU6050setMemoryBank(bank, FALSE, FALSE);
	MPU6050setMemoryStartAddress(address);
	for (i = 0; i < dataSize;) {
		chunkSize = MPU6050_DMP_MEMORY_CHUNK_SIZE;
		if (i + chunkSize > dataSize) {
			chunkSize = dataSize - i;
		}
		if (chunkSize > 256 - address) {
			chunkSize = 256 - address;
		}
		readBytes(MPU6050_ADDRESS, MPU6050_RA_MEM_R_W, chunkSize, data + i);
		i += chunkSize;
		address += chunkSize;
		if (i < dataSize) {
			if (address == 0) {
				bank++;
			}
			MPU6050setMemoryBank(bank, FALSE, FALSE);
			MPU6050setMemoryStartAddress(address);
		}
	}
}

boolean MPU6050writeMemoryBlock(const uint8 *data, uint16 dataSize, uint8 bank, uint8 address, boolean verify, boolean useProgMem)
{
	uint8 ram1[MPU6050_DMP_MEMORY_CHUNK_SIZE];
	uint8 ram2[MPU6050_DMP_MEMORY_CHUNK_SIZE];
	uint8 chunkSize;
	uint8 *verifyBuffer;
	uint8 *progBuffer;
	uint16 i;
	uint8 j;
	
	MPU6050setMemoryBank(bank, FALSE, FALSE);
	MPU6050setMemoryStartAddress(address);
	if (verify) {
		verifyBuffer = ram1;
	}
	if (useProgMem) {
		progBuffer = ram2;
	}
	for (i = 0; i < dataSize;) {
		chunkSize = MPU6050_DMP_MEMORY_CHUNK_SIZE;
		if (i + chunkSize > dataSize) {
			chunkSize = dataSize - i;
		}
		if (chunkSize > 256 - address) {
			chunkSize = 256 - address;
		}
		if (useProgMem) {
			for (j = 0; j < chunkSize; j++) progBuffer[j] = pgm_read_byte(data + i + j);
		} else {
			progBuffer = (uint8 *)data + i;
		}
		writeBytes(MPU6050_ADDRESS, MPU6050_RA_MEM_R_W, chunkSize, progBuffer);
		if (verify && verifyBuffer) {
			MPU6050setMemoryBank(bank, FALSE, FALSE);
			MPU6050setMemoryStartAddress(address);
			readBytes(MPU6050_ADDRESS, MPU6050_RA_MEM_R_W, chunkSize, verifyBuffer);
			if (memcmp(progBuffer, verifyBuffer, chunkSize) != 0) {
				return FALSE;
			}
		}
		i += chunkSize;
		address += chunkSize;
		if (i < dataSize) {
			if (address == 0) bank++;
			MPU6050setMemoryBank(bank, FALSE, FALSE);
			MPU6050setMemoryStartAddress(address);
		}
	}
	return TRUE;
}

boolean MPU6050writeProgMemoryBlock(const uint8 *data, uint16 dataSize, uint8 bank, uint8 address, boolean verify)
{
	return MPU6050writeMemoryBlock(data, dataSize, bank, address, verify, TRUE);
}

boolean MPU6050writeDMPConfigurationSet(const uint8 *data, uint16 dataSize, boolean useProgMem)
{
	uint8 ram1[64];
	uint8 *progBuffer, success, special;
	uint8 bank, offset, length;
	uint16 i, j;
	
	if (useProgMem) {
		progBuffer = ram1;
	}
	for (i = 0; i < dataSize;) {
		if (useProgMem) {
			bank = pgm_read_byte(data + i++);
			offset = pgm_read_byte(data + i++);
			length = pgm_read_byte(data + i++);
		} else {
			bank = data[i++];
			offset = data[i++];
			length = data[i++];
		}
		if (length > 0) {
			if (useProgMem) {
				for (j = 0; j < length; j++) progBuffer[j] = pgm_read_byte(data + i + j);
			} else {
				progBuffer = (uint8_t *)data + i;
			}
			success = MPU6050writeMemoryBlock(progBuffer, length, bank, offset, TRUE, FALSE);
			i += length;
		} else {
			if (useProgMem) {
				special = pgm_read_byte(data + i++);
			} else {
				special = data[i++];
			}
			if (special == 0x01) {
				// enable DMP-related interrupts
				//setIntZeroMotionEnabled(true);
				//setIntFIFOBufferOverflowEnabled(true);
				//setIntDMPEnabled(true);
				writeByte(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, 0x32);
				success = TRUE;
			} else {
				// unknown special command
				success = FALSE;
			}
		}
		if (!success) {
			return FALSE;
		}
	}
	return TRUE;
}

boolean MPU6050writeProgDMPConfigurationSet(const uint8 *data, uint16 dataSize)
{
	return MPU6050writeDMPConfigurationSet(data, dataSize, TRUE);
}

void MPU6050setDMPConfig1(uint8 config)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_DMP_CFG_1, config);
}

void MPU6050setDMPConfig2(uint8 config)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_DMP_CFG_2, config);
}
