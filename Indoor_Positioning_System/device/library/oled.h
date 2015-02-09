#ifndef __OLED_H__
#define __OLED_H__

#include "define.h"

#define OLED_SET_LOWER_COLUMN_START_ADDRESS				0x00
#define OLED_SET_HIGHER_COLUMN_START_ADDRESS			0x10
#define OLED_SET_MEMORY_ADDRESSING_MODE					0x20
#define OLED_SET_COLUMN_ADDRESS							0x21
#define OLED_SET_PAGE_ADDRESS							0x22
#define OLED_SET_DISPLAY_START_LINE						0x40
#define OLED_SET_CONTRAST_CONTROL						0x81
#define OLED_CHARGE_PUMP_SETTING						0x8D
#define OLED_SET_SEGMENT_REMAP							0xA0
#define OLED_ENTIRE_DISPLAY_ON							0xA4
#define OLED_SET_NORMAL_INVERSE_DISPLAY					0xA6
#define OLED_SET_MULTIPLEX_RATIO						0xA8
#define OLED_SET_DISPLAY_ON_OFF							0xAE
#define OLED_SET_PAGE_START_ADDRESS						0xB0
#define OLED_SET_COM_OUTPUT_SCAN_DIRECTION				0xC0
#define OLED_SET_DISPLAY_OFFSET							0xD3
#define OLED_SET_DISPLAY_CLOCK_DIVIDE_RATIO				0xD5
#define OLED_SET_PRECHARGE_PERIOD						0xD9
#define OLED_SET_COM_PINS_HARDWARE_CONFIGURATION		0xDA
#define OLED_SET_VCOMH_DESELECT_LEVEL					0xDB
#define OLED_NOP										0xE3

void oledSetColumnStartAddress(uint8 address);
void oledSetMemoryAddressingMode(uint8 mode);
void oledSetDisplayStartLine(uint8 line);
void oledSetContrastControl(uint8 contrast);
void oledChargePumpSetting(boolean enable);
void oledSetSegmentRemap(boolean remap);
void oledEntireDisplayOn(boolean on);
void oledSetNormalInverseDisplay(boolean inverse);
void oledSetMulitplexRatio(uint8 ratio);
void oledSetDisplayOnOff(boolean on);
void oledSetPageStartAddress(uint8 page);
void oledSetComOutPutScanDirection(boolean remap);
void oledSetDisplayOffset(uint8 offset);
void oledSetDisplayClockDivideRatio(uint8 ratio);
void oledSetPrechargePeriod(uint8 period);
void oledSetComPinsHardwareConfiguration(uint8 config);
void oledSetVcomhDeselectLevel(uint8 level);

void oledInitFromTask(void);
void oledFillPage(uint8 page, uint8 fill);
void oledClearScreen(void);
void oledPrint(uint8 page, uint8 column, char *str);
void oledHex8(uint8 page, uint8 column, uint8 hex8);
void oledHex16(uint8 page, uint8 column, uint16 hex16);
void oledHex32(uint8 page, uint8 column, uint32 hex32);
void oledLongInt(uint8 page, uint8 column, uint32 x);
void oledLoadPicture(uint8 page, uint8 column, uint8 pageSize, uint8 columnSize, uint8 *picture);

#endif
