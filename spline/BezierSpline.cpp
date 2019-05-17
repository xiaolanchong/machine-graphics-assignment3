// BezierSpline.cpp: implementation of the CBezierSpline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "spline.h"
#include "BezierSpline.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBezierSpline::CBezierSpline()
{

}

CBezierSpline::~CBezierSpline()
{

}

void CBezierSpline::Create(unsigned /*nDegu*/, unsigned /*nDegv*/, const Array2D<CPoint3D>& arr, int nu, int nv, SPSTATE xclose, SPSTATE yclose)
{
	m_nDegu		= 3;
	m_nDegv		= 3;
	m_uclose	= xclose;
	m_vclose	= yclose;
	m_nexpoint.cx	= nu;
	m_nexpoint.cy	= nv;
	m_arCarcas		= arr;
	int sizex, sizey;
	int numu, numv;
	switch(xclose)
	{
	case SP_ELEMNOTCLOSE:
			numu	=	arr.SizeX() - m_nDegu;
			sizex	=	numu + 1 + numu*nu;
			break;
	case SP_ELEMCLOSE:
			numu	=	arr.SizeX() ;
			sizex	=	numu + 1 + numu*nu;
			break;
	case SP_BASIC:
			numu	=  (arr.SizeX()-1)/m_nDegu;
			sizex	=	numu + 1 + numu*nu;
			break;
	}
	switch(yclose)
	{
	case SP_ELEMNOTCLOSE:
			numv	=	arr.SizeY() - m_nDegv;
			sizey	=	numv + 1 + numv*nv;
			break;
	case SP_ELEMCLOSE:
			numv	=	arr.SizeY() ;
			sizey	=	numv + 1 + numv*nv;
			break;
	case SP_BASIC:
			numv	=  (arr.SizeY()-1)/m_nDegv;
			sizey	=	numv + 1 + numv*nv;
			break;
	}
	m_nsurf.cx = numu;
	m_nsurf.cy = numv;

	Array2D<CPoint3D> arTmp(m_nDegu+1,m_nDegv+1);
	m_arPoint.Alloc(sizex, sizey);  
	for(int i=0; i<numu; i ++)
		for(int j=0; j<numv; j ++)
		{
			arTmp.Copy(arr, i, j, m_nDegu+1, m_nDegv+1);
		
			for(int k=0; k<nu+2; k ++)
				for(int l=0; l<nv+2; l ++)
				{
					CPoint3D pt = Calculate(arTmp, 1.0*k/(nu+1), 1.0*l/(nv+1));
					m_arPoint(i*(nu+1)+k,j*(nv+1)+l) = pt;
				}
		}

}

void CBezierSpline::Draw(CDC* pDC)
{
	CPen* ppenOld = pDC->GetCurrentPen();
	const CSize shift(300, 300);
	CPen pen;
/*	for(int i=0; i<m_arPoint.SizeX();i++)
	{
		pDC->MoveTo(m_arPoint(i,0).m_x+shift.cx, m_arPoint(i,0).m_y+shift.cy); 
		for(int j=0; j<m_arPoint.SizeY();j++)
			pDC->LineTo(m_arPoint(i,j).m_x+shift.cx, m_arPoint(i,j).m_y+shift.cy);
	}
	for(i=0; i<m_arPoint.SizeY();i++)
	{
		pDC->MoveTo(m_arPoint(0,i).m_x+shift.cx, m_arPoint(0,i).m_y+shift.cy); 
		for(int j=0; j<m_arPoint.SizeX();j++)
			pDC->LineTo(m_arPoint(j,i).m_x+shift.cx, m_arPoint(j,i).m_y+shift.cy);
	}*/
	for(int i=0; i<m_nsurf.cx; i ++)
		for(int j=0; j<m_nsurf.cy; j ++)
		{
			pDC->SelectObject(ppenOld);
			pen.DeleteObject();
			pen.CreatePen(PS_SOLID, 1, RGB((255-(i+j)*11)%255, ((i+j)*31+200)%255, ((i+j)*67)%255 )); 
			pDC->SelectObject(&pen);
			for(int k=0; k< m_nexpoint.cx+2; k ++)
			{
				CPoint3D ptStart = m_arPoint(i*(m_nexpoint.cx+1)+k,j*(m_nexpoint.cy+1));
				pDC->MoveTo(static_cast<int>(ptStart.m_x)+shift.cx, static_cast<int>(ptStart.m_y)+shift.cy);
				for(int l=0; l<m_nexpoint.cy+2; l ++)
				{
					CPoint3D ptNext = m_arPoint(i*(m_nexpoint.cx+1)+k,j*(m_nexpoint.cy+1)+l);
					pDC->LineTo(static_cast<int>(ptNext.m_x)+shift.cx, static_cast<int>(ptNext.m_y)+shift.cy);
				}
			}
			for(int l=0; l< m_nexpoint.cy+2; l ++)
			{
				CPoint3D ptStart = m_arPoint(i*(m_nexpoint.cx+1),j*(m_nexpoint.cy+1)+l);
				pDC->MoveTo(static_cast<int>(ptStart.m_x)+shift.cx, static_cast<int>(ptStart.m_y)+shift.cy);
				for(int k=0; k<m_nexpoint.cx+2; k ++)
				{
					CPoint3D ptNext = m_arPoint(i*(m_nexpoint.cx+1)+k,j*(m_nexpoint.cy+1)+l);
					pDC->LineTo(static_cast<int>(ptNext.m_x)+shift.cx, static_cast<int>(ptNext.m_y)+shift.cy);
				}
			}
		}
	pDC->SelectObject(ppenOld);
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 2, RGB(127, 127, 127)); 
	pDC->SelectObject(&pen);
	for(int i=0; i<m_arCarcas.SizeX();i++)
	{
		pDC->MoveTo(static_cast<int>(m_arCarcas(i,1).m_x)+shift.cx, static_cast<int>(m_arCarcas(i,1).m_y)+shift.cy);
		for(int j=1; j<m_arCarcas.SizeY()-1;j++)
			pDC->LineTo(static_cast<int>(m_arCarcas(i,j).m_x)+shift.cx, static_cast<int>(m_arCarcas(i,j).m_y)+shift.cy);
	}
	for(int i=1; i<m_arCarcas.SizeY()-1;i++)
	{
		pDC->MoveTo(static_cast<int>(m_arCarcas(0,i).m_x)+shift.cx, static_cast<int>(m_arCarcas(0,i).m_y)+shift.cy);
		for(int j=0; j<m_arCarcas.SizeX();j++)
			pDC->LineTo(static_cast<int>(m_arCarcas(j,i).m_x)+shift.cx, static_cast<int>(m_arCarcas(j,i).m_y)+shift.cy);
		pDC->LineTo(static_cast<int>(m_arCarcas(0,i).m_x)+shift.cx, static_cast<int>(m_arCarcas(0,i).m_y)+shift.cy);
	}
	pDC->SelectObject(ppenOld);
} 

