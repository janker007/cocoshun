////////////////////////////////////////////////////////////////////////
// ResizingDialog.cpp : implementation file
//	
// Author: Eli Vingot (elivingt@internet-zahav.net)
//
// Ideas for improving the class are always appreciated
//
//
// The base class for the dialog box you want to allow resizing
// Use SetConrolInfo() to determine how each control behaves when
// the user resize the dialog box.
// (The "Windows default" is ANCHORE_TOP | ANCHORE_LEFT)
//
// e.g. For a right aligned OK button you'll probably call:
// SetControlInfo(IDOK, ANCHORE_RIGHT)
// For a text control that needs to resize with the dialog you may do:
// SetControlInfo(IDD_MYEDITOR, RESIZE_BOTH)
//
// Note: The dialog box "remebers" its size on destroy and the next time
// you launch it, it'll set the dialog size back to the previous size.
// If you don't like this behavior, call SetRememberSize(FALSE)
//
// LIMITATIONS:
// 1) This class does not handle overlapping controls, 
//    e.g., you cannot place two controls one (RESIZE_VER) and the other
//    with (RESIZE_VER | ANCHORE_BOTTOM) one below the other, they may ovelapp.
//
// 2) This class does not remember the mode of the dialog (Maximized/Minimized)
//	  it would be easy to add this feature, though.
//
//
#include "stdafx.h"
#include "ResizingDialog.h"
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CResizingDialog dialog

CResizingDialog::CResizingDialog(UINT nIDTemplate, CWnd* pParentWnd) : 
				CDialog(nIDTemplate,pParentWnd)
{
	m_minWidth = m_minHeight = 0;	// flag that GetMinMax wasn't called yet
	m_old_cx = m_old_cy = 0;
	m_bSizeChanged = FALSE;
	m_nIDTemplate = nIDTemplate;

	m_bRememberSize = TRUE;
	m_bDrawGripper = FALSE;
}

void CResizingDialog::SetControlInfo(WORD CtrlId,WORD Anchore)			
{
	if(Anchore == ANCHORE_LEFT)
		return; // Do nothing

	// Add resizing behaviour for the control
	DWORD c_info = CtrlId | (Anchore << 16);
	m_control_info.Add(c_info);
}

BEGIN_MESSAGE_MAP(CResizingDialog, CDialog)
	//{{AFX_MSG_MAP(CResizingDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
	ON_WM_CREATE()

	ON_MESSAGE(WM_CUSTOM_MSG_DROPFILE,OnAcceptDropFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
// CResizingDialog message handlers



//////////////////////////////////////////////////////////////////////////
// OnInitDialog()
//
BOOL CResizingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(m_bRememberSize)
	{
		// Load the previous size of the dialog box from the INI/Registry
		CString dialog_name;
		GetDialogProfileEntry(dialog_name);

		int cx = AfxGetApp()->GetProfileInt(dialog_name,_T("CX"),0);
		int cy = AfxGetApp()->GetProfileInt(dialog_name,_T("CY"),0);
		
		if(cx && cy)
		{
			SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOMOVE );
		}
	}
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}


//
// OnSize()
// Set the dialog controls new position and size
//
void CResizingDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(nType == SIZE_MINIMIZED)
		return;

	int dx = cx - m_old_cx;
	int dy = cy - m_old_cy;

	if(m_old_cx)
	{
		// Move and Size the controls using the information
		// we got in SetControlInfo()
		//
		m_bSizeChanged = TRUE;
		CRect WndRect;
		CWnd *pWnd;
		DWORD c_info;
		short Anchore;
		for(int i = 0; i < m_control_info.GetSize(); i++)
		{
			c_info = m_control_info[i];
			pWnd = GetDlgItem(LOWORD(c_info));
			if(!pWnd)
			{
				TRACE(_T("Control ID - %d NOT FOUND!!\n"),LOWORD(c_info));
				continue;
			}

			if(!HIWORD(c_info))
				continue; // do nothing if anchored to top and or left

			Anchore = HIWORD(c_info);
			pWnd->GetWindowRect(&WndRect);  ScreenToClient(&WndRect);
			
			if(Anchore & RESIZE_HOR)
				WndRect.right += dx;
			else if(Anchore & ANCHORE_RIGHT)
				WndRect.OffsetRect(dx,0);

			if(Anchore & RESIZE_VER)
				WndRect.bottom += dy;
			else if(Anchore & ANCHORE_BOTTOM)
				WndRect.OffsetRect(0,dy);

			pWnd->MoveWindow(&WndRect);
		}

	}
	m_old_cx = cx;
	m_old_cy = cy;

	// When enlarging a dialog box we need to erase the old gripper 
	if(m_bDrawGripper)
		InvalidateRect(m_GripperRect);
}


void CResizingDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    if (!m_minWidth) // first time
		{
		CDialog::OnGetMinMaxInfo(lpMMI);
		return;
		}
    lpMMI->ptMinTrackSize.x = m_minWidth;
    lpMMI->ptMinTrackSize.y = m_minHeight;
}

void CResizingDialog::OnDestroy() 
{
	// Save the size of the dialog box, so next time
	// we'll start with this size
// 	if(m_bRememberSize && m_bSizeChanged && m_old_cx && m_old_cy)
// 		{
// 		CRect rc;
// 		GetWindowRect(&rc);
// 		CString dialog_name;
// 		GetDialogProfileEntry(dialog_name);
// 
// 		AfxGetApp()->WriteProfileInt(dialog_name,"CX",rc.Width());
// 		AfxGetApp()->WriteProfileInt(dialog_name,"CY",rc.Height());
// 		}
// 
// 	// Important: Reset the internal values in case of reuse of the dialog
// 	// with out deleting.
// 	m_minWidth = m_minHeight = m_old_cx = m_old_cy = 0;
// 	m_bSizeChanged = FALSE;

	CDialog::OnDestroy();
}


//
// OnCreate()
//
int CResizingDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Remember the original size so later we can calculate
	// how to place the controls on dialog Resize
	m_minWidth  = lpCreateStruct->cx;
	m_minHeight = lpCreateStruct->cy;
	return 0;
}

//
// OnPaint()
// Override WM_PAINT to draw a gripper
//
// Credit goes to: Tommy Svensson
//
void CResizingDialog::OnPaint()
{
	CDialog::OnPaint();

	// Draw a resizing gripper at the lower left corner
	//
	// Note: Make sure you leave enough space in your dialog template
	// for the gripper to be drawn.
	// Don't put any controls on the lower left corner.
	if(m_bDrawGripper)
	{
		CRect rc;
		GetClientRect(rc);

		rc.left = rc.right-GetSystemMetrics(SM_CXHSCROLL);
		rc.top = rc.bottom-GetSystemMetrics(SM_CYVSCROLL);
		m_GripperRect = rc;
		CClientDC dc(this);
		dc.DrawFrameControl(rc,DFC_SCROLL,DFCS_SCROLLSIZEGRIP);
	}
}


//
// OnNcHitTest
// Handle mouse over the gripper
//
// Credit: Tommy Svensson
//
UINT CResizingDialog::OnNcHitTest(CPoint point)
{
	UINT ht = CDialog::OnNcHitTest(point);

	if(ht==HTCLIENT && m_bDrawGripper)
	{
		CRect rc;
		GetWindowRect( rc );
		rc.left = rc.right-GetSystemMetrics(SM_CXHSCROLL);
		rc.top = rc.bottom-GetSystemMetrics(SM_CYVSCROLL);
		if(rc.PtInRect(point))
		{
			return HTBOTTOMRIGHT;
		}

		//�϶��ͻ��˽�����ƶ�����
		GetClientRect(&rc);
		ClientToScreen(&rc);
		return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
	}

	return ht;
}


//
// GetDialogProfileEntry()
// Override this (virtual) function in your derived class
// if you want to store the dialog info under a different entry name.
//
// Credit: Ari Greenberg
void CResizingDialog::GetDialogProfileEntry(CString &sEntry)
{
	// By default store the size under the Dialog ID value (Hex)
	sEntry.Format(_T("%x"),m_nIDTemplate);
}


