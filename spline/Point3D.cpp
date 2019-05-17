// Point3D.cpp: implementation of the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "spline.h"
#include "Point3D.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoint3D::CPoint3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z) 
{

}

CPoint3D::~CPoint3D()
{

}

CPoint2D Project()
{
	return CPoint2D(0.0, 0.0);
}
/////////////////////////////////////////////////////////////////

CPoint2D::CPoint2D(double x, double y) : m_x(x), m_y(y) 
{

}

CPoint2D::~CPoint2D()
{

}