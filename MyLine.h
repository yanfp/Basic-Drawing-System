// MyLine.h: interface for the CMyLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLINE_H__CF79B093_0143_45EA_943F_1A7F9F1AD751__INCLUDED_)
#define AFX_MYLINE_H__CF79B093_0143_45EA_943F_1A7F9F1AD751__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Draw.h"
#include "MyPline.h"

class CMyLine : public CDraw  
{
	DECLARE_SERIAL(CMyLine)
public:
	CMyLine();
	CMyLine(int width,int style,COLORREF color);
	virtual ~CMyLine();
	int m_width;//线宽
	COLORREF m_color;//颜色
	int m_style;//线性
	CPoint m_pt1;//起点
	CPoint m_pt2;//终点
	void Draw(CDC *pDC);
	void Add(CPoint pt);
	CMyLine* GetGraph(int id);//返回一个相同的线对象并清空当前对象
	void Clear();
	int m_flag;//画线标志，用于判断画直线线是否开始，是否结束
	void Serialize(CArchive &ar);
	
	//“=”运算符重载
	CMyLine& operator =(const CMyLine& line)
	{
		if(this!=&line)
		{
			m_width=line.m_width;
			m_color=line.m_color;
			m_style=line.m_style;
			m_pt1=line.m_pt1;
			m_pt2=line.m_pt2;
		}
		return *this;
	}
};

#endif // !defined(AFX_MYLINE_H__CF79B093_0143_45EA_943F_1A7F9F1AD751__INCLUDED_)


