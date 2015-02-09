#ifndef __SONAR_RX_H__
#define __SONAR_RX_H__

#include "define.h"

void sonarRxInit(void);
INT8U sonarRxTrigger(INT32U timeout);
void sonarRxReadReset(void);
INT8U sonarRxRead0(uint32 *distance, INT32U timeout);
INT8U sonarRxRead1(uint32 *distance, INT32U timeout);
INT8U sonarRxRead2(uint32 *distance, INT32U timeout);

#endif
