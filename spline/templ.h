// templ.h: interface for the templ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMPL_H__87C118B5_9001_49CC_981E_2252ED4D5E65__INCLUDED_)
#define AFX_TEMPL_H__87C118B5_9001_49CC_981E_2252ED4D5E65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <exception>

template <class T> class Array2D
{
public:
	Array2D();
	Array2D(int sizex, int sizey);
	Array2D(const Array2D& arr);
	Array2D& operator=(const Array2D& arr);
	void	Alloc(int nx, int ny);
	virtual ~Array2D();
	T&	operator()(int x, int y) throw(std::exception);
	const T&	operator()(int x, int y) const throw(std::exception);
	void	Copy(const Array2D& arr, int x, int y, int sizex, int sizey);
	int SizeX() const { return m_sizex; };
	int SizeY() const { return m_sizey; };
private:
	void	Allocate();
	void	Free();

	T**		m_ppT;
	int		m_sizex;
	int		m_sizey;
};

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
	Allocate();
}

template<class T> Array2D<T>::Array2D(const Array2D& arr):
	:	m_sizex(arr.m_sizex),
		m_sizey(arr.m_sizey),
		m_ppT(NULL)
{
	Allocate();
	for(int i=0; i < m_sizex; i++)
		for(int j=0; j < m_sizey; j++)
			m_ppT[i][j] = arr.m_ppT[i][j]; 
}

template<class T> Array2D<T>::~Array2D()
{
	Free();
}

template<class T> T& Array2D<T>::operator()(int x, int y)
{
	if( /*x >= m_sizex || y >= m_sizey ||*/ m_ppT == NULL)
		throw std::exception();
	return m_ppT[x%m_sizex][y%m_sizey];
}

template<class T> const T& Array2D<T>::operator()(int x, int y) const
{
	if( /*x >= m_sizex || y >= m_sizey ||*/ m_ppT == NULL)
		throw std::exception();
	return m_ppT[x%m_sizex][y%m_sizey];
}

template<class T> Array2D<T>& Array2D<T>::operator=(const Array2D& arr)
{
	if(this == &arr) return *this;
	Free();
	m_sizex = arr.m_sizex;
	m_sizey = arr.m_sizey;
	Allocate();
	for(int i=0; i < m_sizex; i++)
		for(int j=0; j < m_sizey; j++)
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
	m_ppT = new T*[m_sizex];
	for(int i = 0; i < m_sizex; i++)
	{
		m_ppT[i] = new T[m_sizey];
	}
}

template<class T> void Array2D<T>::Free()
{
	if(m_ppT)
	{
		for(int i = 0; i < m_sizex; i++)
			delete[] m_ppT[i];
		delete[] m_ppT;
	}
	m_sizex = 0;
	m_sizey = 0;
	m_ppT = NULL;
}

template<class T> void Array2D<T>::Copy(const Array2D& arr, int x, int y, int sizex, int sizey)
{
	if(SizeX() != sizex || SizeY() != sizey)
	{
		Free();
		m_sizex = sizex;
		m_sizey = sizey;
		Allocate();
	}
	for(int i=0; i < m_sizex; i++)
		for(int j=0; j < m_sizey; j++)
			m_ppT[i][j] = arr(i+x,j+y); 
}

#endif // !defined(AFX_TEMPL_H__87C118B5_9001_49CC_981E_2252ED4D5E65__INCLUDED_)
