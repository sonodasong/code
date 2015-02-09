#include "pin.h"
#include "uart0_pending.h"

char hexTable[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


void uart0PendingInit(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(3);
	
	/* peripheral clock, 100 MHz */
	LPC_SC->PCLKSEL0 &= rex(7);
	LPC_SC->PCLKSEL0 |= ex(6);

	/* TXD0 pin configuration */
	pinSel(0, 2, 1);
	pinMode(0, 2, 0);
	pinModeOD(0, 2, 0);

	/* RX0 pin configuration */
	pinSel(0, 3, 1);
	pinMode(0, 3, 0);
	pinModeOD(0, 3, 0);
	
	/* baudrate 115200, 120 MHz, FDR = 0xD5 */
	/* baudrate 460800, 100 MHz, FDR = 0xE5 */
	LPC_UART0->LCR |= ex(7);
	LPC_UART0->DLL = 0x0A;
	LPC_UART0->DLM = 0x00;
	LPC_UART0->LCR &= rex(7);
	LPC_UART0->FDR = 0xE5;

	/* line control, 8-bit, 1 stop bit, no parity check */
	LPC_UART0->LCR = 0x03;

	/* enable FIFO */
	LPC_UART0->FCR = 0x81;
	LPC_UART0->FCR |= 0x06;

	/* transmit enable */
	LPC_UART0->TER = 0x80;

	/* other */
	LPC_UART0->IER = 0x00;
	LPC_UART0->ACR = 0x00;
	LPC_UART0->ICR = 0x00;
}

void uart0PendingPrint(char *str)
{
	char temp;
	uint8 cnt;

	cnt = 0;
	temp = str[0];
	while (temp != '\0') {
		LPC_UART0->THR = temp;
		cnt++;
		temp = str[cnt];
		while (!(LPC_UART0->LSR & ex(5)));
	}
}

void uart0PendingByte(uint8 byte)
{
	LPC_UART0->THR = byte;
	while (!(LPC_UART0->LSR & ex(5)));
}

void uart0PendingHex8(uint8 hex8)
{
	char buffer[5];
	
	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex8>>4)&0x0F];
	buffer[3] = hexTable[hex8&0x0F];
	buffer[4] = '\0';
	uart0PendingPrint(buffer);
}

void uart0PendingHex16(uint16 hex16)
{
	char buffer[7];
	
	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex16>>12)&0x0F];
	buffer[3] = hexTable[(hex16>>8)&0x0F];
	buffer[4] = hexTable[(hex16>>4)&0x0F];
	buffer[5] = hexTable[hex16&0x0F];
	buffer[6] = '\0';
	uart0PendingPrint(buffer);
}

void uart0PendingHex32(uint32 hex32)
{
	char buffer[11];
	
	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex32>>28)&0x0F];
	buffer[3] = hexTable[(hex32>>24)&0x0F];
	buffer[4] = hexTable[(hex32>>20)&0x0F];
	buffer[5] = hexTable[(hex32>>16)&0x0F];
	buffer[6] = hexTable[(hex32>>12)&0x0F];
	buffer[7] = hexTable[(hex32>>8)&0x0F];
	buffer[8] = hexTable[(hex32>>4)&0x0F];
	buffer[9] = hexTable[hex32&0x0F];
	buffer[10] = '\0';
	uart0PendingPrint(buffer);
}

void uart0PendingLongInt(uint32 x)
{
	char digit[11];
	uint8 i;
	
	digit[10] = '\0';
	i = 9;
	do {
		digit[i] = '0' + x%10;
		x /= 10;
		i--;
	} while (x != 0);
	i++;
	uart0PendingPrint(&digit[i]);
}
