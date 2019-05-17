// Point3D.h: interface for the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT3D_H__9588B039_D226_4CDA_B175_F47159908A02__INCLUDED_)
#define AFX_POINT3D_H__9588B039_D226_4CDA_B175_F47159908A02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "math.h"
/*
using std::sin;
using std::cos;
*/
class CPoint2D;

class CPoint3D  
{
public:
	CPoint3D() : m_x(0.0), m_y(0.0), m_z(0.0) {};
	CPoint3D(double x, double y, double z);
	CPoint2D	Project(CSize size, double dist);
	void		RotateX(int ang);
	void		RotateY(int ang);
	void		RotateZ(int ang);
	void		Translate(double x, double y, double z);
//	CPoint3D(C)
	virtual ~CPoint3D();
public:
	double m_x,m_y,m_z;
};

class CPoint2D  
{
public:
	CPoint2D(double x, double y);
//	CPoint3D(C)
	virtual ~CPoint2D();
public:
	double m_x,m_y;
};

inline CPoint2D CPoint3D::Project(CSize size, double dist) 
{
	return CPoint2D(	size.cx/2 + m_x*dist/(dist + m_z),
						size.cy/2 + m_y*dist/(dist + m_z)	);
}

inline void CPoint3D::RotateZ(int ang)
{
	const double PI = 3.14159265359;
	double fang = PI*ang/180;
	double prevx = m_x;
	m_x = m_x*cos(fang)	- m_y*sin(fang);
	m_y = prevx*sin(fang) + m_y*cos(fang);
}

inline void CPoint3D::RotateY(int ang)
{
	const double PI = 3.14159265359;
	double fang = PI*ang/180;
	double prevx = m_x;
	m_x = m_x*cos(fang)	- m_z*sin(fang);
	m_z = prevx*sin(fang) + m_z*cos(fang);
}

inline void CPoint3D::RotateX(int ang)
{
	const double PI = 3.14159265359;
	double fang = PI*ang/180;
	double prevy = m_y;
	m_y = m_y*cos(fang)	- m_z*sin(fang);
	m_z = prevy*sin(fang) + m_z*cos(fang);
}

inline void CPoint3D::Translate(double x, double y, double z)
{
	m_x += x;
	m_y += y;
	m_z += z;
}
#endif // !defined(AFX_POINT3D_H__9588B039_D226_4CDA_B175_F47159908A02__INCLUDED_)