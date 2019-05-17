// templ.cpp: implementation of the templ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "spline.h"
#include "templ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
template<class T> Array2D<T>::Array2D()
	:	m_sizex(0),
		m_sizey(0),
		m_ppT(NULL)
{
	//Allocate()
}

template<class T> Array2D<T>::Array2D(int sizex, int sizey)
	:	m_sizex(sizex),
		m_sizey(sizey),
		m_ppT(NULL)
{
	Allocate()
}

template<class T> Array2D<T>::Array2D(const Array2D& arr):
	:	m_sizex(arr.m_sizex),
		m_sizey(arr.m_sizey),
		m_ppT(NULL)
{
	Allocate();
	for(int i=0; i < m_sizey; i++)
		for(int j=0; j < m_sizex; j++)
			m_ppT[i][j] = arr.m_ppT[i][j]; 
}

template<class T> Array2D<T>::~Array2D()
{
	Free();
}

template<class T> T& Array2D<T>::operator()(int x, int y)
{
	if( x >= m_sizex || y >= m_sizey || m_ppT == NULL)
		throw std::exception();
	return m_ppT[x][y];
}

template<class T> Array2D<T>& Array2D<T>::operator=(const Array2D& arr)
{
	if(this == &arr) return *this;
	Free();
	m_sizex = arr.m_sizex;
	m_sizey = arr.m_sizey;
	Allocate();
	for(int i=0; i < m_sizey; i++)
		for(int j=0; j < m_sizex; j++)
			m_ppT[i][j] = arr.m_ppT[i][j]; 
	return *this;
}


template<class T> void Array2D<T>::Alloc(int nx, int ny)
{
	Free();
	m_sizex = nx;
	m_sizey = ny;
	Allocate();
}

template<class T> void Array2D<T>::Allocate()
{
	m_ppT = new T*[m_sizey];
	for(int i = 0; i < m_sizey; i++)
		m_ppT[i] = new T[m_sizex];
}

template<class T> void Array2D<T>::Free()
{
	if(m_ppT)
	{
		for(int i = 0; i < m_sizey; i++)
			delete[] m_ppT[i];
		delete[] m_ppT;
	}
	m_sizex = 0;
	m_sizey = 0;
	m_ppT = NULL;
}*/