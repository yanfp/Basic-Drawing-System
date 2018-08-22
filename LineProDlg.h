#if !defined(AFX_LINEPRODLG_H__70C169B1_C1C0_4D4C_AA83_3B0D841FCCCA__INCLUDED_)
#define AFX_LINEPRODLG_H__70C169B1_C1C0_4D4C_AA83_3B0D841FCCCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineProDlg.h : header file
//
#include "Draw.h"
#include "MyLine.h"
#include "MyPline.h"
/////////////////////////////////////////////////////////////////////////////
// CLineProDlg dialog

class CLineProDlg : public CDialog
{
// Construction
public:
	CLineProDlg(CDraw* pDraw,CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CLineProDlg)
	enum { IDD = IDD_LINEPROPERTYDLG_DIALOG };
	int		m_LineWidth;
	int		m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineProDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineProDlg)
	afx_msg void OnChangeEdtWidth();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComLinestyle();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnColor();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDraw* m_pDraw;
	
	COLORREF m_color;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEPRODLG_H__70C169B1_C1C0_4D4C_AA83_3B0D841FCCCA__INCLUDED_)
