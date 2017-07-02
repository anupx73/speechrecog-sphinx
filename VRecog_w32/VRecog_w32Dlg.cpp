// VRecog_w32Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "VRecog_w32.h"
#include "VRecog_w32Dlg.h"
#include "PocketSP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CVRecog_w32Dlg *cDlg;


CVRecog_w32Dlg::CVRecog_w32Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVRecog_w32Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVRecog_w32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
}

BEGIN_MESSAGE_MAP(CVRecog_w32Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CVRecog_w32Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CVRecog_w32Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CVRecog_w32Dlg message handlers

BOOL CVRecog_w32Dlg::OnInitDialog()
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVRecog_w32Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVRecog_w32Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVRecog_w32Dlg::SetOutput(LPCSTR szStr)
{
	m_Edit1.SetWindowText(szStr);
}

void CVRecog_w32Dlg::OnBnClickedButton1()
{
	ActivateRecognizer();
}

void CVRecog_w32Dlg::OnBnClickedButton2()
{
	DeactivateRecognizer();
}