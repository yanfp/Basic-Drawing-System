// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_MAINFRM_H__8169F4BE_B06F_41A4_9083_DD6E154AF8B2__INCLUDED_)
#define AFX_MAINFRM_H__8169F4BE_B06F_41A4_9083_DD6E154AF8B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CDialogBar  m_wndDlgBar;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBrowsemap();
	afx_msg void OnUpdateBrowsemap(CCmdUI* pCmdUI);
	afx_msg void OnEdit();
	afx_msg void OnUpdateEdit(CCmdUI* pCmdUI);
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnClose();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolBar m_MapBrowseToolBar;
	CToolBar m_DrawMapToolBar;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8169F4BE_B06F_41A4_9083_DD6E154AF8B2__INCLUDED_)
