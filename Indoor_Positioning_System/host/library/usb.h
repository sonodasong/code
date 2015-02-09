#ifndef __USB_H__
#define __USB_H__

#include "define.h"

//#define DEBUG0
//#define DEBUG1

#define USB_LOGICAL_ENDPOINT0_SIZE				0x40
#define USB_LOGICAL_ENDPOINT1_SIZE				0x10

#define USB_SIE_SET_ADDRESS						0xD0
#define USB_SIE_CONFIGURE_DEVICE				0xD8
#define USB_SIE_SET_MODE						0xF3
#define USB_SIE_READ_CURRENT_FRAME_NUMBER		0xF5
#define USB_SIE_READ_TEST_REGISTER				0xFD
#define USB_SIE_SET_DEVICE_STATUS				0xFE
#define USB_SIE_GET_DEVICE_STATUS				0xFE
#define USB_SIE_GET_ERROR_CODE					0xFF
#define USB_SIE_READ_ERROR_STATUS				0xFB
#define USB_SIE_SELECT_ENDPOINT					0x00
#define USB_SIE_CLEAR_INTERRUPT					0x40
#define USB_SIE_SET_ENDPOINT_STATUS				0x40
#define USB_SIE_CLEAR_BUFFER					0xF2
#define USB_SIE_VALIDATE_BUFFER					0xFA

void usbInit(void);

void usbSIESetAddress(uint8 address);
void usbSIEConfigureDevice(uint8 byte);
void usbSIESetMode(uint8 byte);
uint16 usbSIEReadTestRegister(void);
void usbSIESetDeviceStatus(uint8 byte);
uint8 usbSIEGetDeviceStatus(void);
uint8 usbSIEGetErrorCode(void);
uint8 usbSIEReadErrorStatus(void);
uint8 usbSIESelectEndpoint(uint8 pEp);
uint8 usbSIEClearInterrupt(uint8 pEp);
void usbSIESetEndpointStatus(uint8 pEp, uint8 byte);
uint8 usbSIEClearBuffer(void);
void usbSIEValidateBuffer(void);

void usbConnect(void);
void usbDisconnect(void);
void usbPEpRealization(uint8 pEp, uint8 maxPacketSize);
void usbPEpEnable(uint8 pEp);
uint16 usbLEpBufR(uint8 lEp, uint8 *buf, uint16 size);
uint16 usbLEpBufW(uint8 lEp, uint8 *buf, uint16 size);
void usbLEp0In(uint8 *buf, uint16 size, boolean considerZeroPacket);
void usbLEp0InApd(void);

void usbPrint(char *str);
void usbHex8(uint8 hex8);
void usbHex16(uint16 hex16);
void usbHex32(uint32 hex32);
void usbLongInt(uint32 x);

#endif
