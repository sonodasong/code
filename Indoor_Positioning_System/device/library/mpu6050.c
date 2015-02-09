#include <string.h>
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

boolean MPU6050testConnection(void)
{
	return MPU6050getDeviceID() == 0x34;
}

uint8 MPU6050getAuxVDDIOLevel(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_YG_OFFS_TC, MPU6050_TC_PWR_MODE_BIT, buffer);
	return buffer[0];
}

void MPU6050setAuxVDDIOLevel(uint8 level)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_YG_OFFS_TC, MPU6050_TC_PWR_MODE_BIT, level);
}

uint8 MPU6050getRate(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, buffer);
	return buffer[0];
}

void MPU6050setRate(uint8 rate)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, rate);
}

uint8 MPU6050getExternalFrameSync(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_CONFIG, MPU6050_CFG_EXT_SYNC_SET_BIT, MPU6050_CFG_EXT_SYNC_SET_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setExternalFrameSync(uint8 sync)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_CONFIG, MPU6050_CFG_EXT_SYNC_SET_BIT, MPU6050_CFG_EXT_SYNC_SET_LENGTH, sync);
}

uint8 MPU6050getDLPFMode(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setDLPFMode(uint8 mode)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, mode);
}

uint8 MPU6050getFullScaleGyroRange(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setFullScaleGyroRange(uint8 range)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

boolean MPU6050getAccelXSelfTest(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_XA_ST_BIT, buffer);
	return buffer[0];
}

void MPU6050setAccelXSelfTest(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_XA_ST_BIT, enabled);
}

boolean MPU6050getAccelYSelfTest(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_YA_ST_BIT, buffer);
	return buffer[0];
}

void MPU6050setAccelYSelfTest(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_YA_ST_BIT, enabled);
}

boolean MPU6050getAccelZSelfTest(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_ZA_ST_BIT, buffer);
	return buffer[0];
}

void MPU6050setAccelZSelfTest(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_ZA_ST_BIT, enabled);
}

uint8 MPU6050getFullScaleAccelRange(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setFullScaleAccelRange(uint8 range)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

uint8 MPU6050getDHPFMode(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_ACCEL_HPF_BIT, MPU6050_ACONFIG_ACCEL_HPF_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setDHPFMode(uint8 bandwidth)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_ACCEL_HPF_BIT, MPU6050_ACONFIG_ACCEL_HPF_LENGTH, bandwidth);
}

uint8 MPU6050getFreefallDetectionThreshold(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_FF_THR, buffer);
	return buffer[0];
}

void MPU6050setFreefallDetectionThreshold(uint8 threshold)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_FF_THR, threshold);
}

uint8 MPU6050getFreefallDetectionDuration(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_FF_DUR, buffer);
	return buffer[0];
}

void MPU6050setFreefallDetectionDuration(uint8 duration)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_FF_DUR, duration);
}

uint8 MPU6050getMotionDetectionThreshold(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_MOT_THR, buffer);
	return buffer[0];
}

void MPU6050setMotionDetectionThreshold(uint8 threshold)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_MOT_THR, threshold);
}

uint8 MPU6050getMotionDetectionDuration(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, buffer);
	return buffer[0];
}

void MPU6050setMotionDetectionDuration(uint8 duration)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, duration);
}

uint8 MPU6050getZeroMotionDetectionThreshold(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, buffer);
	return buffer[0];
}

void MPU6050setZeroMotionDetectionThreshold(uint8 threshold)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, threshold);
}

uint8 MPU6050getZeroMotionDetectionDuration(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, buffer);
	return buffer[0];
}

void MPU6050setZeroMotionDetectionDuration(uint8 duration)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, duration);
}

boolean MPU6050getTempFIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_TEMP_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setTempFIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_TEMP_FIFO_EN_BIT, enabled);
}

boolean MPU6050getXGyroFIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_XG_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setXGyroFIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_XG_FIFO_EN_BIT, enabled);
}

boolean MPU6050getYGyroFIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_YG_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setYGyroFIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_YG_FIFO_EN_BIT, enabled);
}

boolean MPU6050getZGyroFIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_ZG_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setZGyroFIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_ZG_FIFO_EN_BIT, enabled);
}

boolean MPU6050getAccelFIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_ACCEL_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setAccelFIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_ACCEL_FIFO_EN_BIT, enabled);
}

