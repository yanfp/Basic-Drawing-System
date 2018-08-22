// MyLine.cpp: implementation of the CMyLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "MyLine.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CMyLine,CObject,1)
CMyLine::CMyLine()
{
	m_flag=0;
	m_width=0;
	m_style=0;
	m_color=RGB(0,0,0);
}
CMyLine::CMyLine(int width,int style,COLORREF color)
{
	this->m_width=width;
	this->m_style=style;
	this->m_color=color;
}
CMyLine::~CMyLine()
{
}
extern void APtoDP(CPoint &pt);
void CMyLine::Draw(CDC *pDC)
{
	////显示是将逻辑坐标依据当前起点和比例显示////
	CPoint pt1,pt2;
	pt1=m_pt1;pt2=m_pt2;
	APtoDP(pt1);
	APtoDP(pt2);
	/////////////////////////////////
	CPen pen(m_style,m_width,m_color);
	CPen *pOldPen=pDC->SelectObject(&pen);
	if(!this->m_IsDeleted)//如果没有被删除
	{
		pDC->MoveTo(pt1);
		pDC->LineTo(pt2);
		
		if(this->m_IsSelected)//如果被选中
		{
			CPen pen(2,1,RGB(255,0,0));
			pDC->SelectObject(&pen);
			pDC->MoveTo(pt1);
			pDC->LineTo(pt2);
		}
	}
	pDC->SelectObject(&pen);	
}
void CMyLine::Add(CPoint pt)
{
	m_flag++;
	if(m_flag==1)
	{
		m_pt1=pt;		
	}
	else
	{
		m_pt2=pt;
	}
}
CMyLine* CMyLine::GetGraph(int id)//返回当前线
{
	CMyLine* temp=new CMyLine(m_width,m_style,m_color);
	temp->m_id=id;
	temp->m_pt1=this->m_pt1;
	temp->m_pt2=this->m_pt2;
	this->Clear();
	return temp;
}

void CMyLine::Clear()//清除
{
	this->m_pt1=0;
	this->m_pt2=0;
	this->m_flag=0;
}

void CMyLine::Serialize(CArchive &ar)//串行化
{
	if(ar.IsStoring())
	{
		ar<<m_id<<m_pt1<<m_pt2<<m_width<<m_style<<m_color;	
	}
	else
	{
		ar>>m_id>>m_pt1>>m_pt2>>m_width>>m_style>>m_color;
	}
}



