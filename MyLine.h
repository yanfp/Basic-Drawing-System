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
	int m_width;//�߿�
	COLORREF m_color;//��ɫ
	int m_style;//����
	CPoint m_pt1;//���
	CPoint m_pt2;//�յ�
	void Draw(CDC *pDC);
	void Add(CPoint pt);
	CMyLine* GetGraph(int id);//����һ����ͬ���߶�����յ�ǰ����
	void Clear();
	int m_flag;//���߱�־�������жϻ�ֱ�����Ƿ�ʼ���Ƿ����
	void Serialize(CArchive &ar);
	
	//��=�����������
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