boolean MPU6050getSlave2FIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_SLV2_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlave2FIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_SLV2_FIFO_EN_BIT, enabled);
}

boolean MPU6050getSlave1FIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_SLV1_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlave1FIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_SLV1_FIFO_EN_BIT, enabled);
}

boolean MPU6050getSlave0FIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_SLV0_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlave0FIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, MPU6050_SLV0_FIFO_EN_BIT, enabled);
}

boolean MPU6050getMultiMasterEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_MULT_MST_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setMultiMasterEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_MULT_MST_EN_BIT, enabled);
}

boolean MPU6050getWaitForExternalSensorEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_WAIT_FOR_ES_BIT, buffer);
	return buffer[0];
}

void MPU6050setWaitForExternalSensorEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_WAIT_FOR_ES_BIT, enabled);
}

boolean MPU6050getSlave3FIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_SLV_3_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlave3FIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_SLV_3_FIFO_EN_BIT, enabled);
}

boolean MPU6050getSlaveReadWriteTransitionEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_I2C_MST_P_NSR_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlaveReadWriteTransitionEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_I2C_MST_P_NSR_BIT, enabled);
}

uint8 MPU6050getMasterClockSpeed(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_I2C_MST_CLK_BIT, MPU6050_I2C_MST_CLK_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setMasterClockSpeed(uint8 speed)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, MPU6050_I2C_MST_CLK_BIT, MPU6050_I2C_MST_CLK_LENGTH, speed);
}

uint8 MPU6050getSlaveAddress(uint8 num)
{
	if (num > 3) return 0;
	readByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR + num*3, buffer);
	return buffer[0];
}

void MPU6050setSlaveAddress(uint8 num, uint8 address)
{
	if (num > 3) return;
	writeByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR + num*3, address);
}

uint8 MPU6050getSlaveRegister(uint8 num)
{
	if (num > 3) return 0;
	readByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG + num*3, buffer);
	return buffer[0];
}

void MPU6050setSlaveRegister(uint8 num, uint8 reg)
{
	if (num > 3) return;
	writeByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG + num*3, reg);
}

boolean MPU6050getSlaveEnabled(uint8 num)
{
	if (num > 3) return 0;
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlaveEnabled(uint8 num, boolean enabled)
{
	if (num > 3) return;
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_EN_BIT, enabled);
}

boolean MPU6050getSlaveWordByteSwap(uint8 num)
{
	if (num > 3) return 0;
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_BYTE_SW_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlaveWordByteSwap(uint8 num, boolean enabled)
{
	if (num > 3) return;
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_BYTE_SW_BIT, enabled);
}

boolean MPU6050getSlaveWriteMode(uint8 num)
{
	if (num > 3) return 0;
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_REG_DIS_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlaveWriteMode(uint8 num, boolean mode)
{
	if (num > 3) return;
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_REG_DIS_BIT, mode);
}

boolean MPU6050getSlaveWordGroupOffset(uint8 num)
{
	if (num > 3) return 0;
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_GRP_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlaveWordGroupOffset(uint8 num, boolean enabled)
{
	if (num > 3) return;
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_GRP_BIT, enabled);
}

uint8 MPU6050getSlaveDataLength(uint8 num)
{
	if (num > 3) return 0;
	readBits(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_LEN_BIT, MPU6050_I2C_SLV_LEN_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setSlaveDataLength(uint8 num, uint8 length)
{
	if (num > 3) return;
	writeBits(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL + num*3, MPU6050_I2C_SLV_LEN_BIT, MPU6050_I2C_SLV_LEN_LENGTH, length);
}

uint8 MPU6050getSlave4Address(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_ADDR, buffer);
	return buffer[0];
}

void MPU6050setSlave4Address(uint8 address)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_ADDR, address);
}

uint8 MPU6050getSlave4Register(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_REG, buffer);
	return buffer[0];
}

void MPU6050setSlave4Register(uint8 reg)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_REG, reg);
}

void MPU6050setSlave4OutputByte(uint8 data)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DO, data);
}

boolean MPU6050getSlave4Enabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, MPU6050_I2C_SLV4_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlave4Enabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, MPU6050_I2C_SLV4_EN_BIT, enabled);
}

