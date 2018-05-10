// calcN.cpp : Defines the entry point for the console application.
//
#include "aml.h"
#include "nlinfit.h"
#include <conio.h>
/************************************************************************/
/* Test nlinfit . Below code is equal with following matlab code.
/* 
/* clc
/* load reaction
/* betafit = nlinfitc(reactants,rate,@hougen,beta);
/* betafit
/* 
/************************************************************************/


matrixd  AML_STDCALL model2(matrixd& beta, matrixd& x, matrixd& param );
matrixd  AML_STDCALL model2(matrixd& beta, matrixd& x, matrixd& param)
{
	aml_size rows = x.GetRowCount();
	aml_size cols = x.GetColCount();

	matrixd xx = zeros(rows, cols);
	matrixd matRet;

	aml_size peak_counts = (aml_size)param(0, 0);
	matrixd ss = zeros(peak_counts + 1, cols);

	for( aml_count i = 0; i < peak_counts ; i++)
	{
		double amp = beta(i * 3 - 2, 0);
		double ap = beta(i * 3 - 1, 0);
		double sp = beta(i * 3, 0);

		if((amp >=0) && (ap <= (param( i * 4 - 2 , 0) + param( i * 4, 0))) 
			&& (ap>=param(i*4-2,0)-param(i*4,0)) )
		{
			if((sp <= (param(i*4-1, 0)+param(i*4+1, 0))) && (sp >= (param(i*4-1, 0) -param(i*4+1, 0))) )
			{

			}

		}
	}


	return matRet;
}

int main(int argc, char* argv[])
{
//	matrixd yfit = nlinfit(matReact, matRate, model2, beta);
//	printmat(yfit,"yfit");
	getchar();
	return 0;
}
