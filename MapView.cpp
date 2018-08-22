// MapView.cpp : implementation of the CMapView class
//

#include "stdafx.h"
#include "Map.h"

#include "MapDoc.h"
#include "MapView.h"
#include "Mainfrm.h"

#include "TextDlg.h"
#include "LineProDlg.h"
#include "PolygonProDlg.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapView

IMPLEMENT_DYNCREATE(CMapView, CScrollView)

BEGIN_MESSAGE_MAP(CMapView, CScrollView)
	//{{AFX_MSG_MAP(CMapView)
	ON_COMMAND(DRAW_POINT, OnPoint)
	ON_COMMAND(DRAW_LINE, OnLine)
	ON_COMMAND(DRAW_PLINE, OnPline)
	ON_COMMAND(DRAW_POLYGON, OnPolygon)
	ON_UPDATE_COMMAND_UI(DRAW_POINT, OnUpdatePoint)
	ON_UPDATE_COMMAND_UI(DRAW_LINE, OnUpdateLine)
	ON_UPDATE_COMMAND_UI(DRAW_PLINE, OnUpdatePline)
	ON_UPDATE_COMMAND_UI(DRAW_POLYGON, OnUpdatePolygon)
	ON_COMMAND(DRAW_TEXT, OnText)
	ON_UPDATE_COMMAND_UI(DRAW_TEXT, OnUpdateText)
	ON_COMMAND(DRAWNONE, OnDRAWNONE)
	ON_UPDATE_COMMAND_UI(DRAWNONE, OnUpdateDRAWNONE)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_COMMAND(IDR_ZOOMIN, OnZoomin)
	ON_UPDATE_COMMAND_UI(IDR_ZOOMIN, OnUpdateZoomin)
	ON_COMMAND(IDR_ZOOMOUT, OnZoomout)
	ON_UPDATE_COMMAND_UI(IDR_ZOOMOUT, OnUpdateZoomout)
	ON_COMMAND(IDR_PAN, OnPan)
	ON_UPDATE_COMMAND_UI(IDR_PAN, OnUpdatePan)
	ON_COMMAND(IDR_MAPRESET, OnMapreset)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_COMMAND(IDM_SELECTLINE, OnSelectline)
	ON_UPDATE_COMMAND_UI(IDM_SELECTLINE, OnUpdateSelectline)
	ON_COMMAND(IDM_SELECTPOINT, OnSelectpoint)
	ON_UPDATE_COMMAND_UI(IDM_SELECTPOINT, OnUpdateSelectpoint)
	ON_COMMAND(IDM_SELECTPLINE, OnSelectpline)
	ON_UPDATE_COMMAND_UI(IDM_SELECTPLINE, OnUpdateSelectpline)
	ON_COMMAND(IDM_SELECTPOLYGON, OnSelectpolygon)
	ON_UPDATE_COMMAND_UI(IDM_SELECTPOLYGON, OnUpdateSelectpolygon)
	ON_COMMAND(IDM_SELECTTEXT, OnSelecttext)
	ON_UPDATE_COMMAND_UI(IDM_SELECTTEXT, OnUpdateSelecttext)
	ON_COMMAND(IDM_CHANGELINE, OnChangeline)
	ON_UPDATE_COMMAND_UI(IDM_CHANGELINE, OnUpdateChangeline)
	ON_COMMAND(IDM_CLEARSELECT, OnClearselect)
	ON_COMMAND(IDM_CHANGEPOLYGON, OnChangepolygon)
	ON_UPDATE_COMMAND_UI(IDM_CHANGEPOLYGON, OnUpdateChangepolygon)
	ON_COMMAND(IDM_CHANGEPOINT, OnChangepoint)
	ON_COMMAND(IDM_CHANGEPLINE, OnChangepline)
	ON_UPDATE_COMMAND_UI(IDM_CHANGEPLINE, OnUpdateChangepline)
	ON_UPDATE_COMMAND_UI(IDM_CHANGEPOINT, OnUpdateChangepoint)
	ON_COMMAND(IDM_CHANGE_TEXT, OnChangeText)
	ON_COMMAND(IDM_SET_DEFAULT, OnSetDefault)
	ON_WM_SIZE()
	ON_COMMAND(IDM_REFRESH, OnRefresh)
	ON_COMMAND(IDM_RESET, OnReset)
	ON_COMMAND(ID_CATCH, OnCatch)
	ON_UPDATE_COMMAND_UI(ID_CATCH, OnUpdateCatch)
	ON_COMMAND(IDR_REDRAW, OnRedraw)
	ON_COMMAND(ID_MOVE_OBJECT, OnMoveObject)
	ON_UPDATE_COMMAND_UI(ID_MOVE_OBJECT, OnUpdateMoveObject)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()