boolean MPU6050getSlave4InterruptEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, MPU6050_I2C_SLV4_INT_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlave4InterruptEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, MPU6050_I2C_SLV4_INT_EN_BIT, enabled);
}

boolean MPU6050getSlave4WriteMode(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, MPU6050_I2C_SLV4_REG_DIS_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlave4WriteMode(boolean mode)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, MPU6050_I2C_SLV4_REG_DIS_BIT, mode);
}

uint8 MPU6050getSlave4MasterDelay(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, MPU6050_I2C_SLV4_MST_DLY_BIT, MPU6050_I2C_SLV4_MST_DLY_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setSlave4MasterDelay(uint8 delay)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, MPU6050_I2C_SLV4_MST_DLY_BIT, MPU6050_I2C_SLV4_MST_DLY_LENGTH, delay);
}

uint8 MPU6050getSlate4InputByte(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DI, buffer);
	return buffer[0];
}

boolean MPU6050getPassthroughStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_STATUS, MPU6050_MST_PASS_THROUGH_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getSlave4IsDone(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_STATUS, MPU6050_MST_I2C_SLV4_DONE_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getLostArbitration(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_STATUS, MPU6050_MST_I2C_LOST_ARB_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getSlave4Nack(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_STATUS, MPU6050_MST_I2C_SLV4_NACK_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getSlave3Nack(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_STATUS, MPU6050_MST_I2C_SLV3_NACK_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getSlave2Nack(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_STATUS, MPU6050_MST_I2C_SLV2_NACK_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getSlave1Nack(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_STATUS, MPU6050_MST_I2C_SLV1_NACK_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getSlave0Nack(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_STATUS, MPU6050_MST_I2C_SLV0_NACK_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getInterruptMode(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_LEVEL_BIT, buffer);
	return buffer[0];
}

void MPU6050setInterruptMode(boolean mode)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_LEVEL_BIT, mode);
}

boolean MPU6050getInterruptDrive(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_OPEN_BIT, buffer);
	return buffer[0];
}

void MPU6050setInterruptDrive(boolean drive)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_OPEN_BIT, drive);
}

boolean MPU6050getInterruptLatch(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_LATCH_INT_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setInterruptLatch(boolean latch)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_LATCH_INT_EN_BIT, latch);
}

boolean MPU6050getInterruptLatchClear(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_RD_CLEAR_BIT, buffer);
	return buffer[0];
}

void MPU6050setInterruptLatchClear(boolean clear)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_RD_CLEAR_BIT, clear);
}

boolean MPU6050getFSyncInterruptLevel(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT, buffer);
	return buffer[0];
}

void MPU6050setFSyncInterruptLevel(boolean level)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT, level);
}

boolean MPU6050getFSyncInterruptEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_FSYNC_INT_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setFSyncInterruptEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_FSYNC_INT_EN_BIT, enabled);
}

boolean MPU6050getI2CBypassEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setI2CBypassEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, enabled);
}

boolean MPU6050getClockOutputEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_CLKOUT_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setClockOutputEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_CLKOUT_EN_BIT, enabled);
}

uint8 MPU6050getIntEnabled(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, buffer);
	return buffer[0];
}

void MPU6050setIntEnabled(uint8 enabled)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, enabled);
}

boolean MPU6050getIntFreefallEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_FF_BIT, buffer);
	return buffer[0];
}

void MPU6050setIntFreefallEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_FF_BIT, enabled);
}

boolean MPU6050getIntMotionEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_MOT_BIT, buffer);
	return buffer[0];
}

void MPU6050setIntMotionEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_MOT_BIT, enabled);
}

boolean MPU6050getIntZeroMotionEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_ZMOT_BIT, buffer);
	return buffer[0];
}

void MPU6050setIntZeroMotionEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_ZMOT_BIT, enabled);
}

boolean MPU6050getIntFIFOBufferOverflowEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_FIFO_OFLOW_BIT, buffer);
	return buffer[0];
}

void MPU6050setIntFIFOBufferOverflowEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_FIFO_OFLOW_BIT, enabled);
}

boolean MPU6050getIntI2CMasterEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_I2C_MST_INT_BIT, buffer);
	return buffer[0];
}

void MPU6050setIntI2CMasterEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_I2C_MST_INT_BIT, enabled);
}

boolean MPU6050getIntDataReadyEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_DATA_RDY_BIT, buffer);
	return buffer[0];
}

