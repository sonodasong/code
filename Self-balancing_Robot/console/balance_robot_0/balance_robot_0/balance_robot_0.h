
// balance_robot_0.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cbalance_robot_0App:
// See balance_robot_0.cpp for the implementation of this class
//

class Cbalance_robot_0App : public CWinApp
{
public:
	Cbalance_robot_0App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cbalance_robot_0App theApp;