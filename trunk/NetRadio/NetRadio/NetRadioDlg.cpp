// NetRadioDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetRadio.h"
#include "NetRadioDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FM_DOUBAN _T("http://douban.fm/radio")
#define FM_BAIDU _T("http://fm.mp3.baidu.com/")


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
	ON_BN_CLICKED(IDC_BAIDU, &CNetRadioDlg::OnBnClickedBaidu)
	ON_BN_CLICKED(IDC_DOUBAN, &CNetRadioDlg::OnBnClickedDouban)
END_MESSAGE_MAP()


// CNetRadioDlg ��Ϣ�������

BOOL CNetRadioDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	m_Browser.CreateFromStatic(IDC_BROWSER,this);

	CONFIG Config;
	ReadConfigFromIni(&Config);

	USES_CONVERSION;  
	LPCSTR proxy=T2A(Config.Proxy.GetBuffer(Config.Proxy.GetLength()));
	SetProxy(proxy);

	CString FM(Config.FM);
	FM = FM.MakeUpper();
	if(FM == "BAIDU")
		TurnBaidu();
	else
		TurnDouban();

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

void CNetRadioDlg::SetProxy( LPCSTR strProxy )
{
	INTERNET_PROXY_INFO_ANSI proxyInfo;
	proxyInfo.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
	proxyInfo.Proxy = strProxy;
	proxyInfo.lpszProxyBypass = NULL;
	UrlMkSetSessionOption(INTERNET_OPTION_PROXY,&proxyInfo,sizeof(proxyInfo),0);
}
void CNetRadioDlg::OnBnClickedBaidu()
{
	TurnBaidu();
}

void CNetRadioDlg::OnBnClickedDouban()
{
	TurnDouban();
}
void CNetRadioDlg::TurnBaidu() 
{
	m_Browser.SetLeft(-130);
	m_Browser.SetTop(-140);
	m_Browser.Navigate2(FM_BAIDU);	
}

void CNetRadioDlg::TurnDouban()
{
	m_Browser.SetLeft(0);
	m_Browser.SetTop(0);
	m_Browser.Navigate2(FM_DOUBAN);	
}

void CNetRadioDlg::ReadConfigFromIni( CONFIG *Config )
{
	CString AppPath = GetAppPath();
	CString FilePath = AppPath + _T("\\NetRadio.ini");
	CString strSection  = _T("NetRadio");
	CString strKeyProxy	= _T("Proxy");
	CString strKeyFM		= _T("FM");
	TCHAR   strValueProxy[100] ;
	TCHAR   strValueFM[100] ;
	
	GetPrivateProfileString (strSection,strKeyProxy,_T(""),strValueProxy,sizeof(strValueProxy),FilePath); 
	GetPrivateProfileString (strSection,strKeyFM,_T(""),strValueFM,sizeof(strValueFM),FilePath); 

	CString fm(strValueFM);
	CString proxy(strValueProxy);
	Config->FM = fm;
	Config->Proxy = proxy;
}
