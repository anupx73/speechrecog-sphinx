// VRecog_w32Dlg.h : header file
//

#pragma once
#include "afxwin.h"



class CVRecog_w32Dlg : public CDialog
{
// Construction
public:
	CVRecog_w32Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VRECOG_W32_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit1;
	void SetOutput(LPCSTR);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};

extern CVRecog_w32Dlg *cDlg;