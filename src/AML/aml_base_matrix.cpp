/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/

#include <math.h>
#include "aml.h"
#include "aml_base_matrix.h"


#ifdef _TEST
#ifdef _DEBUG
#ifdef WIN32

void printMatrix( matrixd& mat, string name)
{
#define BUFSIZE	100

	//OutputDebugStr("\n");
	fprintf(stderr, " \n");
	//OutputDebugStr(name.c_str());
	//OutputDebugStr(" = \n");
	fprintf(stderr, name.c_str());
	fprintf(stderr, "= \n");

	for(aml_count i = 0; i < mat.GetRowCount(); i++)
	{
		for(aml_count j = 0; j < mat.GetColCount(); j++)
		{
			char szStr[BUFSIZE];
			_gcvt(mat(i, j), 10, szStr);

			//OutputDebugStr(szStr);
			//OutputDebugStr("  ");
			fprintf(stderr, szStr);
			fprintf(stderr, "  ");

		}
		//OutputDebugStr("\n");
		fprintf(stderr, " \n");
	}

}

#endif // WIN32
#endif // _DEBUG
#endif // _TEST


matrixd abs(const matrixd& src)
{
	matrixd matRet(src);

	for( aml_count i = 0 ; i < matRet.GetRowCount() ; i++ )
		for( aml_count j = 0 ; j < matRet.GetColCount(); j++)
			matRet(i, j) = abs(matRet(i, j));

	return matRet;

}

matrixd diag(const matrixd& src)
{
	aml_size size = src.GetRowCount();
	matrixd matSrc = src;

	if((src.GetColCount() != 1) && (src.GetRowCount() != 1) )
	{
		if(size > src.GetColCount() )
			size = src.GetColCount();

		matrixd matRet(size,1);


		for(aml_count i = 0; i < size ; i++)
			matRet(i) = matSrc(i, i);

		//printmat(matRet, " Return Matrix (diag)");
		return matRet;
	}

	if(size < src.GetColCount() )
		size = src.GetColCount();

	matrixd matRet(size);

	for(aml_count i = 0; i < size ; i++)
		matRet(i, i) = matSrc(i);

	//printmat(matRet, " Return Matrix (diag)");

	return matRet;	
}


matrixd exp(const matrixd& src )
{
	matrixd matRet(src.GetRowCount(), src.GetColCount());
	matrixd matSrc = src;
	const aml_double E = 2.7189;

	for(aml_count i = 0 ; i < matSrc.GetRowCount();i++)
		for(aml_count j = 0 ; j < matSrc.GetColCount();j++)
			matRet(i,j) = pow(E,matSrc(i,j));

	return matRet;

}

matrixd eye(aml_size size)
{
	matrixd matRet = matrixd(size);
	
	for(aml_count i = 0; i < size; i++)
		for(aml_count j = 0; j < size; j++)
			if(i == j)
				matRet(i, j) = 1;

	//printmat(matRet, " Return Matrix (eye)");
	return matRet;

}

matrixd inv(const matrixd& src)
{

	matrixd matTemp = src;
	aml_size rows = src.GetRowCount();
	aml_size cols = src.GetColCount();
	matrixd  matRet= eye(rows);
	aml_count i;

	for(i = 0; i < rows; i++)
	{
		if(matTemp(i, i) == 0)
		{
			for( aml_count row = 0; row < rows; row++)
			{
				if(matTemp(i, row) != 0)
				{
					swaprows(matTemp, i, row);
					swaprows(matRet, i, row);
					break;
				}
			}
		}
	}


	for( i = 0; i < rows; i++)
	{
		aml_double num = matTemp(i, i);

		for(aml_count j = 0; j < cols; j++ )
		{
			matTemp(i, j) /= num;
			matRet(i, j) /= num;
		}

		for(aml_count k = 0; k < rows ; k++)
		{
			if(k != i)
			{
				aml_double leading = matTemp(k, i);

				for(aml_count j = 0; j < cols; j++)
				{
					matTemp(k, j) -= matTemp(i, j) * leading;
					matRet(k, j) -= matRet(i, j) * leading;
				}
			}
		}

	}
	//printmat(matRet, " Return Matrix");
	//printmat(matTemp, " Temp Matrix");

	return matRet;

}


bool issquare(const matrixd& src)
{
	if(src.GetColCount() == src.GetRowCount())
		return true;

	return false;
}


matrixd leftdivide(const matrixd& src, const matrixd& tgt)
{
	matrixd matRet;

	if(src.GetColCount() == src.GetRowCount())
	{
		matrixd matSrc = inv(src);
		matRet = matSrc * tgt;
	}
	else
	{
		matrixd matSrc = src;

		matRet = inv(transpose(matSrc) * matSrc) * (transpose(matSrc) * tgt);
	}


	return matRet;
}


