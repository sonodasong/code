#include "usb.h"
#include "usb_mouse.h"

static uint8 usbEp0OutBuf[USB_LOGICAL_ENDPOINT0_SIZE];
static uint8 usbDescriptor[64];

static OS_EVENT *usbMouseRdy;

static void usbFillDeviceDescriptor(uint8 *buf);
static void usbFillConfigurationDescriptor(uint8 *buf);
static void usbFillInterfaceDescriptor(uint8 *buf);
static void usbFillEndpointDescriptor(uint8 *buf);
static void usbFillHIDDescriptor(uint8 *buf);
static void usbFillLanguageID(uint8 *buf);
static void usbFillStringDescriptor(uint8 *buf, char *str);
static void usbFillReportDescriptor(uint8 *buf);

static void usbDeviceRequestHandler(void);
static void usbStandardRequestHandler(void);
static void usbSetAddressHandler(void);
static void usbGetDescriptorHandler(void);
static void usbDeviceDescriptorHandler(void);
static void usbConfigurationDescriptorHandler(void);
static void usbStringDescriptorHandler(void);
static void usbReportDescriptorHandler(void);
static void usbSetConfigurationHandler(void);

static void usbClassRequestHandler(void);
static void usbSetIdleHandler(void);

void usbMouseInit(void)
{
	usbInit();
	usbMouseRdy = OSSemCreate(0);
}

void usbMouseConnect(void)
{
	usbConnect();
}

void usbMouseDisconnect(void)
{
	usbDisconnect();
}

INT8U usbMouseInput(uint8 *buf, INT32U timeout)
{
	INT8U err;

	OSSemPend(usbMouseRdy, timeout, &err);
	usbLEpBufW(1, buf, 4);
	return err;
}

void usbLEp0OutHandler(void)
{
#ifdef DEBUG0
	usbPrint("Endpoint 0 Out Interrupt\r\n");
#endif
	if (usbSIEClearInterrupt(0) & 0x04) {
		usbLEpBufR(0, usbEp0OutBuf, USB_LOGICAL_ENDPOINT0_SIZE);
		usbDeviceRequestHandler();
	} else {
		usbLEpBufR(0, usbEp0OutBuf, USB_LOGICAL_ENDPOINT0_SIZE);
	}
}

void usbLEp0InHandler(void)
{
#ifdef DEBUG0
	usbPrint("Endpoint 0 In Interrupt\r\n");
#endif
	usbSIEClearInterrupt(1);
	usbLEp0InApd();
}

void usbLEp1OutHandler(void)
{
#ifdef DEBUG0
	usbPrint("Endpoint 1 Out Interrupt\r\n");
#endif
	usbSIEClearInterrupt(2);
}

void usbLEp1InHandler(void)
{
	INT8U err;

#ifdef DEBUG0
	usbPrint("Endpoint 1 In Interrupt\r\n");
#endif
	usbSIEClearInterrupt(3);
	OSSemSet(usbMouseRdy, 0, &err);
	OSSemPost(usbMouseRdy);
}

static void usbFillDeviceDescriptor(uint8 *buf)
{
	tUSBDeviceDescriptor *p;
	
	p = (tUSBDeviceDescriptor *)buf;
	p->bLength = 0x12;
	p->bDescriptorType = 0x01;
	p->bcdUSBL = 0x10;
	p->bcdUSBH = 0x01;
	p->bDeviceClass = 0x00;
	p->bDeviceSubClass = 0x00;
	p->bDeviceProtocol = 0x00;
	p->bMaxPacketSize0 = USB_LOGICAL_ENDPOINT0_SIZE;
	p->idVendorL = 0x88;
	p->idVendorH = 0x88;
	p->idProductL = 0x00;
	p->idProductH = 0x00;
	p->bcdDeviceL = 0x00;
	p->bcdDeviceH = 0x00;
	p->iManufacturer = USB_STRING_INDEX_1;
	p->iProduct = USB_STRING_INDEX_2;
	p->iSerialNumber = USB_STRING_INDEX_3;
	p->bNumConfigurations = 0x01;
}

static void usbFillConfigurationDescriptor(uint8 *buf)
{
	tUSBConfigurationDescriptor *p;
	
	p = (tUSBConfigurationDescriptor *)buf;
	p->bLength = 0x09;
	p->bDescriptorType = 0x02;
	p->wTotalLengthL = 0x22;
	p->wTotalLengthH = 0x00;
	p->bNumInterfaces = 0x01;
	p->bConfigurationValue = 0x01;
	p->iConfiguration = 0x00;
	p->bmAttributes = 0x80;
	p->bMaxPower = 0x32;
	usbFillInterfaceDescriptor(buf + 0x09);
	usbFillHIDDescriptor(buf + 0x12);
	usbFillEndpointDescriptor(buf + 0x1B);
}

