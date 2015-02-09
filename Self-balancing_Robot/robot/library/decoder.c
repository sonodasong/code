#include "decoder.h"

static volatile int32 decoderLPos = 0;
static volatile int32 decoderRPos = 0;

void decoderInit(void)
{
	// left wheel
	DDRG &= rex(5);
	PORTG |= ex(5);
	EICRB |= 0x03;
	EIFR = ex(4);
	EIMSK |= ex(4);
	// right wheel
	DDRE &= rex(3);
	PORTE |= ex(3);
	EICRB |= 0x0C;
	EIFR = ex(5);
	EIMSK |= ex(5);
}

int8 decoderLSpd8(void)
{
	static int8 prevPos = 0;
	int8 spd;
	
	spd = (int8)decoderLPos - prevPos;
	prevPos = (int8)decoderLPos;
	return spd;
}

int8 decoderRSpd8(void)
{
	static int8 prevPos = 0;
	int8 spd;
	
	spd = (int8)decoderRPos - prevPos;
	prevPos = (int8)decoderRPos;
	return spd;
}

int16 decoderLSpd16(void)
{
	static int16 prevPos = 0;
	int16 spd;
	
	spd = (int16)decoderLPos - prevPos;
	prevPos = (int16)decoderLPos;
	return spd;
}

int16 decoderRSpd16(void)
{
	static int16 prevPos = 0;
	int16 spd;
	
	spd = (int16)decoderRPos - prevPos;
	prevPos = (int16)decoderRPos;
	return spd;
}

int32 decoderLPos32(void)
{
	return decoderLPos;
}

int32 decoderRPos32(void)
{
	return decoderRPos;
}

ISR(INT4_vect)
{
	if (PING & ex(5)) {
		decoderLPos++;
	} else {
		decoderLPos--;
	}
}

ISR(INT5_vect)
{
	if (PINE & ex(3)) {
		decoderRPos--;
	} else {
		decoderRPos++;
	}
}
