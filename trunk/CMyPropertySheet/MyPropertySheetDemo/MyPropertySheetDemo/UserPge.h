#pragma once


// CUserPge �Ի���

class CUserPge : public CPropertyPage
{
	DECLARE_DYNAMIC(CUserPge)

public:
	CUserPge();
	virtual ~CUserPge();

// �Ի�������
	enum { IDD = IDD_USERPGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
