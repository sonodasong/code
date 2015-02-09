#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "define.h"

#define MPU6050_ADDRESS 0x68

#define MPU6050_ADDRESS_COMPASS 0x0C

#define MPU6050_RA_XG_OFFS_TC 0x00
#define MPU6050_RA_YG_OFFS_TC 0x01
#define MPU6050_RA_ZG_OFFS_TC 0x02
#define MPU6050_RA_X_FINE_GAIN 0x03
#define MPU6050_RA_Y_FINE_GAIN 0x04
#define MPU6050_RA_Z_FINE_GAIN 0x05
#define MPU6050_RA_XA_OFFS_H 0x06
#define MPU6050_RA_XA_OFFS_L_TC 0x07
#define MPU6050_RA_YA_OFFS_H 0x08
#define MPU6050_RA_YA_OFFS_L_TC 0x09
#define MPU6050_RA_ZA_OFFS_H 0x0A
#define MPU6050_RA_ZA_OFFS_L_TC 0x0B
#define MPU6050_RA_XG_OFFS_USRH 0x13
#define MPU6050_RA_XG_OFFS_USRL 0x14
#define MPU6050_RA_YG_OFFS_USRH 0x15
#define MPU6050_RA_YG_OFFS_USRL 0x16
#define MPU6050_RA_ZG_OFFS_USRH 0x17
#define MPU6050_RA_ZG_OFFS_USRL 0x18
#define MPU6050_RA_SMPLRT_DIV 0x19
#define MPU6050_RA_CONFIG 0x1A
#define MPU6050_RA_GYRO_CONFIG 0x1B
#define MPU6050_RA_ACCEL_CONFIG 0x1C
#define MPU6050_RA_FF_THR 0x1D
#define MPU6050_RA_FF_DUR 0x1E
#define MPU6050_RA_MOT_THR 0x1F
#define MPU6050_RA_MOT_DUR 0x20
#define MPU6050_RA_ZRMOT_THR 0x21
#define MPU6050_RA_ZRMOT_DUR 0x22
#define MPU6050_RA_FIFO_EN 0x23
#define MPU6050_RA_I2C_MST_CTRL 0x24
#define MPU6050_RA_I2C_SLV0_ADDR 0x25
#define MPU6050_RA_I2C_SLV0_REG 0x26
#define MPU6050_RA_I2C_SLV0_CTRL 0x27
#define MPU6050_RA_I2C_SLV1_ADDR 0x28
#define MPU6050_RA_I2C_SLV1_REG 0x29
#define MPU6050_RA_I2C_SLV1_CTRL 0x2A
#define MPU6050_RA_I2C_SLV2_ADDR 0x2B
#define MPU6050_RA_I2C_SLV2_REG 0x2C
#define MPU6050_RA_I2C_SLV2_CTRL 0x2D
#define MPU6050_RA_I2C_SLV3_ADDR 0x2E
#define MPU6050_RA_I2C_SLV3_REG 0x2F
#define MPU6050_RA_I2C_SLV3_CTRL 0x30
#define MPU6050_RA_I2C_SLV4_ADDR 0x31
#define MPU6050_RA_I2C_SLV4_REG 0x32
#define MPU6050_RA_I2C_SLV4_DO 0x33
#define MPU6050_RA_I2C_SLV4_CTRL 0x34
#define MPU6050_RA_I2C_SLV4_DI 0x35
#define MPU6050_RA_I2C_MST_STATUS 0x36
#define MPU6050_RA_INT_PIN_CFG 0x37
#define MPU6050_RA_INT_ENABLE 0x38
#define MPU6050_RA_DMP_INT_STATUS 0x39
#define MPU6050_RA_INT_STATUS 0x3A
#define MPU6050_RA_ACCEL_XOUT_H 0x3B
#define MPU6050_RA_ACCEL_XOUT_L 0x3C
#define MPU6050_RA_ACCEL_YOUT_H 0x3D
#define MPU6050_RA_ACCEL_YOUT_L 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L 0x40
#define MPU6050_RA_TEMP_OUT_H 0x41
#define MPU6050_RA_TEMP_OUT_L 0x42
#define MPU6050_RA_GYRO_XOUT_H 0x43
#define MPU6050_RA_GYRO_XOUT_L 0x44
#define MPU6050_RA_GYRO_YOUT_H 0x45
#define MPU6050_RA_GYRO_YOUT_L 0x46
#define MPU6050_RA_GYRO_ZOUT_H 0x47
#define MPU6050_RA_GYRO_ZOUT_L 0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS 0x61
#define MPU6050_RA_I2C_SLV0_DO 0x63
#define MPU6050_RA_I2C_SLV1_DO 0x64
#define MPU6050_RA_I2C_SLV2_DO 0x65
#define MPU6050_RA_I2C_SLV3_DO 0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU6050_RA_SIGNAL_PATH_RESET 0x68
#define MPU6050_RA_MOT_DETECT_CTRL 0x69
#define MPU6050_RA_USER_CTRL 0x6A
#define MPU6050_RA_PWR_MGMT_1 0x6B
#define MPU6050_RA_PWR_MGMT_2 0x6C
#define MPU6050_RA_BANK_SEL 0x6D
#define MPU6050_RA_MEM_START_ADDR 0x6E
#define MPU6050_RA_MEM_R_W 0x6F
#define MPU6050_RA_DMP_CFG_1 0x70
#define MPU6050_RA_DMP_CFG_2 0x71
#define MPU6050_RA_FIFO_COUNTH 0x72
#define MPU6050_RA_FIFO_COUNTL 0x73
#define MPU6050_RA_FIFO_R_W 0x74
#define MPU6050_RA_WHO_AM_I 0x75

