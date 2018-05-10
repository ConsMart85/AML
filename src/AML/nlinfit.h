/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/


#ifndef _INCLUDE_NLINFIT_2012_9_6
#define _INCLUDE_NLINFIT_2012_9_6

typedef matrixd (AML_STDCALL  *modelfunc)( matrixd& beta, matrixd& x);
typedef matrixd (AML_STDCALL  *modelfunc2)( matrixd& beta, matrixd& x, matrixd& param );


AML_API(matrixd) nlinfit(const matrixd& X, const matrixd& y, modelfunc model, const matrixd& beta ) ;
AML_API(matrixd) nlinfit2(const matrixd& X, const matrixd& y, modelfunc2 model, const matrixd& beta, const matrixd param) ;


#endif