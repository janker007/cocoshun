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
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	void SetProxy( CString strProxy );
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �Զ���������ؼ�
	CCustomBrowser m_Browser;
	afx_msg void OnBnClickedTest();
};