#define MPU6050_TC_PWR_MODE_BIT 7
#define MPU6050_TC_OFFSET_BIT 6
#define MPU6050_TC_OFFSET_LENGTH 6
#define MPU6050_TC_OTP_BNK_VLD_BIT 0

#define MPU6050_VDDIO_LEVEL_VLOGIC 0
#define MPU6050_VDDIO_LEVEL_VDD 1

#define MPU6050_CFG_EXT_SYNC_SET_BIT 5
#define MPU6050_CFG_EXT_SYNC_SET_LENGTH 3
#define MPU6050_CFG_DLPF_CFG_BIT 2
#define MPU6050_CFG_DLPF_CFG_LENGTH 3

#define MPU6050_EXT_SYNC_DISABLED 0x0
#define MPU6050_EXT_SYNC_TEMP_OUT_L 0x1
#define MPU6050_EXT_SYNC_GYRO_XOUT_L 0x2
#define MPU6050_EXT_SYNC_GYRO_YOUT_L 0x3
#define MPU6050_EXT_SYNC_GYRO_ZOUT_L 0x4
#define MPU6050_EXT_SYNC_ACCEL_XOUT_L 0x5
#define MPU6050_EXT_SYNC_ACCEL_YOUT_L 0x6
#define MPU6050_EXT_SYNC_ACCEL_ZOUT_L 0x7

#define MPU6050_DLPF_BW_256 0x00
#define MPU6050_DLPF_BW_188 0x01
#define MPU6050_DLPF_BW_98 0x02
#define MPU6050_DLPF_BW_42 0x03
#define MPU6050_DLPF_BW_20 0x04
#define MPU6050_DLPF_BW_10 0x05
#define MPU6050_DLPF_BW_5 0x06

#define MPU6050_GCONFIG_FS_SEL_BIT 4
#define MPU6050_GCONFIG_FS_SEL_LENGTH 2

#define MPU6050_GYRO_FS_250 0x00
#define MPU6050_GYRO_FS_500 0x01
#define MPU6050_GYRO_FS_1000 0x02
#define MPU6050_GYRO_FS_2000 0x03

#define MPU6050_ACONFIG_XA_ST_BIT 7
#define MPU6050_ACONFIG_YA_ST_BIT 6
#define MPU6050_ACONFIG_ZA_ST_BIT 5
#define MPU6050_ACONFIG_AFS_SEL_BIT 4
#define MPU6050_ACONFIG_AFS_SEL_LENGTH 2
#define MPU6050_ACONFIG_ACCEL_HPF_BIT 2
#define MPU6050_ACONFIG_ACCEL_HPF_LENGTH 3

#define MPU6050_ACCEL_FS_2 0x00
#define MPU6050_ACCEL_FS_4 0x01
#define MPU6050_ACCEL_FS_8 0x02
#define MPU6050_ACCEL_FS_16 0x03

#define MPU6050_DHPF_RESET 0x00
#define MPU6050_DHPF_5 0x01
#define MPU6050_DHPF_2P5 0x02
#define MPU6050_DHPF_1P25 0x03
#define MPU6050_DHPF_0P63 0x04
#define MPU6050_DHPF_HOLD 0x07

