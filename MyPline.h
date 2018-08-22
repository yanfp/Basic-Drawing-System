// MyPline.h: interface for the CMyPline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPLINE_H__D306FBA7_CE58_4611_BCFD_F721A2865F41__INCLUDED_)
#define AFX_MYPLINE_H__D306FBA7_CE58_4611_BCFD_F721A2865F41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Draw.h"

class CMyPline : public CDraw  
{
	DECLARE_SERIAL(CMyPline)
public:
	CMyPline();
	CMyPline(int width,int style,COLORREF color);
	virtual ~CMyPline();

	int m_width;//线宽
	int m_style;//线型
	COLORREF m_color;//线颜色
	CPoint m_pt[100];//点坐标
	int m_ptNumber;//节点个数

	void Draw(CDC *pDC);
	
	CMyPline* Add(CPoint pt);//添加点

	CMyPline* GetGraph(int id); //返回一个多段线对象的指针并清空当前对象

	void Clear();//复原类成员

	void Serialize(CArchive &ar);

};

#endif // !defined(AFX_MYPLINE_H__D306FBA7_CE58_4611_BCFD_F721A2865F41__INCLUDED_)
