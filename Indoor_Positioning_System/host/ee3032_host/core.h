#ifndef __CORE_H__
#define __CORE_H__

#include <library.h>

void coreInit(void);
INT8U coreSonarPend(INT32U timeout);
INT8U coreSonarD0Pend(INT32U timeout);
INT8U coreSonarD1Pend(INT32U timeout);
INT8U coreSonarD2Pend(INT32U timeout);
void coreTask(void *pdata);
void pointerTask(void *pdata);
void mouseTask(void *pdata);

#endif
