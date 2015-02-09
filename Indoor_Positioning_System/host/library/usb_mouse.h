#ifndef __USB_MOUSE_H__
#define __USB_MOUSE_H__

#include "define.h"

typedef struct {
	uint8 bmRequestType;
	uint8 bRequest;
	uint8 wValueL;
	uint8 wValueH;
	uint8 wIndexL;
	uint8 wIndexH;
	uint8 wLengthL;
	uint8 wLengthH;
} tUSBDeviceRequest;

typedef struct {
	uint8 bLength;
	uint8 bDescriptorType;
	uint8 bcdUSBL;
	uint8 bcdUSBH;
	uint8 bDeviceClass;
	uint8 bDeviceSubClass;
	uint8 bDeviceProtocol;
	uint8 bMaxPacketSize0;
	uint8 idVendorL;
	uint8 idVendorH;
	uint8 idProductL;
	uint8 idProductH;
	uint8 bcdDeviceL;
	uint8 bcdDeviceH;
	uint8 iManufacturer;
	uint8 iProduct;
	uint8 iSerialNumber;
	uint8 bNumConfigurations;
} tUSBDeviceDescriptor;

typedef struct {
	uint8 bLength;
	uint8 bDescriptorType;
	uint8 wTotalLengthL;
	uint8 wTotalLengthH;
	uint8 bNumInterfaces;
	uint8 bConfigurationValue;
	uint8 iConfiguration;
	uint8 bmAttributes;
	uint8 bMaxPower;
} tUSBConfigurationDescriptor;

typedef struct {
	uint8 bLength;
	uint8 bDescriptorType;
	uint8 bInterfaceNumber;
	uint8 bAlternateSetting;
	uint8 bNumEndpoints;
	uint8 bInterfaceClass;
	uint8 bInterfaceSubClass;
	uint8 bInterfaceProtocol;
	uint8 iInterface;
} tUSBInterfaceDescriptor;

typedef struct {
	uint8 bLength;
	uint8 bDescriptorType;
	uint8 bEndpointAddress;
	uint8 bmAttributes;
	uint8 wMaxPacketSizeL;
	uint8 wMaxPacketSizeH;
	uint8 bInterval;
} tUSBEndpointDescriptor;

typedef struct {
	uint8 bLength;
	uint8 bDescriptorType;
	uint8 bcdHIDL;
	uint8 bcdHIDH;
	uint8 bCountryCode;
	uint8 bNumDescriptors;
	uint8 bDescriptor1Type;
	uint8 wDescriptor1LengthL;
	uint8 wDescriptor1LengthH;
} tUSBHIDDescriptor;

#define USB_STANDARD									0x00
#define USB_CLASS										0x01
#define USB_VENDOR										0x02

#define USB_GET_STATUS									0x00
#define USB_CLEAR_FEATURE								0x01
#define USB_SET_FEATURE									0x03
#define USB_SET_ADDRESS									0x05
#define USB_GET_DESCRIPTOR								0x06
#define USB_SET_DESCRIPTOR								0x07
#define USB_GET_CONFIGURATION							0x08
#define USB_SET_CONFIGURATION							0x09
#define USB_GET_INTERFACE								0x0A
#define USB_SET_INTERFACE								0x0B
#define USB_SYNCH_FRAME									0x0C

#define USB_DEVICE_DESCRIPTOR							0x01
#define USB_CONFIGURATION_DESCRIPTOR					0x02
#define USB_STRING_DESCRIPTOR							0x03
#define USB_INTERFACE_DESCRIPTOR						0x04
#define USB_ENDPOINT_DESCRIPTOR							0x05
#define USB_DEVICE_QUALIFIER_DESCRIPTOR					0x06
#define USB_OTHER_SPEED_CONFIGURATIOLN_DESCRIPTOR		0x07
#define USB_INTERFACE_POWER_DESCRIPTOR					0x08
#define USB_HID_DESCRIPTOR								0x21
#define USB_REPORT_DESCRIPTOR							0x22
#define USB_PHYSICAL_DESCRIPTOR							0x23

#define USB_GET_REPORT									0x01
#define USB_GET_IDLE									0x02
#define USB_GET_PROTOCOL								0x03
#define USB_SET_REPORT									0x09
#define USB_SET_IDLE									0x0A
#define USB_SET_PROTOCOL								0x0B

#define USB_STRING_INDEX_1								0x01
#define USB_STRING_INDEX_2								0x02
#define USB_STRING_INDEX_3								0x03

void usbMouseInit(void);
void usbMouseConnect(void);
void usbMouseDisconnect(void);
INT8U usbMouseInput(uint8 *buf, INT32U timeout);

void usbLEp0OutHandler(void);
void usbLEp0InHandler(void);
void usbLEp1OutHandler(void);
void usbLEp1InHandler(void);

#endif