CPoint3D CBezierSpline::Calculate(const Array2D<CPoint3D>& arr, double u, double v)
{ 
	if(arr.SizeX() != (m_nDegu+1) || arr.SizeY() != (m_nDegv+1))
		throw std::exception();
	ASSERT(m_nDegv == 3 && m_nDegu == 3);
	CPoint3D tmp (0.0, 0.0, 0.0);
	double coefu[4], coefv[4];
	if(m_uclose == SP_ELEMCLOSE || m_uclose == SP_ELEMNOTCLOSE)
	{
		coefu[0] = (1-u)*(1-u)*(1-u)/6;
		coefu[1] = (4-6*u*u+3*u*u*u)/6;
		coefu[2] = (1+3*u+3*u*u-3*u*u*u)/6;
		coefu[3] = u*u*u/6;
	}
	else
	{
		coefu[0] = (1-u)*(1-u)*(1-u);
		coefu[1] = 3*u*(1-u)*(1-u);
		coefu[2] = 3*u*u*(1-u);
		coefu[3] = u*u*u;
	}
	if(m_vclose == SP_ELEMCLOSE || m_vclose == SP_ELEMNOTCLOSE)
	{
		coefv[0] = (1-v)*(1-v)*(1-v)/6;
		coefv[1] = (4-6*v*v+3*v*v*v)/6;
		coefv[2] = (1+3*v+3*v*v-3*v*v*v)/6;
		coefv[3] = v*v*v/6;
	}
	else
	{
		coefv[0] = (1-v)*(1-v)*(1-v);
		coefv[1] = 3*v*(1-v)*(1-v);
		coefv[2] = 3*v*v*(1-v);
		coefv[3] = v*v*v;
	}
	for(int i = 0; i <= m_nDegu; i ++ )
		for(int j = 0; j <= m_nDegv; j ++)
		{
/*			double coef = Soch(m_nDegu, i)*Soch(m_nDegv, j)*pow(u,i)*pow(1.0-u,m_nDegu-i)*pow(v,j)*pow(1.0-v,m_nDegv-j); 
			tmp.m_x += coef*arr(i,j).m_x; 	
			tmp.m_y += coef*arr(i,j).m_y;
			tmp.m_z += coef*arr(i,j).m_z;*/
			tmp.m_x += coefu[i]*coefv[j]*arr(i,j).m_x;
			tmp.m_y += coefu[i]*coefv[j]*arr(i,j).m_y;
			tmp.m_z += coefu[i]*coefv[j]*arr(i,j).m_z;
		}
	return tmp;
}

void	CBezierSpline::RotateX(int ang)
{
	for(int i=0; i < m_arPoint.SizeX(); i++)
		for(int j=0; j < m_arPoint.SizeY(); j++)
			m_arPoint(i,j).RotateX(ang); 
	for(int i=0; i < m_arCarcas.SizeX(); i++)
		for(int j=0; j < m_arCarcas.SizeY(); j++)
			m_arCarcas(i,j).RotateX(ang); 
}

void	CBezierSpline::RotateY(int ang)
{
	for(int i=0; i < m_arPoint.SizeX(); i++)
		for(int j=0; j < m_arPoint.SizeY(); j++)
			m_arPoint(i,j).RotateY(ang); 
	for(int i=0; i < m_arCarcas.SizeX(); i++)
		for(int j=0; j < m_arCarcas.SizeY(); j++)
			m_arCarcas(i,j).RotateY(ang); 
}

void	CBezierSpline::RotateZ(int ang)
{
	for(int i=0; i < m_arPoint.SizeX(); i++)
		for(int j=0; j < m_arPoint.SizeY(); j++)
			m_arPoint(i,j).RotateZ(ang); 
	for(int i=0; i < m_arCarcas.SizeX(); i++)
		for(int j=0; j < m_arCarcas.SizeY(); j++)
			m_arCarcas(i,j).RotateZ(ang); 
}

void	CBezierSpline::Translate(double x, double y, double z)
{
	for(int i=0; i < m_arPoint.SizeX(); i++)
		for(int j=0; j < m_arPoint.SizeY(); j++)
			m_arPoint(i,j).Translate(x,y,z); 
}