CPoint ptStart=0;//起始点
double scale=1.00;//当前比例
int clientX,clientY;//客户区宽，高

void DPtoAP(CPoint &pt)//设备坐标转换成实际坐标
{
	pt.x=(int)((pt.x-ptStart.x)/scale+0.5);
	pt.y=(int)(clientY-(pt.y-ptStart.y)/scale+0.5);
}

void APtoDP(CPoint &pt)//实际坐标转换成设备坐标
{
	pt.x=(int)(ptStart.x+pt.x*scale+0.5);
	pt.y=(int)(ptStart.y+(clientY-pt.y)*scale+0.5);
}
/////////////////////////////////////////////////////////////////////////////
// CMapView construction/destruction
void CMapView::SetCurDraw(COLORREF color,int width,int style)
{
	m_myPoint.m_color=color;
	m_myLine.m_color=color;m_myLine.m_width=width;m_myLine.m_style=style;
	m_myPline.m_color=color;m_myPline.m_width=width;m_myPline.m_style=style;
	m_myText.m_color=color;

}

CMapView::CMapView()
{
	// TODO: add construction code here
	SetScrollSizes(MM_TEXT,CSize(1400,700));
	m_Command=0;
	this->m_CurScrollPosV=0;
	this->m_CurScrollPosH=0;
	m_IsCatched=false;
	m_CatchType=0;
	this->m_pMoveObject=NULL;
}

CMapView::~CMapView()
{
}

BOOL CMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CScrollView::PreCreateWindow(cs);
}

void CMapView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class	
	CScrollView::OnBeginPrinting(pDC, pInfo);
}

BOOL CMapView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	return DoPreparePrinting(pInfo);
}

void CMapView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnEndPrinting(pDC, pInfo);
}
/////////////////////////////////////////////////////////////////////////////
// CMapView drawing
void CMapView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnPrepareDC(pDC, pInfo);
}

void CMapView::OnDraw(CDC* pDC)
{
	CMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//CPoint pt=pDC->GetViewportOrg();
	pDC->SetViewportOrg(CPoint(0,0));
	//////////////冲绘代码//////////////////////
	pDoc->OnDraw(pDC);
	///////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CMapView diagnostics

#ifdef _DEBUG
void CMapView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMapDoc* CMapView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapDoc)));
	return (CMapDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapView message handlers

void CMapView::OnLine() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=2;
}

void CMapView::OnUpdateLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==2);
}

void CMapView::OnPline() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=3;
}

void CMapView::OnUpdatePline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==3);
}

void CMapView::OnPoint() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=1;
}

void CMapView::OnUpdatePoint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==1);
}

void CMapView::OnPolygon() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=4;
}

void CMapView::OnUpdatePolygon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==4);
}

void CMapView::OnText() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=5;
}

void CMapView::OnUpdateText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==5);
}


void CMapView::OnDRAWNONE() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=0;
}

void CMapView::OnUpdateDRAWNONE(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==0);
}


