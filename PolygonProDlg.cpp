// PolygonProDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Map.h"
#include "PolygonProDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolygonProDlg dialog


CPolygonProDlg::CPolygonProDlg(CMyPolygon* pPolygon,CWnd* pParent /*=NULL*/)
	: CDialog(CPolygonProDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPolygonProDlg)
	m_id = 0;
	//}}AFX_DATA_INIT
	this->m_pPolygon=pPolygon;
}


void CPolygonProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPolygonProDlg)
	DDX_Text(pDX, IDC_EDT_ID, m_id);
	DDV_MinMaxInt(pDX, m_id, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPolygonProDlg, CDialog)
	//{{AFX_MSG_MAP(CPolygonProDlg)
	ON_CBN_SELCHANGE(IDC_COM_STYLE, OnSelchangeComStyle)
	ON_BN_CLICKED(IDC_BTN_COLOR, OnBtnColor)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COM_TYPE, OnSelchangeComType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolygonProDlg message handlers
BOOL CPolygonProDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_id=this->m_pPolygon->m_id;
	if(this->m_pPolygon->m_logbrush.lbStyle==BS_SOLID)
	{
		((CComboBox*)GetDlgItem(IDC_COM_STYLE))->SetCurSel(0);
		m_style=BS_SOLID;
		m_color=this->m_pPolygon->m_logbrush.lbColor;
	}
	else
	{
		((CComboBox*)GetDlgItem(IDC_COM_STYLE))->SetCurSel(1);
		m_style=BS_HATCHED;
		m_color=this->m_pPolygon->m_logbrush.lbColor;
	}
	
	((CComboBox*)GetDlgItem(IDC_COM_TYPE))->EnableWindow(m_style==BS_HATCHED);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPolygonProDlg::OnSelchangeComStyle() 
{
	// TODO: Add your control notification handler code here
	
	if(((CComboBox*)GetDlgItem(IDC_COM_STYLE))->GetCurSel()==0)
	{
		m_style=BS_SOLID;
		((CComboBox*)GetDlgItem(IDC_COM_TYPE))->EnableWindow(false);
	}
	else
	{
		m_style=BS_HATCHED;
		((CComboBox*)GetDlgItem(IDC_COM_TYPE))->EnableWindow(true);
		((CComboBox*)GetDlgItem(IDC_COM_TYPE))->SetCurSel(0);
		m_type=HS_BDIAGONAL;
	}
	Invalidate();
}

void CPolygonProDlg::OnBtnColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	if(IDOK==dlg.DoModal())
	{
		m_color=dlg.m_cc.rgbResult;
		Invalidate();
	}
}

void CPolygonProDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//ÑÕÉ«¸üÐÂ
	CRect rectColor;
	((CButton*)GetDlgItem(IDC_BTN_COLOR))->GetWindowRect(rectColor);
	ScreenToClient(&rectColor);
	rectColor.left+=50;
	rectColor.right+=50;
	dc.FillRect(rectColor,&CBrush(m_color));
	//Ô¤ÀÀ
	CRect rectPreview;
	((CStatic*)GetDlgItem(IDC_S_PREVIEW))->GetWindowRect(&rectPreview);
	ScreenToClient(&rectPreview);
	rectPreview.left+=20;rectPreview.right-=20;rectPreview.top+=20;rectPreview.bottom-=20;
	CRgn rgn;
	CBrush brush;
	LOGBRUSH logbrush;
	logbrush.lbColor=m_color;logbrush.lbHatch=m_type;logbrush.lbStyle=m_style;
	brush.CreateBrushIndirect(&logbrush);
	rgn.CreateRectRgn(rectPreview.left,rectPreview.top,rectPreview.right,rectPreview.bottom);
	dc.FillRgn(&rgn,&brush);
	// Do not call CDialog::OnPaint() for painting messages
}

void CPolygonProDlg::OnSelchangeComType() 
{
	// TODO: Add your control notification handler code here
	switch(((CComboBox*)GetDlgItem(IDC_COM_TYPE))->GetCurSel())
	{
	case 0:
		m_type=HS_BDIAGONAL;
		break;
	case 1:
		m_type=HS_CROSS;
		break;
	case 2:
		m_type=HS_DIAGCROSS;
		break;
	case 3:
		m_type=HS_FDIAGONAL;
		break;
	case 4:
		m_type=HS_HORIZONTAL;
		break;
	case 5:
		m_type=HS_VERTICAL;
		break;
	}
	Invalidate();
}

void CPolygonProDlg::OnOK() 
{
	// TODO: Add extra validation here
	LOGBRUSH logbrush;
	logbrush.lbColor=m_color;logbrush.lbHatch=m_type;logbrush.lbStyle=m_style;
	this->m_pPolygon->m_logbrush=logbrush;
	this->m_pPolygon->m_IsSelected=false;
	CDialog::OnOK();
}

void CPolygonProDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	this->m_pPolygon->m_IsSelected=false;
	CDialog::OnCancel();
}
