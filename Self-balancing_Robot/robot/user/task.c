#include "task.h"

void mpu6050Task(void)
{
	uint8 mpuIntStatus;
	uint8 fifoBuffer[42];
	int16 buf[3];
	int16 ax, gy;
	
	mpu6050DMPPend();
	mpuIntStatus = MPU6050getIntStatus();
	if (mpuIntStatus & 0x02) {
		MPU6050getFIFOBytes(fifoBuffer, 48);
		MPU6050dmpGetAccel(buf, fifoBuffer);
		ax = buf[0];
		MPU6050dmpGetGyro(buf, fifoBuffer);
		gy = buf[1];
		fAngle = complementary(ax, -gy / 4);
	} else if (mpuIntStatus & 0x10) {
		MPU6050resetFIFO();
	}
}

void pidAngleTask(void)
{
	int16 spd;
	int32 turn;
	
	spd = pidAngle(sAngle, fAngle);
	gSpd = aSpdExp(spd);
	turn = rxBit32[0];
	turn -= 32768;
	turn /= 512;
	gLSpd = gSpd + turn;
	gRSpd = gSpd - turn;
}

void pidVelocityTask(void)
{
	int16 angle;
	int32 velocity;
	
	velocity = rxBit32[1];
	velocity -= 32768;
	velocity /= 256;
	angle = -pidVelocity(velocity, gSpd);
	sAngle = vAglExp(angle);
}

ISR(TIMER1_CAPT_vect)
{
	static uint8 div = 0;
	int16 spd;
	int16 pwm;
	
	sei();
	if (div == 3) {
		spd = decoderLSpd8() * FIXED_DIV;
		pwm = pidLSpd(gLSpd, spd);
		motorL(pwm);
		div = 0;
	} else if (div == 1) {
		spd = decoderRSpd8() * FIXED_DIV;
		pwm = pidRSpd(gRSpd, spd);
		motorR(pwm);
		div++;
	} else {
		div++;
	}
}