///鼠标消息
//鼠标左键按下
void CMapView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(m_CatchType==1)
	{
		if(this->m_IsCatched && this->m_pCatchedPoint)
		{
			CPoint TempPt=*this->m_pCatchedPoint;
			APtoDP(TempPt);
			point=TempPt;
		}
	}

	this->m_ptOrigin=point;
	this->m_ptOld=m_ptOrigin;
	CPoint OldPoint=point;//保存未转换坐标前的设备坐标
	////设备坐标转换成逻辑坐标////
	DPtoAP(point);
	///////////////////////////////
	CClientDC dc(this);
	//dc.SetMapMode(MM_LOMETRIC);
	//dc.DPtoAP(&point);
	switch(m_Command)
	{
	case DRAWPOINT:
		this->m_myPoint.Add(point)->Draw(&dc);
		break;
	case DRAWLINE:
		this->m_myLine.Add(point);
		break;
	case DRAWPLINE:
		this->m_myPline.Add(point);
		break;
	case DRAWPOLYGON:
		this->m_myPolygon.Add(point);
		break;
	case DRAWTEXT:
		{
			CTextDlg textDlg;
			if(textDlg.DoModal()==IDOK)
			{	
				m_myText.m_str=textDlg.m_str;
				m_myText.Add(point)->Draw(&dc);
				this->GetDocument()->m_TextArray.Add(m_myText.GetGraph(GetDocument()->m_TextArray.GetSize()));
			}		
		}
		break;
	//地图操作命令
	case MAP_PAN:
	case MAP_ZOOMIN:
	case MAP_ZOOMOUT:
		m_operateMap.m_command=m_Command;
		m_operateMap.m_pt1=OldPoint;
		break;
	//以下是选择命令
	case SELECT_POINT:
		{
			CMyPoint *pPoint=this->GetDocument()->SelectPoint(point);
			if(pPoint)
			{
				pPoint->m_IsSelected=true;
				Invalidate();
			}	
		}
		break;
	case SELECT_LINE:
		{
			CMyLine *pLine=this->GetDocument()->SelectLine(point);
			if(pLine)
			{	
				pLine->m_IsSelected=true;
				Invalidate();
			}			
		}
		break;
	case SELECT_PLINE:
		{
			CMyPline *pPline=this->GetDocument()->SelectPline(point);
			if(pPline)
			{
				pPline->m_IsSelected=true;
				Invalidate();
			}		
		}
		break;
	case SELECT_POLYGON:
		{
			CMyPolygon *pPolygon=this->GetDocument()->SelectPolygon(point);
			if(pPolygon)
			{
				pPolygon->m_IsSelected=true;
				pPolygon->Draw(&dc);
			}		
		}
		break;
	case SELECT_TEXT:
		{
			CMyText* pText=this->GetDocument()->SelectText(point);
			if(pText)
			{
				pText->m_IsSelected=true;
				Invalidate();
			}
		}
		break;
	//修改参数命令
	case CHANGE_LINE:
		{
			CMyLine *pLine=this->GetDocument()->SelectLine(point);
			if(pLine)
			{
				pLine->m_IsSelected=true;pLine->Draw(&dc);
				CLineProDlg line(pLine);
				line.DoModal();
				Invalidate();
			}
		}
		break;
	case CHANGE_POLYGON:
		{
			CMyPolygon *pPolygon=this->GetDocument()->SelectPolygon(point);
			if(pPolygon)
			{
				pPolygon->m_IsSelected=true;pPolygon->Draw(&dc);
				CPolygonProDlg polygon(pPolygon);
				polygon.DoModal();
				Invalidate();
			}
		}
		break;
	case CHANGE_PLINE:
		{
			CMyPline* pPline=this->GetDocument()->SelectPline(point);
			if(pPline)
			{
				pPline->m_IsSelected=true;pPline->Draw(&dc);
				CLineProDlg line(pPline);
				line.DoModal();
				Invalidate();
			}

		}
		break;
	case MOVE_OBJECT:
		{
			CDraw* pDraw=this->GetDocument()->SeekObject(point);
			if(pDraw!=NULL)
				this->m_pMoveObject=pDraw;
			else
				return;	
		}
		break;
	}
	APtoDP(point);
	CScrollView::OnLButtonDown(nFlags, point);
}
//鼠标左键松开
void CMapView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//m_ptOld=point;

	CPoint OldPoint=point;//保存未转换坐标前的设备坐标

	/******捕捉坐标******/
	if(m_CatchType==1)
	{
		if(this->m_IsCatched && this->m_pCatchedPoint)
		{
			CPoint TempPt=*this->m_pCatchedPoint;
			APtoDP(TempPt);
			point=TempPt;
		}
	}
	////设备坐标转换成逻辑坐标////
	DPtoAP(point);
	///////////////////////////////
	CClientDC dc(this);
	if(m_Command==DRAWPOINT)
		this->GetDocument()->m_PointArray.Add(m_myPoint.GetGraph(GetDocument()->m_PointArray.GetSize()));
	if(m_Command==DRAWLINE)
	{
		if(m_myLine.m_flag==1)
		{
			m_myLine.Add(point);
			this->GetDocument()->m_LineArray.Add(m_myLine.GetGraph(GetDocument()->m_LineArray.GetSize()));
		}
		else
			m_myLine.Clear();
	}
	if(m_Command==MAP_ZOOMIN || m_Command==MAP_ZOOMOUT || m_Command==MAP_PAN)
	{
		m_operateMap.m_pt2=OldPoint;
		m_operateMap.SetMap(ptStart,scale,clientX,clientY);
		Invalidate();
	}
	if(this->m_Command==MOVE_OBJECT && this->m_pMoveObject)
	{
		if(m_pMoveObject->IsKindOf(RUNTIME_CLASS(CMyLine)))
		{
			CMyLine* pLine=(CMyLine*)m_pMoveObject;
			pLine->m_pt1.x+=OldPoint.x-m_ptOrigin.x;
			pLine->m_pt1.y+=m_ptOrigin.y-OldPoint.y;
			pLine->m_pt2.x+=OldPoint.x-m_ptOrigin.x;
			pLine->m_pt2.y+=m_ptOrigin.y-OldPoint.y;
			pLine->Draw(&dc);
			this->m_pMoveObject=NULL;
			this->Invalidate();
		}
	}
	CScrollView::OnLButtonUp(nFlags, point);
}


