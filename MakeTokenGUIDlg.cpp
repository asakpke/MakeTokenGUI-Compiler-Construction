// MakeTokenGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MakeTokenGUI.h"
#include "MakeTokenGUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeTokenGUIDlg dialog

CMakeTokenGUIDlg::CMakeTokenGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeTokenGUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakeTokenGUIDlg)
	m_sTXT_FILE_NAME = _T("MyCPP.txt");
	m_sTXT_NEXT_TOKEN = _T("");
	m_sTXT_NEXT_CHAR = _T("");
	m_sTXT_TOKEN_TYPE = _T("");
	m_sTXT_MAIN_TOKEN = _T("");
	m_nTXT_SKIP_TOKENS = 10;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMakeTokenGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakeTokenGUIDlg)
	DDX_Text(pDX, IDC_TXT_FILE_NAME, m_sTXT_FILE_NAME);
	DDX_Text(pDX, IDC_TXT_NEXT_TOKEN, m_sTXT_NEXT_TOKEN);
	DDX_Text(pDX, IDC_TXT_NEXT_CHAR, m_sTXT_NEXT_CHAR);
	DDX_Text(pDX, IDC_TXT_TOKEN_TYPE, m_sTXT_TOKEN_TYPE);
	DDX_Text(pDX, IDC_TXT_MAIN_TOKEN, m_sTXT_MAIN_TOKEN);
	DDX_Text(pDX, IDC_TXT_SKIP_TOKENS, m_nTXT_SKIP_TOKENS);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMakeTokenGUIDlg, CDialog)
	//{{AFX_MSG_MAP(CMakeTokenGUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN_FILE, OnBtnOpenFile)
	ON_BN_CLICKED(IDC_BTN_GET_NEXT_CHAR, OnBtnGetNextChar)
	ON_BN_CLICKED(IDC_BTN_CLOSE_FILE, OnBtnCloseFile)
	ON_BN_CLICKED(IDC_BTN_GET_NEXT_TOKEN, OnBtnGetNextToken)
	ON_BN_CLICKED(IDC_BTN_SKIP_TOKENS, OnBtnSkipTokens)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeTokenGUIDlg message handlers

BOOL CMakeTokenGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here			
	//m_cNextChar = 'x';
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*
	///////////////////
	// start	temp //
	///////////////////
	CStringList m_slReserveWords;

	m_slReserveWords.AddTail("asm");
	m_slReserveWords.AddTail("auto");
	m_slReserveWords.AddTail("bad_cast");
	m_slReserveWords.AddTail("bad_typeid");
	m_slReserveWords.AddTail("bool");
	m_slReserveWords.AddTail("break");
	m_slReserveWords.AddTail("case");
	m_slReserveWords.AddTail("catch");

	int siz = m_slReserveWords.GetCount();

	POSITION pos = m_slReserveWords.Find("if");		

	if(pos == NULL)
		MessageBox("not found");		
	else
	{
		CString str;
		int fnd = int(pos);
		pos = m_slReserveWords.GetHeadPosition();
		int hd = int(pos);
		int ind = -((hd - fnd)/12);
		str.Format("Found at %d, size = %d",ind, siz);
		MessageBox(str);
	}
	///////////////////
	// ended	temp //
	///////////////////
*/

void CMakeTokenGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMakeTokenGUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMakeTokenGUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMakeTokenGUIDlg::OnBtnOpenFile() 
{
	// TODO: Add your control notification handler code here

	UpdateData();

	//m_fp = fopen(m_sTXT_FILE_NAME, "r");
	bool bIsFileOpen;
	bIsFileOpen = m_tknSourceFile.OpenSourceFile(m_sTXT_FILE_NAME);
	//if(bIsFileOpen == false)


	//if(m_fp == NULL)
		//m_fp = fopen("..\\" + m_sTXT_FILE_NAME, "r");

	if(bIsFileOpen == false)
		MessageBox("ERROR: Cannot open input file.");
	else
	{
		CButton *btn;

		btn = (CButton*) GetDlgItem(IDC_BTN_OPEN_FILE);
		btn->EnableWindow(FALSE);
		
		btn = (CButton*) GetDlgItem(IDC_BTN_GET_NEXT_CHAR);
		btn->EnableWindow();

		btn = (CButton*) GetDlgItem(IDC_BTN_GET_NEXT_TOKEN);
		btn->EnableWindow();		
		
		btn = (CButton*) GetDlgItem(IDC_BTN_CLOSE_FILE);
		btn->EnableWindow();

		btn = (CButton*) GetDlgItem(IDC_BTN_SKIP_TOKENS);									
		btn->EnableWindow();

		//m_cNextChar = 'x';
		m_tknSourceFile.GetNextChar();
		//GetNextChar();

		CString sCmdLine;
		sCmdLine = "Notepad " + m_sTXT_FILE_NAME;
		WinExec(sCmdLine, SW_SHOW);
	} // else of if(bIsFileOpen == false)
}

/*
char CMakeTokenGUIDlg::GetNextChar()
{
	if(m_cNextChar != EOF)	
		m_cNextChar = fgetc(m_fp);
	else
		MessageBox("EOF");

	return m_cNextChar;
}
*/

