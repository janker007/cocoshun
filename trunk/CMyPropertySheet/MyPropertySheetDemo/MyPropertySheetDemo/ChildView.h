// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include "ServerPge.h"
#include "UserPge.h"
// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	CServerPge m_pgeServer;
	CUserPge m_pgeUser;
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOptions();
};

