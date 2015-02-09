#include "pin.h"
#include "uart0_pending.h"
#include "usb.h"
#include "usb_mouse.h"

#define USB_DEV_EP_SLOW			2
#define USB_DEV_DEV_STAT		3
#define USB_DEV_CCEMPTY			4
#define USB_DEV_CDFULL			5
#define USB_DEV_EP_RLZED		8

static uint8 *usbEp0InBuf;
static uint16 usbEp0InSize;
static uint8 usbEp0InSendZeroPacket;

static void usbCmdW(uint8 cmd, uint8 byte, boolean byteFollowed)
{
	LPC_USB->USBDevIntClr = ex(USB_DEV_CCEMPTY);
	LPC_USB->USBCmdCode = (0x05 << 8) | (cmd << 16);
	while (!(LPC_USB->USBDevIntSt & ex(USB_DEV_CCEMPTY)));
	LPC_USB->USBDevIntClr = ex(USB_DEV_CCEMPTY);
	if (byteFollowed) {
		LPC_USB->USBCmdCode = (0x01 << 8) | (byte << 16);
		while (!(LPC_USB->USBDevIntSt & ex(USB_DEV_CCEMPTY)));
		LPC_USB->USBDevIntClr = ex(USB_DEV_CCEMPTY);
	}
}

static void usbCmdR(uint8 cmd, uint8 *buf, uint8 size)
{
	uint8 i;

	LPC_USB->USBDevIntClr = ex(USB_DEV_CCEMPTY) | ex(USB_DEV_CDFULL);
	LPC_USB->USBCmdCode = (0x05 << 8) | (cmd << 16);
	while (!(LPC_USB->USBDevIntSt & ex(USB_DEV_CCEMPTY)));
	LPC_USB->USBDevIntClr = ex(USB_DEV_CCEMPTY);
	for (i = 0; i < size; i++) {
		LPC_USB->USBCmdCode = (0x02 << 8) | (cmd << 16);
		while (!(LPC_USB->USBDevIntSt & ex(USB_DEV_CDFULL)));
		LPC_USB->USBDevIntClr = ex(USB_DEV_CDFULL);
		buf[i] = LPC_USB->USBCmdData;
	}
}

void usbInit(void)
{
	/* enable power */
	LPC_SC->PCONP |= ex(31);
	
	LPC_USB->USBClkCtrl = 0x12;
	while ((LPC_USB->USBClkSt & 0x12) != 0x12);

	/* VBUS configuration */
	pinSel(1, 30, 2);
	pinMode(1, 30, 2);
	pinModeOD(1, 30, 0);

	/* USB_CONNECT configuration */
	pinSel(2, 9, 1);
	pinMode(2, 9, 2);
	pinModeOD(2, 9, 0);

	/* USB_UP_LED configuration */
	pinSel(1, 18, 1);
	pinMode(1, 18, 2);
	pinModeOD(1, 18, 0);

	/* USB_D+ configuration */
	pinSel(0, 29, 1);
	pinMode(0, 29, 2);
	pinModeOD(0 ,29, 0);

	/* USB_D+ configuration */
	pinSel(0, 30, 1);
	pinMode(0, 30, 2);
	pinModeOD(0 ,30, 0);

	usbPEpRealization(0, USB_LOGICAL_ENDPOINT0_SIZE);
	usbPEpRealization(1, USB_LOGICAL_ENDPOINT0_SIZE);

	/* set up interrupt */
	LPC_USB->USBEpIntClr = 0xFFFFFFFF;
	LPC_USB->USBDevIntClr = 0x03FF;
	LPC_USB->USBEpIntEn = 0x0F;
	LPC_USB->USBEpIntPri = 0x00;
	usbSIESetMode(0x01);
	LPC_USB->USBDevIntEn = ex(USB_DEV_EP_SLOW) | ex(USB_DEV_DEV_STAT);
	LPC_USB->USBDevIntPri = 0x00;
	NVIC_ClearPendingIRQ(USB_IRQn);
	NVIC_EnableIRQ(USB_IRQn);
}

void usbSIESetAddress(uint8 address)
{
	usbCmdW(USB_SIE_SET_ADDRESS, 0x80 | address, TRUE);	
}

void usbSIEConfigureDevice(uint8 byte)
{
	usbCmdW(USB_SIE_CONFIGURE_DEVICE, byte, TRUE);	
}

void usbSIESetMode(uint8 byte)
{
	usbCmdW(USB_SIE_SET_MODE, byte, TRUE);
}

uint16 usbSIEReadTestRegister(void)
{
	uint16 testReg;

	usbCmdR(USB_SIE_READ_TEST_REGISTER, (uint8 *)&testReg, 2);
	return testReg;
}

void usbSIESetDeviceStatus(uint8 byte)
{
	usbCmdW(USB_SIE_SET_DEVICE_STATUS, byte, TRUE);
}

