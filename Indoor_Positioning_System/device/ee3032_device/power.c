#include "display.h"
#include "power.h"

void powerTask(void *pdata)
{
	static uint16 power;
	uint16 temp;

	(void)pdata;
	OSTimeDly(1000);	//wait for power to setup
	adcPend();
	power = adcRead2();
	adcPost();
	while (1) {
		adcPend();
		temp = adcRead2();
		adcPost();
		power += (temp >> 3) - (power >> 3);
		temp = (uint16)constrain(map((float)power, 3275.0, 3920.0, 0.0, 100.0), 0.0, 100.0);
		displayPowerUpdate(temp);
		OSTimeDly(500);
	}
}
