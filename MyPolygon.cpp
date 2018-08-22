// MyPolygon.cpp: implementation of the CMyPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "MyPolygon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CMyPolygon,CObject,1)
CMyPolygon::CMyPolygon()
{
	m_ptNumber=0;
	m_RegionMode=WINDING;
	//m_brush.CreateSolidBrush(RGB(255,0,0));
	//m_brush.CreateHatchBrush(HS_VERTICAL,RGB(255,0,0));
	m_logbrush.lbColor=RGB(255,0,0);
	m_logbrush.lbStyle=BS_SOLID;
	m_logbrush.lbHatch=HS_BDIAGONAL;
}

CMyPolygon::~CMyPolygon()
{

}
extern void APtoDP(CPoint &pt);
void CMyPolygon::Draw(CDC *pDC)
{	
	////坐标转换////
	CPoint *pt=new CPoint[m_ptNumber];
	for(int j=0;j<m_ptNumber;j++)
	{
		pt[j]=m_pt[j];
		APtoDP(pt[j]);
	}
	////////////////

	if(!this->m_IsDeleted)
	{
		pDC->MoveTo(pt[0]);
		for(int i=1;i<m_ptNumber;i++)
		{
			pDC->LineTo(pt[i]);		
		}
		pDC->LineTo(pt[0]);
		CRgn rgn;
		CBrush brush;
		brush.CreateBrushIndirect(&m_logbrush);
		if(rgn.CreatePolygonRgn(pt,m_ptNumber,m_RegionMode))
			pDC->FillRgn(&rgn,&brush);

		if(this->m_IsSelected)//如果被选中
		{		
			pDC->MoveTo(pt[0]);
			for(int i=1;i<m_ptNumber;i++)
			{
				pDC->LineTo(pt[i]);		
			}
			pDC->LineTo(pt[0]);
			CRgn rgn;
			CBrush brush;
			brush.CreateSolidBrush(RGB(0,255,0));
			if(rgn.CreatePolygonRgn(pt,m_ptNumber,m_RegionMode))
				pDC->FillRgn(&rgn,&brush);
		}
	}
	
	delete pt;//清除内存
}

CMyPolygon* CMyPolygon::Add(CPoint pt)
{
	m_pt[m_ptNumber++]=pt;
	return this;
}

CMyPolygon* CMyPolygon::GetGraph(int id)
{
	CMyPolygon *temp=new CMyPolygon();
	temp->m_id=id;
	temp->m_logbrush=this->m_logbrush;
	temp->m_ptNumber=this->m_ptNumber;
	for(int i=0;i<this->m_ptNumber;i++)
	{
		temp->m_pt[i]=this->m_pt[i];
	}
	temp->m_RegionMode=this->m_RegionMode;
	this->Clear();
	return temp;
}

void CMyPolygon::Clear()
{
	for(int i=0;i<m_ptNumber;i++)
	{
		this->m_pt[i]=0;
	}
	this->m_ptNumber=0;	
}

void CMyPolygon::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		if(!this->m_IsDeleted)
		{
			ar<<m_id<<m_ptNumber;
			for(int i=0;i<m_ptNumber;i++)
				ar<<m_pt[i];
			ar<<m_RegionMode<<m_logbrush.lbColor<<m_logbrush.lbHatch<<m_logbrush.lbStyle;
		}
	}
	else
	{		
		ar>>m_id>>m_ptNumber;
		for(int i=0;i<m_ptNumber;i++)
			ar>>m_pt[i];
		ar>>m_RegionMode>>m_logbrush.lbColor>>m_logbrush.lbHatch>>m_logbrush.lbStyle;
	}

}