#define MPU6050_TEMP_FIFO_EN_BIT 7
#define MPU6050_XG_FIFO_EN_BIT 6
#define MPU6050_YG_FIFO_EN_BIT 5
#define MPU6050_ZG_FIFO_EN_BIT 4
#define MPU6050_ACCEL_FIFO_EN_BIT 3
#define MPU6050_SLV2_FIFO_EN_BIT 2
#define MPU6050_SLV1_FIFO_EN_BIT 1
#define MPU6050_SLV0_FIFO_EN_BIT 0

#define MPU6050_MULT_MST_EN_BIT 7
#define MPU6050_WAIT_FOR_ES_BIT 6
#define MPU6050_SLV_3_FIFO_EN_BIT 5
#define MPU6050_I2C_MST_P_NSR_BIT 4
#define MPU6050_I2C_MST_CLK_BIT 3
#define MPU6050_I2C_MST_CLK_LENGTH 4

#define MPU6050_CLOCK_DIV_348 0x0
#define MPU6050_CLOCK_DIV_333 0x1
#define MPU6050_CLOCK_DIV_320 0x2
#define MPU6050_CLOCK_DIV_308 0x3
#define MPU6050_CLOCK_DIV_296 0x4
#define MPU6050_CLOCK_DIV_286 0x5
#define MPU6050_CLOCK_DIV_276 0x6
#define MPU6050_CLOCK_DIV_267 0x7
#define MPU6050_CLOCK_DIV_258 0x8
#define MPU6050_CLOCK_DIV_500 0x9
#define MPU6050_CLOCK_DIV_471 0xA
#define MPU6050_CLOCK_DIV_444 0xB
#define MPU6050_CLOCK_DIV_421 0xC
#define MPU6050_CLOCK_DIV_400 0xD
#define MPU6050_CLOCK_DIV_381 0xE
#define MPU6050_CLOCK_DIV_364 0xF

#define MPU6050_I2C_SLV_RW_BIT 7
#define MPU6050_I2C_SLV_ADDR_BIT 6
#define MPU6050_I2C_SLV_ADDR_LENGTH 7
#define MPU6050_I2C_SLV_EN_BIT 7
#define MPU6050_I2C_SLV_BYTE_SW_BIT 6
#define MPU6050_I2C_SLV_REG_DIS_BIT 5
#define MPU6050_I2C_SLV_GRP_BIT 4
#define MPU6050_I2C_SLV_LEN_BIT 3
#define MPU6050_I2C_SLV_LEN_LENGTH 4

#define MPU6050_I2C_SLV4_RW_BIT 7
#define MPU6050_I2C_SLV4_ADDR_BIT 6
#define MPU6050_I2C_SLV4_ADDR_LENGTH 7
#define MPU6050_I2C_SLV4_EN_BIT 7
#define MPU6050_I2C_SLV4_INT_EN_BIT 6
#define MPU6050_I2C_SLV4_REG_DIS_BIT 5
#define MPU6050_I2C_SLV4_MST_DLY_BIT 4
#define MPU6050_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU6050_MST_PASS_THROUGH_BIT 7
#define MPU6050_MST_I2C_SLV4_DONE_BIT 6
#define MPU6050_MST_I2C_LOST_ARB_BIT 5
#define MPU6050_MST_I2C_SLV4_NACK_BIT 4
#define MPU6050_MST_I2C_SLV3_NACK_BIT 3
#define MPU6050_MST_I2C_SLV2_NACK_BIT 2
#define MPU6050_MST_I2C_SLV1_NACK_BIT 1
#define MPU6050_MST_I2C_SLV0_NACK_BIT 0

#define MPU6050_INTCFG_INT_LEVEL_BIT 7
#define MPU6050_INTCFG_INT_OPEN_BIT 6
#define MPU6050_INTCFG_LATCH_INT_EN_BIT 5
#define MPU6050_INTCFG_INT_RD_CLEAR_BIT 4
#define MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT 3
#define MPU6050_INTCFG_FSYNC_INT_EN_BIT 2
#define MPU6050_INTCFG_I2C_BYPASS_EN_BIT 1
#define MPU6050_INTCFG_CLKOUT_EN_BIT 0

#define MPU6050_INTMODE_ACTIVEHIGH 0x00
#define MPU6050_INTMODE_ACTIVELOW 0x01

