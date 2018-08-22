// MyPline.cpp: implementation of the CMyPline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "MyPline.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CMyPline,CObject,1)
CMyPline::CMyPline()
{
	this->m_ptNumber=0;
	this->m_width=1;
	this->m_style=0;
	this->m_color=RGB(0,0,0);

}

CMyPline::CMyPline(int width,int style,COLORREF color)
{
	this->m_width=width;
	this->m_style=style;
	this->m_color=color;
}

CMyPline::~CMyPline()
{

}

CMyPline* CMyPline::Add(CPoint pt)
{
	m_pt[m_ptNumber++]=pt;
	return this;
}

extern void APtoDP(CPoint &pt);
void CMyPline::Draw(CDC *pDC)
{
	////坐标转换////
	CPoint *pt=new CPoint[m_ptNumber];
	for(int j=0;j<m_ptNumber;j++)
	{
		pt[j]=m_pt[j];
		APtoDP(pt[j]);
	}
	/////////////////

	CPen pen(m_style,m_width,m_color);
	CPen *pOldPen=pDC->SelectObject(&pen);
	if(!this->m_IsDeleted)//没有被删除
	{
		pDC->MoveTo(pt[0]);
		for(int i=1;i<m_ptNumber;i++)
		{
			pDC->LineTo(pt[i]);		
		}
		if(this->m_IsSelected)
		{
			CPen pen(2,1,RGB(255,0,0));
			pDC->SelectObject(&pen);
			pDC->MoveTo(pt[0]);
			for(int i=1;i<m_ptNumber;i++)
			{
				pDC->LineTo(pt[i]);		
			}
		}
	}
	
	delete pt;
	
	pDC->SelectObject(pOldPen);	
}

CMyPline* CMyPline::GetGraph(int id)
{
	
	CMyPline *temp=new CMyPline();
	temp->m_id=id;
	temp->m_width=this->m_width;
	temp->m_style=this->m_style;
	temp->m_color=this->m_color;
	temp->m_ptNumber=this->m_ptNumber;
	for(int i=0;i<m_ptNumber;i++)
	{
		temp->m_pt[i]=this->m_pt[i];
	}
	this->Clear();
	return temp;
}

void CMyPline::Clear()
{
	for(int i=0;i<m_ptNumber;i++)
	{
		this->m_pt[i]=0;
	}
	this->m_ptNumber=0;
}

void CMyPline::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		if(!this->m_IsDeleted)
		{
			ar<<m_id<<m_ptNumber;
			for(int i=0;i<m_ptNumber;i++)
				ar<<m_pt[i];
			ar<<m_width<<m_style<<m_color;
		}
	}
	else
	{		
		ar>>m_id>>m_ptNumber;
		for(int i=0;i<m_ptNumber;i++)
			ar>>m_pt[i];
		ar>>m_width>>m_style>>m_color;
	}
}
