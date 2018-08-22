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

	int m_width;//�߿�
	int m_style;//����
	COLORREF m_color;//����ɫ
	CPoint m_pt[100];//������
	int m_ptNumber;//�ڵ����

	void Draw(CDC *pDC);
	
	CMyPline* Add(CPoint pt);//��ӵ�

	CMyPline* GetGraph(int id); //����һ������߶����ָ�벢��յ�ǰ����

	void Clear();//��ԭ���Ա

	void Serialize(CArchive &ar);

};

#endif // !defined(AFX_MYPLINE_H__D306FBA7_CE58_4611_BCFD_F721A2865F41__INCLUDED_)
