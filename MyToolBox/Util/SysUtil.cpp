// SysUtil.cpp: implementation of the SysUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysUtil.h"
#include "windows.h"
#include "Tlhelp32.h"
#include <shlwapi.h> 
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SysUtil::SysUtil()
{

}

SysUtil::~SysUtil()
{

}
void SysUtil::KillProcess(LPCTSTR ExeName) 
{ 
	LPCTSTR File=NULL; 
	HANDLE hProcessSnap; 
	PROCESSENTRY32 pe32; 
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);   
	pe32.dwSize=sizeof(PROCESSENTRY32); 
	if(Process32First(hProcessSnap,&pe32)) 
	{ 
		do 
		{ 
			File=pe32.szExeFile; 
			if(strcmp(File,ExeName)==0) 
			{ 
				TerminateProcess(OpenProcess(PROCESS_ALL_ACCESS,0,pe32.th32ProcessID),0); 
				break; 
			}    
		} 
		while(Process32Next(hProcessSnap,&pe32)); 
	} 
	CloseHandle(hProcessSnap); 
}

OSType SysUtil::GetOS()   
{   
    OSType     ShellType;   
    DWORD           winVer;   
    OSVERSIONINFO   *osvi;   
    
    winVer=GetVersion();
    DWORD dwMajorVersion=(DWORD)(LOBYTE(LOWORD(winVer)));
    DWORD dwMinorVersion=(DWORD)(HIBYTE(LOWORD(winVer)));
    if(winVer<0x80000000){/*NT   */   
        ShellType=WinNT3;   
        osvi=   (OSVERSIONINFO   *)malloc(sizeof(OSVERSIONINFO));   
        if   (osvi!=NULL){   
            memset(osvi,0,sizeof(OSVERSIONINFO));   
            osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);   
            GetVersionEx(osvi);   
            if(osvi->dwMajorVersion==4L)ShellType=WinNT4;   
            else   if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==0L)ShellType=Win2000; //version 5.0  
            else   if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==1L)ShellType=WinXP;   //version 5.1
            free(osvi);   
        }   
    }   
    else if (LOBYTE(LOWORD(winVer))<4)   
        ShellType=Win32s;   
    else{   
        ShellType=Win95;   
        osvi=   (OSVERSIONINFO   *)malloc(sizeof(OSVERSIONINFO));   
        if   (osvi!=NULL){   
            memset(osvi,0,sizeof(OSVERSIONINFO));   
            osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);   
            GetVersionEx(osvi);   
            if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==10L)ShellType=Win98;   
            else   if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==90L)ShellType=WinME;   
            free(osvi);   
        }   
    }   
    return ShellType;   
}


void SysUtil::RebulidIconCache()
{
    TCHAR Content[MAX_PATH] = {0};  //����   
    DWORD Contentsize = sizeof(Content) / sizeof(TCHAR);    //����   
    DWORD dwType = REG_SZ;   
    TCHAR RegPath[] = _T("Control Panel\\Desktop\\WindowMetrics");   
    TCHAR VauleName[] = _T("Shell Icon Size");   
    
    
    if (SHGetValue(HKEY_CURRENT_USER, RegPath, VauleName, &dwType, &Content, &Contentsize) == ERROR_SUCCESS)   
    {   
        TCHAR Contenttmp[] = _T("24");   
        Contentsize = sizeof(Contenttmp) / sizeof(TCHAR);   //����       
        if (SHSetValue(HKEY_CURRENT_USER, RegPath, VauleName, REG_SZ, Contenttmp, Contentsize) == ERROR_SUCCESS)   
        {   
            SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, SPI_SETNONCLIENTMETRICS,    
                0, SMTO_ABORTIFHUNG, 5000, NULL);    
            
            Contentsize = sizeof(Content) / sizeof(TCHAR);  //����   
            if (SHSetValue(HKEY_CURRENT_USER, RegPath, VauleName, REG_SZ, Content, Contentsize) == ERROR_SUCCESS)   
            {   
                SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, SPI_SETNONCLIENTMETRICS,    
                    0, SMTO_ABORTIFHUNG, 5000, NULL);   
            }   
        }   
        printf("%s", "�ؽ�ͼ�껺��ɹ���");   
    }   
    else  
    {   
        printf("%s", "�ؽ�ͼ�껺��ʧ�ܣ�");   
    }   
//    system("pause");    //���� ����getchar()
}
