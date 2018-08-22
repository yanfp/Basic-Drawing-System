// MyPoint.h: interface for the CMyPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPOINT_H__69611085_A082_46FB_9B1E_599B139DBACB__INCLUDED_)
#define AFX_MYPOINT_H__69611085_A082_46FB_9B1E_599B139DBACB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Draw.h"

#include "Draw.h"

class CMyPoint : public CDraw
{
	DECLARE_SERIAL(CMyPoint)
public:
	CMyPoint();
	CMyPoint(int width,COLORREF color);
	virtual ~CMyPoint();

	CPoint m_pt;//点坐标
	int m_width;//大小
	COLORREF m_color;//颜色
	void Draw(CDC *pDC);//画点函数
	CMyPoint* Add(CPoint pt);
	CMyPoint* GetGraph(int id);//返回一个相同的点对象并清空当前对象
	void Serialize(CArchive &ar);

};

#endif // !defined(AFX_MYPOINT_H__69611085_A082_46FB_9B1E_599B139DBACB__INCLUDED_)
