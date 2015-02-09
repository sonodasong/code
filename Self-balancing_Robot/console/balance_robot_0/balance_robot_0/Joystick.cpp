// Joystick.cpp : implementation file
//

#include "stdafx.h"
#include "balance_robot_0.h"
#include "Joystick.h"


// Joystick

CJoystick::CJoystick()
{
	m_lpDIDevice = NULL;
	m_lpDI = NULL;
	m_hWnd = NULL;
	m_hInstance = GetModuleHandle(NULL);
}

CJoystick::~CJoystick()
{
	if (m_lpDIDevice) {
		m_lpDIDevice->Unacquire();
	}
	if (m_lpDIDevice) {
		m_lpDIDevice->Release();
		m_lpDIDevice = NULL;
	}
	if (m_lpDI) {
		m_lpDI->Release();
		m_lpDI = NULL;
	}
}


// Joystick member functions

bool CJoystick::Initialise(void)
{
	HRESULT hr;

	if (m_lpDI == NULL) {
		hr = DirectInput8Create (
			m_hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void **)&m_lpDI,
			NULL
		);
		if FAILED(hr) {
			return false;
		}
	}
	hr = m_lpDI->EnumDevices (
		DI8DEVCLASS_GAMECTRL,
		DIEnumDevicesCallback,
		&JoystickGUID,
		DIEDFL_ATTACHEDONLY
	);
	if FAILED(hr) {
		return false;
	}
	if (!m_lpDIDevice) {
		hr = m_lpDI->CreateDevice(JoystickGUID, &m_lpDIDevice, NULL);
		if FAILED(hr) {
			return false;
		}
	}
	hr = m_lpDIDevice->SetCooperativeLevel (
		m_hWnd,
		DISCL_FOREGROUND | DISCL_EXCLUSIVE
	);
	if FAILED(hr) {
		return false;
	}
	hr = m_lpDIDevice->SetDataFormat(&c_dfDIJoystick);
	if FAILED(hr) {
		return false;
	}
	hr = m_lpDIDevice->EnumObjects (
		EnumObjectsCallback,
		(void *)this,
		DIDFT_ALL
	);
	if FAILED(hr) {
		return false;
	}
	return true;
}

BOOL CJoystick::DIEnumDevicesCallback(const DIDEVICEINSTANCE *lpddi, void *pvRef)
{
	*(GUID *)pvRef = lpddi->guidInstance;
	return DIENUM_STOP;
}

BOOL CJoystick::EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, void *pContext)
{
	HRESULT hr;
	CJoystick *js = (CJoystick *)pContext;

	if (pdidoi->dwType & DIDFT_AXIS) {
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pdidoi->dwType;
		diprg.lMin = -1024;
		diprg.lMax = 1024;
		hr = js->m_lpDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		if FAILED(hr) {
			return DIENUM_STOP;
		}
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = pdidoi->dwType;//////
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = 1000;
		hr = js->m_lpDIDevice->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		if FAILED(hr) {
			return DIENUM_STOP;
		}
	}
	return DIENUM_CONTINUE;
}

HRESULT CJoystick::PollDevice(void)
{
	HRESULT hr;

	if (m_lpDIDevice == NULL) {
		return S_OK;
	}
	hr = m_lpDIDevice->Poll();
	if FAILED(hr) {
		hr = m_lpDIDevice->Acquire();
		while (hr == DIERR_INPUTLOST) {
			static int iCount = 0;
			if (iCount > 30) {
				exit(-1);
			}
			iCount++;
			hr = m_lpDIDevice->Acquire();
			if (SUCCEEDED(hr)) {
				iCount = 0;
			}
		}
		return S_OK;
	}
	hr = m_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &m_diJs);
	if FAILED(hr) {
		return hr;
	}
	return S_OK;
}
