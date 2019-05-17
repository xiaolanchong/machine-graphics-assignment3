// Spline2.h: interface for the CSpline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINE2_H__1625F9CC_45FF_4D49_87DD_9ECDEF237820__INCLUDED_)
#define AFX_SPLINE2_H__1625F9CC_45FF_4D49_87DD_9ECDEF237820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define pi 3.14

class CSpline  
{ 
public:
	void BSplineCom(CPoint *PointCoord, int i, double t, double r[]);
	int PointNum;
	int PointRad;
	CPoint *PointCoord;
	void DrawSpline(CDC *pDC, int ShowCarcas);
	CSpline(int PtNum, CPoint Center);
	virtual ~CSpline();
};

#endif // !defined(AFX_SPLINE2_H__1625F9CC_45FF_4D49_87DD_9ECDEF237820__INCLUDED_)
