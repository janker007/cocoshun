// UserPge.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPropertySheetDemo.h"
#include "UserPge.h"


// CUserPge �Ի���

IMPLEMENT_DYNAMIC(CUserPge, CPropertyPage)

CUserPge::CUserPge()
	: CPropertyPage(CUserPge::IDD)
{

}

CUserPge::~CUserPge()
{
}

void CUserPge::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserPge, CPropertyPage)
END_MESSAGE_MAP()


// CUserPge ��Ϣ�������
