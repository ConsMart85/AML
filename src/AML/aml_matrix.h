/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/


#ifndef _INCLUDE_AML_MATRIX_2012_9_9
#define _INCLUDE_AML_MATRIX_2012_9_9

#include "aml_memory.hpp"


/************************************************************************/
/*
/************************************************************************/
template <class T>
AML_CLASS aml_matrix
{
public:


	aml_matrix()
	{
		m_autoData = aml_allocator<T>(1);
		m_siRows = 1;
		m_siCols = 1;
	}

	aml_matrix(aml_size rows, aml_size cols = 0) 
	{
		if(cols == 0)
			cols = rows;

		if((rows <= 0) ||(cols <= 0) )
		{
			throw aml_exception_param("Invalid parameters.");
		}

		aml_size size = rows * cols;
		m_autoData = aml_allocator<T>(size);
		m_siRows = rows;
		m_siCols = cols;

	}


#if (WINVER > 0x0400 )
	aml_matrix(const aml_matrix<T>& src )
	{
		aml_size size = src.GetRowCount() * src.GetColCount();
		m_autoData = aml_allocator<T>(size);
		m_autoData.SetMemory(src.GetBuf(), src.GetElementsCount());
		m_siRows = src.GetRowCount();
		m_siCols = src.GetColCount();
	}

#endif
	
	template<class OtherT>
	aml_matrix(const aml_matrix<OtherT>& src )
	{
		  m_autoData.Resize(src.GetElementsCount());
		  m_autoData.SetMemory(src.GetBuf(), src.GetElementsCount() );
		  m_siRows = src.GetRowCount();
		  m_siCols = src.GetColCount();
	}
	
public:


	AML_INLINE(T*) GetBuf() const 
	{
		return m_autoData.GetBuf();
	}
	

	AML_INLINE(aml_size) GetRowCount() const
	{
		return m_siRows;
	}


	AML_INLINE(aml_size) GetColCount() const
	{
		return m_siCols;
	}


	AML_INLINE(aml_size) GetElementsCount() const
	{
		return m_autoData.GetCount();
	}

	void  Reset(aml_size rows, aml_size cols = 0)
	{
		if(cols == 0)
			cols = rows;

		if((rows <= 0) || (cols <= 0))
		{

			throw aml_exception_param("Invalid parameters.");

		}

		m_autoData.Resize(rows * cols);
		m_siRows = rows;
		m_siCols = cols;
	}


	void Set(T value, ...)
	{
		T* parg = &value;

		for(int i = 0; i <m_rows * m_cols; i++ )
		{
			m_autoData.SetAt(i, *parg);
			parg++;
		}
	}

	void SetAt(aml_uint pos, T value )
	{
		m_autoData.SetAt(pos, value);
	}

	void SetAt(aml_uint rows, aml_uint cols, T value )
	{
		aml_uint pos = rows * m_siCols + cols;
		m_autoData.SetAt(pos, value);
	}


	T GetAt(aml_uint rows, aml_uint cols)
	{
		aml_uint pos = rows * m_siCols + cols;
		return m_autoData.GetAt(pos);
	}

	T GetElement(aml_uint pos)
	{
		return m_autoData.GetAt(pos);
	}


	aml_matrix<T> GetRow(aml_uint row)
	{
		if(row >= m_siRows)
		{

			throw aml_exception_param("Invalid parameters.");


		}
		
		aml_matrix<T> matRet(1, m_siCols);

		for(aml_count j = 0 ; j < m_siCols ; j++)
		{
			aml_uint pos = row * m_siCols + j;
			matRet(j) = m_autoData(pos);
		}

		return matRet;
	}


	aml_matrix<T> GetCol(aml_uint col)
	{
		if(col >= m_siCols)
		{
			throw aml_exception_param("Invalid parameters.");
		}

		aml_matrix<T> matRet( m_siRows, 1);

		for(aml_count i = 0 ; i < m_siRows ; i++)
		{
			aml_uint pos = i * m_siCols + col;
			matRet(i) = m_autoData(pos);
		}

		return matRet;
	}


	aml_matrix<T> GetSubMatrix(aml_uint rstart, aml_uint cstart, aml_uint rend, aml_uint cend)
	{
		if(((rend - rstart) <= 0) || ((cend - cstart) <= 0))
		{
			throw aml_exception_param("Invalid parameters.");
		}

		aml_matrix<T> matRet(rend - rstart, cend - cstart) ;

		for(aml_count i = rstart ; i < rend - rstart ; i++)
			for(aml_count j = cstart ; j < cend ; j++)
			{
				aml_uint pos = i * m_siCols + j;
				matRet(i - rstart, j - cstart) = m_autoData(pos);
			}

		return matRet; 

	}

	aml_matrix<T> Spread(bool rowdirect = true)
	{
		matrixd matRet = matrixd(this->GetElementsCount(), 1);

		aml_count id = 0;

		if(rowdirect)
		{
			for(aml_count i = 0; i < m_siCols; i++)
			{
				for(aml_count j =0; j < m_siRows; j++ )
				{
					aml_count pos = j * m_siCols + i;
					matRet(id) = m_autoData(pos);
					id++;
				}
			}
		}
		else
		{
			for(aml_count i = 0; i < m_siRows; i++)
			{
				for(aml_count j =0; j < m_siCols; j++ )
				{
					aml_count pos = i * m_siCols + j;
					matRet(id) = m_autoData(pos);
					id++;
				}
			}
		}
	
		return matRet;
	}


	aml_size SizeOfType() const
	{
		return sizeof(T);
	}

	
	aml_matrix<T>& operator =(const aml_matrix<T>& src)
	{
		m_autoData.Resize(src.GetElementsCount());
		m_autoData.SetMemory(src.GetBuf(), src.GetElementsCount());		
		m_siRows = src.GetRowCount();
		m_siCols = src.GetColCount();
		return *this;
	}

	T& operator()(aml_uint rows, aml_uint cols = 0)
	{

		if((m_siRows == 1) && (cols == 0))
		{
			cols = rows;
			rows = 0;
		}
		
		aml_uint pos = rows * m_siCols + cols;

		return m_autoData(pos);

	}

	aml_matrix<T> operator +(const aml_matrix<T>& tgt)
	{
		if((m_siCols != tgt.GetColCount()) || (m_siRows != tgt.GetRowCount()))
		{
			throw aml_exception_param("Invalid parameters.");
		}

		aml_matrix<T> matRet = aml_matrix<T>(*this);
		aml_matrix<T> matTgt = tgt;

		for(aml_count i = 0; i < m_siRows; i++)
		{
			for(aml_count j = 0; j < m_siCols; j++)
			{
				matRet(i, j) += matTgt(i, j);
			}
		}

		return matRet;

	}

	aml_matrix<T> operator +( T value)
	{
		
		aml_matrix<T> matRet = aml_matrix<T>(*this);

		for(aml_count i = 0; i < m_siRows; i++)
		{
			for(aml_count j = 0; j < m_siCols; j++)
			{
				matRet(i, j) += value;
			}
		}

		return matRet;

	}

	aml_matrix<T> operator -( T value)
	{

		aml_matrix<T> matRet = aml_matrix<T>(*this);

		for(aml_count i = 0; i < m_siRows; i++)
		{
			for(aml_count j = 0; j < m_siCols; j++)
			{
				matRet(i, j) -= value;
			}
		}

		return matRet;

	}

	aml_matrix<T> operator -(const aml_matrix<T>& tgt)
	{
		if((m_siCols != tgt.GetColCount()) || (m_siRows != tgt.GetRowCount()))
		{
			throw aml_exception_param("Invalid parameters.");
		}

		aml_matrix<T> matRet = aml_matrix<T>(*this);
		aml_matrix<T> matTgt = tgt;

		for(aml_count i = 0; i < m_siRows; i++)
		{
			for(aml_count j = 0; j < m_siCols; j++)
			{
				matRet(i, j) -= matTgt(i, j);
			}
		}

		return matRet;
	}

	aml_matrix<T> operator *(T value)
	{
		aml_count size = m_siCols * m_siRows;
		aml_matrix<T> matRet = aml_matrix<T>(*this);

		for(aml_count i = 0; i < m_siRows; i++)
		{
			for(aml_count j = 0; j < m_siCols; j++)
			{
				matRet(i, j) *= value;
			}
		}

		return matRet;
	}

	aml_matrix<T> operator *(const aml_matrix<T> tgt)
	{
		if(m_siCols != tgt.GetRowCount())
		{
			throw aml_exception_param("You can not multiply with these matrices .");
		}

		aml_size rows = m_siRows;
		aml_size cols =  tgt.GetColCount();
		aml_matrix<T> matRet = aml_matrix<T>(rows, cols);
		aml_matrix<T> matTgt = tgt;


		for(aml_count i = 0; i < rows; i++)
			for(aml_count j =0; j < cols; j++)
				for( aml_count k = 0; k < m_siCols; k++)
					matRet(i, j) += m_autoData( k + i * m_siCols) * matTgt( k, j);
					
			return matRet;
	}

	aml_matrix<T> operator /(T value)
	{
		aml_count size = m_siCols * m_siRows;
		aml_matrix<T> matRet = aml_matrix<T>(*this);

		for(aml_count i = 0; i < m_siRows; i++)
		{
			for(aml_count j = 0; j < m_siCols; j++)
			{
				matRet(i, j) /= value;
			}
		}

		return matRet;
	}

	bool operator >(T value)
	{
		if(m_autoData(0) > value)
			return true;

		return false;
	}

	bool operator <(T value)
	{
		if(m_autoData(0) < value)
			return true;

		return false;
	}

	bool operator >=(T value)
	{
		if(m_autoData(0) > value)
			return true;

		return false;
	}

	bool operator <=(T value)
	{
		if(m_autoData(0) < value)
			return true;

		return false;
	}

	bool operator >(const aml_matrix<T>& tgt)
	{
		aml_matrix<T> matTgt = tgt;

		if(m_autoData(0) > matTgt.GetElement(0))
			return true;
		
		return false;
	}

	bool operator <(const aml_matrix<T>& tgt)
	{
		aml_matrix<T> matTgt = tgt;

		if(m_autoData(0) < matTgt.GetElement(0))
			return true;

		return false;
	}

	bool operator >=(const aml_matrix<T>& tgt)
	{
		aml_matrix<T> matTgt = tgt;

		if(m_autoData(0) >= matTgt.GetElement(0))
			return true; 

		return false;
	}

	bool operator <=(const aml_matrix<T>& tgt)
	{
		aml_matrix<T> matTgt = tgt;

		if(m_autoData(0) <= matTgt.GetElement(0))
			return true;

		return false;
	}	

	aml_matrix<T>& operator +=(const aml_matrix<T>& tgt)
	{
		if((m_siCols != tgt.GetColCount()) || (m_siRows != tgt.GetRowCount()))
		{
			throw aml_exception_param("Invalid parameters.");
		}
		
		aml_count size = m_siCols * m_siRows;

		for(aml_count i = 0; i < size; i++)
			m_autoData(i) += tgt.GetElement(i);

		return *this;
		
	}

	aml_matrix<T>& operator +=(T value)
	{
		aml_count size = m_siCols * m_siRows;

		for(aml_count i = 0; i < size; i++)
			m_autoData(i) +=value;

		return *this;
	}

	aml_matrix<T>& operator -=(const aml_matrix<T>& tgt)
	{
		if((m_siCols != tgt.GetColCount()) || (m_siRows != tgt.GetRowCount()))
		{
			throw aml_exception_param("Invalid parameters.");
		}

		aml_count size = m_siCols * m_siRows;

		for(aml_count i = 0; i < size; i++)
			m_autoData(i) -= tgt.GetElement(i);

		return *this;

	}

	aml_matrix<T>& operator *= (T value)
	{
		aml_count size = m_siCols * m_siRows;

		for(aml_count i = 0; i < size; i++)
			m_autoData(i) *= value;
	}


protected:
		aml_allocator<T> m_autoData; /* ªÙµÍ */

		aml_size m_siRows; /* √‘ */
		aml_size m_siCols; /* µ€ */
};

#define matrix aml_matrix
// #define matrixi aml_matrix<aml_int>
// #define matrixd aml_matrix<aml_double>
// #define matrixf aml_matrix<aml_float>

typedef aml_matrix<aml_int> matrixi;
typedef aml_matrix<aml_double> matrixd;
typedef aml_matrix<aml_float> matrixf;

#endif
