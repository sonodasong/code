#include "usart0.h"

char hexTable[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

#define usart0TxFlagClr()		UCSR0A |= ex(TXC0)
#define usart0RxIntEnable()		UCSR0B |= ex(RXCIE0)

static char usart0RxQ[ex(USART0_RX_Q_SIZE)][ex(USART0_RX_SIZE)];
static boolean usart0RxQFull[ex(USART0_RX_Q_SIZE)] = {FALSE};
static uint8 usart0RxCnt = 0;
static uint8 usart0RxQCnt = 0;
static uint8 usart0RxReadCnt = 0;

void usart0Init(void)
{
	/* baud rate 115200 */
	UCSR0A = 0x02;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0 = 16;
	usart0RxIntEnable();
}

void usart0Print(char *str)
{
	char temp;
	uint8 cnt;
	
	cnt = 0;
	temp = str[0];
	while (temp != '\0') {
		UDR0 = temp;
		cnt++;
		temp = str[cnt];
		while (!(UCSR0A & ex(TXC0)));
		usart0TxFlagClr();
	}
}

void usart0Bit8(uint8 bit8)
{
	UDR0 = bit8;
	while (!(UCSR0A & ex(TXC0)));
	usart0TxFlagClr();
}

void usart0Bit16(uint16 bit16)
{
	UDR0 = bit16 & 0xFF;
	while (!(UCSR0A & ex(TXC0)));
	usart0TxFlagClr();
	UDR0 = (bit16 >> 8) & 0xFF;
	while (!(UCSR0A & ex(TXC0)));
	usart0TxFlagClr();
}

void usart0Bit32(uint32 bit32)
{
	UDR0 = bit32 & 0xFF;
	while (!(UCSR0A & ex(TXC0)));
	usart0TxFlagClr();
	UDR0 = (bit32 >> 8) & 0xFF;
	while (!(UCSR0A & ex(TXC0)));
	usart0TxFlagClr();
	UDR0 = (bit32 >> 16) & 0xFF;
	while (!(UCSR0A & ex(TXC0)));
	usart0TxFlagClr();
	UDR0 = (bit32 >> 24) & 0xFF;
	while (!(UCSR0A & ex(TXC0)));
	usart0TxFlagClr();
}

void usart0Hex8(uint8 hex8)
{
	char buffer[5];
	
	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex8 >> 4) & 0x0F];
	buffer[3] = hexTable[hex8 & 0x0F];
	buffer[4] = '\0';
	usart0Print(buffer);
}

void usart0Hex16(uint16 hex16)
{
	char buffer[7];
	
	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex16 >> 12) & 0x0F];
	buffer[3] = hexTable[(hex16 >> 8) & 0x0F];
	buffer[4] = hexTable[(hex16 >> 4) & 0x0F];
	buffer[5] = hexTable[hex16 & 0x0F];
	buffer[6] = '\0';
	usart0Print(buffer);
}

void usart0Hex32(uint32 hex32)
{
	char buffer[11];
	
	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex32 >> 28) & 0x0F];
	buffer[3] = hexTable[(hex32 >> 24) & 0x0F];
	buffer[4] = hexTable[(hex32 >> 20) & 0x0F];
	buffer[5] = hexTable[(hex32 >> 16) & 0x0F];
	buffer[6] = hexTable[(hex32 >> 12) & 0x0F];
	buffer[7] = hexTable[(hex32 >> 8) & 0x0F];
	buffer[8] = hexTable[(hex32 >> 4) & 0x0F];
	buffer[9] = hexTable[hex32 & 0x0F];
	buffer[10] = '\0';
	usart0Print(buffer);
}

void usart0LongInt(uint32 x)
{
	char digit[11];
	uint8 i;
	
	digit[10] = '\0';
	i = 9;
	do {
		digit[i] = '0' + x % 10;
		x /= 10;
		i--;
	} while (x != 0);
	i++;
	usart0Print(&digit[i]);
}

boolean usart0RxAvailable(void)
{
	return usart0RxQFull[usart0RxReadCnt];
}

char *usart0Read(void)
{
	char *str;
	
	str = usart0RxQ[usart0RxReadCnt];
	cli();
	usart0RxQFull[usart0RxReadCnt] = FALSE;
	sei();
	usart0RxReadCnt++;
	usart0RxReadCnt &= ex(USART0_RX_Q_SIZE) - 1;
	return str;
}

ISR(USART0_RX_vect)
{
	char USART0RxChar;
	
	USART0RxChar = UDR0;
	if (USART0RxChar == USART0_RX_EOF) {
		usart0RxQ[usart0RxQCnt][usart0RxCnt] = '\0';
		usart0RxQFull[usart0RxQCnt] = TRUE;
		usart0RxQCnt++;
		usart0RxQCnt &= ex(USART0_RX_Q_SIZE) - 1;
		usart0RxCnt = 0;
	} else {
		usart0RxQ[usart0RxQCnt][usart0RxCnt] = USART0RxChar;
		usart0RxCnt++;
		usart0RxCnt &= ex(USART0_RX_SIZE) - 1;
	}
}
