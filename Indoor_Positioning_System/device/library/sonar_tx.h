#ifndef __SONAR_TX_H__
#define __SONAR_TX_H__

#include "define.h"

#define REPETITIVE_TIMER_TIMEOUT		0xFFFFFFFF

void sonarTxInit(void);
INT8U sonarTxSendPulse(uint32 delay, INT32U timeout);

#endif
