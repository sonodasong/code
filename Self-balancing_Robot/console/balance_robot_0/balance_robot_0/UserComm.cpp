// UserComm.cpp : implementation file
//

#include "stdafx.h"
#include "balance_robot_0.h"
#include "UserComm.h"


// CUserComm

CUserComm::CUserComm()
{
}

CUserComm::~CUserComm()
{
}


// CUserComm member functions

void CUserComm::initialize(CMscomm1 *pComm)
{
	m_pComm = pComm;
}

void CUserComm::connect(int port)
{
	if (m_pComm->get_PortOpen()) {
		m_pComm->put_PortOpen(false);
	}
	m_pComm->put_CommPort(port);
	m_pComm->put_InBufferSize(1024);
	m_pComm->put_OutBufferSize(512);
	m_pComm->put_InputLen(0);
	m_pComm->put_InputMode(1);
	m_pComm->put_RThreshold(24);
	m_pComm->put_SThreshold(0);
	m_pComm->put_Settings(_T("38400, n, 8, 1"));
	m_pComm->put_PortOpen(true);
}

void CUserComm::disconnect(void)
{
	if (m_pComm->get_PortOpen()) {
		m_pComm->put_PortOpen(false);
	}
}

void CUserComm::rx(int *x)
{
	VARIANT v;
	COleSafeArray s;
	byte rx[24];
	int temp;

	v = m_pComm->get_Input();
	s = v;
	for (long i = 0; i < 24; i++) {
		s.GetElement(&i, &rx[i]);
	}
	for (int i = 0; i < 6; i++) {
		temp = rx[i * 4 + 3] & 0xFF;
		temp = temp << 8;
		temp |= rx[i * 4 + 2] & 0xFF;
		temp = temp << 8;
		temp |= rx[i * 4 + 1] & 0xFF;
		temp = temp << 8;
		temp |= rx[i * 4] & 0xFF;
		x[i] = temp;
	}
}

void CUserComm::tx(char cmd, int data)
{
	CByteArray buf;

	buf.RemoveAll();
	buf.SetSize(10);
	for (int i = 0; i < 8; i++) {
		buf.SetAt(i, (byte)((data >> (28 - i * 4)) & 0x0F) + 32);
	}
	buf.SetAt(8, cmd);
	buf.SetAt(9, '\r');
	m_pComm->put_Output(COleVariant(buf));
}
