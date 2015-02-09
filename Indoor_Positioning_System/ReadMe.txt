Indoor Positioning System

https://www.youtube.com/watch?v=ysPJ32R-4bY

This project consists of two parts: device and host.

1. Device

Device gets orientation information from MPU9150.

It also transmits ultrasound.

IDE: LPCXpresso

Code Structure:

"startup" contains initialization code and other supporting code for LPC1769.

"uCOS-II" contains the source code for the RTOS as well as the porting code.

"APP" contains user customized part of the RTOS.

"library" contains device drivers and API.

"ee3032_deivce" contains upper level code.

2. Host

Host gets the position of the device by receiving the ultrasound and calculate distance.

Besides, host provides USB HID interface.

IDE: Keil

Code Structure:

"CMSIS" contains initialization code and other supporting code for LPC1768.

"uCOS-II" contains the source code for the RTOS as well as the porting code.

"APP" contains user customized part of the RTOS.

"library" contains device drivers and API.

"ee3032_host" contains upper level code.

3. Reference

The code for MPU9150 references jrowberg's code:

https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
