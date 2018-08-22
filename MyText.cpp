// MyText.cpp: implementation of the CMyText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "MyText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMyText,CObject,1)
CMyText::CMyText()
{
	m_color=RGB(0,0,0);
}

CMyText::~CMyText()
{

}

CMyText* CMyText::Add(CPoint pt)
{
	m_pt=pt;
	return this;
}
extern void APtoDP(CPoint &pt);
void CMyText::Draw(CDC *pDC)
{
	////坐标转换////
	CPoint pt;
	pt=m_pt;
	APtoDP(pt);
	////////////////

	COLORREF oldColor=pDC->SetTextColor(m_color);
	if(!this->m_IsDeleted)//如果未被删除
	{
		pDC->TextOut(pt.x,pt.y,m_str);

		if(this->m_IsSelected)//如果选中
		{
			pDC->SetTextColor(RGB(255,0,0));
			pDC->TextOut(pt.x,pt.y,m_str);
		}
	}
	
	pDC->SetTextColor(oldColor);
}

void CMyText::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		if(!this->m_IsDeleted)
			ar<<m_pt<<m_str<<m_color;
	}
	else
	{
		ar>>m_pt>>m_str<<m_color;
	}
}

CMyText* CMyText::GetGraph(int id)
{
	CMyText *temp=new CMyText();
	temp->m_id=id;
	temp->m_color=this->m_color;
	temp->m_pt=this->m_pt;
	temp->m_str=this->m_str;
	return temp;
}
