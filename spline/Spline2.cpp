// Spline2.cpp: implementation of the CSpline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Spline_2d.h"
#include "Spline2.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpline::CSpline(int PtNum, CPoint Center)
{
   PointNum = PtNum;
   PointRad = 6;
   PointCoord = new CPoint[PointNum]; 

   for(int i=0; i<PointNum; i++)
   { PointCoord[i].x = Center.x + 150*cos(2*pi*i/PointNum);
     PointCoord[i].y = Center.y + 150*sin(2*pi*i/PointNum);
   }
}

CSpline::~CSpline()
{
  if(PointCoord) delete PointCoord;
}

void CSpline::DrawSpline(CDC *pDC, int ShowCarcas)
{
    if(ShowCarcas)
	for(int i=0; i<PointNum; i++)
   { 
	 pDC->MoveTo(PointCoord[i].x, PointCoord[i].y);
	 if(i!=PointNum -1) pDC->LineTo(PointCoord[i+1].x, PointCoord[i+1].y);
	  else pDC->LineTo(PointCoord[0].x, PointCoord[0].y);
   }
	
	for(int i=0; i<PointNum; i++)
   { 
     pDC->Ellipse(PointCoord[i].x - PointRad, PointCoord[i].y - PointRad,
		          PointCoord[i].x + PointRad, PointCoord[i].y + PointRad);
   }

    double r[2], r0[2];
	int N = 40;
	double t, dt = 1.0/N;
    COLORREF Col = RGB(250, 100, 0);
	CPen Pen(PS_SOLID,3,Col);
	CPen *pPen = pDC->SelectObject(&Pen);
	pDC->SelectObject(Pen);
	
	BSplineCom(PointCoord, 0, 0, r);
	r0[0] = r[0]; r0[1] = r[1];
	pDC->MoveTo(r[0], r[1]);
    
	for(int j=0; j</*PointNum*/1; j++)
	 for(int i=0; i<N; i++)	 
	 { t = dt*i;
	   BSplineCom(PointCoord, j, t, r);
	   pDC->LineTo(r[0], r[1]);
	 }  
       pDC->LineTo(r0[0], r0[1]);
	   pDC->SelectObject(pPen);
} 

void CSpline::BSplineCom(CPoint *PointCoord, int i, double t, double r[])
{ double t2 = pow(t, 2), t3 = pow(t, 3);
  double b0 = (1-3*t+3*t2-t3)/6;
  double b1 = (4-6*t2+3*t3)/6;
  double b2 = (1+3*t+3*t2-3*t3)/6;
  double b3 = t3/6;
  int i1, i2, i3;
  if(i+1>=PointNum)i1 = i+1-PointNum;else i1 = i+1;
  if(i+2>=PointNum)i2 = i+2-PointNum;else i2 = i+2;
  if(i+3>=PointNum)i3 = i+3-PointNum;else i3 = i+3;
  r[0] = PointCoord[i].x*b0 + PointCoord[i1].x*b1 + PointCoord[i2].x*b2 + PointCoord[i3].x*b3;
  r[1] = PointCoord[i].y*b0 + PointCoord[i1].y*b1 + PointCoord[i2].y*b2 + PointCoord[i3].y*b3;
}
