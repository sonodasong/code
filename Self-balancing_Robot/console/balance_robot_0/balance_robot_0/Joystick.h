#pragma once

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"DxErr.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"comctl32.lib")

#define DIRECTINPUT_VERSION		0x0800

#include <dinput.h>

// Joystick command target

class CJoystick : public CObject
{
public:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	LPDIRECTINPUT8 m_lpDI;
	LPDIRECTINPUTDEVICE8 m_lpDIDevice;
	DIJOYSTATE m_diJs;
	GUID JoystickGUID;
public:
	CJoystick();
	virtual ~CJoystick();
	bool Initialise(void);
	static BOOL CALLBACK DIEnumDevicesCallback (
		const DIDEVICEINSTANCE *lpddi,
		void *pvRef
	);
	static BOOL CALLBACK EnumObjectsCallback (
		const DIDEVICEOBJECTINSTANCE *pdidop,
		void *pContext
	);
	HRESULT PollDevice(void);
};