void MPU6050setIntDataReadyEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_DATA_RDY_BIT, enabled);
}

uint8 MPU6050getIntStatus(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, buffer);
	return buffer[0];
}

boolean MPU6050getIntFreefallStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, MPU6050_INTERRUPT_FF_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getIntMotionStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, MPU6050_INTERRUPT_MOT_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getIntZeroMotionStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, MPU6050_INTERRUPT_ZMOT_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getIntFIFOBufferOverflowStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, MPU6050_INTERRUPT_FIFO_OFLOW_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getIntI2CMasterStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, MPU6050_INTERRUPT_I2C_MST_INT_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getIntDataReadyStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, MPU6050_INTERRUPT_DATA_RDY_BIT, buffer);
	return buffer[0];
}

void MPU6050getMotion9(int16* ax, int16* ay, int16* az, int16* gx, int16* gy, int16* gz, int16* mx, int16* my, int16* mz)
{
	MPU6050getMotion6(ax, ay, az, gx, gy, gz);
	// TODO: magnetometer integration
}

void MPU6050getMotion6(int16* ax, int16* ay, int16* az, int16* gx, int16* gy, int16* gz)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 14, buffer);
	*ax = (((int16)buffer[0]) << 8) | buffer[1];
	*ay = (((int16)buffer[2]) << 8) | buffer[3];
	*az = (((int16)buffer[4]) << 8) | buffer[5];
	*gx = (((int16)buffer[8]) << 8) | buffer[9];
	*gy = (((int16)buffer[10]) << 8) | buffer[11];
	*gz = (((int16)buffer[12]) << 8) | buffer[13];
}

void MPU6050getAcceleration(int16* x, int16* y, int16* z)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 6, buffer);
	*x = (((int16)buffer[0]) << 8) | buffer[1];
	*y = (((int16)buffer[2]) << 8) | buffer[3];
	*z = (((int16)buffer[4]) << 8) | buffer[5];
}

int16 MPU6050getAccelerationX(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

int16 MPU6050getAccelerationY(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

int16 MPU6050getAccelerationZ(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

int16 MPU6050getTemperature(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_TEMP_OUT_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

void MPU6050getRotation(int16* x, int16* y, int16* z)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, 6, buffer);
	*x = (((int16)buffer[0]) << 8) | buffer[1];
	*y = (((int16)buffer[2]) << 8) | buffer[3];
	*z = (((int16)buffer[4]) << 8) | buffer[5];
}

int16 MPU6050getRotationX(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

int16 MPU6050getRotationY(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

int16 MPU6050getRotationZ(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_H, 2, buffer);
	return (((int16)buffer[0]) << 8) | buffer[1];
}

uint8 MPU6050getExternalSensorByte(int position)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_EXT_SENS_DATA_00 + position, buffer);
	return buffer[0];
}

uint16 MPU6050getExternalSensorWord(int position)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_EXT_SENS_DATA_00 + position, 2, buffer);
	return (((uint16)buffer[0]) << 8) | buffer[1];
}

uint32 MPU6050getExternalSensorDWord(int position)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_EXT_SENS_DATA_00 + position, 4, buffer);
	return (((uint32)buffer[0]) << 24) | (((uint32)buffer[1]) << 16) | (((uint16)buffer[2]) << 8) | buffer[3];
}

boolean MPU6050getXNegMotionDetected(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_STATUS, MPU6050_MOTION_MOT_XNEG_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getXPosMotionDetected(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_STATUS, MPU6050_MOTION_MOT_XPOS_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getYNegMotionDetected(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_STATUS, MPU6050_MOTION_MOT_YNEG_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getYPosMotionDetected(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_STATUS, MPU6050_MOTION_MOT_YPOS_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getZNegMotionDetected(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_STATUS, MPU6050_MOTION_MOT_ZNEG_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getZPosMotionDetected(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_STATUS, MPU6050_MOTION_MOT_ZPOS_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getZeroMotionDetected(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_STATUS, MPU6050_MOTION_MOT_ZRMOT_BIT, buffer);
	return buffer[0];
}

void MPU6050setSlaveOutputByte(uint8 num, uint8 data)
{
	if (num > 3) return;
	writeByte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_DO + num, data);
}

boolean MPU6050getExternalShadowDelayEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT, buffer);
	return buffer[0];
}

void MPU6050setExternalShadowDelayEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT, enabled);
}

