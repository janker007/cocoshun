// ImportLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "ImportLyricDlg.h"
#include <sys/types.h>
#include <sys/stat.h>  
#include "KmcMakerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  MAX_LYRIC_LEN 1024*10 //限制大小10K

/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg dialog


CImportLyricDlg::CImportLyricDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CImportLyricDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportLyricDlg)
	m_EditReplaceTxt = _T("");
	m_EditTargetTxt = _T("");
	m_EditFontsize = _T("");
	//}}AFX_DATA_INIT
}


void CImportLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportLyricDlg)
	DDX_Control(pDX, IDC_SLIDER_FONTSIZE, m_SliderFontsize);
	DDX_Control(pDX, IDC_BTN_NEXTSTEP, m_BtnNextStep);
	DDX_Control(pDX, IDC_BTN_FILTER, m_BtnFilter);
	DDX_Control(pDX, IDC_BTN_IMPORT, m_BtnImport);
	DDX_Control(pDX, IDC_LYRIC_EDITOR, m_LyricEditor);
	DDX_Text(pDX, IDC_EDIT_REPLACE_TXT, m_EditReplaceTxt);
	DDX_Text(pDX, IDC_EDIT_TARGET_TXT, m_EditTargetTxt);
	DDX_Text(pDX, IDC_EDIT_FONTSIZE, m_EditFontsize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CImportLyricDlg)
	ON_BN_CLICKED(IDC_BTN_IMPORT, OnImportLyric)
	ON_BN_CLICKED(IDC_BTN_FILTER, OnBtnFilter)
	ON_BN_CLICKED(IDC_BTN_NEXTSTEP, OnBtnNextstep)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_FONTSIZE, OnChangeEditFontsize)
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

	short	shBtnColor = 30;
	m_BtnImport.SetIcon(IDI_FOLDER);
	m_BtnFilter.SetIcon(IDI_ACCEPT);
	m_BtnNextStep.SetIcon(IDI_NEXT);
	
	//set Controls
	SetControlInfo(IDC_LYRIC_EDITOR,RESIZE_BOTH);
	SetControlInfo(IDC_STATIC_TIP,ANCHORE_RIGHT  );
	SetControlInfo(IDC_STATIC_HELP,ANCHORE_RIGHT );
	SetControlInfo(IDC_STATIC_FILTER_OPTION,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_XML_HTML,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_LRC,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_KSC,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_SPACE,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_REPLACE,ANCHORE_RIGHT );
	SetControlInfo(IDC_EDIT_REPLACE_TXT,ANCHORE_RIGHT );
	SetControlInfo(IDC_CHECK_DEL_EMPTYLINE,ANCHORE_RIGHT );
	SetControlInfo(IDC_STATIC_FOR,ANCHORE_RIGHT );
	SetControlInfo(IDC_EDIT_TARGET_TXT,ANCHORE_RIGHT );
	SetControlInfo(IDC_BTN_FILTER,ANCHORE_RIGHT );
	SetControlInfo(IDC_STATIC_FIND,ANCHORE_RIGHT );

	SetControlInfo(IDC_BTN_IMPORT,ANCHORE_RIGHT );

	SetControlInfo(IDC_STATIC_FONTSIZE,ANCHORE_RIGHT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_SLIDER_FONTSIZE,ANCHORE_RIGHT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_EDIT_FONTSIZE,ANCHORE_RIGHT | ANCHORE_BOTTOM);
	
	SetControlInfo(IDC_BTN_NEXTSTEP,ANCHORE_RIGHT | ANCHORE_BOTTOM );

	SetCheck(IDC_CHECK_DEL_SPACE);
	SetCheck(IDC_CHECK_DEL_EMPTYLINE);
	
	// create a bunch of fonts
	m_LyricEditor.SetFont(&((CKmcMakerDlg *)GetParent())->GetLyricFont());
	m_LyricEditor.SetFocus();
	m_SliderFontsize.SetRange(12,24);
	m_SliderFontsize.SetPos(18);
	m_EditFontsize = _T("18");
	UpdateData(FALSE);
// 	LoadLyric(_T(".\\Test\\en.txt"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CImportLyricDlg::OnImportLyric() 
{
 	TCHAR szFilter[] = _T("All Files (*.*)|*.*|Lyric Files (*.lrc)|*.lrc|\
		Text Files(*.txt)|*.txt||");
 	CFileDialogEx ImportFileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);;
 	if( ImportFileDlg.DoModal() == IDOK)
	{
		LoadLyric(ImportFileDlg.GetFileName());
	}
}

void CImportLyricDlg::OnOK() 
{
	//不响应OnOK消息
}

LRESULT CImportLyricDlg::OnAcceptDropFile(WPARAM wParam , LPARAM lParam  )
{
	
	TCHAR *DropFileName = (TCHAR *)wParam;
	//接受文件手动消息
	LoadLyric(DropFileName);
	return 1L;
}