static void usbFillInterfaceDescriptor(uint8 *buf)
{
	tUSBInterfaceDescriptor *p;
	
	p = (tUSBInterfaceDescriptor *)buf;
	p->bLength = 0x09;
	p->bDescriptorType = 0x04;
	p->bInterfaceNumber = 0x00;
	p->bAlternateSetting = 0x00;
	p->bNumEndpoints = 0x01;
	p->bInterfaceClass = 0x03;
	p->bInterfaceSubClass = 0x01;
	p->bInterfaceProtocol = 0x02;
	p->iInterface = 0x00;
}

static void usbFillEndpointDescriptor(uint8 *buf)
{
	tUSBEndpointDescriptor *p;
	
	p = (tUSBEndpointDescriptor *)buf;
	p->bLength = 0x07;
	p->bDescriptorType = 0x05;
	p->bEndpointAddress = 0x81;
	p->bmAttributes = 0x03;
	p->wMaxPacketSizeL = USB_LOGICAL_ENDPOINT1_SIZE & 0xFF;
	p->wMaxPacketSizeH = (USB_LOGICAL_ENDPOINT1_SIZE >> 8) & 0xFF;
	p->bInterval = 0x0A;
}

static void usbFillHIDDescriptor(uint8 *buf)
{
	tUSBHIDDescriptor *p;
	
	p = (tUSBHIDDescriptor *)buf;
	p->bLength = 0x09;
	p->bDescriptorType = 0x21;
	p->bcdHIDL = 0x10;
	p->bcdHIDH = 0x01;
	p->bCountryCode = 0x21;
	p->bNumDescriptors = 0x01;
	p->bDescriptor1Type = 0x22;
	p->wDescriptor1LengthL = 0x34;
	p->wDescriptor1LengthH = 0x00;
}

static void usbFillLanguageID(uint8 *buf)
{
	buf[0] = 0x04;
	buf[1] = 0x03;
	buf[2] = 0x09;
	buf[3] = 0x04;
}

static void usbFillStringDescriptor(uint8 *buf, char *str)
{
	uint8 index;
	uint8 cnt;
	
	index = 2;
	cnt = 0;
	while (str[cnt] != '\0') {
		buf[index] = str[cnt];
		buf[index + 1] = 0x00;
		cnt++;
		index +=2;
	}
	buf[0] = index;
	buf[1] = 0x03;
}

static void usbFillReportDescriptor(uint8 *buf)
{
	uint16 *p;
	
	p = (uint16 *)buf;
	p[0] = 0x0105;		// USAGE_PAGE (Generic Desktop)
	p[1] = 0x0209;		// USAGE (Mouse)
	p[2] = 0x01a1;		// COLLECTION (Application)
	p[3] = 0x0109;		//   USAGE (Pointer)
	p[4] = 0x00A1;		//   COLLECTION (Physical)
	p[5] = 0x0905;		//     USAGE_PAGE (Button)
	p[6] = 0x0119;		//     USAGE_MINIMUM (Button 1)
	p[7] = 0x0329;		//     USAGE_MAXIMUM (Button 3)
	p[8] = 0x0015;		//     LOGICAL_MINIMUM (0)
	p[9] = 0x0125;		//     LOGICAL_MAXIMUM (1)
	p[10] = 0x0395;		//     REPORT_COUNT (3)
	p[11] = 0x0175;		//     REPORT_SIZE (1)
	p[12] = 0x0281;		//     INPUT (Data,Var,Abs)
	p[13] = 0x0195;		//     REPORT_COUNT (1)
	p[14] = 0x0575;		//     REPORT_SIZE (5)
	p[15] = 0x0381;		//     INPUT (Cnst,Var,Abs)
	p[16] = 0x0105;		//     USAGE_PAGE (Generic Desktop)
	p[17] = 0x3009;		//     USAGE (X)
	p[18] = 0x3109;		//     USAGE (Y)
	p[19] = 0x3809;		//     USAGE (Wheel)
	p[20] = 0x8115;		//     LOGICAL_MINIMUM (-127)
	p[21] = 0x7F25;		//     LOGICAL_MAXIMUM (127)
	p[22] = 0x0875;		//     REPORT_SIZE (8)
	p[23] = 0x0395;		//     REPORT_COUNT (3)
	p[24] = 0x0681;		//     INPUT (Data,Var,Rel)
	buf[0x32] = 0xC0;	//   END_COLLECTION
	buf[0x33] = 0xC0;	//   END_COLLECTION
}