boolean MPU6050getSlaveDelayEnabled(uint8 num)
{
	// MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT is 4, SLV3 is 3, etc.
	if (num > 4) return 0;
	readBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, num, buffer);
	return buffer[0];
}

void MPU6050setSlaveDelayEnabled(uint8 num, boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, num, enabled);
}

void MPU6050resetGyroscopePath(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, MPU6050_PATHRESET_GYRO_RESET_BIT, TRUE);
}

void MPU6050resetAccelerometerPath(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, MPU6050_PATHRESET_ACCEL_RESET_BIT, TRUE);
}

void MPU6050resetTemperaturePath(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, MPU6050_PATHRESET_TEMP_RESET_BIT, TRUE);
}

uint8 MPU6050getAccelerometerPowerOnDelay(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, MPU6050_DETECT_ACCEL_ON_DELAY_BIT, MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setAccelerometerPowerOnDelay(uint8 delay)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, MPU6050_DETECT_ACCEL_ON_DELAY_BIT, MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH, delay);
}

uint8 MPU6050getFreefallDetectionCounterDecrement(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, MPU6050_DETECT_FF_COUNT_BIT, MPU6050_DETECT_FF_COUNT_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setFreefallDetectionCounterDecrement(uint8 decrement)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, MPU6050_DETECT_FF_COUNT_BIT, MPU6050_DETECT_FF_COUNT_LENGTH, decrement);
}

uint8 MPU6050getMotionDetectionCounterDecrement(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, MPU6050_DETECT_MOT_COUNT_BIT, MPU6050_DETECT_MOT_COUNT_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setMotionDetectionCounterDecrement(uint8 decrement)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, MPU6050_DETECT_MOT_COUNT_BIT, MPU6050_DETECT_MOT_COUNT_LENGTH, decrement);
}

boolean MPU6050getFIFOEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setFIFOEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_EN_BIT, enabled);
}

boolean MPU6050getI2CMasterModeEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, buffer);
	return buffer[0];
}

void MPU6050setI2CMasterModeEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, enabled);
}

void MPU6050switchSPIEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_IF_DIS_BIT, enabled);
}

void MPU6050resetFIFO(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_RESET_BIT, TRUE);
}

void MPU6050resetI2CMaster(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_RESET_BIT, TRUE);
}

void MPU6050resetSensors(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_SIG_COND_RESET_BIT, TRUE);
}

void MPU6050reset(void)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT, TRUE);
}

boolean MPU6050getSleepEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, buffer);
	return buffer[0];
}

void MPU6050setSleepEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

boolean MPU6050getWakeCycleEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CYCLE_BIT, buffer);
	return buffer[0];
}

void MPU6050setWakeCycleEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CYCLE_BIT, enabled);
}

boolean MPU6050getTempSensorEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_TEMP_DIS_BIT, buffer);
	return buffer[0] == 0; // 1 is actually disabled here
}

void MPU6050setTempSensorEnabled(boolean enabled)
{
	// 1 is actually disabled here
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_TEMP_DIS_BIT, !enabled);
}

uint8 MPU6050getClockSource(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setClockSource(uint8 source)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

uint8 MPU6050getWakeFrequency(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_LP_WAKE_CTRL_BIT, MPU6050_PWR2_LP_WAKE_CTRL_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setWakeFrequency(uint8 frequency)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_LP_WAKE_CTRL_BIT, MPU6050_PWR2_LP_WAKE_CTRL_LENGTH, frequency);
}

boolean MPU6050getStandbyXAccelEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_XA_BIT, buffer);
	return buffer[0];
}

void MPU6050setStandbyXAccelEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_XA_BIT, enabled);
}

boolean MPU6050getStandbyYAccelEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_YA_BIT, buffer);
	return buffer[0];
}

void MPU6050setStandbyYAccelEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_YA_BIT, enabled);
}

boolean MPU6050getStandbyZAccelEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_ZA_BIT, buffer);
	return buffer[0];
}

void MPU6050setStandbyZAccelEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_ZA_BIT, enabled);
}

boolean MPU6050getStandbyXGyroEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_XG_BIT, buffer);
	return buffer[0];
}