//鼠标移动
void CMapView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptDevice=point;

	if(this->m_CatchType==1)
	{
		if(m_IsCatched && this->m_pCatchedPoint)
		{
			CPoint TempPt=*this->m_pCatchedPoint;
			APtoDP(TempPt);
			point=TempPt;
		}
	}
	CClientDC dc(this);
	dc.SetROP2(R2_NOT);
	BOOL IsDrawingLine=(nFlags==MK_LBUTTON && m_myLine.m_flag==1);//判断是否在画直线

	if(m_myPline.m_ptNumber>0 ||m_myPolygon.m_ptNumber>0 ||IsDrawingLine)
	{
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOld=point;
	}
	if(m_Command==MOVE_OBJECT && nFlags==MK_LBUTTON)
	{
		if(this->m_pMoveObject)
		{
			if(m_pMoveObject->IsKindOf(RUNTIME_CLASS(CMyLine)))
			{
				((CMyLine*)m_pMoveObject)->Draw(&dc);
				CMyLine line,line2;
				line=*((CMyLine*)m_pMoveObject);
				line2=*((CMyLine*)m_pMoveObject);

				line.m_pt1.x+=point.x-m_ptOrigin.x;
				line.m_pt1.y+=m_ptOrigin.y-point.y;
				line.m_pt2.x+=point.x-m_ptOrigin.x;
				line.m_pt2.y+=m_ptOrigin.y-point.y;
				line.Draw(&dc);

				line2.m_pt1.x+=m_ptOld.x-m_ptOrigin.x;
				line2.m_pt1.y+=m_ptOrigin.y-m_ptOld.y;
				line2.m_pt2.x+=m_ptOld.x-m_ptOrigin.x;
				line2.m_pt2.y+=m_ptOrigin.y-m_ptOld.y;
				line2.Draw(&dc);
				m_ptOld=point;
			}
		}

	}
	if(m_operateMap.m_command==MAP_ZOOMIN||m_operateMap.m_command==MAP_ZOOMOUT)
	{	
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		dc.SelectObject(pBrush);
		dc.Rectangle(CRect(m_ptOrigin,m_ptOld));
		dc.Rectangle(CRect(m_ptOrigin,point));
		m_ptOld=point;
	}
	DPtoAP(ptDevice);
	if(this->m_CatchType==1)
	{
		/*************捕捉效果**********************/
		static int flag=0;
		static CPoint ptFormer;
		CPoint* pPt=this->GetDocument()->SeekPoint(ptDevice);
		if(pPt)
		{	
			m_IsCatched=true;
			this->m_pCatchedPoint=pPt;
			CPoint CatchedPt=*pPt;	
			APtoDP(CatchedPt);
			ptFormer=CatchedPt;
			//ClientToScreen(&point);
			//SetCursorPos(point.x,point.y);
			//CRect rect(point.x-30,point.y-30,point.x+30,point.y+30);	
			++flag%=2;
			CClientDC dc2(this);
			//dc2.SetROP2(R2_NOT);
			CPen pen(0,1,RGB(100,100,100));
			CBrush *pBrush2=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			dc2.SelectObject(pBrush2);
			dc2.SelectObject(&pen);
			dc2.Rectangle(CatchedPt.x-10,CatchedPt.y-10,CatchedPt.x+10,CatchedPt.y+10);
			//if(flag%2==0)
			//{
			//	dc2.Rectangle(CatchedPt.x-10,CatchedPt.y-10,CatchedPt.x+10,CatchedPt.y+10);
			//}
		}
		else
		{
			if(m_IsCatched)
			{
				CClientDC dc3(this);
				CPen pen(0,1,RGB(255,255,255));
				CBrush *pBrush2=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				dc3.SelectObject(pBrush2);
				dc3.SelectObject(&pen);
				dc3.Rectangle(ptFormer.x-10,ptFormer.y-10,ptFormer.x+10,ptFormer.y+10);
			}
			m_IsCatched=false;
			this->m_pCatchedPoint=NULL;
		}
	}

	//状态栏上显示坐标
	CString str;
	str.Format("x=%d,y=%d",ptDevice.x,ptDevice.y);
	CMainFrame* pMainFrm;
	pMainFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMainFrm->m_wndStatusBar.SetWindowText(str);

	CScrollView::OnMouseMove(nFlags, point);
}

