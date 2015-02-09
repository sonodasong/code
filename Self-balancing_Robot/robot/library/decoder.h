#ifndef __DECODER_H__
#define __DECODER_H__

#include "define.h"

void decoderInit(void);
int8 decoderLSpd8(void);
int8 decoderRSpd8(void);
int16 decoderLSpd16(void);
int16 decoderRSpd16(void);
int32 decoderLPos32(void);
int32 decoderRPos32(void);

#endif
