// MyPropertySheetDemo.h : MyPropertySheetDemo Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyPropertySheetDemoApp:
// �йش����ʵ�֣������ MyPropertySheetDemo.cpp
//

class CMyPropertySheetDemoApp : public CWinApp
{
public:
	CMyPropertySheetDemoApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyPropertySheetDemoApp theApp;