void CMakeTokenGUIDlg::OnBtnGetNextChar() 
{
	// TODO: Add your control notification handler code here
	//CString sChar;
	//char ch;
	
	//ch = GetNextChar();
	//sChar.Format("%c",m_cNextChar);
	//char ch = m_tknSourceFile.GetCurrentChar();
	//m_sTXT_NEXT_CHAR.Format("%d, %c", ch, ch);
	m_sTXT_NEXT_CHAR = m_tknSourceFile.GetCurrentChar();
	//m_sTXT_NEXT_CHAR.Format("%c",m_cNextChar);
	UpdateData(FALSE);
	m_tknSourceFile.GetNextChar();
	//UpdateData(FALSE);

	//m_cNextChar = m_tknSourceFile.GetNextChar();

	//MessageBox(sChar);
}

void CMakeTokenGUIDlg::OnBtnCloseFile() 
{
	// TODO: Add your control notification handler code here
	m_tknSourceFile.CloseSourceFile();

	CButton *btn;

	btn = (CButton*) GetDlgItem(IDC_BTN_OPEN_FILE);
	btn->EnableWindow();
	
	btn = (CButton*) GetDlgItem(IDC_BTN_GET_NEXT_CHAR);
	btn->EnableWindow(FALSE);

	btn = (CButton*) GetDlgItem(IDC_BTN_GET_NEXT_TOKEN);
	btn->EnableWindow(FALSE);		
	
	btn = (CButton*) GetDlgItem(IDC_BTN_CLOSE_FILE);
	btn->EnableWindow(FALSE);

	btn = (CButton*) GetDlgItem(IDC_BTN_SKIP_TOKENS);
	btn->EnableWindow(FALSE);
}

void CMakeTokenGUIDlg::OnBtnGetNextToken() 
{
	// TODO: Add your control notification handler code here
	//m_sNextToken = m_tknSourceFile.GetNextToken();

	ETokenType tt;
	tt = m_tknSourceFile.GetNextToken(&m_sTXT_NEXT_TOKEN, &m_sTXT_TOKEN_TYPE);
	m_sTXT_MAIN_TOKEN = m_tknSourceFile.GetMainToken();

	UpdateData(FALSE);

	//CString str;
	//str.Format("tt = %d",tt);	
	//MessageBox(str);
}

/*
void CMakeTokenGUIDlg::GetNextToken()
{	
	int nsLen;

	m_eNextTokenType = tt_Null;
	m_sNextTokenType = "Null";

	m_sNextToken.Empty();

	if(m_cNextChar == EOF)
	{
		MessageBox("EOF");
		return;// m_sNextToken;
	}

	while(m_cNextChar != EOF)
	{
		while(m_cNextChar == ' ')
		{
			GetNextChar();
			if(m_cNextChar == EOF)
				MessageBox("EOF");
		}

		if(m_cNextChar >= '0' && m_cNextChar <= '9')
		{			
			while(m_cNextChar >= '0' && m_cNextChar <= '9')
			{
				nsLen = m_sNextToken.GetLength();
				m_sNextToken.Insert(nsLen, m_cNextChar);
				GetNextChar();
			}
			m_eNextTokenType = ttNumber;
			m_sNextTokenType = "Number";
			return;// m_sNextToken;
		} 
		else if(m_cNextChar >= 'A' && m_cNextChar <= 'Z'
			 || m_cNextChar >= 'a' && m_cNextChar <= 'z'
			 || m_cNextChar == '_')
		{			
			while(m_cNextChar >= 'A' && m_cNextChar <= 'Z'
			   || m_cNextChar >= 'a' && m_cNextChar <= 'z'
			   || m_cNextChar == '_')
			{
				nsLen = m_sNextToken.GetLength();
				m_sNextToken.Insert(nsLen, m_cNextChar);
				GetNextChar();
			}
			m_eNextTokenType = ttString;
			m_sNextTokenType = "String";

			return;// m_sNextToken;
		} // else if(m_cNextChar >= 'A' && m_cNextChar <= 'Z'

		GetNextChar();				
	} // while(ch != EOF)
	//if(m_cNextChar == EOF)
		//MessageBox("EOF");

	return;// m_sNextToken;
} // CMakeTokenGUIDlg::GetNextToken()
*/

/*
		switch(m_cNextChar)
		{
		case 9://tab
			//tokenCounter--;
			break;

		case ' ':
		case EOF:
		case 10://end of line									
			//m_sNextToken = sNextToken;
			return m_sNextToken;
			break;
		}

		nsLen = m_sNextToken.GetLength();
		m_sNextToken.Insert(nsLen, m_cNextChar);
		GetNextChar();
*/

void CMakeTokenGUIDlg::OnBtnSkipTokens() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	for(UINT v=0; v < m_nTXT_SKIP_TOKENS-1; v++) 
		// -1 so that only read data in str for last rec
		m_tknSourceFile.GetNextToken();

	ETokenType tt;
	tt = m_tknSourceFile.GetNextToken(&m_sTXT_NEXT_TOKEN, &m_sTXT_TOKEN_TYPE);
	m_sTXT_MAIN_TOKEN = m_tknSourceFile.GetMainToken();

	UpdateData(FALSE);
}
