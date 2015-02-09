#pragma once

#include "mscomm1.h"

// CUserComm command target

class CUserComm : public CObject
{
public:
	CUserComm();
	virtual ~CUserComm();
private:
	CMscomm1 *m_pComm;
public:
	void initialize(CMscomm1 *pComm);
	void connect(int port);
	void disconnect(void);
	void rx(int *x);
	void tx(char cmd, int data);
};


