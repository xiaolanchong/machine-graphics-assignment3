// splineView.h : interface of the CSplineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEVIEW_H__9FB9D21B_A18B_4876_9B0B_B1C1F68F157F__INCLUDED_)
#define AFX_SPLINEVIEW_H__9FB9D21B_A18B_4876_9B0B_B1C1F68F157F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSplineView : public CView
{
protected: // create from serialization only
	CSplineView();
	DECLARE_DYNCREATE(CSplineView)

// Attributes
public:
	CSplineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplineView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	enum			MOUSE_STATE{MS_CASUAL, MS_DRAG};
	MOUSE_STATE		m_ms;
	CPoint			m_ptPrev;
	int				m_nBasisPoint;
	CRect			m_rcPrev;

	HCURSOR			m_hCasual;
	HCURSOR			m_hDrag;

	void			ResetDrag();
	void			SetDrag(CPoint);
	void			DrawBSpline(CDC* pDC);
// Generated message map functions
protected:
	//{{AFX_MSG(CSplineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in splineView.cpp
inline CSplineDoc* CSplineView::GetDocument()
   { return (CSplineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLINEVIEW_H__9FB9D21B_A18B_4876_9B0B_B1C1F68F157F__INCLUDED_)
