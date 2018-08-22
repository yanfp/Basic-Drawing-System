#if !defined(AFX_TEXTDLG_H__8BF00C73_D29F_4EC5_B138_5720F21E0E93__INCLUDED_)
#define AFX_TEXTDLG_H__8BF00C73_D29F_4EC5_B138_5720F21E0E93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog

class CTextDlg : public CDialog
{
// Construction
public:
	CTextDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextDlg)
	afx_msg void OnChangeEdit1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTDLG_H__8BF00C73_D29F_4EC5_B138_5720F21E0E93__INCLUDED_)
