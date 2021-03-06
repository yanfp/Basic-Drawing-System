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

//计算两点之间的距离
float CalDist(float x1,float y1,float x2,float y2)
{
	return (float)sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

//计算点到直线的距离
float PointLine(float xx,float yy,float x1,float y1,float x2,float y2)
{
	float a,b,c,ang1,ang2,ang;
    //计算三条边的距离
    a=CalDist(x1,y1,xx,yy);if(a==0.0)return 0.0;
    b=CalDist(x2,y2,xx,yy);if(b==0.0)return 0.0;
    c=CalDist(x1,y1,x2,y2);
    //如果（x1,y1)和(x2,y2)是一个点直接返回距离
    if(c==0.0) return a;
	if(a<b) //如果(xx,yy)的点(x1,y1）这条边较短
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
			if(y1>y2)ang1=(float)pi*2-ang1;  //直线(x1,y1)-(x2,y2)的弧度
		}
		ang2=(float)acos((xx-x1)/a);
		if(y1>yy)ang2=(float)pi*2-ang2;  //直线(x1,y1)-(xx,yy)的弧度
		ang=ang2-ang1;
		if(ang<0)ang=-ang;
		if(ang>pi) ang=(float)pi*2-ang;  //交角的大小
		if(ang>pi/2) return a;    //如果为钝角，直接返回距离
		else 
			return (a*(float)sin(ang)); //否则返回计算得到的距离 
	}
	else //如果(xx,yy)的点(x2,y2）这条边较短
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
			ang1=(float)acos((x1-x2)/c);     //直线（x2,y2)-(x1,y1)的斜率的弧度
			if(y2>y1)ang1=(float)pi*2-ang1;
		}
		ang2=(float)acos((xx-x2)/b);     //直线（x2,x1）-(xx,yy)的斜率的弧度
		if(y2>yy)ang2=(float)pi*2-ang2;
		ang=ang2-ang1;
		if(ang<0) ang=-ang;
		if(ang>pi) ang=(float)pi*2-ang;  //交角的大小 �

		if(ang>pi/2)  return b;   //如果为钝角，直接返回距离
		else 
			return(b*(float)sin(ang));  //否则返回计算得到的距离
	}
}

//函数PointRgn作用：判断一个点是否在任意多边形区域内
//参数：Numble-边界点数，x,y是点的坐标，多边形顶点的坐标在结构数组PointList中
//返回：1-点在多边形区域0-不在
BOOL PointRgn(float x,float y,int Numble,CPoint *pPoint,float blc)
{
	CRgn rgn;         //定义一个CRgn对象
	int x1,y1,i;
	CPoint bbcc[500];
	//POINT* bbcc;      // 定义一个点结构指针
	if(Numble<3) 
		return 0;//如果点的数目<3即不是一个区域返回不成功标志
	//bbcc=new POINT[Numble+1]; //分配sm个点
	//将点的坐标转变成屏幕坐标
	x1=(int)(x/blc);
	y1=(int)(y/blc);
	//将封闭区域各点的坐标转成屏幕坐标
	for(i=0;i<Numble;i++)
	{
		bbcc[i].x=(int)((pPoint[i].x)/blc);
		bbcc[i].y=(int)((pPoint[i].y)/blc);
	}
	rgn.CreatePolygonRgn(bbcc,Numble,1);//初试化一个多边形区域
	i=(rgn.PtInRegion(x1,y1)!=0);		//如果在区域内j=1,否则j=0;
	rgn.DeleteObject();					//删除定义的rgn对象
	//delete bbcc;
	return i;
}

////函数作用：找到一个点在多段线中哪一段线的范围类////
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

