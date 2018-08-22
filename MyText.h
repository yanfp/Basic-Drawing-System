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


	COLORREF m_color;//颜色
	CPoint m_pt;//位置
	CString m_str;//文本

	CMyText* Add(CPoint pt);
	void Draw(CDC *pDC);
	void Serialize(CArchive &ar);
	CMyText* GetGraph(int id);//返回一个相同的文本对象并清空当前对象
	

};

#endif // !defined(AFX_MYTEXT_H__FC193D8A_6EC2_4BED_AD44_DEEFF68E8961__INCLUDED_)
