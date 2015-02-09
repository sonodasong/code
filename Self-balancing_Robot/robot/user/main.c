#include "user.h"

int main()
{
	enablePullup();
	ledInit();
	decoderInit();
	i2cInit();
	motorInit();
	mpu6050DMPInit();
	pwmInit();
	usart0Init();
	usart2Init();
	sei();
	while (mpu6050DMPInitFromTask());
	while (1) {
		mpu6050Task();
		pidAngleTask();
		pidVelocityTask();
	}
	return 0;
}
