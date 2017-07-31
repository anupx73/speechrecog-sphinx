// VRecog_CEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VRecog_CE.h"
#include "VRecog_CEDlg.h"
#include "PocketSP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVRecog_CEDlg *cDlg;

CVRecog_CEDlg::CVRecog_CEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVRecog_CEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVRecog_CEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
}

BEGIN_MESSAGE_MAP(CVRecog_CEDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CVRecog_CEDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CVRecog_CEDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CVRecog_CEDlg message handlers

BOOL CVRecog_CEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	cDlg = this;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CVRecog_CEDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_VRECOG_CE_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_VRECOG_CE_DIALOG));
	}
}
#endif

void CVRecog_CEDlg::SetOutput(LPWSTR szStr)
{
	m_Edit1.SetWindowText(szStr);
}

void CVRecog_CEDlg::OnBnClickedButton1()
{
	ActivateRecognizer();	
}

void CVRecog_CEDlg::OnBnClickedButton2()
{
	DeactivateRecognizer();
}
