/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/

#ifndef _INCLUDE_AML_BASE_2012_9_6
#define _INCLUDE_AML_BASE_2012_9_6


#define _TEST

#ifdef _TEST
#ifdef _DEBUG
#ifdef WIN32
void printMatrix( matrixd& mat, string name);
#define printmat printMatrix
#endif // WIN32
#endif // _DEBUG
#else
#define printmat 
#endif // _TEST

	// Matrix Operations 
	
	
	AML_API(matrixd) abs(const matrixd& src);	
	AML_API(matrixd) diag(const matrixd& src);
	AML_API(matrixd) eye(aml_size size);
	AML_API(matrixd) inv(const matrixd& src);
	AML_API(bool) issquare(const matrixd& src);	
	AML_API(matrixd) leftdivide(const matrixd& src, const matrixd& tgt);
	#define AML_ROW 1
	#define AML_COL 2
	AML_API(matrixd) merge(const matrixd& src1, const matrixd& src2, aml_uint direct = AML_ROW);
	AML_API(double) norm(const matrixd src);
	AML_API(matrixd) ones(aml_size rows , aml_size cols );
	AML_API(matrixd) power(const matrixd& src,  aml_int p);
	AML_API(matrixd) rightdivide(const matrixd& src, const matrixd& tgt);

	AML_API(matrixd) sqrt(const matrixd& src);
	AML_API(double) sum( const matrixd& src );	
	AML_API(matrixd) summ( const matrixd& src );
	AML_API(void) swaprows(matrixd& src, aml_uint row1, aml_uint row2 );
	AML_API(matrixd) transpose(const matrixd& src);		
	AML_API(matrixd) zeros(aml_size rows, aml_size cols);

	
	
#endif