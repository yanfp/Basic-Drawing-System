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

//��������֮��ľ���
float CalDist(float x1,float y1,float x2,float y2)
{
	return (float)sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

//����㵽ֱ�ߵľ���
float PointLine(float xx,float yy,float x1,float y1,float x2,float y2)
{
	float a,b,c,ang1,ang2,ang;
    //���������ߵľ���
    a=CalDist(x1,y1,xx,yy);if(a==0.0)return 0.0;
    b=CalDist(x2,y2,xx,yy);if(b==0.0)return 0.0;
    c=CalDist(x1,y1,x2,y2);
    //�����x1,y1)��(x2,y2)��һ����ֱ�ӷ��ؾ���
    if(c==0.0) return a;
	if(a<b) //���(xx,yy)�ĵ�(x1,y1�������߽϶�
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
			if(y1>y2)ang1=(float)pi*2-ang1;  //ֱ��(x1,y1)-(x2,y2)�Ļ���
		}
		ang2=(float)acos((xx-x1)/a);
		if(y1>yy)ang2=(float)pi*2-ang2;  //ֱ��(x1,y1)-(xx,yy)�Ļ���
		ang=ang2-ang1;
		if(ang<0)ang=-ang;
		if(ang>pi) ang=(float)pi*2-ang;  //���ǵĴ�С
		if(ang>pi/2) return a;    //���Ϊ�۽ǣ�ֱ�ӷ��ؾ���
		else 
			return (a*(float)sin(ang)); //���򷵻ؼ���õ��ľ��� 
	}
	else //���(xx,yy)�ĵ�(x2,y2�������߽϶�
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
			ang1=(float)acos((x1-x2)/c);     //ֱ�ߣ�x2,y2)-(x1,y1)��б�ʵĻ���
			if(y2>y1)ang1=(float)pi*2-ang1;
		}
		ang2=(float)acos((xx-x2)/b);     //ֱ�ߣ�x2,x1��-(xx,yy)��б�ʵĻ���
		if(y2>yy)ang2=(float)pi*2-ang2;
		ang=ang2-ang1;
		if(ang<0) ang=-ang;
		if(ang>pi) ang=(float)pi*2-ang;  //���ǵĴ�С �

		if(ang>pi/2)  return b;   //���Ϊ�۽ǣ�ֱ�ӷ��ؾ���
		else 
			return(b*(float)sin(ang));  //���򷵻ؼ���õ��ľ���
	}
}

//����PointRgn���ã��ж�һ�����Ƿ�����������������
//������Numble-�߽������x,y�ǵ�����꣬����ζ���������ڽṹ����PointList��
//���أ�1-���ڶ��������0-����
BOOL PointRgn(float x,float y,int Numble,CPoint *pPoint,float blc)
{
	CRgn rgn;         //����һ��CRgn����
	int x1,y1,i;
	CPoint bbcc[500];
	//POINT* bbcc;      // ����һ����ṹָ��
	if(Numble<3) 
		return 0;//��������Ŀ<3������һ�����򷵻ز��ɹ���־
	//bbcc=new POINT[Numble+1]; //����sm����
	//���������ת�����Ļ����
	x1=(int)(x/blc);
	y1=(int)(y/blc);
	//�����������������ת����Ļ����
	for(i=0;i<Numble;i++)
	{
		bbcc[i].x=(int)((pPoint[i].x)/blc);
		bbcc[i].y=(int)((pPoint[i].y)/blc);
	}
	rgn.CreatePolygonRgn(bbcc,Numble,1);//���Ի�һ�����������
	i=(rgn.PtInRegion(x1,y1)!=0);		//�����������j=1,����j=0;
	rgn.DeleteObject();					//ɾ�������rgn����
	//delete bbcc;
	return i;
}

////�������ã��ҵ�һ�����ڶ��������һ���ߵķ�Χ��////
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

