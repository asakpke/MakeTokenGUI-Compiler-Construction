// MakeTokenGUIDlg.h : header file
//

#if !defined(AFX_MAKETOKENGUIDLG_H__54F86F5C_D0E2_4C54_A800_F46548078141__INCLUDED_)
#define AFX_MAKETOKENGUIDLG_H__54F86F5C_D0E2_4C54_A800_F46548078141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHeader.h"
#include "Token.h"

/////////////////////////////////////////////////////////////////////////////
// CMakeTokenGUIDlg dialog

class CMakeTokenGUIDlg : public CDialog
{
// Construction
public:
	//void GetNextToken();
	//char GetNextChar();
	CMakeTokenGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMakeTokenGUIDlg)
	enum { IDD = IDD_MAKETOKENGUI_DIALOG };
	CString	m_sTXT_FILE_NAME;
	CString	m_sTXT_NEXT_TOKEN;
	CString	m_sTXT_NEXT_CHAR;
	CString	m_sTXT_TOKEN_TYPE;
	CString	m_sTXT_MAIN_TOKEN;
	UINT	m_nTXT_SKIP_TOKENS;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakeTokenGUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMakeTokenGUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpenFile();
	afx_msg void OnBtnGetNextChar();
	afx_msg void OnBtnCloseFile();
	afx_msg void OnBtnGetNextToken();
	afx_msg void OnBtnSkipTokens();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToken m_tknSourceFile; // SF = source file
	//CString m_sNextTokenType;
	//CString m_sNextToken;
	//char m_cNextChar;
	//FILE *m_fp;
	ETokenType m_eNextTokenType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKETOKENGUIDLG_H__54F86F5C_D0E2_4C54_A800_F46548078141__INCLUDED_)