//鼠标右键按下
void CMapView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_Command==0)
	{
		CMenu menu;
		if(menu.LoadMenu(IDR_RBUTTONMENU))
		{
			CMenu* pMenu=menu.GetSubMenu(0);
			ClientToScreen(&point);
			pMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
		
		}
		return;
	}
	CClientDC dc(this);
	dc.SetROP2(R2_NOT);
	if(m_Command==DRAWPLINE)
	{		
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		if(m_myPline.m_ptNumber>1)
			this->GetDocument()->m_PlineArray.Add(m_myPline.GetGraph(GetDocument()->m_PlineArray.GetSize()));
		return;
	}
	if(m_Command==DRAWPOLYGON)
	{		
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);		
		if(m_myPolygon.m_ptNumber>2)
		{
			CClientDC dc2(this);
			m_myPolygon.Draw(&dc2);
			Invalidate();//重绘
			this->GetDocument()->m_PolygonArray.Add(m_myPolygon.GetGraph(GetDocument()->m_PolygonArray.GetSize()));
		}
		else
		{
			m_myPolygon.Clear();
			Invalidate();//重绘
		}
		return;
	}
	CScrollView::OnRButtonDown(nFlags, point);
}
//设置光标
BOOL CMapView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_Command==0)
		SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR,(LONG)LoadCursor(NULL,IDC_ARROW));
	if(m_Command>0 && m_Command<11)
		SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR,(LONG)LoadCursor(NULL,IDC_CROSS));
	if(m_Command==MAP_PAN)
	{
		m_hCurrentCur=LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR1));
		::SetCursor(m_hCurrentCur);
		return NULL;//注意这一句
	}
	
	if(m_Command==MAP_ZOOMIN)
	{
		m_hCurrentCur=LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR2));
		::SetCursor(m_hCurrentCur);
		return NULL;

	}
	if(m_Command==MAP_ZOOMOUT)
	{
		m_hCurrentCur=LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR3));
		::SetCursor(m_hCurrentCur);
		return NULL;
	}

	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}
