// ServerPge.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPropertySheetDemo.h"
#include "ServerPge.h"


// CServerPge �Ի���

IMPLEMENT_DYNAMIC(CServerPge, CPropertyPage)

CServerPge::CServerPge()
	: CPropertyPage(CServerPge::IDD)
{

}

CServerPge::~CServerPge()
{
}

void CServerPge::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerPge, CPropertyPage)
END_MESSAGE_MAP()


// CServerPge ��Ϣ�������
