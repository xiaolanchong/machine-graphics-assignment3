// splineView.cpp : implementation of the CSplineView class
//

#include "stdafx.h"
#include "spline.h"

#include "splineDoc.h"
#include "splineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#include <vector>
#include "Spline2.h"

/////////////////////////////////////////////////////////////////////////////
// CSplineView

IMPLEMENT_DYNCREATE(CSplineView, CView)

BEGIN_MESSAGE_MAP(CSplineView, CView)
	//{{AFX_MSG_MAP(CSplineView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplineView construction/destruction

CSplineView::CSplineView()
	:	m_ms(MS_CASUAL),
		m_hCasual(::LoadCursor(NULL, IDC_ARROW)),
		m_hDrag(::LoadCursor(NULL, IDC_CROSS)),
		m_nBasisPoint(-1)
{
	// TODO: add construction code here

}

CSplineView::~CSplineView()
{
}

BOOL CSplineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSplineView drawing

void CSplineView::OnDraw(CDC* pDC)
{
//	DrawBSpline(pDC);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CRect rect;
	GetClientRect(&rect);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CGdiObject* const oldBmp =  memDC.SelectObject(&bmp);
	memDC.FillSolidRect(&rect, RGB(255, 255, 255));

	CSplineDoc* pDoc = GetDocument();
//	pDoc->m_bspl.Draw(pDC);
	pDoc->Draw(&memDC);	
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBmp);
}

/////////////////////////////////////////////////////////////////////////////
// CSplineView diagnostics

#ifdef _DEBUG
void CSplineView::AssertValid() const
{
	CView::AssertValid();
}

void CSplineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSplineDoc* CSplineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplineDoc)));
	return (CSplineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplineView message handlers

void CSplineView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CSplineDoc* pDoc = GetDocument();
	::GetClipCursor(m_rcPrev);
//	SetTimer(0, 100, NULL);
	// TODO: Add your specialized code here and/or call the base class
}

void CSplineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CSplineDoc* pDoc = GetDocument();
	if( (m_nBasisPoint = pDoc->GetPoint(point, 4.0)) != -1)
	{
		SetDrag(point);
	}
	if(pDoc->m_surf)
		SetDrag(point);
	CView::OnLButtonDown(nFlags, point);
}

void CSplineView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CSplineDoc* pDoc = GetDocument();
	if(m_ms == MS_DRAG)
	{
		ResetDrag();
	}
	CView::OnLButtonUp(nFlags, point);
}

void CSplineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CSplineDoc* pDoc = GetDocument();
	if(m_ms == MS_DRAG)
	{
		pDoc->MovePoint(m_nBasisPoint, point - m_ptPrev );
/*		if(pDoc->m_surf)
		{
			pDoc->RotateY(point.x - m_ptPrev.y);
			pDoc->RotateZ(point.y - m_ptPrev.y);
		}*/
		m_ptPrev = point;
		Invalidate();
		 
	}
	CView::OnMouseMove(nFlags, point);
}

void CSplineView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(bActivate == FALSE)
	{
		ResetDrag();
	}
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CSplineView::ResetDrag()
{
	m_ms = MS_CASUAL;
	SetCursor(m_hCasual);
	::ClipCursor(&m_rcPrev);
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (long)m_hCasual);
}

void CSplineView::SetDrag(CPoint point )
{
	m_ms = MS_DRAG;
	m_ptPrev = point;
	m_hCasual = SetCursor(m_hDrag);
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (long)m_hDrag);
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	//	::GetClipCursor(&m_rcPrev);
	::ClipCursor(rc);
}

void CSplineView::DrawBSpline(CDC* /*pDC*/)
{
	CSplineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
/*	const VecPoint& vec = pDoc->GetBasisPoint();
	std::vector<CPoint> vecd;
	pDoc->GetSplinePoint(vecd);
	CPen *ppenOld, penSpline, penLine;
	penSpline.CreatePen(PS_SOLID, 2, RGB(255,0,0));
	penLine.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	ppenOld = pDC->SelectObject(&penLine);
	//////////////////////////////////////////
	pDC->MoveTo(vec[0].x, vec[0].y);
	for(int i = 1; i < vec.size(); i++)
	{
		pDC->LineTo(vec[i].x, vec[i].y);	
	}
	CPoint* mas = new CPoint[vec.size()];
	for(i = 0; i < vec.size(); i++)
	{
		mas[i] = vec[i];	
	}
	pDC->PolyBezier(mas, vec.size());
	delete []mas;
	///////////////////////////////////////////
	for(i = 0; i < vec.size(); i++)
	{
		pDC->Ellipse(vec[i].x-3, vec[i].y-3, vec[i].x+3, vec[i].y+3);	
	}
	pDC->SelectObject(&penSpline);
	//////////////////////////////////////////
	pDC->MoveTo(vecd[0].x, vecd[0].y);
	for(i = 1; i < vecd.size(); i++)
	{
		pDC->LineTo(vecd[i].x, vecd[i].y);	
	}
	pDC->SelectObject(ppenOld);*/
}

void CSplineView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CSplineDoc* pDoc = GetDocument();
	if(!pDoc->m_surf) return;
	static int xang = 1, yang = 2, zang = 3;
	static int cnt = 0;
	pDoc->m_bspl.RotateX(1);
	pDoc->m_bspl.RotateY(2);
	pDoc->m_bspl.RotateZ(3);
	Invalidate();
	CView::OnTimer(nIDEvent);
}


BOOL CSplineView::OnEraseBkgnd(CDC* /*pDC*/)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}
