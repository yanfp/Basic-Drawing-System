// MyPolygon.h: interface for the CMyPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPOLYGON_H__15BB8BA0_5CF4_45A0_B368_E8E52095881E__INCLUDED_)
#define AFX_MYPOLYGON_H__15BB8BA0_5CF4_45A0_B368_E8E52095881E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Draw.h"

class CMyPolygon : public CDraw
{
	DECLARE_SERIAL(CMyPolygon)
public:
	CMyPolygon();
	virtual ~CMyPolygon();

	void Draw(CDC *pDC);
	CMyPolygon* Add(CPoint pt);
	CPoint m_pt[100];
	int m_ptNumber;
	int m_RegionMode;//�߽�����
	LOGBRUSH m_logbrush;//��ˢ�ṹ��
	CMyPolygon* GetGraph(int id);//���ض���ζ�����յ�ǰ�����
	void Clear();
	void Serialize(CArchive &ar);

};

#endif // !defined(AFX_MYPOLYGON_H__15BB8BA0_5CF4_45A0_B368_E8E52095881E__INCLUDED_)
