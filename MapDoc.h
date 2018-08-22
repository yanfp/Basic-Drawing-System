// MapDoc.h : interface of the CMapDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDOC_H__6AC5C821_DB1E_44E2_B526_D0470781F6DA__INCLUDED_)
#define AFX_MAPDOC_H__6AC5C821_DB1E_44E2_B526_D0470781F6DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyPoint.h"
#include "MyLine.h"
#include "MyPline.h"
#include "MyPolygon.h"
#include "MyText.h"
#include "afxtempl.h"

class CMapDoc : public CDocument
{
protected: // create from serialization only
	CMapDoc();
	DECLARE_DYNCREATE(CMapDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMapDoc)
	afx_msg void OnDeleteseleted();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//CObArray m_ptrArray;
	CTypedPtrArray<CObArray,CMyPoint*>m_PointArray;//��
	CTypedPtrArray<CObArray,CMyLine*>m_LineArray;//��
	CTypedPtrArray<CObArray,CMyPline*>m_PlineArray;//�����
	CTypedPtrArray<CObArray,CMyPolygon*>m_PolygonArray;//�����
	CTypedPtrArray<CObArray,CMyText*>m_TextArray;//�ı�

public://ͨ����ѡ��Ԫ��
	CMyPoint* SelectPoint(CPoint pt);
	CMyLine* SelectLine(CPoint pt);
	CMyPline* SelectPline(CPoint pt);
	CMyPolygon* SelectPolygon(CPoint pt);
	CMyText* SelectText(CPoint pt);
public://�ҵ�
	CPoint* SeekPoint(CPoint pt);
	CDraw* SeekObject(CPoint pt);
	void ClearSelect();
public:
	void OnDraw(CDC* pDC);//�ػ溯��

public:
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPDOC_H__6AC5C821_DB1E_44E2_B526_D0470781F6DA__INCLUDED_)
