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

	CPoint m_pt;//������
	int m_width;//��С
	COLORREF m_color;//��ɫ
	void Draw(CDC *pDC);//���㺯��
	CMyPoint* Add(CPoint pt);
	CMyPoint* GetGraph(int id);//����һ����ͬ�ĵ������յ�ǰ����
	void Serialize(CArchive &ar);

};

#endif // !defined(AFX_MYPOINT_H__69611085_A082_46FB_9B1E_599B139DBACB__INCLUDED_)