matrixd merge(const matrixd& src1, const matrixd& src2, aml_uint direct)
{

	matrixd matRet;
	matrixd matSrc1 = src1;
	matrixd matSrc2 = src2;

	if(direct == AML_ROW)
	{
		if(matSrc1.GetColCount() != matSrc2.GetColCount())
		{

			throw aml_exception_param("Invalid parameters.");

		}
		matRet = matrixd(matSrc1.GetRowCount() + matSrc2.GetRowCount(), matSrc1.GetColCount());

		memcpy(matRet.GetBuf(), matSrc1.GetBuf(), sizeof(double) * matSrc1.GetElementsCount());
		memcpy(matRet.GetBuf() + matSrc1.GetElementsCount(), matSrc2.GetBuf(), sizeof(double)
			* matSrc2.GetElementsCount());
	}
	else
	{
		if(matSrc1.GetRowCount() != matSrc2.GetRowCount())
		{

			throw aml_exception_param("Invalid parameters.");

		}
		matRet = matrixd(matSrc1.GetRowCount() + matSrc2.GetRowCount(), matSrc1.GetColCount());

		aml_count rows = matSrc1.GetRowCount();
		aml_count col1 = matSrc1.GetColCount();
		aml_count col2 = 	matSrc2.GetColCount();	

		double* pbuf = matRet.GetBuf();
		double* pbufSrc1 = matSrc1.GetBuf();
		double* pbufSrc2 = matSrc2.GetBuf();


		for( aml_count i = 0; i < rows ; i++)
		{
			memcpy(pbuf, pbufSrc1, sizeof(double) * col1);
			pbuf += col1;
			memcpy(pbuf, pbufSrc2, sizeof(double) * col2);
			pbuf += col2;
			pbufSrc1 += col1;
			pbufSrc2 += col2;
		}

	}

	return matRet;
}


double norm(const matrixd src)
{
	double sum = 0;
	matrixd matSrc = src;

	for(aml_count i = 0; i < matSrc.GetElementsCount(); i++)
		sum += matSrc.GetElement(i) * matSrc.GetElement(i);

	sum = sqrt(sum);

	return sum;
}


matrixd ones(aml_size rows , aml_size cols )
{
	matrixd matRet(rows, cols);

	double* pbuf = matRet.GetBuf();

	memset(pbuf, 0x01, matRet.GetElementsCount() * sizeof(double));

	return matRet;
}


matrixd power(const matrixd& src,  aml_int p)
{
	matrixd matRet(src.GetRowCount(), src.GetColCount());
	matrixd matSrc = src;

	for(aml_count i = 0; i < matSrc.GetRowCount(); i++	)
		for(aml_count j = 0; j < matSrc.GetColCount(); j++)
		{
			matRet(i, j) = pow(matSrc(i, j), p);
		}

		return matRet;
}


matrixd rightdivide(const matrixd& src, const matrixd& tgt)
{

	if((src.GetRowCount() != tgt.GetRowCount()) && (src.GetColCount() != tgt.GetColCount()))
	{

		throw aml_exception_param("Invalid parameters.");

	}

	aml_count rows = src.GetRowCount();
	aml_count cols = src.GetColCount();

	matrixd matRet(rows, cols);
	matrixd matSrc = src;
	matrixd matTgt = tgt;

	for(aml_count i = 0 ; i < rows; i ++)
		for(aml_count j = 0 ; j <cols ; j++)
			matRet(i, j) = matSrc(i, j) / matTgt(i , j);

	return matRet;
}


matrixd sqrt(const matrixd& src)
{
	matrixd matRet(src.GetRowCount(), src.GetColCount());
	matrixd matSrc = src;

	for(aml_count i = 0; i < matSrc.GetRowCount(); i++	)
		for(aml_count j = 0; j < matSrc.GetColCount(); j++)
		{
			matRet(i, j) = sqrt(matSrc(i, j));
		}

		return matRet;
}


double sum( const matrixd& src )
{
	matrixd matSrc = src;
	double sum = 0;

	for(aml_count i = 0 ; i < src.GetElementsCount(); i++)
	{
		sum += matSrc.GetElement(i);
	}

	return sum;
}


matrixd summ( const matrixd& src )
{
	matrixd matSrc = src;
	aml_count cols = matSrc.GetColCount();
	aml_count rows = matSrc.GetRowCount(); 
	matrixd matRet(1, cols); 

	for(aml_count j = 0 ; j < cols ; j++)
	{
		for( aml_count i = 0; i < rows ; i++)
		{
			matRet(j) += matSrc(i, j);
		}
	}

	return matRet;
}

void swaprows(matrixd& src, aml_uint row1, aml_uint row2 )
{
	aml_count rows = src.GetRowCount();
	aml_count cols = src.GetColCount();

	if(row1 >= rows || row2 >= rows)
	{

		throw aml_exception_param("Invalid parameters.");

	}

	for(aml_count i = 0; i < cols; i++)
	{
		double v1 = src(row1, i);
		double v2 = src(row2, i);
		src(row1) = v2;
		src(row2) = v1;		
	}

}


matrixd transpose(const matrixd& src)
{
	aml_count rows = src.GetRowCount();
	aml_count cols = src.GetColCount();

	matrixd matRet = matrixd(cols, rows);
	matrixd matCloneSrc = src;

	for(aml_count i = 0; i < rows; i++)
		for(aml_count j = 0; j < cols; j++)
		{
			matRet(j, i) = matCloneSrc(i, j);
		}

	return matRet;
	
}

matrixd zeros(aml_size rows, aml_size cols)
{
	return matrixd(rows, cols);
}