void CResizingDialog::OnDropFiles(HDROP dropInfo)
{
	// Get the number of pathnames that have been dropped
	WORD wNumFilesDropped = DragQueryFile(dropInfo, -1, NULL, 0);
	
	CString csFirstFile = _T("");
	
	// there may be many, but we'll only use the first
	if (wNumFilesDropped > 0)
	{
		// Get the number of bytes required by the file's full pathname
		WORD wPathnameSize = DragQueryFile(dropInfo, 0, NULL, 0);
		
		// Allocate memory to contain full pathname & zero byte
		wPathnameSize+=1;
		
		TCHAR * pFile = new TCHAR[wPathnameSize];
		if (pFile == NULL)
		{
			ASSERT(0);
			DragFinish(dropInfo);
			return;
		}
		
		// Copy the pathname into the buffer
		DragQueryFile(dropInfo, 0, pFile, wPathnameSize);
		
		csFirstFile = pFile;
		
		// clean up
		delete [] pFile; 
	}
	
	// Free the memory block containing the dropped-file information
	DragFinish(dropInfo);
	
	// if this was a shortcut, we need to expand it to the target path
	CString csExpandedFile = ExpandShortcut(csFirstFile);
	
	// if that worked, we should have a real file name
	if (!csExpandedFile.IsEmpty()) 
	{
		csFirstFile = csExpandedFile;
	}
	
	if (!csFirstFile.IsEmpty())
	{
		struct _stat buf;
		
		// get some info about that file
		int result = _stat( csFirstFile, &buf );
		if( result == 0 ) 
		{
			// verify that we have a dir (if we want dirs)
			if ((buf.st_mode & _S_IFDIR) == _S_IFDIR) 
			{
				if (m_bUseDir)
				{
					SendMessage(WM_CUSTOM_MSG_DROPFILE,(WPARAM)csFirstFile.GetBuffer(0),0);
					//SetWindowText(csFirstFile);
				}
				
				// verify that we have a file (if we want files)
			} 
			else if ((buf.st_mode & _S_IFREG) == _S_IFREG) 
			{
				if (!m_bUseDir)
				{
					SendMessage(WM_CUSTOM_MSG_DROPFILE,(WPARAM)csFirstFile.GetBuffer(0),0);
					//SetWindowText(csFirstFile);
				}
			}
		}
	}
	
}
CString CResizingDialog::ExpandShortcut(CString &inFile)
{
	CString outFile;
	
	// Make sure we have a path
	ASSERT(inFile != _T(""));
	
	IShellLink* psl;
	HRESULT hres;
	LPTSTR lpsz = inFile.GetBuffer(MAX_PATH);
	
	// Create instance for shell link
	hres = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*) &psl);
	
	if (SUCCEEDED(hres))
	{
		// Get a pointer to the persist file interface
		IPersistFile* ppf;
		
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*) &ppf);
		if (SUCCEEDED(hres))
		{
			// Make sure it's ANSI
			WORD wsz[MAX_PATH];
			::MultiByteToWideChar(CP_ACP, 0, lpsz, -1, wsz, MAX_PATH);
			
			// Load shortcut
			hres = ppf->Load(wsz, STGM_READ);
			
			if (SUCCEEDED(hres)) 
			{
				WIN32_FIND_DATA wfd;
				
				// find the path from that
				HRESULT hres = psl->GetPath(outFile.GetBuffer(MAX_PATH), 
					MAX_PATH,
					&wfd, 
					SLGP_UNCPRIORITY);
				
				outFile.ReleaseBuffer();
			}
			
			ppf->Release();
		}
		
		psl->Release();
	}
	
	inFile.ReleaseBuffer();
	
	// if this fails, outFile == ""
	return outFile;
}

void CResizingDialog::PreSubclassWindow() 
{
	DragAcceptFiles(TRUE);
	
	CDialog::PreSubclassWindow();
}

LRESULT CResizingDialog::OnAcceptDropFile(WPARAM wParam , LPARAM lParam  )
{
	return 1L;
}