#define MPU6050_INTDRV_PUSHPULL 0x00
#define MPU6050_INTDRV_OPENDRAIN 0x01

#define MPU6050_INTLATCH_50USPULSE 0x00
#define MPU6050_INTLATCH_WAITCLEAR 0x01

#define MPU6050_INTCLEAR_STATUSREAD 0x00
#define MPU6050_INTCLEAR_ANYREAD 0x01

#define MPU6050_INTERRUPT_FF_BIT 7
#define MPU6050_INTERRUPT_MOT_BIT 6
#define MPU6050_INTERRUPT_ZMOT_BIT 5
#define MPU6050_INTERRUPT_FIFO_OFLOW_BIT 4
#define MPU6050_INTERRUPT_I2C_MST_INT_BIT 3
#define MPU6050_INTERRUPT_PLL_RDY_INT_BIT 2
#define MPU6050_INTERRUPT_DMP_INT_BIT 1
#define MPU6050_INTERRUPT_DATA_RDY_BIT 0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define MPU6050_DMPINT_5_BIT 5
#define MPU6050_DMPINT_4_BIT 4
#define MPU6050_DMPINT_3_BIT 3
#define MPU6050_DMPINT_2_BIT 2
#define MPU6050_DMPINT_1_BIT 1
#define MPU6050_DMPINT_0_BIT 0

#define MPU6050_MOTION_MOT_XNEG_BIT 7
#define MPU6050_MOTION_MOT_XPOS_BIT 6
#define MPU6050_MOTION_MOT_YNEG_BIT 5
#define MPU6050_MOTION_MOT_YPOS_BIT 4
#define MPU6050_MOTION_MOT_ZNEG_BIT 3
#define MPU6050_MOTION_MOT_ZPOS_BIT 2
#define MPU6050_MOTION_MOT_ZRMOT_BIT 0

#define MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT 7
#define MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT 4
#define MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT 3
#define MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT 2
#define MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT 1
#define MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT 0

#define MPU6050_PATHRESET_GYRO_RESET_BIT 2
#define MPU6050_PATHRESET_ACCEL_RESET_BIT 1
#define MPU6050_PATHRESET_TEMP_RESET_BIT 0

#define MPU6050_DETECT_ACCEL_ON_DELAY_BIT 5
#define MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH 2
#define MPU6050_DETECT_FF_COUNT_BIT 3
#define MPU6050_DETECT_FF_COUNT_LENGTH 2
#define MPU6050_DETECT_MOT_COUNT_BIT 1
#define MPU6050_DETECT_MOT_COUNT_LENGTH 2

#define MPU6050_DETECT_DECREMENT_RESET 0x0
#define MPU6050_DETECT_DECREMENT_1 0x1
#define MPU6050_DETECT_DECREMENT_2 0x2
#define MPU6050_DETECT_DECREMENT_4 0x3

#define MPU6050_USERCTRL_DMP_EN_BIT 7
#define MPU6050_USERCTRL_FIFO_EN_BIT 6
#define MPU6050_USERCTRL_I2C_MST_EN_BIT 5
#define MPU6050_USERCTRL_I2C_IF_DIS_BIT 4
#define MPU6050_USERCTRL_DMP_RESET_BIT 3
#define MPU6050_USERCTRL_FIFO_RESET_BIT 2
#define MPU6050_USERCTRL_I2C_MST_RESET_BIT 1
#define MPU6050_USERCTRL_SIG_COND_RESET_BIT 0

#define MPU6050_PWR1_DEVICE_RESET_BIT 7
#define MPU6050_PWR1_SLEEP_BIT 6
#define MPU6050_PWR1_CYCLE_BIT 5
#define MPU6050_PWR1_TEMP_DIS_BIT 3
#define MPU6050_PWR1_CLKSEL_BIT 2
#define MPU6050_PWR1_CLKSEL_LENGTH 3

#define MPU6050_CLOCK_INTERNAL 0x00
#define MPU6050_CLOCK_PLL_XGYRO 0x01
#define MPU6050_CLOCK_PLL_YGYRO 0x02
#define MPU6050_CLOCK_PLL_ZGYRO 0x03
#define MPU6050_CLOCK_PLL_EXT32K 0x04
#define MPU6050_CLOCK_PLL_EXT19M 0x05
#define MPU6050_CLOCK_KEEP_RESET 0x07

