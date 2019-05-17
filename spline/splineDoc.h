// splineDoc.h : interface of the CSplineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEDOC_H__AE0A7E2C_2708_4694_96A1_B62DCD8A49A3__INCLUDED_)
#define AFX_SPLINEDOC_H__AE0A7E2C_2708_4694_96A1_B62DCD8A49A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <exception>
#include "BSpline.h"
#include "BezierSpline.h"

class CSplineDoc : public CDocument
{
protected: // create from serialization only
	CSplineDoc();
	DECLARE_DYNCREATE(CSplineDoc)

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	void			Draw(CDC* pDC);
	int				GetPoint(CPoint pt, double rad);
	void			MovePoint(int nNum, CSize size);
	void			SetMenu(UINT id);
//	void			GetSplinePoint(VecPoint& vec) { m_spl.GetPoints(m_vecPoint, vec); };
//	const VecPoint&	GetBasisPoint() { return m_vecPoint; };

// Implementation
public:
	virtual ~CSplineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//	enum			STATE{BAS, CLO, PER};

	CBSpline		m_splbas;
	CBSpline		m_splper;
	CBSpline		m_splclo;
	CBSpline*		m_pAct;

	UINT			m_PrevMenu;
//	STATE			m_state;
public:
	CBezierSpline	m_bspl;
	bool			m_surf;
// Generated message map functions
protected:
	//{{AFX_MSG(CSplineDoc)
	afx_msg void OnCurvesBasic();
	afx_msg void OnCurvesClose();
	afx_msg void OnCurvesElem();
	afx_msg void OnCurvesSurface();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLINEDOC_H__AE0A7E2C_2708_4694_96A1_B62DCD8A49A3__INCLUDED_)
