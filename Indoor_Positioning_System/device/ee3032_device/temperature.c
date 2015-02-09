#include "display.h"
#include "temperature.h"

void temperatureTask(void *pdata)
{
	static uint16 temperature;
	uint16 temp;

	(void)pdata;
	OSTimeDly(1000);	//wait for temperature to setup
	adcPend();
	temperature = adcRead3();
	adcPost();
	while (1) {
		adcPend();
		temp = adcRead3();
		adcPost();
		temperature += (temp >> 3) - (temperature >> 3);
		temp = (uint16)constrain(map((float)temperature, 0.0, 4096.0, 0.0, 3300.0), 0.0, 999.0);
		displayTemperatureUpdate(temp);
		OSTimeDly(500);
	}
}
