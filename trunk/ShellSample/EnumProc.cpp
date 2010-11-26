////////////////////////////////////////////////////////////////
// MSDN Magazine -- July 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio 6.0 and Visual Studio .NET
// Runs in Windows XP and probably Windows 2000 too.
//
#include "stdafx.h"
#include "EnumProc.h"
#include "Psapi.h"

CWindowIterator::CWindowIterator(DWORD nAlloc)
{
	ASSERT(nAlloc > 0);
	m_current = m_count = 0;
	m_hwnds = new HWND [nAlloc];
	m_nAlloc = nAlloc;
}

CWindowIterator::~CWindowIterator()
{
	delete [] m_hwnds;
}

//////////////////
// Move to first top-level window.

// Stuff entire array and return the first HWND.

//�оٳ���ǰ�߳����еĴ��ڣ����ص�һ������

HWND CWindowIterator::First()
{
	//�ص�����EnumProc�Ĳ�����(LPARAM)this����������
	
	::EnumWindows(EnumProc, (LPARAM)this);
	
	m_current = 0;
	
	//���ص�0������
	
	return Next();
}

//////////////////
// Static enumerator passes to virtual fn.
//
BOOL CALLBACK CWindowIterator::EnumProc(HWND hwnd, LPARAM lp)
{
	return ((CWindowIterator*)lp)->OnEnumProc(hwnd);
}

//////////////////
// Virtual enumerator proc: add HWND to array if OnWindow is TRUE.
//
BOOL CWindowIterator::OnEnumProc(HWND hwnd)
{
	//������ڿɼ������Һ͵�ǰ���ڵ�id��ͬ
	
	if (OnWindow(hwnd))
	{
		//�ѵ�ǰ������ӵ���������
		
		if (m_count < m_nAlloc)
		{
			m_hwnds[m_count++] = hwnd;
		}
	}
	
	return TRUE; // keep looking
}

//////////////////
// Main window iterator: special case to iterate main windows of a process.
//
CMainWindowIterator::CMainWindowIterator(DWORD pid, DWORD nAlloc)
: CWindowIterator(nAlloc)
{
	m_pid = pid;
}

CMainWindowIterator::~CMainWindowIterator()
{
}

//////////////////
// virtual override: is this window a main window of my process?
//
BOOL CMainWindowIterator::OnWindow(HWND hwnd)
{
	//������ڿɼ�
	
	if (GetWindowLong(hwnd,GWL_STYLE) & WS_VISIBLE) 
	{
		DWORD pidwin;
		
		//��ô��ڶ�Ӧ��threadid������͵�ǰ���߳�id
		
		//��ȷ���true
		
		GetWindowThreadProcessId(hwnd, &pidwin);
		
		if (pidwin == m_pid)
		{
			return TRUE;
		}
		
	}
	return FALSE;
}

CProcessIterator::CProcessIterator()
{
	m_pids = NULL;
}

CProcessIterator::~CProcessIterator()
{
	delete [] m_pids;
}

//////////////////
// Get first process.
// Call EnumProcesses to initialize entire array, then return first one.
//
DWORD CProcessIterator::First()
{
	m_current = (DWORD)-1;
	
	m_count = 0;
	
	DWORD nalloc = 1024;
	
	do {
		delete [] m_pids;
		
		m_pids = new DWORD [nalloc];// ����һ��1024���һ������
		
		//������е��̣߳����浽m_pids�������棬m_count�����˻���̵߳���Ŀ
		
		if ( ::EnumProcesses(m_pids, nalloc*sizeof(DWORD), &m_count) ) 
		{
			m_count /= sizeof(DWORD);
			
			//m_currentָ���һ���ڵ㣬������0��idle process
			
			m_current = 1; // important: skip IDLE process with pid=0.
		}
		
	} while (nalloc <= m_count);
	
	return Next();
}

CProcessModuleIterator::CProcessModuleIterator(DWORD pid)
{
	// open the process
	
	m_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE, pid);
}

CProcessModuleIterator::~CProcessModuleIterator()
{
	CloseHandle(m_hProcess);
	
	delete [] m_hModules;
}

//////////////////
// Get first module in process. Call EnumProcesseModules to
// initialize entire array, then return first module.
//
HMODULE CProcessModuleIterator::First()
{
	m_count = 0;
	m_current = (DWORD) -1; 
	m_hModules = NULL;
	if (m_hProcess) 
	{
		DWORD nalloc = 1024;
		do {
			delete [] m_hModules;
			m_hModules = new HMODULE [nalloc];
			if (EnumProcessModules(m_hProcess, m_hModules,
				nalloc*sizeof(DWORD), &m_count)) 
			{
				m_count /= sizeof(HMODULE);
				m_current = 0;
			}
		} while (nalloc <= m_count);
	}
	return Next();
}

