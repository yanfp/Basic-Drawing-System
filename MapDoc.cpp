// MapDoc.cpp : implementation of the CMapDoc class
//

#include "stdafx.h"
#include "Map.h"

#include "MapDoc.h"
#include "MapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapDoc

IMPLEMENT_DYNCREATE(CMapDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapDoc, CDocument)
	//{{AFX_MSG_MAP(CMapDoc)
	ON_COMMAND(IDM_DELETESELETED, OnDeleteseleted)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapDoc construction/destruction

CMapDoc::CMapDoc()
{
	// TODO: add one-time construction code here
	//this->m_pLastSelectedLine=NULL;
}

CMapDoc::~CMapDoc()
{
}

BOOL CMapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMapDoc serialization

void CMapDoc::Serialize(CArchive& ar)
{
	//this->m_ptrArray.Serialize(ar);
	this->m_PointArray.Serialize(ar);
	this->m_LineArray.Serialize(ar);
	this->m_PlineArray.Serialize(ar);
	this->m_PolygonArray.Serialize(ar);
	this->m_TextArray.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMapDoc diagnostics

#ifdef _DEBUG
void CMapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapDoc commands
////清除缓存
void CMapDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	//清除缓存
	int nPoint=m_PointArray.GetSize();
	int nLine=m_LineArray.GetSize();
	int nPline=m_PlineArray.GetSize();
	int nPolygon=m_PolygonArray.GetSize();
	int nText=m_TextArray.GetSize();
	int i=0;
	for(i=0;i<nPoint;i++)
		delete m_PointArray.GetAt(i);
	for(i=0;i<nLine;i++)
		delete m_LineArray.GetAt(i);
	for(i=0;i<nPline;i++)
		delete m_PlineArray.GetAt(i);
	for(i=0;i<nPolygon;i++)
		delete m_PolygonArray.GetAt(i);
	for(i=0;i<nText;i++)
		delete m_TextArray.GetAt(i);
	this->m_PointArray.RemoveAll();
	this->m_LineArray.RemoveAll();
	this->m_PlineArray.RemoveAll();
	this->m_PolygonArray.RemoveAll();
	this->m_TextArray.RemoveAll();

	CDocument::DeleteContents();
}

extern float CalDist(float x1,float y1,float x2,float y2);

extern float PointLine(float xx,float yy,float x1,float y1,float x2,float y2);
CMyPoint * CMapDoc::SelectPoint(CPoint pt)
{
	int nPoint=this->m_PointArray.GetSize();
	CMyPoint *pPoint;
	for(int i=0;i<nPoint;i++)
	{
		pPoint=this->m_PointArray.GetAt(i);		
		if(2>CalDist(pt.x,pt.y,pPoint->m_pt.x,pPoint->m_pt.y))
			return pPoint;
	}
	return NULL;
}

CMyLine* CMapDoc::SelectLine(CPoint pt)
{
	int nLine=this->m_LineArray.GetSize();
	CMyLine *pLine;
	for(int i=0;i<nLine;i++)
	{
		pLine=this->m_LineArray.GetAt(i);
		if(2>PointLine(pt.x,pt.y,pLine->m_pt1.x,pLine->m_pt1.y,pLine->m_pt2.x,pLine->m_pt2.y))
		{
			//this->m_pLastSelectedLine=pLine;
			return pLine;		
		}
	}
	return NULL;
}

extern int PointPosition(CPoint pt,CPoint *pP,int number);
CMyPline* CMapDoc::SelectPline(CPoint pt)
{
	int nPline=this->m_PlineArray.GetSize();
	CMyPline *pPline;
	for(int i=0;i<nPline;i++)
	{	
		pPline=this->m_PlineArray.GetAt(i);	
		int n=PointPosition(pt,pPline->m_pt,pPline->m_ptNumber);
		if(n>-1)//如果n!=-1
		{
			CPoint pt1=pPline->m_pt[n];
			CPoint pt2=pPline->m_pt[n+1];
			if(10>PointLine(pt.x,pt.y,pt1.x,pt1.y,pt2.x,pt2.y))
				return pPline;
		}		
	}
	return NULL;
}

extern BOOL PointRgn(float x,float y,int Numble,CPoint *pPoint,float blc);
extern double scale;
CMyPolygon* CMapDoc::SelectPolygon(CPoint pt)
{
	int nPolygon=this->m_PolygonArray.GetSize();
	CMyPolygon *pPolygon;
	for(int i=0;i<nPolygon;i++)
	{
		pPolygon=this->m_PolygonArray.GetAt(i);
		if(PointRgn(pt.x,pt.y,pPolygon->m_ptNumber,pPolygon->m_pt,1))
			return pPolygon;
	}
	return NULL;
}
CMyText* CMapDoc::SelectText(CPoint pt)
{
	int nText=this->m_TextArray.GetSize();
	CMyText *pText;
	for(int i=0;i<nText;i++)
	{
		pText=this->m_TextArray.GetAt(i);		
		if(10>CalDist(pt.x,pt.y,pText->m_pt.x,pText->m_pt.y))
			return pText;
	}
	return NULL;

}

