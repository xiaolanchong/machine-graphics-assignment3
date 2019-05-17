// BezierSpline.h: interface for the CBezierSpline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIERSPLINE_H__840CAA00_893F_42E3_B578_FEDD162B16C3__INCLUDED_)
#define AFX_BEZIERSPLINE_H__840CAA00_893F_42E3_B578_FEDD162B16C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Point3D.h"
#include <vector>
#include "templ.h"

using std::vector;

class CBezierSpline  
{
public:
	enum SPSTATE;
	CBezierSpline();
	void		Create(unsigned nDegu, unsigned nDegv, const Array2D<CPoint3D>& arr, int nu, int nv, SPSTATE xclose, SPSTATE yclose);
	void		RotateX(int ang);
	void		RotateY(int ang);
	void		RotateZ(int ang);
	void		Translate(double x, double y, double z);
	void		Draw(CDC* pDC);
	CPoint3D	Calculate(const Array2D<CPoint3D>& arr, double u, double v);
	virtual ~CBezierSpline();
	
	enum		SPSTATE{SP_BASIC, SP_ELEMNOTCLOSE, SP_ELEMCLOSE};
private:
	unsigned	Fact(unsigned n) { return n? n*Fact(n-1) : 1;};
	unsigned	Soch(unsigned n, unsigned m) { return Fact(n)/(Fact(m)*Fact(n-m));};

	int					m_nDegu;
	int					m_nDegv;
	Array2D<CPoint3D>	m_arPoint;
	Array2D<CPoint3D>	m_arCarcas;
	SPSTATE				m_uclose;
	SPSTATE				m_vclose;
	CSize				m_nsurf;
	CSize				m_nexpoint;

};



#endif // !defined(AFX_BEZIERSPLINE_H__840CAA00_893F_42E3_B578_FEDD162B16C3__INCLUDED_)
