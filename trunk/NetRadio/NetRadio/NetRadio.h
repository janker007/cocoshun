// NetRadio.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNetRadioApp:
// �йش����ʵ�֣������ NetRadio.cpp
//

class CNetRadioApp : public CWinApp
{
public:
	CNetRadioApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNetRadioApp theApp;