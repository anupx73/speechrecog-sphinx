// VRecog_CE.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VRecog_CE.h"
#include "VRecog_CEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVRecog_CEApp

BEGIN_MESSAGE_MAP(CVRecog_CEApp, CWinApp)
END_MESSAGE_MAP()


// CVRecog_CEApp construction
CVRecog_CEApp::CVRecog_CEApp()
	: CWinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CVRecog_CEApp object
CVRecog_CEApp theApp;

// CVRecog_CEApp initialization

BOOL CVRecog_CEApp::InitInstance()
{
	CVRecog_CEDlg dlg;

	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}
