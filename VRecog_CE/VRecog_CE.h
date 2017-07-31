// VRecog_CE.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CVRecog_CEApp:
// See VRecog_CE.cpp for the implementation of this class
//

class CVRecog_CEApp : public CWinApp
{
public:
	CVRecog_CEApp();
	
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVRecog_CEApp theApp;