////清除选择项
void CMapDoc::ClearSelect()
{
	int nPoint=m_PointArray.GetSize();
	int nLine=m_LineArray.GetSize();
	int nPline=m_PlineArray.GetSize();
	int nPolygon=m_PolygonArray.GetSize();
	int nText=m_TextArray.GetSize();
	int i=0;
	for(i=0;i<nPoint;i++)
		if(this->m_PointArray.GetAt(i)->m_IsSelected)
			this->m_PointArray.GetAt(i)->m_IsSelected=false;
	for(i=0;i<nLine;i++)
		if(this->m_LineArray.GetAt(i)->m_IsSelected)
			this->m_LineArray.GetAt(i)->m_IsSelected=false;
	for(i=0;i<nPline;i++)
		if(this->m_PlineArray.GetAt(i)->m_IsSelected)
			this->m_PlineArray.GetAt(i)->m_IsSelected=false;
	for(i=0;i<nPolygon;i++)
		if(this->m_PolygonArray.GetAt(i)->m_IsSelected)
			this->m_PolygonArray.GetAt(i)->m_IsSelected=false;
	for(i=0;i<nText;i++)
		if(this->m_TextArray.GetAt(i)->m_IsSelected)
			this->m_TextArray.GetAt(i)->m_IsSelected=false;

}

CPoint* CMapDoc::SeekPoint(CPoint pt)
{
	int nPoint=m_PointArray.GetSize();
	int nLine=m_LineArray.GetSize();
	int nPline=m_PlineArray.GetSize();
	int nPolygon=m_PolygonArray.GetSize();
	int nText=m_TextArray.GetSize();
	int i=0;
	CMyPoint* pPoint;
	for(i=0;i<nPoint;i++)
	{
		pPoint=this->m_PointArray.GetAt(i);	
		if(10>CalDist(pt.x,pt.y,pPoint->m_pt.x,pPoint->m_pt.y))
		{
			return &pPoint->m_pt;
		}
	}
	CMyLine* pLine;
	for(i=0;i<nLine;i++)
	{
		pLine=this->m_LineArray.GetAt(i);
		if(10>CalDist(pt.x,pt.y,pLine->m_pt1.x,pLine->m_pt1.y))
		{
			return &pLine->m_pt1;
		}
		if(10>CalDist(pt.x,pt.y,pLine->m_pt2.x,pLine->m_pt2.y))
		{
			return &pLine->m_pt2;
		}
	}
	
	CMyPline* pPline;
	for(i=0;i<nPline;i++)
	{
		pPline=this->m_PlineArray.GetAt(i);
		for(int j=0;j<pPline->m_ptNumber;j++)
		{
			CPoint ptTemp=pPline->m_pt[j];
			if(10>CalDist(pt.x,pt.y,ptTemp.x,ptTemp.y))
				return &pPline->m_pt[j];
		}
	}
	CMyPolygon* pPolygon;
	for(i=0;i<nPolygon;i++)
	{
		pPolygon=this->m_PolygonArray.GetAt(i);
		for(int j=0;j<pPolygon->m_ptNumber;j++)
		{
			CPoint ptTemp=pPolygon->m_pt[j];
			if(10>CalDist(pt.x,pt.y,ptTemp.x,ptTemp.y))
				return &pPolygon->m_pt[j];
		}
	}	
	return NULL;
}

CDraw* CMapDoc::SeekObject(CPoint pt)
{
	CMyPoint* pPoint=this->SelectPoint(pt);
	if(pPoint)
		return pPoint;
	CMyLine* pLine=this->SelectLine(pt);
	if(pLine)
		return pLine;
	CMyPline* pPline=this->SelectPline(pt);
	if(pPline)
		return pPline;
	CMyPolygon* pPolygon=this->SelectPolygon(pt);
	if(pPolygon)
		return pPolygon;
	return NULL;
}

void CMapDoc::OnDraw(CDC *pDC)
{
	int nPoint=this->m_PointArray.GetSize();
	int nLine=this->m_LineArray.GetSize();
	int nPline=this->m_PlineArray.GetSize();
	int nPolygon=this->m_PolygonArray.GetSize();
	int nText=this->m_TextArray.GetSize();
	int i=0;
	for(i=0;i<nPoint;i++)
		this->m_PointArray.GetAt(i)->Draw(pDC);
	for(i=0;i<nLine;i++)
		this->m_LineArray.GetAt(i)->Draw(pDC);
	for(i=0;i<nPline;i++)
		this->m_PlineArray.GetAt(i)->Draw(pDC);
	for(i=0;i<nPolygon;i++)
		this->m_PolygonArray.GetAt(i)->Draw(pDC);
	for(i=0;i<nText;i++)
		this->m_TextArray.GetAt(i)->Draw(pDC);
}
//删除选中项菜单函数
void CMapDoc::OnDeleteseleted() 
{
	// TODO: Add your command handler code here
	int nPoint=this->m_PointArray.GetSize();
	int nLine=this->m_LineArray.GetSize();
	int nPline=this->m_PlineArray.GetSize();
	int nPolygon=this->m_PolygonArray.GetSize();
	int nText=this->m_TextArray.GetSize();
	int i=0;
	for(i=0;i<nPoint;i++)
		this->m_PointArray.GetAt(i)->m_IsDeleted=this->m_PointArray.GetAt(i)->m_IsSelected;
	for(i=0;i<nLine;i++)
		this->m_LineArray.GetAt(i)->m_IsDeleted=this->m_LineArray.GetAt(i)->m_IsSelected;
	for(i=0;i<nPline;i++)
		this->m_PlineArray.GetAt(i)->m_IsDeleted=this->m_PlineArray.GetAt(i)->m_IsSelected;
	for(i=0;i<nPolygon;i++)
		this->m_PolygonArray.GetAt(i)->m_IsDeleted=this->m_PolygonArray.GetAt(i)->m_IsSelected;
	for(i=0;i<nText;i++)
		this->m_TextArray.GetAt(i)->m_IsDeleted=this->m_TextArray.GetAt(i)->m_IsSelected;

	//文档类获取视图类的方法
	POSITION pos=GetFirstViewPosition();
	CMapView *pView=(CMapView*)GetNextView(pos);
	pView->Invalidate();	
}
