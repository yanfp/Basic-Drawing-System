// OperateMap.h: interface for the COperateMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPERATEMAP_H__7B953713_F2EE_422F_966D_4F4FB70B6174__INCLUDED_)
#define AFX_OPERATEMAP_H__7B953713_F2EE_422F_966D_4F4FB70B6174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COperateMap  
{
public:
	COperateMap();
	virtual ~COperateMap();
public:
	CPoint m_pt1;
	CPoint m_pt2;
public:
	int m_command;
	void SetMap(CPoint &pt,double &scale,int x,int y);
	void Clear();

};

#endif // !defined(AFX_OPERATEMAP_H__7B953713_F2EE_422F_966D_4F4FB70B6174__INCLUDED_)
