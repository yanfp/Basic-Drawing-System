// Draw.cpp: implementation of the CDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "Draw.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDraw,CObject,1)
CDraw::CDraw()
{
	this->m_IsDeleted=false;
	this->m_IsSelected=false;
}

CDraw::~CDraw()
{

}

void CDraw::Draw(CDC *pDC)
{
	::MessageBox(NULL,"δʵ��CDraw������","��ʾ",MB_OKCANCEL);
}

void CDraw::Serialize(CArchive &ar)
{
	::MessageBox(NULL,"δʵ��Serialize����","��ʾ",MB_OKCANCEL);
}