void MPU6050setStandbyXGyroEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_XG_BIT, enabled);
}

boolean MPU6050getStandbyYGyroEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_YG_BIT, buffer);
	return buffer[0];
}

void MPU6050setStandbyYGyroEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_YG_BIT, enabled);
}

boolean MPU6050getStandbyZGyroEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_ZG_BIT, buffer);
	return buffer[0];
}

void MPU6050setStandbyZGyroEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, MPU6050_PWR2_STBY_ZG_BIT, enabled);
}

uint16 MPU6050getFIFOCount(void)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_FIFO_COUNTH, 2, buffer);
	return (((uint16)buffer[0]) << 8) | buffer[1];
}

uint8 MPU6050getFIFOByte(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, buffer);
	return buffer[0];
}

void MPU6050getFIFOBytes(uint8 *data, uint8 length)
{
	readBytes(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, length, data);
}

void MPU6050setFIFOByte(uint8 data)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, data);
}

uint8 MPU6050getDeviceID(void)
{
	readBits(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, buffer);
	return buffer[0];
}

void MPU6050setDeviceID(uint8 id)
{
	writeBits(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, id);
}

/* ======== UNDOCUMENTED/DMP REGISTERS/METHODS ======== */

uint8 MPU6050getOTPBankValid(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_XG_OFFS_TC, MPU6050_TC_OTP_BNK_VLD_BIT, buffer);
	return buffer[0];
}

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

int8 MPU6050getXFineGain(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_X_FINE_GAIN, buffer);
	return buffer[0];
}

void MPU6050setXFineGain(int8 gain)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_X_FINE_GAIN, gain);
}

int8 MPU6050getYFineGain(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_Y_FINE_GAIN, buffer);
	return buffer[0];
}

void MPU6050setYFineGain(int8 gain)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_Y_FINE_GAIN, gain);
}

int8 MPU6050getZFineGain(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_Z_FINE_GAIN, buffer);
	return buffer[0];
}

void MPU6050setZFineGain(int8 gain)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_Z_FINE_GAIN, gain);
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

boolean MPU6050getIntPLLReadyEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_PLL_RDY_INT_BIT, buffer);
	return buffer[0];
}

void MPU6050setIntPLLReadyEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_PLL_RDY_INT_BIT, enabled);
}

boolean MPU6050getIntDMPEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_DMP_INT_BIT, buffer);
	return buffer[0];
}

void MPU6050setIntDMPEnabled(boolean enabled)
{
	writeBit(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_DMP_INT_BIT, enabled);
}

boolean MPU6050getDMPInt5Status(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_DMP_INT_STATUS, MPU6050_DMPINT_5_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getDMPInt4Status(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_DMP_INT_STATUS, MPU6050_DMPINT_4_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getDMPInt3Status(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_DMP_INT_STATUS, MPU6050_DMPINT_3_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getDMPInt2Status(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_DMP_INT_STATUS, MPU6050_DMPINT_2_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getDMPInt1Status(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_DMP_INT_STATUS, MPU6050_DMPINT_1_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getDMPInt0Status(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_DMP_INT_STATUS, MPU6050_DMPINT_0_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getIntPLLReadyStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, MPU6050_INTERRUPT_PLL_RDY_INT_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getIntDMPStatus(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_INT_STATUS, MPU6050_INTERRUPT_DMP_INT_BIT, buffer);
	return buffer[0];
}

boolean MPU6050getDMPEnabled(void)
{
	readBit(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_DMP_EN_BIT, buffer);
	return buffer[0];
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

uint8 MPU6050readMemoryByte(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_MEM_R_W, buffer);
	return buffer[0];
}

void MPU6050writeMemoryByte(uint8 data)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_MEM_R_W, data);
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

uint8 MPU6050getDMPConfig1(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_DMP_CFG_1, buffer);
	return buffer[0];
}

void MPU6050setDMPConfig1(uint8 config)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_DMP_CFG_1, config);
}

uint8 MPU6050getDMPConfig2(void)
{
	readByte(MPU6050_ADDRESS, MPU6050_RA_DMP_CFG_2, buffer);
	return buffer[0];
}

void MPU6050setDMPConfig2(uint8 config)
{
	writeByte(MPU6050_ADDRESS, MPU6050_RA_DMP_CFG_2, config);
}
