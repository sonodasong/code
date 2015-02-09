#include "global.h"

volatile int32 rxBit32[2] = {32768, 32768};

volatile boolean mpu6050DMPRdy;
volatile int32 sAngle;
volatile int32 fAngle;
volatile int16 gLSpd;
volatile int16 gRSpd;

volatile int16 gSpd;
