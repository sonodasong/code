#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <library.h>

void mouseInit(void);
void mouseRead(uint8 *buf);
void mouseTask(void *pdata);

#endif
