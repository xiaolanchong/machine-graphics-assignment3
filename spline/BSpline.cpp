// BSpline.cpp: implementation of the CBSpline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "spline.h"
#include "BSpline.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBSpline::CBSpline()
{

}

CBSpline::~CBSpline()
{

}

/////////////////////////////////////////////////////////////////////

void	CBSpline::FillKnot(unsigned k)
{
	int n = m_arCarcas.size()-1;
	int m = n+k+1;
	switch(m_state)
	{
	case SP_BASIC:
		m_arKnot.resize(m+1, 0.0);
		for(int i = 0; i< static_cast<int>(k)+1; i++)
			m_arKnot[i] = 0.0;
		for(int i = k+1; i < n+1; i++  )
			m_arKnot[i] = i - k;
		for(int i = n+1; i < m+1; i++)
			m_arKnot[i] = n-k+1;
		break;
//		m_arKnot.resize(m, 0.0);
	case SP_CLOSE:
	case SP_PERIODIC:
	m_arKnot.resize(m+1, 0.0);
		for(int i = 0; i < m+1 ; i++)
			m_arKnot[i] = i;
		break;
	}
	
}

double CBSpline::GetBasisValue(unsigned i, unsigned k, double t)
{
	ASSERT(k >= 0 && !m_arKnot.empty());
	if( k == 0) 
	{
		if( (m_arKnot[i] <= t)  && ( m_arKnot[i+1] > t))
			return 1.0;
		else 
			return 0.0;
	}
	else
	{
		double a = ( t - m_arKnot[i]) * GetBasisValue(i, k-1, t);
		double b = ( m_arKnot[i+k+1] - t) * GetBasisValue(i+1, k-1, t);
		if( a == 0.0 && (m_arKnot[i+k] - m_arKnot[i]) == 0.0)
			a = 0;
		else
			a /= m_arKnot[i+k] - m_arKnot[i];
		if( b == 0.0 && (m_arKnot[i+k+1] - m_arKnot[i+1]) == 0.0)
			b = 0;
		else
			b /= m_arKnot[i+k+1] - m_arKnot[i+1];
		return a + b;
	}
}

void CBSpline::Create(unsigned nDeg, unsigned nPoint, const VecPoint& arr, SP_STATE state)
{
	m_nDeg		= nDeg;
	m_nPoint	= nPoint;
	m_state		= state;
	m_arCarcas	= arr;
	FillKnot(nDeg);
//	FillVector(nDeg);
}

void CBSpline::Draw(CDC* pDC)
{
	CPen	*ppenOld;
	CPen	penSpline(PS_SOLID, 2, RGB(255,0,0));
	CPen	penCarcas(PS_SOLID, 1, RGB(0, 0, 255));
	ppenOld = pDC->SelectObject(&penSpline);
	CPoint ptStart(0,0);
	double maxt,mint;
	switch(m_state)
	{
	case SP_BASIC:
		maxt = m_arKnot[m_arKnot.size()-1];
		mint = m_arKnot[0];
		break;
	case SP_PERIODIC:
	case SP_CLOSE:
		if(m_arKnot.size()%2 == 0)
		{
			double r = m_arKnot.size();
			maxt = m_arKnot.size()/2;
			mint = m_arKnot.size()/2-1;
		}
		else
		{
			maxt = m_arKnot.size()/2+0.5;
			mint = m_arKnot.size()/2-0.5;
		}
		break;
	}
	for(int i=0; i< static_cast<int>(m_arCarcas.size()); i++)
	{
		double t = GetBasisValue(i, m_nDeg, mint);
		ptStart.x += static_cast<int>(m_arCarcas[i].x * GetBasisValue(i, m_nDeg, mint));
		ptStart.y += static_cast<int>(m_arCarcas[i].y * GetBasisValue(i, m_nDeg, mint));
	}
	pDC->MoveTo(ptStart);
	if(m_state == SP_BASIC ||m_state == SP_PERIODIC)
	for(unsigned int i = 1; i < m_nPoint; i++)
	{
		CPoint ptNext(0,0);
		for(unsigned int j = 0; j < m_arCarcas.size(); j++)
		{
			if(m_state == SP_BASIC && i == m_nPoint-1 && j == m_arCarcas.size()-1)
			{
				ptNext.x += m_arCarcas[j].x;
				ptNext.y += m_arCarcas[j].y;
			}
			double t = GetBasisValue(j, m_nDeg, mint);
			ptNext.x += static_cast<int>(m_arCarcas[j].x*GetBasisValue(j, m_nDeg, mint+(maxt-mint)*i/(m_nPoint-1)));
			ptNext.y += static_cast<int>(m_arCarcas[j].y*GetBasisValue(j, m_nDeg, mint+(maxt-mint)*i/(m_nPoint-1)));
		}
		pDC->LineTo(ptNext);
	}
	int size = m_arCarcas.size();
	if(m_state == SP_CLOSE)
	{
		for(int k = 0;k< static_cast<int>(m_arCarcas.size());k++)
		{
			CPoint ptStartSeg(0,0);
			pDC->SelectObject(ppenOld);
			penSpline.DeleteObject();
			penSpline.CreatePen(PS_SOLID, 2, RGB((k*53+100)%255, (k*91+200)%255, (k*143+300)%255));
			pDC->SelectObject(&penSpline);
			for(int i=k; i< static_cast<int>(m_arCarcas.size()+k); i++)
			{
			//	double t = GetBasisValue(i-k, m_nDeg, mint);
				ptStartSeg.x += static_cast<int>(m_arCarcas[i%size].x * GetBasisValue(i-k, m_nDeg, mint));
				ptStartSeg.y += static_cast<int>(m_arCarcas[i%size].y * GetBasisValue(i-k, m_nDeg, mint));
			}
			pDC->MoveTo(ptStartSeg);
			for(unsigned int i = 1; i < m_nPoint; i++)
			{
				CPoint ptNext(0,0);
				for(int j = k; j < static_cast<int>(m_arCarcas.size()+k); j++)
				{
			//		double t = GetBasisValue(i, m_nDeg, mint);
					ptNext.x += static_cast<int>(m_arCarcas[j%size].x*GetBasisValue(j-k, m_nDeg, mint+(maxt-mint)*(i)/(m_nPoint-1)));
					ptNext.y += static_cast<int>(m_arCarcas[j%size].y*GetBasisValue(j-k, m_nDeg, mint+(maxt-mint)*(i)/(m_nPoint-1)));
				}
				pDC->LineTo(ptNext);
			}
		}
	}
	pDC->SelectObject(&penCarcas);
	pDC->MoveTo(m_arCarcas[0]);
	for(size_t i = 1; i < m_arCarcas.size(); i++)
	{
		pDC->LineTo(m_arCarcas[i]);
	}
	if(m_state == SP_CLOSE)
		pDC->LineTo(m_arCarcas[0]);
	for(size_t i = 0; i < m_arCarcas.size(); i++)
	{
		pDC->Ellipse(	m_arCarcas[i].x - 4, m_arCarcas[i].y - 4,
						m_arCarcas[i].x + 4, m_arCarcas[i].y + 4);
	}
/*	CPoint point[4];
	point[0] = m_arCarcas[0];
	point[1] = m_arCarcas[1];
	point[2] = m_arCarcas[2];
	point[3] = m_arCarcas[3];
	pDC->PolyBezier(point, 4);*/
	pDC->SelectObject(ppenOld);
//	m_pvecDouble[m_nPoint-1][m_nVec-1] = 1.0; 
}