//判断是否正在绘图
BOOL CMapView::IsDrawing()
{
	if(m_myLine.m_flag==1 || m_myPline.m_ptNumber>0 || m_myPolygon.m_ptNumber>0)
		return true;
	else
		return false;
}

//放大
void CMapView::OnZoomin() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=12;
	
}

void CMapView::OnUpdateZoomin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==12);
}

void CMapView::OnZoomout() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=13;
	
}

void CMapView::OnUpdateZoomout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==13);
}

void CMapView::OnPan() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=11;	
}

void CMapView::OnUpdatePan(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==11);
}

void CMapView::OnMapreset() 
{
	// TODO: Add your command handler code here
	scale=1;
	ptStart=0;
	Invalidate();
}

//垂直滚动条
void CMapView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(nSBCode==SB_THUMBPOSITION)
	{
		ptStart.y-=(int)nPos-m_CurScrollPosV;
		this->m_CurScrollPosV=nPos;
		Invalidate();
	}
	
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}
//水平滚动条
void CMapView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(nSBCode==SB_THUMBPOSITION)
	{
		ptStart.x-=(int)nPos-m_CurScrollPosH;
		this->m_CurScrollPosH=nPos;
		Invalidate();
	}
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


//选择
void CMapView::OnSelectpoint() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=SELECT_POINT;
}

void CMapView::OnUpdateSelectpoint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==SELECT_POINT);
}

void CMapView::OnSelectline() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=SELECT_LINE;
}

void CMapView::OnUpdateSelectline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==SELECT_LINE);
}



void CMapView::OnSelectpline() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=SELECT_PLINE;
}

void CMapView::OnUpdateSelectpline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==SELECT_PLINE);
}

void CMapView::OnSelectpolygon() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=SELECT_POLYGON;
}

void CMapView::OnUpdateSelectpolygon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==SELECT_POLYGON);
}

void CMapView::OnSelecttext() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=SELECT_TEXT;
}

void CMapView::OnUpdateSelecttext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==SELECT_TEXT);
}


void CMapView::OnChangeline() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		m_Command=CHANGE_LINE;
}

void CMapView::OnUpdateChangeline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==CHANGE_LINE);
}

void CMapView::OnClearselect() 
{
	// TODO: Add your command handler code here
	
	


	this->GetDocument()->ClearSelect();
	Invalidate();
}

void CMapView::OnChangepolygon() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		this->m_Command=CHANGE_POLYGON;
}

void CMapView::OnUpdateChangepolygon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==CHANGE_POLYGON);
}

void CMapView::OnChangepoint() 
{
	// TODO: Add your command handler code here

	//Invalidate();
}
void CMapView::OnUpdateChangepoint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
void CMapView::OnChangepline() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		this->m_Command=CHANGE_PLINE;
}

void CMapView::OnUpdateChangepline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==CHANGE_PLINE);
}



void CMapView::OnChangeText() 
{
	// TODO: Add your command handler code here
	GetDocument()->SetModifiedFlag(1);
	Invalidate();
}

void CMapView::OnSetDefault() 
{
	// TODO: Add your command handler code here
	
}

void CMapView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	clientX=cx;
	clientY=cy;
	// TODO: Add your message handler code here
	
}

void CMapView::OnRefresh() 
{
	// TODO: Add your command handler code here
	this->Invalidate();
}

void CMapView::OnReset() 
{
	// TODO: Add your command handler code here
	ptStart=0;
	scale=1;
	this->Invalidate();
}

void CMapView::OnCatch() 
{
	// TODO: Add your command handler code here
	++m_CatchType%=2;
}

void CMapView::OnUpdateCatch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_CatchType==1);
}

void CMapView::OnRedraw() 
{
	// TODO: Add your command handler code here
	this->Invalidate();
}

void CMapView::OnMoveObject() 
{
	// TODO: Add your command handler code here
	if(!IsDrawing())
		this->m_Command=MOVE_OBJECT;
}

void CMapView::OnUpdateMoveObject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Command==MOVE_OBJECT);
}