uint8 usbSIEGetDeviceStatus(void)
{
	uint8 byte;

	usbCmdR(USB_SIE_GET_DEVICE_STATUS, &byte, 1);
	return byte;
}

uint8 usbSIEGetErrorCode(void)
{
	uint8 byte;

	usbCmdR(USB_SIE_GET_ERROR_CODE, &byte, 1);
	return byte;
}

uint8 usbSIEReadErrorStatus(void)
{
	uint8 byte;

	usbCmdR(USB_SIE_READ_ERROR_STATUS, &byte, 1);
	return byte;
}

uint8 usbSIESelectEndpoint(uint8 pEp)
{
	uint8 byte;

	usbCmdR(USB_SIE_SELECT_ENDPOINT + pEp, &byte, 1);
	return byte;
}

uint8 usbSIEClearInterrupt(uint8 pEp)
{
	uint8 byte;

	usbCmdR(USB_SIE_CLEAR_INTERRUPT + pEp, &byte, 1);
	return byte;
}

void usbSIESetEndpointStatus(uint8 pEp, uint8 byte)
{
	usbCmdW(USB_SIE_SET_ENDPOINT_STATUS + pEp, byte, TRUE);
}

uint8 usbSIEClearBuffer(void)
{
	uint8 byte;

	usbCmdR(USB_SIE_CLEAR_BUFFER, &byte, 1);
	return byte;
}

void usbSIEValidateBuffer(void)
{
	usbCmdW(USB_SIE_VALIDATE_BUFFER, 0x00, FALSE);
}

void usbConnect(void)
{
#ifdef DEBUG0
	usbPrint("USB Connect\r\n");
#endif
	usbSIESetDeviceStatus(0x01);
}

void usbDisconnect(void)
{
#ifdef DEBUG0
	usbPrint("USB Disconnect\r\n");
#endif
	usbSIESetDeviceStatus(0x00);
}

void usbPEpRealization(uint8 pEp, uint8 maxPacketSize)
{
	LPC_USB->USBDevIntClr = ex(USB_DEV_EP_RLZED);
	LPC_USB->USBReEp |= ex(pEp);
	LPC_USB->USBEpInd = pEp;
	LPC_USB->USBMaxPSize = maxPacketSize;
	while (!(LPC_USB->USBDevIntSt & ex(USB_DEV_EP_RLZED)));
	LPC_USB->USBDevIntClr = ex(USB_DEV_EP_RLZED);
}

void usbPEpEnable(uint8 pEp)
{
	usbSIESetEndpointStatus(pEp, 0x00);
}

uint16 usbLEpBufR(uint8 lEp, uint8 *buf, uint16 size)
{
	uint16 cnt;
	uint16 i;
	uint32 temp;

	LPC_USB->USBCtrl = 0x01 | (lEp << 2);
	while (!(LPC_USB->USBRxPLen & ex(11)));
	cnt = LPC_USB->USBRxPLen & 0x03FF;
	if (cnt > size) {
		cnt = size;
	}
#ifdef DEBUG1
	usbPrint("Read Logical Endpoint ");
	usbLongInt(lEp);
	usbPrint(" buffer ");
	usbLongInt(cnt);
	usbPrint(" Byte:");
#endif
	for (i = 0; i < cnt; i += 4) {
		temp = LPC_USB->USBRxData;
		buf[i] = temp & 0xFF;
		temp = temp >> 8;
		buf[i + 1] = temp & 0xFF;
		temp = temp >> 8;
		buf[i + 2] = temp & 0xFF;
		temp = temp >> 8;
		buf[i + 3] = temp & 0xFF;
#ifdef DEBUG1
		if (i % 16 == 0) {
			usbPrint("\r\n");
		}
		usbHex8(buf[i]);
		usbPrint(" ");
		usbHex8(buf[i + 1]);
		usbPrint(" ");
		usbHex8(buf[i + 2]);
		usbPrint(" ");
		usbHex8(buf[i + 3]);
		usbPrint(" ");
#endif
	}
#ifdef DEBUG1
	usbPrint("\r\n");
#endif
	LPC_USB->USBCtrl = 0;	//extremely important
	usbSIESelectEndpoint(lEp * 2);
	usbSIEClearBuffer();
	return cnt;
}

