// SysClearer.h: interface for the CSysClearer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSCLEARER_H__380A9448_D156_4FE7_9086_8B1084F075D1__INCLUDED_)
#define AFX_SYSCLEARER_H__380A9448_D156_4FE7_9086_8B1084F075D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wininet.h>
#include <UrlHist.h>
#include <shlwapi.h>

#define SWEEP_BUFFER_SIZE			10000

class CSysClearer  
{
public:
	void ClearTaskbarIconHistory();
	CSysClearer();
	virtual ~CSysClearer();

    void ClearInternetTemp();
    void ClearCookies();
    void ClearBrowserAddress(); //�������ַ����ʷ��ַ�����
    void ClearFormAutoComplete();
    void ClearAutoPassword();
    void ClearFavorite();
    void ClearSysTempDir();
    void ClearRecyclebin();
    void ClearRun();
    void ClearDocument();
    void ClearLastLoginName();
    void ClearFindFile();
    void ClearFindComputer();
    void ClearBrowseAddress(); //��������ַ��ʷ��¼

    enum DEL_CACHE_TYPE //Ҫɾ�������͡�
    {
        File,//��ʾinternet��ʱ�ļ�
        Cookie //��ʾCookie
    };
protected:


    //����ΪһЩ����������.
    BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
    BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE,   BOOL bWipeIndexDat = FALSE);
    BOOL IsWindowsNT();//�ж�ϵͳ
    BOOL IsWindows2k();
    BOOL GetUserSid(PSID* ppSid);
    void GetSidString(PSID pSid, LPTSTR szBuffer);
    BOOL GetOldSD(HKEY hKey, LPCTSTR pszSubKey, BYTE** pSD);
    BOOL CreateNewSD(PSID pSid, SECURITY_DESCRIPTOR* pSD, PACL* ppDacl);
    BOOL RegSetPrivilege(HKEY hKey, LPCTSTR pszSubKey, SECURITY_DESCRIPTOR* pSD, BOOL bRecursive);
    BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);
};

#endif // !defined(AFX_SYSCLEARER_H__380A9448_D156_4FE7_9086_8B1084F075D1__INCLUDED_)
