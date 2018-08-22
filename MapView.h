// MapView.h : interface of the CMapView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPVIEW_H__149CE476_0366_401B_80C0_AEB3E81DD1D5__INCLUDED_)
#define AFX_MAPVIEW_H__149CE476_0366_401B_80C0_AEB3E81DD1D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define DRAWPOINT 1
#define DRAWLINE 2
#define DRAWPLINE 3
#define DRAWPOLYGON 4
#define DRAWTEXT 5

#define MAP_PAN 11
#define MAP_ZOOMIN 12
#define MAP_ZOOMOUT 13
#define MAP_RESET 14

#define SELECT_POINT 21
#define SELECT_LINE 22
#define SELECT_PLINE 23
#define SELECT_POLYGON 24
#define SELECT_TEXT 25

#define CHANGE_POINT 31
#define CHANGE_LINE 32
#define CHANGE_PLINE 33
#define CHANGE_POLYGON 34
#define CHNAGE_TEXT 35
#define MOVE_OBJECT 36


#include "MyPline.h"
#include "MyPolygon.h"
#include "MyPoint.h"
#include "MyLine.h"
#include "MyText.h"
#include "OperateMap.h"

class CMapView : public CScrollView
{
protected: // create from serialization only
	CMapView();
	DECLARE_DYNCREATE(CMapView)

// Attributes
public:
	CMapDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMapView)	
	afx_msg void OnPoint();
	afx_msg void OnLine();
	afx_msg void OnPline();
	afx_msg void OnPolygon();
	afx_msg void OnUpdatePoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePline(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePolygon(CCmdUI* pCmdUI);
	afx_msg void OnText();
	afx_msg void OnUpdateText(CCmdUI* pCmdUI);
	afx_msg void OnDRAWNONE();
	afx_msg void OnUpdateDRAWNONE(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnZoomin();
	afx_msg void OnUpdateZoomin(CCmdUI* pCmdUI);
	afx_msg void OnZoomout();
	afx_msg void OnUpdateZoomout(CCmdUI* pCmdUI);
	afx_msg void OnPan();
	afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
	afx_msg void OnMapreset();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelectline();
	afx_msg void OnUpdateSelectline(CCmdUI* pCmdUI);
	afx_msg void OnSelectpoint();
	afx_msg void OnUpdateSelectpoint(CCmdUI* pCmdUI);
	afx_msg void OnSelectpline();
	afx_msg void OnUpdateSelectpline(CCmdUI* pCmdUI);
	afx_msg void OnSelectpolygon();
	afx_msg void OnUpdateSelectpolygon(CCmdUI* pCmdUI);
	afx_msg void OnSelecttext();
	afx_msg void OnUpdateSelecttext(CCmdUI* pCmdUI);
	afx_msg void OnChangeline();
	afx_msg void OnUpdateChangeline(CCmdUI* pCmdUI);
	afx_msg void OnClearselect();
	afx_msg void OnChangepolygon();
	afx_msg void OnUpdateChangepolygon(CCmdUI* pCmdUI);
	afx_msg void OnChangepoint();
	afx_msg void OnChangepline();
	afx_msg void OnUpdateChangepline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChangepoint(CCmdUI* pCmdUI);
	afx_msg void OnChangeText();
	afx_msg void OnSetDefault();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRefresh();
	afx_msg void OnReset();
	afx_msg void OnCatch();
	afx_msg void OnUpdateCatch(CCmdUI* pCmdUI);
	afx_msg void OnRedraw();
	afx_msg void OnMoveObject();
	afx_msg void OnUpdateMoveObject(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL IsDrawing();
	int m_Command;//画图类型
	CMyPline m_myPline;//画多段线对象
	CMyPolygon m_myPolygon;//画多边形对象
	CMyPoint m_myPoint;
	CMyLine m_myLine;
	CMyText m_myText;
	COperateMap m_operateMap;//地图操作对象

	CPoint m_ptOrigin;//原始点
	CPoint m_ptOld;//当前点

	////捕捉用变量
	int m_CatchType;
	CPoint* m_pCatchedPoint;
	BOOL m_IsCatched;

	//移动对象
	CDraw* m_pMoveObject;
	
private:
	HCURSOR m_hCurrentCur;//鼠标形状
	
	int m_CurScrollPosV;
	int	m_CurScrollPosH;
private:
	
	
public:
	void SetCurDraw(COLORREF color,int width,int style);

};

#ifndef _DEBUG  // debug version in MapView.cpp
inline CMapDoc* CMapView::GetDocument()
   { return (CMapDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPVIEW_H__149CE476_0366_401B_80C0_AEB3E81DD1D5__INCLUDED_)