uint16 usbLEpBufW(uint8 lEp, uint8 *buf, uint16 size)
{
	uint16 i;
	uint32 temp;

	LPC_USB->USBCtrl = 0x02 | (lEp << 2);
	LPC_USB->USBTxPLen = size;
#ifdef DEBUG1
	usbPrint("Write Logical Endpoint ");
	usbLongInt(lEp);
	usbPrint(" buffer ");
	usbLongInt(size);
	usbPrint(" Byte:");
#endif
	for (i = 0; i < size; i += 4) {
		temp = buf[i + 3];
		temp = temp << 8;
		temp |= buf[i + 2];
		temp = temp << 8;
		temp |= buf[i + 1];
		temp = temp << 8;
		temp |= buf[i];
		LPC_USB->USBTxData = temp;
#ifdef DEBUG1
		if (i % 16 == 0) {
			usbPrint("\r\n");
		}
		usbHex8(buf[i]);
		usbPrint(" ");
		usbHex8(buf[i + 1]);
		usbPrint(" ");
		usbHex8(buf[i + 2]);
		usbPrint(" ");
		usbHex8(buf[i + 3]);
		usbPrint(" ");
#endif
	}
#ifdef DEBUG1
	usbPrint("\r\n");
#endif
	LPC_USB->USBCtrl = 0;
	usbSIESelectEndpoint(lEp * 2 + 1);
	usbSIEValidateBuffer();
	return size;
}

void usbLEp0In(uint8 *buf, uint16 size, boolean considerZeroPacket)
{
	usbEp0InBuf = buf;
	usbEp0InSize = size;
	if ((considerZeroPacket == TRUE) && (size % USB_LOGICAL_ENDPOINT0_SIZE == 0)) {
		usbEp0InSendZeroPacket = TRUE;
	} else {
		usbEp0InSendZeroPacket = FALSE;
	}
	if (usbEp0InSize > USB_LOGICAL_ENDPOINT0_SIZE) {
		usbLEpBufW(0, usbEp0InBuf, USB_LOGICAL_ENDPOINT0_SIZE);
		usbEp0InBuf += USB_LOGICAL_ENDPOINT0_SIZE;
		usbEp0InSize -= USB_LOGICAL_ENDPOINT0_SIZE;
	} else if (usbEp0InSize > 0) {
		usbLEpBufW(0, usbEp0InBuf, size);
		usbEp0InSize = 0;
	} else if (considerZeroPacket) {
		usbLEpBufW(0, usbEp0InBuf, 0);
		usbEp0InSendZeroPacket = FALSE;
	}
}

void usbLEp0InApd(void)
{
	if (usbEp0InSize > USB_LOGICAL_ENDPOINT0_SIZE) {
		usbLEpBufW(0, usbEp0InBuf, USB_LOGICAL_ENDPOINT0_SIZE);
		usbEp0InBuf += USB_LOGICAL_ENDPOINT0_SIZE;
		usbEp0InSize -= USB_LOGICAL_ENDPOINT0_SIZE;
	} else if (usbEp0InSize > 0) {
		usbLEpBufW(0, usbEp0InBuf, usbEp0InSize);
		usbEp0InSize = 0;
	} else if (usbEp0InSendZeroPacket) {
		usbLEpBufW(0, usbEp0InBuf, 0);
		usbEp0InSendZeroPacket = FALSE;
	}
}

static void usbHandler(void)
{
	if (LPC_USB->USBDevIntSt & ex(USB_DEV_EP_SLOW)) {
		LPC_USB->USBDevIntClr = ex(USB_DEV_EP_SLOW);
		if (LPC_USB->USBEpIntSt & ex(0)) {
			usbLEp0OutHandler();
			LPC_USB->USBEpIntClr = ex(0);	//execute after usbSIEClearInterrupt()
		}
		if (LPC_USB->USBEpIntSt & ex(1)) {
			usbLEp0InHandler();
			LPC_USB->USBEpIntClr = ex(1);	//execute after usbSIEClearInterrupt()
		}
		if (LPC_USB->USBEpIntSt & ex(2)) {
			usbLEp1OutHandler();
			LPC_USB->USBEpIntClr = ex(2);	//execute after usbSIEClearInterrupt()
		}
		if (LPC_USB->USBEpIntSt & ex(3)) {
			usbLEp1InHandler();
			LPC_USB->USBEpIntClr = ex(3);	//execute after usbSIEClearInterrupt()
		}
	}
	if (LPC_USB->USBDevIntSt & ex(USB_DEV_DEV_STAT)) {
		LPC_USB->USBDevIntClr = ex(USB_DEV_DEV_STAT);
		usbSIEGetDeviceStatus();
#ifdef DEBUG0
		usbPrint("****** USB Device Status Change Interrupt\r\n");
#endif
	}
}

void USB_IRQHandler(void)
{
	OSIntEnter();
	usbHandler();
	OSIntExit();
}

void usbPrint(char *str)
{
	uart0PendingPrint(str);
}

void usbHex8(uint8 hex8)
{
	uart0PendingHex8(hex8);
}

void usbHex16(uint16 hex16)
{
	uart0PendingHex16(hex16);
}

void usbHex32(uint32 hex32)
{
	uart0PendingHex32(hex32);
}

void usbLongInt(uint32 x)
{
	uart0PendingLongInt(x);
}
