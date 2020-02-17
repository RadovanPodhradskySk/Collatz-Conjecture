
// CollatzConjectureMfcApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <sstream>

// CCollatzConjectureMfcApp:
// See CollatzConjectureMfcApp.cpp for the implementation of this class
//

#define WMU_SEQUENCEFINISH	(WM_USER + 1)

class CCollatzConjectureMfcApp : public CWinApp
{
public:
	CCollatzConjectureMfcApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCollatzConjectureMfcApp theApp;