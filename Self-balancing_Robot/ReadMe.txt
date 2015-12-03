Self-balancing Robot

https://www.youtube.com/watch?v=CnfftP7SnFE

Note that balance_robot_0.exe under code/Self-balancing_Robot/console/balance_robot_0/Debug/ cannot be opened without a joystick plugged into the computer.


This project consists of two parts: a self-balancing robot and a PC console

1. Self-balancing Robot

The core hardware for this robot is Arduino Mega 2560, MPU6050 and DC motor with encoder.

The main control algorithm is PID, and there are three PID loops.
May be this is called cascade PID control (I'm not sure).

The inner loop is a PI controller.
The setpoint is motor speed and the output is PWM.

The middle loop is a combination of P controller and PI controller.
Special considerations are taken to ensure smooth transition between P controller and PI controller.
The setpoint is angle and the output is speed.

The outer loop is a PI controller.
The integration (I) part of this controller is affected by the middle loop.
The setpoint is speed and the output is angle.

A little tricky of the setpoint and the output of the three loops.

IDE: Atmel Studio

Upload Tool: XLoader

Code Structure:

"library" contains device drivers and API.

"user" contains upper level code.

2. Console

The console on PC is an MFC (Microsoft Foundation Class) application.

It reads in joystick input through DirectX.

It sends command over Com Port through Microsoft Communication Control.

3. Reference

The code for MPU6050 references jrowberg's code:

https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
