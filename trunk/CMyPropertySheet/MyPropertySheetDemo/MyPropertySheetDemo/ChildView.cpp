// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "MyPropertySheetDemo.h"
#include "ChildView.h"
#include "MyPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_OPTIONS, &CChildView::OnOptions)
END_MESSAGE_MAP()



// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	// TODO: �ڴ˴������Ϣ����������
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}


void CChildView::OnOptions()
{
	CMyPropertySheet myps(_T("ѡ��"),this,0);
	
	myps.AddPage(&m_pgeServer);
	myps.AddPage(&m_pgeUser);
	myps.AddIcon(::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_GLOBAL)));
	myps.AddIcon(::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ADDITION)));
	myps.DoModal();
	
}
