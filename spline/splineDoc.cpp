// splineDoc.cpp : implementation of the CSplineDoc class
//

#include "stdafx.h"
#include "spline.h"

#include "splineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplineDoc

IMPLEMENT_DYNCREATE(CSplineDoc, CDocument)

BEGIN_MESSAGE_MAP(CSplineDoc, CDocument)
	//{{AFX_MSG_MAP(CSplineDoc)
	ON_COMMAND(ID_CURVES_BASIC, OnCurvesBasic)
	ON_COMMAND(ID_CURVES_CLOSE, OnCurvesClose)
	ON_COMMAND(ID_CURVES_ELEM, OnCurvesElem)
	ON_COMMAND(ID_CURVES_SURFACE, OnCurvesSurface)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplineDoc construction/destruction

CSplineDoc::CSplineDoc() :
	m_surf(false),
	m_pAct(&m_splbas),
	m_PrevMenu(ID_CURVES_BASIC)
{
	// TODO: add one-time construction code here
	VecPoint	arr;
	arr.push_back(CPoint(50, 50));
	arr.push_back(CPoint(100, 350));
	arr.push_back(CPoint(250, 300));
	arr.push_back(CPoint(400, 100));
/*	arr.push_back(CPoint(500, 50));
	arr.push_back(CPoint(600, 100));*/
	////////////////////////////////
	srand( (unsigned)time( NULL ) );
	const int nx = 7;
	const int ny = 6;
	const int rx = 100;
	const int ry = 75;
	const int rz = 75;	
	Array2D<CPoint3D> vec(nx,ny);
	try
	{
	const double PI = 3.1415;
	for(int i=0; i<nx; i++)
		for(int j=0; j<ny;j++)
		{
			vec(i,j) = CPoint3D(rx*cos(i*2*PI/nx), ry*sin(i*2*PI/nx), rz*j );
//			vec(i,j) = CPoint3D(rx*cos(i*2*PI/nx)*sqrt(j), ry*sin(i*2*PI/nx)*sqrt(j), rz*j );
/*			vec(i,j) = CPoint3D(sqrt( (rz*ny/2)*(rz*ny/2) - (rz*(ny/2-j)*(rz*(ny/2-j)))) *cos(i*2*PI/nx), 
								sqrt( (rz*ny/2)*(rz*ny/2) - (rz*(ny/2-j)*(rz*(ny/2-j)))) *sin(i*2*PI/nx), rz*(ny/2-j) );*/
			vec(i,j).Translate(-rx/2, -ry/2, -rz/2);
			vec(i,j).RotateZ(60);
			vec(i,j).RotateX(45);
		}
	}
	catch(std::exception ex)
	{
		::AfxMessageBox(_T("exc"));
	}
	m_bspl.Create(3,3, vec, 3, 3, CBezierSpline::SP_ELEMCLOSE, CBezierSpline::SP_ELEMNOTCLOSE);
	m_splbas.Create(2, 30, arr, CBSpline::SP_BASIC);
	m_splper.Create(2, 30, arr, CBSpline::SP_PERIODIC);
	m_splclo.Create(2, 30, arr, CBSpline::SP_CLOSE);
}

CSplineDoc::~CSplineDoc()
{
}

BOOL CSplineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSplineDoc serialization

void CSplineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSplineDoc diagnostics

#ifdef _DEBUG
void CSplineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSplineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplineDoc commands

int CSplineDoc::GetPoint(CPoint pt, double rad)
{
	if(m_surf)
		return -1;
	for(int i=0; i < static_cast<int>(m_pAct->m_arCarcas.size()); i++)
	{
		CSize sz = pt - m_pAct->m_arCarcas[i];
		if( ( sz.cx * sz.cx + sz.cy * sz.cy ) < (rad*rad) )
			return i;
	}
	return -1;
}

void CSplineDoc::MovePoint(int nNum, CSize size)
{
	if(!m_surf)
	{
		ASSERT( nNum > -1 && nNum < m_pAct->m_arCarcas.size());
		m_pAct->m_arCarcas[nNum] += size;
	}
	else
	{
		m_bspl.RotateX(size.cy);
		m_bspl.RotateY(size.cx);
	}
}

void CSplineDoc::Draw(CDC* pDC)
{
	if(!m_surf)
		m_pAct->Draw(pDC);
	else
		m_bspl.Draw(pDC);
}

void CSplineDoc::OnCurvesBasic() 
{
	// TODO: Add your command handler code here
	m_pAct = &m_splbas;
	m_surf = false;
	POSITION pos = GetFirstViewPosition();
	GetNextView(pos)->Invalidate();
	SetMenu(ID_CURVES_BASIC);
}

void CSplineDoc::OnCurvesClose() 
{
	// TODO: Add your command handler code here
	m_pAct = &m_splclo;
	m_surf = false;
	POSITION pos = GetFirstViewPosition();
	GetNextView(pos)->Invalidate();	
	SetMenu(ID_CURVES_CLOSE);

}

void CSplineDoc::OnCurvesElem() 
{
	// TODO: Add your command handler code here
	m_pAct = &m_splper;
	m_surf = false;
	POSITION pos = GetFirstViewPosition();
	GetNextView(pos)->Invalidate();	
	SetMenu(ID_CURVES_ELEM);
}

void CSplineDoc::OnCurvesSurface() 
{
	// TODO: Add your command handler code here
//	m_pAct = &m_splbas;
	m_surf = true;
	POSITION pos = GetFirstViewPosition();
	GetNextView(pos)->Invalidate();	
	SetMenu(ID_CURVES_SURFACE);
}

void CSplineDoc::SetMenu(UINT id)
{
	CMenu	*pMain = NULL, *pSub = NULL;
	pMain	= ::AfxGetMainWnd()->GetMenu();
	if(!pMain)
		return;
	pSub	= pMain->GetSubMenu(1); //Curves;
	if(!pSub)
		return;
	pSub->CheckMenuItem(m_PrevMenu, MF_BYCOMMAND|MF_UNCHECKED);
	pSub->CheckMenuItem(id, MF_BYCOMMAND|MF_CHECKED);
	m_PrevMenu = id;
}