#define MPU6050_PWR2_LP_WAKE_CTRL_BIT 7
#define MPU6050_PWR2_LP_WAKE_CTRL_LENGTH 2
#define MPU6050_PWR2_STBY_XA_BIT 5
#define MPU6050_PWR2_STBY_YA_BIT 4
#define MPU6050_PWR2_STBY_ZA_BIT 3
#define MPU6050_PWR2_STBY_XG_BIT 2
#define MPU6050_PWR2_STBY_YG_BIT 1
#define MPU6050_PWR2_STBY_ZG_BIT 0

#define MPU6050_WAKE_FREQ_1P25 0x0
#define MPU6050_WAKE_FREQ_2P5 0x1
#define MPU6050_WAKE_FREQ_5 0x2
#define MPU6050_WAKE_FREQ_10 0x3

#define MPU6050_BANKSEL_PRFTCH_EN_BIT 6
#define MPU6050_BANKSEL_CFG_USER_BANK_BIT 5
#define MPU6050_BANKSEL_MEM_SEL_BIT 4
#define MPU6050_BANKSEL_MEM_SEL_LENGTH 5

#define MPU6050_WHO_AM_I_BIT 6
#define MPU6050_WHO_AM_I_LENGTH 6

#define MPU6050_DMP_MEMORY_BANKS 8
#define MPU6050_DMP_MEMORY_BANK_SIZE 256
#define MPU6050_DMP_MEMORY_CHUNK_SIZE 16

void MPU6050initialize(void);
boolean MPU6050testConnection(void);
uint8 MPU6050getAuxVDDIOLevel(void);
void MPU6050setAuxVDDIOLevel(uint8 level);
uint8 MPU6050getRate(void);
void MPU6050setRate(uint8 rate);
uint8 MPU6050getExternalFrameSync(void);
void MPU6050setExternalFrameSync(uint8 sync);
uint8 MPU6050getDLPFMode(void);
void MPU6050setDLPFMode(uint8 mode);
uint8 MPU6050getFullScaleGyroRange(void);
void MPU6050setFullScaleGyroRange(uint8 range);
boolean MPU6050getAccelXSelfTest(void);
void MPU6050setAccelXSelfTest(boolean enabled);
boolean MPU6050getAccelYSelfTest(void);
void MPU6050setAccelYSelfTest(boolean enabled);
boolean MPU6050getAccelZSelfTest(void);
void MPU6050setAccelZSelfTest(boolean enabled);
uint8 MPU6050getFullScaleAccelRange(void);
void MPU6050setFullScaleAccelRange(uint8 range);
uint8 MPU6050getDHPFMode(void);
void MPU6050setDHPFMode(uint8 bandwidth);
uint8 MPU6050getFreefallDetectionThreshold(void);
void MPU6050setFreefallDetectionThreshold(uint8 threshold);
uint8 MPU6050getFreefallDetectionDuration(void);
void MPU6050setFreefallDetectionDuration(uint8 duration);
uint8 MPU6050getMotionDetectionThreshold(void);
void MPU6050setMotionDetectionThreshold(uint8 threshold);
uint8 MPU6050getMotionDetectionDuration(void);
void MPU6050setMotionDetectionDuration(uint8 duration);
uint8 MPU6050getZeroMotionDetectionThreshold(void);
void MPU6050setZeroMotionDetectionThreshold(uint8 threshold);
uint8 MPU6050getZeroMotionDetectionDuration(void);
void MPU6050setZeroMotionDetectionDuration(uint8 duration);
boolean MPU6050getTempFIFOEnabled(void);
void MPU6050setTempFIFOEnabled(boolean enabled);
boolean MPU6050getXGyroFIFOEnabled(void);
void MPU6050setXGyroFIFOEnabled(boolean enabled);
boolean MPU6050getYGyroFIFOEnabled(void);
void MPU6050setYGyroFIFOEnabled(boolean enabled);
boolean MPU6050getZGyroFIFOEnabled(void);
void MPU6050setZGyroFIFOEnabled(boolean enabled);
boolean MPU6050getAccelFIFOEnabled(void);
void MPU6050setAccelFIFOEnabled(boolean enabled);
boolean MPU6050getSlave2FIFOEnabled(void);
void MPU6050setSlave2FIFOEnabled(boolean enabled);
boolean MPU6050getSlave1FIFOEnabled(void);
void MPU6050setSlave1FIFOEnabled(boolean enabled);
boolean MPU6050getSlave0FIFOEnabled(void);
void MPU6050setSlave0FIFOEnabled(boolean enabled);
boolean MPU6050getMultiMasterEnabled(void);
void MPU6050setMultiMasterEnabled(boolean enabled);
boolean MPU6050getWaitForExternalSensorEnabled(void);
void MPU6050setWaitForExternalSensorEnabled(boolean enabled);
boolean MPU6050getSlave3FIFOEnabled(void);
void MPU6050setSlave3FIFOEnabled(boolean enabled);
boolean MPU6050getSlaveReadWriteTransitionEnabled(void);
void MPU6050setSlaveReadWriteTransitionEnabled(boolean enabled);
uint8 MPU6050getMasterClockSpeed(void);
void MPU6050setMasterClockSpeed(uint8 speed);
uint8 MPU6050getSlaveAddress(uint8 num);
void MPU6050setSlaveAddress(uint8 num, uint8 address);
uint8 MPU6050getSlaveRegister(uint8 num);
void MPU6050setSlaveRegister(uint8 num, uint8 reg);
boolean MPU6050getSlaveEnabled(uint8 num);
void MPU6050setSlaveEnabled(uint8 num, boolean enabled);
boolean MPU6050getSlaveWordByteSwap(uint8 num);
void MPU6050setSlaveWordByteSwap(uint8 num, boolean enabled);
boolean MPU6050getSlaveWriteMode(uint8 num);
void MPU6050setSlaveWriteMode(uint8 num, boolean mode);
boolean MPU6050getSlaveWordGroupOffset(uint8 num);
void MPU6050setSlaveWordGroupOffset(uint8 num, boolean enabled);
uint8 MPU6050getSlaveDataLength(uint8 num);
void MPU6050setSlaveDataLength(uint8 num, uint8 length);
uint8 MPU6050getSlave4Address(void);
void MPU6050setSlave4Address(uint8 address);
uint8 MPU6050getSlave4Register(void);
void MPU6050setSlave4Register(uint8 reg);
void MPU6050setSlave4OutputByte(uint8 data);
boolean MPU6050getSlave4Enabled(void);
void MPU6050setSlave4Enabled(boolean enabled);
boolean MPU6050getSlave4InterruptEnabled(void);
void MPU6050setSlave4InterruptEnabled(boolean enabled);
boolean MPU6050getSlave4WriteMode(void);
void MPU6050setSlave4WriteMode(boolean mode);
uint8 MPU6050getSlave4MasterDelay(void);
void MPU6050setSlave4MasterDelay(uint8 delay);
uint8 MPU6050getSlate4InputByte(void);
boolean MPU6050getPassthroughStatus(void);
boolean MPU6050getSlave4IsDone(void);
boolean MPU6050getLostArbitration(void);
boolean MPU6050getSlave4Nack(void);
boolean MPU6050getSlave3Nack(void);
boolean MPU6050getSlave2Nack(void);
boolean MPU6050getSlave1Nack(void);
boolean MPU6050getSlave0Nack(void);
boolean MPU6050getInterruptMode(void);
void MPU6050setInterruptMode(boolean mode);
boolean MPU6050getInterruptDrive(void);
void MPU6050setInterruptDrive(boolean drive);
boolean MPU6050getInterruptLatch(void);
void MPU6050setInterruptLatch(boolean latch);
boolean MPU6050getInterruptLatchClear(void);
void MPU6050setInterruptLatchClear(boolean clear);
boolean MPU6050getFSyncInterruptLevel(void);
void MPU6050setFSyncInterruptLevel(boolean level);
boolean MPU6050getFSyncInterruptEnabled(void);
void MPU6050setFSyncInterruptEnabled(boolean enabled);
boolean MPU6050getI2CBypassEnabled(void);
void MPU6050setI2CBypassEnabled(boolean enabled);
boolean MPU6050getClockOutputEnabled(void);
void MPU6050setClockOutputEnabled(boolean enabled);
uint8 MPU6050getIntEnabled(void);
void MPU6050setIntEnabled(uint8 enabled);
boolean MPU6050getIntFreefallEnabled(void);
void MPU6050setIntFreefallEnabled(boolean enabled);
boolean MPU6050getIntMotionEnabled(void);
void MPU6050setIntMotionEnabled(boolean enabled);
boolean MPU6050getIntZeroMotionEnabled(void);
void MPU6050setIntZeroMotionEnabled(boolean enabled);
boolean MPU6050getIntFIFOBufferOverflowEnabled(void);
void MPU6050setIntFIFOBufferOverflowEnabled(boolean enabled);
boolean MPU6050getIntI2CMasterEnabled(void);
void MPU6050setIntI2CMasterEnabled(boolean enabled);
boolean MPU6050getIntDataReadyEnabled(void);
void MPU6050setIntDataReadyEnabled(boolean enabled);
uint8 MPU6050getIntStatus(void);
boolean MPU6050getIntFreefallStatus(void);
boolean MPU6050getIntMotionStatus(void);
boolean MPU6050getIntZeroMotionStatus(void);
boolean MPU6050getIntFIFOBufferOverflowStatus(void);
boolean MPU6050getIntI2CMasterStatus(void);
boolean MPU6050getIntDataReadyStatus(void);
void MPU6050getMotion9(int16* ax, int16* ay, int16* az, int16* gx, int16* gy, int16* gz, int16* mx, int16* my, int16* mz);
void MPU6050getMotion6(int16* ax, int16* ay, int16* az, int16* gx, int16* gy, int16* gz);
void MPU6050getAcceleration(int16* x, int16* y, int16* z);
int16 MPU6050getAccelerationX(void);
int16 MPU6050getAccelerationY(void);
int16 MPU6050getAccelerationZ(void);
int16 MPU6050getTemperature(void);
void MPU6050getRotation(int16* x, int16* y, int16* z);
int16 MPU6050getRotationX(void);
int16 MPU6050getRotationY(void);
int16 MPU6050getRotationZ(void);
uint8 MPU6050getExternalSensorByte(int position);
uint16 MPU6050getExternalSensorWord(int position);
uint32 MPU6050getExternalSensorDWord(int position);
boolean MPU6050getXNegMotionDetected(void);
boolean MPU6050getXPosMotionDetected(void);
boolean MPU6050getYNegMotionDetected(void);
boolean MPU6050getYPosMotionDetected(void);
boolean MPU6050getZNegMotionDetected(void);
boolean MPU6050getZPosMotionDetected(void);
boolean MPU6050getZeroMotionDetected(void);
void MPU6050setSlaveOutputByte(uint8 num, uint8 data);
boolean MPU6050getExternalShadowDelayEnabled(void);
void MPU6050setExternalShadowDelayEnabled(boolean enabled);
boolean MPU6050getSlaveDelayEnabled(uint8 num);
void MPU6050setSlaveDelayEnabled(uint8 num, boolean enabled);
void MPU6050resetGyroscopePath(void);
void MPU6050resetAccelerometerPath(void);
void MPU6050resetTemperaturePath(void);
uint8 MPU6050getAccelerometerPowerOnDelay(void);
void MPU6050setAccelerometerPowerOnDelay(uint8 delay);
uint8 MPU6050getFreefallDetectionCounterDecrement(void);
void MPU6050setFreefallDetectionCounterDecrement(uint8 decrement);
uint8 MPU6050getMotionDetectionCounterDecrement(void);
void MPU6050setMotionDetectionCounterDecrement(uint8 decrement);
boolean MPU6050getFIFOEnabled(void);
void MPU6050setFIFOEnabled(boolean enabled);
boolean MPU6050getI2CMasterModeEnabled(void);
void MPU6050setI2CMasterModeEnabled(boolean enabled);
void MPU6050switchSPIEnabled(boolean enabled);
void MPU6050resetFIFO(void);
void MPU6050resetI2CMaster(void);
void MPU6050resetSensors(void);
void MPU6050reset(void);
boolean MPU6050getSleepEnabled(void);
void MPU6050setSleepEnabled(boolean enabled);
boolean MPU6050getWakeCycleEnabled(void);
void MPU6050setWakeCycleEnabled(boolean enabled);
boolean MPU6050getTempSensorEnabled(void);
void MPU6050setTempSensorEnabled(boolean enabled);
uint8 MPU6050getClockSource(void);
void MPU6050setClockSource(uint8 source);
uint8 MPU6050getWakeFrequency(void);
void MPU6050setWakeFrequency(uint8 frequency);
boolean MPU6050getStandbyXAccelEnabled(void);
void MPU6050setStandbyXAccelEnabled(boolean enabled);
boolean MPU6050getStandbyYAccelEnabled(void);
void MPU6050setStandbyYAccelEnabled(boolean enabled);
boolean MPU6050getStandbyZAccelEnabled(void);
void MPU6050setStandbyZAccelEnabled(boolean enabled);
boolean MPU6050getStandbyXGyroEnabled(void);
void MPU6050setStandbyXGyroEnabled(boolean enabled);
boolean MPU6050getStandbyYGyroEnabled(void);
void MPU6050setStandbyYGyroEnabled(boolean enabled);
boolean MPU6050getStandbyZGyroEnabled(void);
void MPU6050setStandbyZGyroEnabled(boolean enabled);
uint16 MPU6050getFIFOCount(void);
uint8 MPU6050getFIFOByte(void);
void MPU6050getFIFOBytes(uint8 *data, uint8 length);
void MPU6050setFIFOByte(uint8 data);
uint8 MPU6050getDeviceID(void);
void MPU6050setDeviceID(uint8 id);

