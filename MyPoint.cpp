// MyPoint.cpp: implementation of the CMyPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "MyPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMyPoint,CObject,1)
CMyPoint::CMyPoint()
{
	this->m_width=1;
	this->m_color=RGB(0,0,0);
}

CMyPoint::CMyPoint(int width,COLORREF color)
{
	this->m_width=width;
	this->m_color=color;
}

CMyPoint::~CMyPoint()
{

}
extern void APtoDP(CPoint &pt);
void CMyPoint::Draw(CDC *pDC)
{
	////坐标转换////
	CPoint pt;
	pt=m_pt;
	APtoDP(pt);
	///////////////
	//pDC->SetMapMode(MM_LOMETRIC);
	//pDC->DPtoLP(&pt);
	
	if(!this->m_IsDeleted)//如果没被删除
	{
		for(int i=-m_width;i<m_width+1;i++)
		{
			for(int j=-m_width;j<m_width+1;j++)
			{
				pDC->SetPixel(pt.x+i,pt.y+j,m_color);
			}
		}

		if(this->m_IsSelected)//如果被选中
		{
			for(int i=-m_width;i<m_width+1;i++)
			{
				for(int j=-m_width;j<m_width+1;j++)
				{
					pDC->SetPixel(pt.x+i,pt.y+j,RGB(255,0,0));
				}
			}	
		}
	}
	

}

CMyPoint* CMyPoint::Add(CPoint pt)
{
	this->m_pt=pt;
	return this;
}

CMyPoint* CMyPoint::GetGraph(int id)
{
	CMyPoint *temp=new CMyPoint(m_width,m_color);
	temp->m_id=id;
	temp->m_pt=this->m_pt;
	return temp;	
}

void CMyPoint::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		if(!this->m_IsDeleted)
			ar<<m_id<<m_pt<<m_width<<m_color;
	}
	else
	{
		ar>>m_id>>m_pt>>m_width>>m_color;
	}
}
