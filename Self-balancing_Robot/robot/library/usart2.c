#include "global.h"
#include "usart2.h"

#define usart2TxIntEnable()		UCSR2B |= ex(TXCIE2)
#define usart2TxIntDisable()	UCSR2B &= rex(TXCIE2)
#define usart2TxFlagClr()		UCSR2A |= ex(TXC2)

#define usart2RxIntEnable()		UCSR2B |= ex(RXCIE2)

static uint8 *usart2TxPtr;
static uint8 usart2TxCnt;

void usart2Init(void)
{
	/* baud rate 38400 */
	UCSR2A = 0x02;
	UCSR2B = 0x18;
	UCSR2C = 0x06;
	UBRR2 = 51;
	usart2RxIntEnable();
	usart2TxFlagClr();
	usart2TxIntEnable();
}

void usart2Tx(int32 *x)
{
	UDR2 = x[0] & 0xFF;
	usart2TxPtr = (uint8 *)x;
	usart2TxCnt = 1;
}

ISR(USART2_RX_vect)
{
	static int32 rx32 = 0;
	uint8 rx8;
	
	rx8 = UDR2;
	sei();
	if (rx8 == '\r') {
		rx32 = 0;
	} else if (rx8 < 48) {
		rx32 = rx32 << 4;
		rx32 |= rx8 & 0x0F;
	} else {
		rxBit32[rx8 - 48] = rx32;
	}
}

ISR(USART2_TX_vect)
{
	sei();
	if (usart2TxCnt < 24) {
		UDR2 = usart2TxPtr[usart2TxCnt];
		usart2TxCnt++;
	}
}
