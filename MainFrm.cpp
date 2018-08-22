// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Map.h"
//#include "MapView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_BROWSEMAP, OnBrowsemap)
	ON_UPDATE_COMMAND_UI(IDM_BROWSEMAP, OnUpdateBrowsemap)
	ON_COMMAND(IDM_EDIT, OnEdit)
	ON_UPDATE_COMMAND_UI(IDM_EDIT, OnUpdateEdit)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_WM_CLOSE()
	
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	 //设置各指示器的风格和宽度
	m_wndStatusBar.SetPaneInfo(1,300,SBPS_NORMAL,180);
	m_wndStatusBar.SetPaneInfo(2,301,SBPS_NORMAL,80);
	m_wndStatusBar.SetPaneInfo(3,302,SBPS_NORMAL,80);
	//m_wndStatusBar.SetPaneInfo(0,304,SBPS_STRETCH,80);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//创建地图操作工具栏
	if (!m_MapBrowseToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_MapBrowseToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}	
	m_MapBrowseToolBar.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_RIGHT|CBRS_ALIGN_LEFT);
	DockControlBar(&m_MapBrowseToolBar);
	//创建绘图工具栏
	if (!m_DrawMapToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_DrawMapToolBar.LoadToolBar(IDR_TOOLBAR2))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}	
	m_DrawMapToolBar.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_RIGHT|CBRS_ALIGN_LEFT);
	DockControlBar(&m_DrawMapToolBar);

	//对话框工具栏
/*	if(m_wndDlgBar.Create(this,IDD_DIALOGBAR,CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY,CBRS_TOP))
	{
		CComboBox* pCom1=(CComboBox*)m_wndDlgBar.GetDlgItem(IDC_COMBO1);
		pCom1->AddString("线型");
		pCom1->AddString("颜色");
		pCom1->AddString("线宽");	
		pCom1->SetCurSel(0);
		CComboBox* pCom2=(CComboBox*)m_wndDlgBar.GetDlgItem(IDC_COMBO2);
		pCom2->ResetContent();
		pCom2->AddString("PS_SOLID _________");
		pCom2->AddString("PS_DASH __ __ __ ");
		pCom2->AddString("PS_DOT _ _ _ _ _");
		pCom2->SetCurSel(0);
	}*/
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnBrowsemap() 
{
	// TODO: Add your command handler code here
	
	if(!this->m_MapBrowseToolBar.IsWindowVisible())
	{
		m_MapBrowseToolBar.EnableDocking(CBRS_ALIGN_TOP);
		DockControlBar(&m_MapBrowseToolBar);
		m_MapBrowseToolBar.ShowWindow(SW_SHOW);
	}
	else
	{		
		m_MapBrowseToolBar.ShowWindow(SW_HIDE);
		
	}
	RecalcLayout();
}

void CMainFrame::OnUpdateBrowsemap(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_MapBrowseToolBar.IsWindowVisible());
}

void CMainFrame::OnEdit() 
{
	// TODO: Add your command handler code here
	if(!this->m_DrawMapToolBar.IsWindowVisible())
	{
		m_DrawMapToolBar.EnableDocking(CBRS_ALIGN_TOP);
		DockControlBar(&m_DrawMapToolBar);
		m_DrawMapToolBar.ShowWindow(SW_SHOW);
	}
	else
	{		
		m_DrawMapToolBar.ShowWindow(SW_HIDE);
		
	}
	RecalcLayout();
}

void CMainFrame::OnUpdateEdit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_DrawMapToolBar.IsWindowVisible());
}


void CMainFrame::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCom1=(CComboBox*)m_wndDlgBar.GetDlgItem(IDC_COMBO1);
	CComboBox* pCom2=(CComboBox*)m_wndDlgBar.GetDlgItem(IDC_COMBO2);
	if(pCom1->GetCurSel()==0)
	{
		pCom2->ResetContent();
		pCom2->AddString("PS_SOLID _________");
		pCom2->AddString("PS_DASH __ __ __ ");
		pCom2->AddString("PS_DOT _ _ _ _ _");

		
	}
}

void CMainFrame::OnSelchangeCombo2() 
{
	// TODO: Add your control notification handler code here
	
}



LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	this->GetWindowRect(&rect);
	//ClientToScreen(&rect);
	switch(message)  
	{  
	case WM_NCLBUTTONDOWN:  
		if(wParam==HTCAPTION)
			
		break;
	case WM_NCLBUTTONUP:
		if(HTCAPTION==wParam)
		{}
		break;

	}  
	return CFrameWnd::DefWindowProc(message, wParam, lParam);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnClose();
}