static void usbDeviceRequestHandler(void)
{
	tUSBDeviceRequest *p;
	
	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	switch ((p->bmRequestType >> 5) & 0x03) {
	case USB_STANDARD:
#ifdef DEBUG0
		usbPrint("USB Standard Request: ");
#endif
		usbStandardRequestHandler();
		break;
	case USB_CLASS:
#ifdef DEBUG0
		usbPrint("USB Class Request: ");
#endif
		usbClassRequestHandler();
		break;
	case USB_VENDOR:
#ifdef DEBUG0
		usbPrint("USB Vendor Request\r\n");
#endif
		break;
	default:
#ifdef DEBUG0
		usbPrint("Reserved\r\n");
#endif
		break;
	}
}

static void usbStandardRequestHandler(void)
{
	tUSBDeviceRequest *p;
	
	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	switch (p->bRequest) {
	case USB_GET_STATUS:
#ifdef DEBUG0
		usbPrint("Get Status\r\n");
#endif
		break;
	case USB_CLEAR_FEATURE:
#ifdef DEBUG0
		usbPrint("Clear Feature\r\n");
#endif
		break;
	case USB_SET_FEATURE:
#ifdef DEBUG0
		usbPrint("Set Feature\r\n");
#endif
		break;
	case USB_SET_ADDRESS:
#ifdef DEBUG0
		usbPrint("Set Address: ");
#endif
		usbSetAddressHandler();
		break;
	case USB_GET_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Get Descriptor: ");
#endif
		usbGetDescriptorHandler();
		break;
	case USB_SET_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Set Descriptor\r\n");
#endif
		break;
	case USB_GET_CONFIGURATION:
#ifdef DEBUG0
		usbPrint("Get Configuration\r\n");
#endif
		break;
	case USB_SET_CONFIGURATION:
#ifdef DEBUG0
		usbPrint("Set Configuration\r\n");
#endif
		usbSetConfigurationHandler();
		break;
	case USB_GET_INTERFACE:
#ifdef DEBUG0
		usbPrint("Get Interface\r\n");
#endif
		break;
	case USB_SET_INTERFACE:
#ifdef DEBUG0
		usbPrint("Set Interface\r\n");
#endif
		break;
	case USB_SYNCH_FRAME:
#ifdef DEBUG0
		usbPrint("Synchronize Frame\r\n");
#endif
		break;
	default:
#ifdef DEBUG0
	usbPrint("Reserved\r\n");
#endif
		break;
	}
}

static void usbSetAddressHandler(void)
{
	tUSBDeviceRequest *p;
	uint16 wValue;
	
	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	wValue = p->wValueH;
	wValue = wValue << 8;
	wValue |= p->wValueL;
#ifdef DEBUG0
	usbHex8(wValue & 0xFF);
	usbPrint("\r\n");
#endif
	usbSIESetAddress(wValue & 0xFF);
	usbLEp0In((uint8 *)NULL, 0, TRUE);
}

static void usbGetDescriptorHandler(void)
{
	tUSBDeviceRequest *p;
	uint16 wValue;
	
	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	wValue = p->wValueH;
	wValue = wValue << 8;
	wValue |= p->wValueL;
	switch ((wValue >> 8) & 0xFF) {
	case USB_DEVICE_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Device Descriptor\r\n");
#endif
		usbDeviceDescriptorHandler();
		break;
	case USB_CONFIGURATION_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Configuration Descriptor\r\n");
#endif
		usbConfigurationDescriptorHandler();
		break;
	case USB_STRING_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("String Descriptor: ");
#endif
		usbStringDescriptorHandler();
		break;
	case USB_DEVICE_QUALIFIER_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Device Qualifier Descriptor\r\n");
#endif
		break;
	case USB_OTHER_SPEED_CONFIGURATIOLN_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Other Speed Configuration Descriptor\r\n");
#endif
		break;
	case USB_INTERFACE_POWER_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Interface Power Descriptor\r\n");
#endif
		break;
	case USB_REPORT_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Report Descriptor\r\n");
#endif
		usbReportDescriptorHandler();
		break;
	case USB_PHYSICAL_DESCRIPTOR:
#ifdef DEBUG0
		usbPrint("Physical Descriptor\r\n");
#endif
		break;
	default:
#ifdef DEBUG0
		usbPrint("Reserved\r\n");
#endif
		break;
	}
}

static void usbDeviceDescriptorHandler(void)
{
	tUSBDeviceRequest *p;
	uint16 wLength;
	tUSBDeviceDescriptor *q;
	
	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	wLength = p->wLengthH;
	wLength = wLength << 8;
	wLength |= p->wLengthL;
	q = (tUSBDeviceDescriptor *)usbDescriptor;
	usbFillDeviceDescriptor(usbDescriptor);
	if (wLength > q->bLength) {
		usbLEp0In(usbDescriptor, q->bLength, TRUE);
	} else {
		usbLEp0In(usbDescriptor, wLength, FALSE);
	}
}

