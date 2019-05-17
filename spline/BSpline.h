// BSpline.h: interface for the CBSpline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSPLINE_H__1C722371_C453_4315_B34A_AA478960A3E4__INCLUDED_)
#define AFX_BSPLINE_H__1C722371_C453_4315_B34A_AA478960A3E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <iostream>
//#include <Point3D.h>

using std::vector;
typedef vector<CPoint> VecPoint;
typedef vector<double> VecDouble;

class CBSpline  
{
public:
	enum	SP_STATE{SP_BASIC, SP_PERIODIC, SP_CLOSE};

	CBSpline();
//	void	Create(const VecPoint& vec, unsigned nDeg, unsigned nFrac);
//	void	GetPoints(const VecPoint& vecp, VecPoint& vecres) const;
	void	Create(unsigned nDeg, unsigned nPoint, const VecPoint& arr, SP_STATE state);
	void	Draw(CDC* pDC);
	virtual ~CBSpline();
private:
	void	FillKnot(unsigned k);
//	void	FillVector(unsigned num);
	double	GetBasisValue(unsigned i, unsigned k, double t);

public:

	VecPoint			m_arPoint;
	VecDouble			m_arKnot;
	VecPoint			m_arCarcas;
//	VecDouble*			m_pvecDouble;
//	unsigned			m_nVec;
//	double				m_fMaxt;
	unsigned			m_nDeg;
	unsigned			m_nPoint;
	SP_STATE			m_state;
//	unsigned			m_nPoint;
};

#endif // !defined(AFX_BSPLINE_H__1C722371_C453_4315_B34A_AA478960A3E4__INCLUDED_)
