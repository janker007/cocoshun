#pragma once


// CServerPge �Ի���

class CServerPge : public CPropertyPage
{
	DECLARE_DYNAMIC(CServerPge)

public:
	CServerPge();
	virtual ~CServerPge();

// �Ի�������
	enum { IDD = IDD_SERVERPGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
