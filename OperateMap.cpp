// OperateMap.cpp: implementation of the COperateMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "OperateMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COperateMap::COperateMap()
{
	m_command=11;
	m_pt1=m_pt2=0;

}

COperateMap::~COperateMap()
{

}

extern ptStart;
extern void DPtoAP(CPoint &pt);
extern void APtoDP(CPoint &pt);
void COperateMap::SetMap(CPoint &pt,double &scale,int x,int y)
{
	
	if(this->m_command==12)
	{
		CPoint ptTemp=m_pt1;
		DPtoAP(ptTemp);
		scale*=x/abs(m_pt1.x-m_pt2.x);
		pt.x=-ptTemp.x*scale;
		pt.y=-scale*y+ptTemp.y*scale;	
	}
	if(this->m_command==13)
	{
		scale/=abs(m_pt1.x-m_pt2.x)/y;
		//scale/=1.5;
		DPtoAP(m_pt1);DPtoAP(m_pt2);
		pt.x+=(m_pt1.x-pt.x)/2;
		pt.y+=(m_pt1.y-pt.y)/2;
		
	}
	if(this->m_command==11)
	{
		pt.x+=m_pt2.x-m_pt1.x;
		pt.y+=m_pt2.y-m_pt1.y;
	}
	this->Clear();
}

void COperateMap::Clear()
{
	m_pt1=m_pt2=0;
	m_command=0;
}