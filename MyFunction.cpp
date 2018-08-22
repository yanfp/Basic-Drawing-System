// MyFunction.cpp: implementation of the MyFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "MyFunction.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define pi 3.1415926
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyFunction::MyFunction()
{

}

MyFunction::~MyFunction()
{

}

//¼ÆËãÁ½µãÖ®¼äµÄ¾àÀë
float CalDist(float x1,float y1,float x2,float y2)
{
	return (float)sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

//¼ÆËãµãµ½Ö±ÏßµÄ¾àÀë
float PointLine(float xx,float yy,float x1,float y1,float x2,float y2)
{
	float a,b,c,ang1,ang2,ang;
    //¼ÆËãÈıÌõ±ßµÄ¾àÀë
    a=CalDist(x1,y1,xx,yy);if(a==0.0)return 0.0;
    b=CalDist(x2,y2,xx,yy);if(b==0.0)return 0.0;
    c=CalDist(x1,y1,x2,y2);
    //Èç¹û£¨x1,y1)ºÍ(x2,y2)ÊÇÒ»¸öµãÖ±½Ó·µ»Ø¾àÀë
    if(c==0.0) return a;
	if(a<b) //Èç¹û(xx,yy)µÄµã(x1,y1£©ÕâÌõ±ß½Ï¶Ì
	{
		if(y1==y2)
		{
			if(x1<x2)
				ang1=0;
			else
				ang1=(float)pi;
		}
		else
		{
			ang1=(float)acos((x2-x1)/c);
			if(y1>y2)ang1=(float)pi*2-ang1;  //Ö±Ïß(x1,y1)-(x2,y2)µÄ»¡¶È
		}
		ang2=(float)acos((xx-x1)/a);
		if(y1>yy)ang2=(float)pi*2-ang2;  //Ö±Ïß(x1,y1)-(xx,yy)µÄ»¡¶È
		ang=ang2-ang1;
		if(ang<0)ang=-ang;
		if(ang>pi) ang=(float)pi*2-ang;  //½»½ÇµÄ´óĞ¡
		if(ang>pi/2) return a;    //Èç¹ûÎª¶Û½Ç£¬Ö±½Ó·µ»Ø¾àÀë
		else 
			return (a*(float)sin(ang)); //·ñÔò·µ»Ø¼ÆËãµÃµ½µÄ¾àÀë 
	}
	else //Èç¹û(xx,yy)µÄµã(x2,y2£©ÕâÌõ±ß½Ï¶Ì
	{
		if(y1==y2)
		{
			if(x1<x2)
				ang1=(float)pi;
			else
				ang1=0;
		}
		else
		{
			ang1=(float)acos((x1-x2)/c);     //Ö±Ïß£¨x2,y2)-(x1,y1)µÄĞ±ÂÊµÄ»¡¶È
			if(y2>y1)ang1=(float)pi*2-ang1;
		}
		ang2=(float)acos((xx-x2)/b);     //Ö±Ïß£¨x2,x1£©-(xx,yy)µÄĞ±ÂÊµÄ»¡¶È
		if(y2>yy)ang2=(float)pi*2-ang2;
		ang=ang2-ang1;
		if(ang<0) ang=-ang;
		if(ang>pi) ang=(float)pi*2-ang;  //½»½ÇµÄ´óĞ¡ Ç

		if(ang>pi/2)  return b;   //Èç¹ûÎª¶Û½Ç£¬Ö±½Ó·µ»Ø¾àÀë
		else 
			return(b*(float)sin(ang));  //·ñÔò·µ»Ø¼ÆËãµÃµ½µÄ¾àÀë
	}
}

//º¯ÊıPointRgn×÷ÓÃ£ºÅĞ¶ÏÒ»¸öµãÊÇ·ñÔÚÈÎÒâ¶à±ßĞÎÇøÓòÄÚ
//²ÎÊı£ºNumble-±ß½çµãÊı£¬x,yÊÇµãµÄ×ø±ê£¬¶à±ßĞÎ¶¥µãµÄ×ø±êÔÚ½á¹¹Êı×éPointListÖĞ
//·µ»Ø£º1-µãÔÚ¶à±ßĞÎÇøÓò0-²»ÔÚ
BOOL PointRgn(float x,float y,int Numble,CPoint *pPoint,float blc)
{
	CRgn rgn;         //¶¨ÒåÒ»¸öCRgn¶ÔÏó
	int x1,y1,i;
	CPoint bbcc[500];
	//POINT* bbcc;      // ¶¨ÒåÒ»¸öµã½á¹¹Ö¸Õë
	if(Numble<3) 
		return 0;//Èç¹ûµãµÄÊıÄ¿<3¼´²»ÊÇÒ»¸öÇøÓò·µ»Ø²»³É¹¦±êÖ¾
	//bbcc=new POINT[Numble+1]; //·ÖÅäsm¸öµã
	//½«µãµÄ×ø±ê×ª±ä³ÉÆÁÄ»×ø±ê
	x1=(int)(x/blc);
	y1=(int)(y/blc);
	//½«·â±ÕÇøÓò¸÷µãµÄ×ø±ê×ª³ÉÆÁÄ»×ø±ê
	for(i=0;i<Numble;i++)
	{
		bbcc[i].x=(int)((pPoint[i].x)/blc);
		bbcc[i].y=(int)((pPoint[i].y)/blc);
	}
	rgn.CreatePolygonRgn(bbcc,Numble,1);//³õÊÔ»¯Ò»¸ö¶à±ßĞÎÇøÓò
	i=(rgn.PtInRegion(x1,y1)!=0);		//Èç¹ûÔÚÇøÓòÄÚj=1,·ñÔòj=0;
	rgn.DeleteObject();					//É¾³ı¶¨ÒåµÄrgn¶ÔÏó
	//delete bbcc;
	return i;
}

////º¯Êı×÷ÓÃ£ºÕÒµ½Ò»¸öµãÔÚ¶à¶ÎÏßÖĞÄÄÒ»¶ÎÏßµÄ·¶Î§Àà////
int PointPosition(CPoint pt,CPoint *pP,int number)
{
	for(int i=0;i<number-1;i++)
	{
		if(pt.x>pP[i].x && pt.x<pP[i+1].x && pt.y>pP[i].y && pt.y<pP[i+1].y)
			return i;
	}
	return NULL;
}

float PointToLine(CPoint pt,CPoint pt1,CPoint pt2)
{
	return NULL;

}

