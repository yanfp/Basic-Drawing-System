// LineProDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Map.h"
#include "LineProDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineProDlg dialog


CLineProDlg::CLineProDlg(CDraw* pDraw,CWnd* pParent /*=NULL*/)
	: CDialog(CLineProDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineProDlg)
	m_LineWidth = 0;
	m_id = 0;
	//}}AFX_DATA_INIT
	this->m_pDraw=pDraw;
}

void CLineProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineProDlg)
	DDX_Text(pDX, IDC_EDT_WIDTH, m_LineWidth);
	DDV_MinMaxInt(pDX, m_LineWidth, 0, 10);
	DDX_Text(pDX, IDC_EDT_ID, m_id);
	DDV_MinMaxInt(pDX, m_id, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineProDlg, CDialog)
	//{{AFX_MSG_MAP(CLineProDlg)
	ON_EN_CHANGE(IDC_EDT_WIDTH, OnChangeEdtWidth)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COM_LINESTYLE, OnSelchangeComLinestyle)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_COLOR, OnBtnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineProDlg message handlers
BOOL CLineProDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pDraw->IsKindOf(RUNTIME_CLASS(CMyLine)))
	{
		CMyLine* m_pLine=(CMyLine*)m_pDraw;
		this->m_id=m_pLine->m_id;
		((CComboBox*)GetDlgItem(IDC_COM_LINESTYLE))->SetCurSel(m_pLine->m_style);
		m_LineWidth=m_pLine->m_width;
		m_color=m_pLine->m_color;
	}
	else
	{
		CMyPline* m_pPline=(CMyPline*)m_pDraw;
		this->m_id=m_pPline->m_id;
		((CComboBox*)GetDlgItem(IDC_COM_LINESTYLE))->SetCurSel(m_pPline->m_style);
		m_LineWidth=m_pPline->m_width;
		m_color=m_pPline->m_color;

	}
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLineProDlg::OnChangeEdtWidth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	Invalidate();
}

void CLineProDlg::OnSelchangeComLinestyle() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CLineProDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//颜色更新
	CRect rectColor;
	((CButton*)GetDlgItem(IDC_BTN_COLOR))->GetWindowRect(rectColor);
	ScreenToClient(&rectColor);
	rectColor.left+=47;
	rectColor.right+=47;
	dc.FillRect(rectColor,&CBrush(m_color));

	//预览更新
	CRect rect;
	((CStatic*)GetDlgItem(IDC_S_PREVIEW))->GetWindowRect(&rect);
	ScreenToClient(&rect);
	CPen pen(((CComboBox*)GetDlgItem(IDC_COM_LINESTYLE))->GetCurSel(),m_LineWidth,m_color);
	dc.SelectObject(&pen);
	CPoint pt1,pt2;
	pt1.x=rect.left+5;pt1.y=rect.top+rect.Height()/2;
	pt2.x=rect.right-5;pt2.y=rect.top+rect.Height()/2;
	dc.MoveTo(pt1);
	dc.LineTo(pt2);
	// Do not call CDialog::OnPaint() for painting messages
}





HBRUSH CLineProDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_BTN_COLOR)
	{
		pDC->SetTextColor(RGB(255,0,0));
		return CBrush(m_color);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


void CLineProDlg::OnBtnColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult=m_color;
	if(IDOK==dlg.DoModal())
	{
		m_color=dlg.m_cc.rgbResult;
		Invalidate();
	}
}

void CLineProDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(m_pDraw->IsKindOf(RUNTIME_CLASS(CMyLine)))
	{
		CMyLine* m_pLine=(CMyLine*)m_pDraw;
		m_pLine->m_color=m_color;
		m_pLine->m_style=((CComboBox*)GetDlgItem(IDC_COM_LINESTYLE))->GetCurSel();
		m_pLine->m_width=m_LineWidth;
		m_pLine->m_IsSelected=false;
	}
	else
	{
		CMyPline* m_pPline=(CMyPline*)m_pDraw;
		m_pPline->m_color=m_color;
		m_pPline->m_style=((CComboBox*)GetDlgItem(IDC_COM_LINESTYLE))->GetCurSel();
		m_pPline->m_width=m_LineWidth;
		m_pPline->m_IsSelected=false;

	}
	CDialog::OnOK();
}

void CLineProDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_pDraw->IsKindOf(RUNTIME_CLASS(CMyLine)))
	{
		CMyLine* m_pLine=(CMyLine*)m_pDraw;
		m_pLine->m_IsSelected=false;
	}
	else
	{
		CMyPline* m_pPline=(CMyPline*)m_pDraw;
		m_pPline->m_IsSelected=false;
	}
	CDialog::OnCancel();
}
