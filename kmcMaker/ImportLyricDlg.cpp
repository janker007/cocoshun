// ImportLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "ImportLyricDlg.h"
#include <sys/types.h>
#include <sys/stat.h>  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  MAX_LYRIC_LEN 1024*10 //���ƴ�С10K

/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg dialog


CImportLyricDlg::CImportLyricDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CImportLyricDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportLyricDlg)
	m_EditReplaceTxt = _T("");
	m_EditTargetTxt = _T("");
	//}}AFX_DATA_INIT
}


void CImportLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportLyricDlg)
	DDX_Control(pDX, IDC_BTN_IMPORT, m_BtnImport);
	DDX_Control(pDX, IDC_LYRIC_EDITOR, m_LyricEditor);
	DDX_Text(pDX, IDC_EDIT_REPLACE_TXT, m_EditReplaceTxt);
	DDX_Text(pDX, IDC_EDIT_TARGET_TXT, m_EditTargetTxt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CImportLyricDlg)
	ON_BN_CLICKED(IDC_BTN_IMPORT, OnImportLyric)
	ON_BN_CLICKED(IDC_CHECK_DEL_XML_HTML, OnCheckDelXmlHtml)
	ON_BN_CLICKED(IDC_CHECK_DEL_LRC, OnCheckDelLrc)
	ON_BN_CLICKED(IDC_CHECK_DEL_KSC, OnCheckDelKsc)
	ON_BN_CLICKED(IDC_CHECK_DEL_SPACE, OnCheckDelSpace)
	ON_BN_CLICKED(IDC_CHECK_REPLACE, OnCheckReplace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg message handlers

void CImportLyricDlg::OnCancel() 
{
//	CResizingDialog::OnCancel();
}

BOOL CImportLyricDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	//set Controls
	SetControlInfo(IDC_LYRIC_EDITOR,RESIZE_BOTH);

	SetControlInfo(IDC_STATIC_TIP,ANCHORE_RIGHT |ANCHORE_TOP );

	SetControlInfo(IDC_STATIC_HELP,ANCHORE_RIGHT );
	SetControlInfo(IDC_STATIC_FILTER_OPTION,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_XML_HTML,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_LRC,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_KSC,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_SPACE,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_REPLACE,ANCHORE_RIGHT );
	SetControlInfo(IDC_EDIT_REPLACE_TXT,ANCHORE_RIGHT );
	SetControlInfo(IDC_STATIC_FOR,ANCHORE_RIGHT );
	SetControlInfo(IDC_EDIT_TARGET_TXT,ANCHORE_RIGHT );
	SetControlInfo(IDC_BTN_FILTER,ANCHORE_RIGHT );

	SetControlInfo(IDC_BTN_IMPORT,ANCHORE_RIGHT );
	SetControlInfo(IDC_BTN_NEXTSTEP,ANCHORE_RIGHT );
	
	m_LyricEditor.SetFocus();
	LoadLyric(_T(".\\Test\\ʮ��.txt"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CImportLyricDlg::OnImportLyric() 
{
 	TCHAR szFilter[] = _T("Lyric (*.lrc)|*.lrc|Lyric (*.txt)|*.txt|All Files (*.*)|*.*||");
 	CFileDialogEx ImportFileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);;
 	if( ImportFileDlg.DoModal() == IDOK)
	{
		LoadLyric(ImportFileDlg.GetFileName());
	}
}

void CImportLyricDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CResizingDialog::OnOK();
}

LRESULT CImportLyricDlg::OnAcceptDropFile(WPARAM wParam , LPARAM lParam  )
{
	TCHAR *DropFileName = (TCHAR *)wParam;

	LoadLyric(DropFileName);
	return 1L;
}


BOOL CImportLyricDlg::LoadLyric(LPCTSTR pszFileName)
{
	int Len = GetFileLenght(pszFileName);

	if(Len > MAX_LYRIC_LEN)
	{
		int ret = MessageBox(_T("�򿪵��ļ�����10K�����ܲ�����ȷ�ĸ���ı���ʽ��ȷ�������򿪣�"),
			_T("��ʾ"),MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION);

		if( ret == IDNO)
			return FALSE;
	}
	
	if(!m_LyricText.LoadLyric(pszFileName))
	{
		return FALSE;
	}

	m_LyricEditor.SetWindowText(m_LyricText.GetText());
	m_LyricEditor.GetWindowText(m_OrgText);

	return TRUE;
}

int CImportLyricDlg::GetFileLenght( LPCTSTR pszFileName )
{
	struct stat buf;
	if(stat(pszFileName, &buf)<0)
	{
		return 0;
	}
	return (unsigned long)buf.st_size;
}

void CImportLyricDlg::OnCheckDelXmlHtml() 
{
	
}

void CImportLyricDlg::OnCheckDelLrc() 
{
	if(GetCheck(IDC_CHECK_DEL_LRC))
	{
		m_LyricText.SplitLRC();
		m_LyricEditor.SetWindowText(m_LyricText.GetText());
	}else
	{
		m_LyricEditor.SetWindowText(m_OrgText);
	}
}

void CImportLyricDlg::OnCheckDelKsc() 
{
	
}

void CImportLyricDlg::OnCheckDelSpace() 
{
	
}

void CImportLyricDlg::OnCheckReplace() 
{
	
}

BOOL CImportLyricDlg::GetCheck( UINT ID )
{
	return ((CButton *)GetDlgItem(ID))->GetCheck();
}