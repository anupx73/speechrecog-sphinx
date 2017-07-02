// VRecog_w32.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CVRecog_w32App:
// See VRecog_w32.cpp for the implementation of this class
//

class CVRecog_w32App : public CWinApp
{
public:
	CVRecog_w32App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVRecog_w32App theApp;