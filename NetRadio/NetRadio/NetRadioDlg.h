// NetRadioDlg.h : ͷ�ļ�
//

#pragma once
#include "custombrowser.h"


// CNetRadioDlg �Ի���
class CNetRadioDlg : public CDialog
{
// ����
public:
	CNetRadioDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NETRADIO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	typedef struct {

		//
		// dwAccessType - INTERNET_OPEN_TYPE_DIRECT, INTERNET_OPEN_TYPE_PROXY, or
		// INTERNET_OPEN_TYPE_PRECONFIG (set only)
		//

		DWORD dwAccessType;

		//
		// lpszProxy - proxy server list
		//

		LPCSTR Proxy;

		//
		// lpszProxyBypass - proxy bypass list
		//

		LPCSTR lpszProxyBypass;
	} INTERNET_PROXY_INFO_ANSI, * LPINTERNET_PROXY_INFO_ANSI;

	typedef struct	{
		CString Proxy;
		CString FM;
	}CONFIG;

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	void TurnDouban();
	void TurnBaidu();
	void ReadConfigFromIni(CONFIG *Config);
	void SetProxy( LPCSTR strProxy );
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �Զ���������ؼ�
	CCustomBrowser m_Browser;
	afx_msg void OnBnClickedTest();
	afx_msg void OnBnClickedBaidu();
	afx_msg void OnBnClickedDouban();
	
};
