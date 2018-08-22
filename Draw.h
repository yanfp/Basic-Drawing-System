// Draw.h: interface for the CDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAW_H__902CAD48_40EE_454A_B621_861D88EC59F1__INCLUDED_)
#define AFX_DRAW_H__902CAD48_40EE_454A_B621_861D88EC59F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDraw : public CObject  
{
	DECLARE_SERIAL(CDraw)
public:
	CDraw();
	virtual ~CDraw();
public:
	virtual void Draw(CDC *pDC);
	virtual void Serialize(CArchive& ar);
	int m_id;//idºÅ
	int m_layer;//Í¼²ãºÅ
	BOOL m_IsSelected;//ÊÇ·ñÑ¡ÖÐ
	BOOL m_IsDeleted;//ÊÇ·ñÉ¾³ý
};

#endif // !defined(AFX_DRAW_H__902CAD48_40EE_454A_B621_861D88EC59F1__INCLUDED_)
