// TextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Map.h"
#include "TextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog


CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextDlg)
	m_str = _T("");
	//}}AFX_DATA_INIT
}


void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextDlg)
	DDX_Text(pDX, IDC_EDIT1, m_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialog)
	//{{AFX_MSG_MAP(CTextDlg)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDlg message handlers

void CTextDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_EDIT1,str);
	if(str=="")
		((CButton*)GetDlgItem(IDOK))->EnableWindow(false);
	else
		((CButton*)GetDlgItem(IDOK))->EnableWindow(true);

}

BOOL CTextDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDOK))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();
	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
