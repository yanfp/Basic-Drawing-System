// MyText.h: interface for the CMyText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTEXT_H__FC193D8A_6EC2_4BED_AD44_DEEFF68E8961__INCLUDED_)
#define AFX_MYTEXT_H__FC193D8A_6EC2_4BED_AD44_DEEFF68E8961__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Draw.h"

class CMyText : public CDraw  
{
	DECLARE_SERIAL(CMyText)
public:
	CMyText();
	virtual ~CMyText();


	COLORREF m_color;//��ɫ
	CPoint m_pt;//λ��
	CString m_str;//�ı�

	CMyText* Add(CPoint pt);
	void Draw(CDC *pDC);
	void Serialize(CArchive &ar);
	CMyText* GetGraph(int id);//����һ����ͬ���ı�������յ�ǰ����
	

};

#endif // !defined(AFX_MYTEXT_H__FC193D8A_6EC2_4BED_AD44_DEEFF68E8961__INCLUDED_)