BOOL CImportLyricDlg::LoadLyric(LPCTSTR pszFileName)
{
	int Len = GetFileLenght(pszFileName);

	if(Len > MAX_LYRIC_LEN)
	{
		int ret = MessageBox(_T("打开的文件大于10K，可能不是正确的歌词文本格式，确定继续打开？"),
			_T("提示"),MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION);

		if( ret == IDNO)
			return FALSE;
	}
	
	if(!m_LyricText.LoadLyric(pszFileName))
	{
		return FALSE;
	}

	CString Text;
	m_LyricText.GetText(Text);
	m_LyricEditor.SetWindowText(Text);

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


BOOL CImportLyricDlg::GetCheck( UINT ID )
{
	return ((CButton *)GetDlgItem(ID))->GetCheck();
}

void CImportLyricDlg::SetCheck( UINT ID,BOOL bCheck )
{
	((CButton *)GetDlgItem(ID))->SetCheck(bCheck);
}
void CImportLyricDlg::OnBtnFilter() 
{
	// 得到过滤参数
	UpdateData(TRUE);
	CString Text;

	m_LyricEditor.GetWindowText(Text);
	m_LyricText.SetLyric(Text);
	// 去换行符
	int p = m_EditReplaceTxt.Find(LINE_SEPARATOR);
	if(p != -1)
	{
		m_EditReplaceTxt = m_EditReplaceTxt.Mid(0, p);
	}

	// 设置过滤参数
	CLyricText::FilterParam filterParam(
		GetCheck(IDC_CHECK_DEL_SPACE),
		GetCheck(IDC_CHECK_DEL_EMPTYLINE),
		GetCheck(IDC_CHECK_DEL_XML_HTML),
		GetCheck(IDC_CHECK_DEL_KSC),
		GetCheck(IDC_CHECK_DEL_LRC),
		GetCheck(IDC_CHECK_REPLACE),
		m_EditReplaceTxt,m_EditTargetTxt);
	m_LyricText.SetFilterParam(&filterParam);

	Text = _T("");
	m_LyricText.GetFilterText(Text);
	m_LyricEditor.SetWindowText(Text);
}


void CImportLyricDlg::OnBtnNextstep() 
{
	((CKmcMakerDlg *)GetParent())->OnCheckStep2();
}

BOOL CImportLyricDlg::CheckLeave()
{
	CString Lyric;
	m_LyricEditor.GetWindowText(Lyric);
	Lyric.TrimLeft();
	Lyric.TrimRight();
	if(Lyric.IsEmpty())
	{
		MessageBox(_T("请先导入歌词!"),_T("提示"),MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

void CImportLyricDlg::GetLyric(CString &Lyric)
{
	m_LyricEditor.GetWindowText(Lyric);
}

void CImportLyricDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CWnd *pSliderPos = this->GetDlgItem(IDC_SLIDER_FONTSIZE);
	if(pScrollBar == pSliderPos)
	{
		int FontSize = m_SliderFontsize.GetPos();
		 ((CKmcMakerDlg *)GetParent())->CreateLyricFont(FontSize);
		m_LyricEditor.SetFont(&((CKmcMakerDlg *)GetParent())->GetLyricFont());
		CString strFontSize;
		strFontSize.Format(_T("%d"),FontSize);
		m_EditFontsize = strFontSize;
		UpdateData(FALSE);
	}
	
	CResizingDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImportLyricDlg::OnChangeEditFontsize() 
{
	UpdateData();
	for(int i=0;i<m_EditFontsize.GetLength();i++)
	{
		TCHAR ch = m_EditFontsize.GetAt(i);
		if(ch < 0x30 || ch>0x39)
		{
			m_EditFontsize.Delete(i,1);
		}
	}
	UpdateData(FALSE);
}

BOOL CImportLyricDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->hwnd == GetDlgItem(IDC_EDIT_FONTSIZE)->m_hWnd)
	if(pMsg->message == WM_KEYDOWN)	
	{
		if( pMsg->wParam == 13)
		{
			UpdateData();
			
			int FontSize = atoi(m_EditFontsize);
			if(FontSize>24)
				FontSize = 24;
			if(FontSize<12)
				FontSize = 12;
			
			((CKmcMakerDlg *)GetParent())->CreateLyricFont(FontSize);
			m_LyricEditor.SetFont(&((CKmcMakerDlg *)GetParent())->GetLyricFont());
			
			m_SliderFontsize.SetPos(FontSize);
			CString strFontSize;
			strFontSize.Format(_T("%d"),FontSize);
			m_EditFontsize = strFontSize;
			
			UpdateData(FALSE);
		}
	}
	return CResizingDialog::PreTranslateMessage(pMsg);
}
