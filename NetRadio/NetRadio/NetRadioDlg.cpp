// NetRadioDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetRadio.h"
#include "NetRadioDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString GetAppPath();

// CNetRadioDlg �Ի���
CNetRadioDlg::CNetRadioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetRadioDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetRadioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetRadioDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_TEST, &CNetRadioDlg::OnBnClickedTest)
END_MESSAGE_MAP()


// CNetRadioDlg ��Ϣ�������

BOOL CNetRadioDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



	CString strProxy = _T("110.77.129.82:8080");

	m_Browser.CreateFromStatic(IDC_BROWSER,this);

	SetProxy(strProxy);
	m_Browser.Navigate2(_T("http://douban.fm/radio"));	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetRadioDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

// 	WinHttpClient HttpClient("http://www.douban.fm/radio");
// 	HttpClient.SendHttpRequest("");
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CNetRadioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNetRadioDlg::OnBnClickedTest()
{
	CString strValue;
	IHTMLDocument2* pDoc = (IHTMLDocument2*)m_Browser.GetHtmlDocument();
	HRESULT hr = S_FALSE;
	IHTMLElementCollection* pAllElem = NULL;
	IHTMLElementCollection* pAllScript = NULL;
	IHTMLElement* pElem = NULL;

	hr = pDoc->get_scripts(&pAllScript);
	if(SUCCEEDED(hr) && pAllScript != NULL)
	{
		IDispatchPtr pElemDisp = NULL;
		_variant_t varID(1);
		_variant_t varIdx(0);
		hr = pAllScript->item(varID, varIdx, &pElemDisp);
		if(SUCCEEDED(hr) && pElemDisp != NULL)
		{
			hr = pElemDisp->QueryInterface(IID_IHTMLElement,(void**)&pElem);
			if(SUCCEEDED(hr) && pElem != NULL)
			{
				BSTR bstrTagName;
				hr = pElem->get_outerHTML(&bstrTagName);
			
				hr = pElem->get_outerHTML(&bstrTagName);
				if(SUCCEEDED(hr))
				{
					CString strTagName(bstrTagName);
					SysFreeString(bstrTagName);
					MessageBox(strTagName);
				}
			}
		}
	}

	hr = pDoc->get_all(&pAllElem);

	if(SUCCEEDED(hr) && pAllElem != NULL)
	{
		IDispatchPtr pElemDisp = NULL;
		_variant_t varID(_T("body"));
		_variant_t varIdx(0);
		hr = pAllElem->item(varID, varIdx, &pElemDisp);
		if(SUCCEEDED(hr) && pElemDisp != NULL)
		{
			MessageBox(_T("OK"));
		}
	}

}

void CNetRadioDlg::SetProxy( CString strProxy )
{
// 	INTERNET_PROXY_INFO ipi;
// 	ipi.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
// 	ipi.lpszProxy = strProxy;
// 	ipi.lpszProxyBypass = NULL;
// 	DWORD dwBufferLength = sizeof(ipi);
// 	DWORD dwReserved = 0;
// 	HRESULT hr = ::UrlMkSetSessionOption(INTERNET_OPTION_PROXY, (void *)&ipi, dwBufferLength, dwReserved);

	INTERNET_PROXY_INFO proxyInfo;
	proxyInfo.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
	proxyInfo.lpszProxy = strProxy;
	proxyInfo.lpszProxyBypass = NULL;

	//session.SetOption(INTERNET_OPTION_PROXY,(LPVOID)&proxyInfo,sizeof(INTERNET_OPTION_PROXY),0);
	UrlMkSetSessionOption(INTERNET_OPTION_PROXY,&proxyInfo,sizeof(proxyInfo),0); 
}