static void usbConfigurationDescriptorHandler(void)
{
	tUSBDeviceRequest *p;
	uint16 wLength;
	tUSBConfigurationDescriptor *q;
	uint16 wTotalLength;

	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	wLength = p->wLengthH;
	wLength = wLength << 8;
	wLength |= p->wLengthL;
	q = (tUSBConfigurationDescriptor *)usbDescriptor;
	usbFillConfigurationDescriptor(usbDescriptor);
	wTotalLength = q->wTotalLengthH;
	wTotalLength = wTotalLength << 8;
	wTotalLength |= q->wTotalLengthL;
	
	if (wLength > wTotalLength) {
		usbLEp0In(usbDescriptor, wTotalLength, TRUE);
	} else {
		usbLEp0In(usbDescriptor, wLength, FALSE);
	}
}

static void usbStringDescriptorHandler(void)
{
	tUSBDeviceRequest *p;
	uint16 wValue;
	uint16 wLength;
	
	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	wValue = p->wValueH;
	wValue = wValue << 8;
	wValue |= p->wValueL;
	wLength = p->wLengthH;
	wLength = wLength << 8;
	wLength |= p->wLengthL;
	switch (wValue & 0xFF) {
	case 0x00:
#ifdef DEBUG0
		usbPrint("Language ID\r\n");
#endif
		usbFillLanguageID(usbDescriptor);
		break;
	case USB_STRING_INDEX_1:
#ifdef DEBUG0
		usbPrint("Manufacturer Description\r\n");
#endif
		usbFillStringDescriptor(usbDescriptor, "EE3032 Group 1 - 2");
		break;
	case USB_STRING_INDEX_2:
#ifdef DEBUG0
usbPrint("Product Description\r\n");
#endif
		usbFillStringDescriptor(usbDescriptor, "EE3032 3D Mouse");
		break;
	case USB_STRING_INDEX_3:
#ifdef DEBUG0
		usbPrint("Product Serial Number\r\n");
#endif
		usbFillStringDescriptor(usbDescriptor, "6TX3V-WRDJ6-JC34X-BDDPV-6F3PB");
		break;
	default:
#ifdef DEBUG0
		usbPrint("Reserved\r\n");
#endif
		break;
	}
	if (wLength > usbDescriptor[0]) {
		usbLEp0In(usbDescriptor, usbDescriptor[0], TRUE);
	} else {
		usbLEp0In(usbDescriptor, wLength, FALSE);
	}
}

static void usbReportDescriptorHandler(void)
{
	tUSBDeviceRequest *p;
	uint16 wLength;
	
	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	wLength = p->wLengthH;
	wLength = wLength << 8;
	wLength |= p->wLengthL;
	usbFillReportDescriptor(usbDescriptor);
	if (wLength > 0x34) {
		usbLEp0In(usbDescriptor, 0x34, TRUE);
	} else {
		usbLEp0In(usbDescriptor, wLength, FALSE);
	}
}

static void usbSetConfigurationHandler(void)
{
	usbPEpRealization(2, USB_LOGICAL_ENDPOINT1_SIZE);
	usbPEpRealization(3, USB_LOGICAL_ENDPOINT1_SIZE);
	usbPEpEnable(2);
	usbPEpEnable(3);
	usbSIEConfigureDevice(0x01);
	usbLEp0In((uint8 *)NULL, 0, TRUE);
}

static void usbClassRequestHandler(void)
{
	tUSBDeviceRequest *p;
	
	p = (tUSBDeviceRequest *)usbEp0OutBuf;
	switch (p->bRequest) {
	case USB_GET_REPORT:
#ifdef DEBUG0
		usbPrint("Get Report\r\n");
#endif
		break;
	case USB_GET_IDLE:
#ifdef DEBUG0
		usbPrint("Get Idle\r\n");
#endif
		break;
	case USB_GET_PROTOCOL:
#ifdef DEBUG0
		usbPrint("Get Protocol\r\n");
#endif
		break;
	case USB_SET_REPORT:
#ifdef DEBUG0
		usbPrint("Set Report\r\n");
#endif
		break;
	case USB_SET_IDLE:
#ifdef DEBUG0
		usbPrint("Set Idle\r\n");
#endif
		usbSetIdleHandler();
		break;
	case USB_SET_PROTOCOL:
#ifdef DEBUG0
		usbPrint("Set Protocol\r\n");
#endif
		break;
	default:
#ifdef DEBUG0
		usbPrint("Reserved\r\n");
#endif
		break;
	}
}

static void usbSetIdleHandler(void)
{
	usbLEp0In((uint8 *)NULL, 0, TRUE);
}
