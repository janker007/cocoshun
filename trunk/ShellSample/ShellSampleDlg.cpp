// ShellSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShellSample.h"
#include "ShellSampleDlg.h"
#include "Psapi.h"
#include "EnumProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define tpf _tprintf // to hide ugly underbars
// global switches

BOOL bClassName = FALSE;  // show window classname
BOOL bTitle = FALSE;   // show window title
BOOL bBare = FALSE;    // no header

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
// CShellSampleDlg dialog

CShellSampleDlg::CShellSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShellSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShellSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShellSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShellSampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShellSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CShellSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SENDMSG, OnButtonSendmsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellSampleDlg message handlers

BOOL CShellSampleDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShellSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShellSampleDlg::OnPaint() 
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
HCURSOR CShellSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShellSampleDlg::OnButtonSendmsg() 
{
// 	CWnd*pWnd=CWnd::FindWindow(_T("Lingoes ���˹"),NULL);
// 
// 	if(pWnd)
// 		pWnd->ShowWindow(SW_SHOW);
// 	else
// 		MessageBox("û���ҵ�����!");
	// Iterate over all processes
	//
	
	int count = 0;
	
	BOOL bFirstModule = TRUE;
	
	CProcessIterator itp;

	CString strInfo;
	
	//�����е��߳�id���оٳ���һ��module��Ӧ�����еĴ��ڵ�exe���ƺͱ����
	
	for (DWORD pid = itp.First(); pid; pid = itp.Next()) 
	{
		// Note: first module in CProcessModuleIterator is EXE for this process
		
		TCHAR modname[_MAX_PATH];
		
		//�ڹ��캯���д�pidָ����process
		
		CProcessModuleIterator itm(pid);
		
		//�򿪵�ǰ�߳�id��Ӧ�ĵ�һ��module
		
		//������е��̣߳����浽�߳�id���飬���ص�һ���߳�id
		
		HMODULE hModule = itm.First(); // .EXE
		
		if (hModule) // ����NULL
		{
			//��module��basename���浽modname������
			GetModuleBaseName(itm.GetProcessHandle(),
				hModule, modname, _MAX_PATH);
			
			// Iterate over all top-level windows in process
			
			//�оٳ���ǰģ��hModule�����еĶ��㴰��
			
			BOOL bFirstWindow = TRUE;
			
			if(strcmp(modname, "editplus.exe") ==0 )
			{
				
				CMainWindowIterator itw(pid);
				
				for (HWND hwnd = itw.First(); hwnd; hwnd=itw.Next()) 
				{
					char classname[256],title[256];
					
					//�������
					
					GetClassName(hwnd,classname,sizeof(classname));
					
					//��ô��ڵı���
					
					::GetWindowText(hwnd,title,sizeof(title));
					
					hwnd = FindWindowEx(hwnd, NULL , "AfxFrameOrView42su",NULL);

					::SendMessage(hwnd,WM_SETTEXT,0,0x31); 
					

					//MessageBox(title);
					
				} // end of for (HWND hwnd = itw.First(); hwnd; hwnd=itw.Next()) 
				
				//�ܵ�module��Ŀ��1
				
				bFirstWindow || count++;
			}
		}
	}


}
