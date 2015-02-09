#include "laser.h"

void laserInit(void)
{
	/* laser button configuration */
	pinSel(2, 3, 0);
	pinMode(2, 3, 0);
	pinModeOD(2, 3, 0);
	LPC_GPIO2->FIOMASK &= rex(3);
	LPC_GPIO2->FIODIR &= rex(3);

	/*laser drive pin configuration */
	pinSel(2, 0, 0);
	pinMode(2, 0, 0);
	pinModeOD(2, 0, 0);
	LPC_GPIO2->FIOMASK &= rex(0);
	LPC_GPIO2->FIODIR |= ex(0);
}

void laserTask(void *pdata)
{
	(void)pdata;
	while (1) {
		if (LPC_GPIO2->FIOPIN & ex(3)) {
			LPC_GPIO2->FIOCLR = ex(0);
		} else {
			LPC_GPIO2->FIOSET = ex(0);
		}
		OSTimeDly(10);
	}
}
