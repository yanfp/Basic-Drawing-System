#if !defined(AFX_POLYGONPRODLG_H__CC16BE0B_948B_4159_A0C1_A8997C3CDC5C__INCLUDED_)
#define AFX_POLYGONPRODLG_H__CC16BE0B_948B_4159_A0C1_A8997C3CDC5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PolygonProDlg.h : header file
//
#include "MyPolygon.h"
/////////////////////////////////////////////////////////////////////////////
// CPolygonProDlg dialog

class CPolygonProDlg : public CDialog
{
// Construction
public:
	CPolygonProDlg(CMyPolygon* pPolygon,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPolygonProDlg)
	enum { IDD = IDD_POLYGONPRODLG_DIALOG };
	int		m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolygonProDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPolygonProDlg)
	afx_msg void OnSelchangeComStyle();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnColor();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeComType();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMyPolygon* m_pPolygon;
	COLORREF m_color;
	UINT m_style;
	LONG m_type;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLYGONPRODLG_H__CC16BE0B_948B_4159_A0C1_A8997C3CDC5C__INCLUDED_)