/* ======== UNDOCUMENTED/DMP REGISTERS/METHODS ======== */

uint8 MPU6050getOTPBankValid(void);
void MPU6050setOTPBankValid(boolean enabled);
int8 MPU6050getXGyroOffsetTC(void);
void MPU6050setXGyroOffsetTC(int8 offset);
int8 MPU6050getYGyroOffsetTC(void);
void MPU6050setYGyroOffsetTC(int8 offset);
int8 MPU6050getZGyroOffsetTC(void);
void MPU6050setZGyroOffsetTC(int8 offset);
int8 MPU6050getXFineGain(void);
void MPU6050setXFineGain(int8 gain);
int8 MPU6050getYFineGain(void);
void MPU6050setYFineGain(int8 gain);
int8 MPU6050getZFineGain(void);
void MPU6050setZFineGain(int8 gain);
int16 MPU6050getXAccelOffset(void);
void MPU6050setXAccelOffset(int16 offset);
int16 MPU6050getYAccelOffset(void);
void MPU6050setYAccelOffset(int16 offset);
int16 MPU6050getZAccelOffset(void);
void MPU6050setZAccelOffset(int16 offset);
int16 MPU6050getXGyroOffset(void);
void MPU6050setXGyroOffset(int16 offset);
int16 MPU6050getYGyroOffset(void);
void MPU6050setYGyroOffset(int16 offset);
int16 MPU6050getZGyroOffset(void);
void MPU6050setZGyroOffset(int16 offset);
boolean MPU6050getIntPLLReadyEnabled(void);
void MPU6050setIntPLLReadyEnabled(boolean enabled);
boolean MPU6050getIntDMPEnabled(void);
void MPU6050setIntDMPEnabled(boolean enabled);
boolean MPU6050getDMPInt5Status(void);
boolean MPU6050getDMPInt4Status(void);
boolean MPU6050getDMPInt3Status(void);
boolean MPU6050getDMPInt2Status(void);
boolean MPU6050getDMPInt1Status(void);
boolean MPU6050getDMPInt0Status(void);
boolean MPU6050getIntPLLReadyStatus(void);
boolean MPU6050getIntDMPStatus(void);
boolean MPU6050getDMPEnabled(void);
void MPU6050setDMPEnabled(boolean enabled);
void MPU6050resetDMP(void);
void MPU6050setMemoryBank(uint8 bank, boolean prefetchEnabled, boolean userBank);
void MPU6050setMemoryStartAddress(uint8 address);
uint8 MPU6050readMemoryByte(void);
void MPU6050writeMemoryByte(uint8 data);
void MPU6050readMemoryBlock(uint8 *data, uint16 dataSize, uint8 bank, uint8 address);
boolean MPU6050writeMemoryBlock(const uint8 *data, uint16 dataSize, uint8 bank, uint8 address, boolean verify, boolean useProgMem);
boolean MPU6050writeProgMemoryBlock(const uint8 *data, uint16 dataSize, uint8 bank, uint8 address, boolean verify);
boolean MPU6050writeDMPConfigurationSet(const uint8 *data, uint16 dataSize, boolean useProgMem);
boolean MPU6050writeProgDMPConfigurationSet(const uint8 *data, uint16 dataSize);
uint8 MPU6050getDMPConfig1(void);
void MPU6050setDMPConfig1(uint8 config);
uint8 MPU6050getDMPConfig2(void);
void MPU6050setDMPConfig2(uint8 config);

#endif
