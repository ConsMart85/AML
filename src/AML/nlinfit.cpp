/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/


#include <math.h>
#include "aml.h"
#include "nlinfit.h"

matrixd nlinfit(const matrixd& X, const matrixd& y, modelfunc model, const matrixd& beta )
{
	matrixd yfit;
	matrixd _X = X;
	matrixd _y = y;
	matrixd _beta = beta;
	
	try
	{
		yfit = model(_beta, _X);
		printmat(yfit, "First Output");
	}
	catch (aml_exception_base e)
	{
		throw e;
		
	}

	if(yfit.GetRowCount() != y.GetRowCount())
	{
		throw aml_exception_param("MODELFUN should return a vector of fitted values the same length as Y.");
	}

	matrixd betaold;
	matrixd sseold;


	aml_double maxiter = 200;
	aml_double betatol = 1.0000e-008;
	aml_double rtol  = 1.0000e-008;
	aml_double fdiffstep = 6.0555e-006;

	aml_uint n = _y.GetElementsCount();
	aml_uint p = _beta.GetElementsCount();
	const aml_double eps =  2.2204e-016;

	//printmat(_y, "_y");
	aml_double sqrteps = sqrt(eps);
	matrixd J(n, p);
	matrixd r =  _y.Spread() - yfit.Spread();
	//printmat(_y.Spread(),"Spread y");
	//printmat(r,"r");

	matrixd sse = transpose(r) * r;

	//printmat(sse,"sse");
	
	matrixd zbeta(_beta.GetRowCount(), _beta.GetColCount());
	matrixd zerosp(p, 1);


	aml_double lambda = 0.01;
	aml_double iter = 0;
	bool breakOut = false;

	while(iter < maxiter)
	{
		iter++;
		betaold = _beta;
		sseold = sse;
		//printmat(_beta,"_beta");
		//printmat(sse,"sse");
		//printmat(r, "r");

		for(aml_count k = 0; k < p; k++)
		{
			matrixd delta = zbeta;

			if(_beta(k) == 0)
			{
				double nb = sqrt(norm(_beta));
				delta(k) = fdiffstep * (nb + (nb == 0));
			}
			else
			{
				delta(k) = fdiffstep * _beta(k);
			}

			//printmat(delta,"delta");
			matrixd yplus = model(_beta + delta, _X);
			//printmat(yplus,"yplus");
			matrixd dy = yplus.Spread() - yfit.Spread();
			//printmat(dy,"dy");


			for( aml_count i = 0; i < J.GetRowCount(); i++)
				J(i, k) = dy(i) / delta(k);

			//printmat(J,"J");

		}

		matrixd matTem = summ(power(J, 2));
		//printmat(matTem,"matrix temp");

		matTem = diag(sqrt(matTem * lambda));
		//printmat(matTem,"matrix temp");

		matrixd Jplus = merge(J, matTem);
		//printmat(Jplus,"Jplus");
		matrixd rplus = merge(r, zerosp);
		//printmat(rplus,"rplus");
		matrixd step = leftdivide(Jplus, rplus);
		//printmat(step,"step");
		_beta = _beta.Spread();
		_beta = _beta + step;
		yfit = model(_beta, _X);
		//printmat(yfit,"yfit");
		r = _y.Spread() - yfit.Spread();
		sse = transpose(r) * r;
		//printmat(r,"r");
		//printmat(sse,"sse");

		if(sse < sseold)
			lambda = 0.1 * lambda;
		else
		{
			while(sse > sseold)
			{
				lambda = 10 * lambda;

				if(lambda > 1e16)
				{
					breakOut = true;
					break;
				}

				matTem = summ(power(J, 2));
				matTem = diag(sqrt(matTem * lambda));
				Jplus = merge(J, matTem);
				//printmat(Jplus,"Jplus");
				step = leftdivide(Jplus, rplus);
				//printmat(step,"step");
				_beta = betaold.Spread() + step;
				_beta = _beta.Spread();
				yfit = model(_beta, _X);

				r = _y.Spread() - yfit.Spread();
				//printmat(r, "r");
				sse = transpose(r) * r;
				//printmat(sse,"sse");
			}
		}

		aml_uint verbose = 0;

		if( verbose > 2 )
		{

		}

		if( norm(step) < betatol *(norm(_beta) + sqrteps))
		{
			if(verbose > 1)
			{

			}

			break;
		}
		else if(abs(sse - sseold) <= sse * rtol )
		{
			if(verbose > 1)
			{

			}

			break;
		}
		else if(breakOut)
		{
			break;
		}
		printmat(r, "r");
		printmat(yfit, " yfit");
		printmat(_beta, " beta");
		printmat(J, " J");


	}

	return _beta;
}

matrixd nlinfit2(const matrixd& X, const matrixd& y, modelfunc2 model, const matrixd& beta, const matrixd param) 
{

	matrixd yfit;
	matrixd _X = X;
	matrixd _y = y;
	matrixd _beta = beta;
	matrixd _param = param;

	try
	{
		yfit = model(_beta, _X, _param);
		printmat(yfit, "First Output");
	}
	catch (aml_exception_base e)
	{
		throw e;

	}

	if(yfit.GetRowCount() != y.GetRowCount())
	{
		throw aml_exception_param("MODELFUN should return a vector of fitted values the same length as Y.");
	}

	matrixd betaold;
	matrixd sseold;

	//100
	aml_double maxiter = 200;
	aml_double betatol = 1.0000e-008;
	aml_double rtol  = 1.0000e-008;
	aml_double fdiffstep = 6.0555e-006;

	aml_uint n = _y.GetElementsCount();
	aml_uint p = _beta.GetElementsCount();
	const aml_double eps =  2.2204e-016;

	//printmat(_y, "_y");
	aml_double sqrteps = sqrt(eps);
	matrixd J(n, p);
	matrixd r =  _y.Spread() - yfit.Spread();
	//printmat(_y.Spread(),"Spread y");
	//printmat(r,"r");

	matrixd sse = transpose(r) * r;

	//printmat(sse,"sse");

	matrixd zbeta(_beta.GetRowCount(), _beta.GetColCount());
	matrixd zerosp(p, 1);

	aml_double lambda = 0.01;
	aml_double iter = 0;
	bool breakOut = false;

	while(iter < maxiter)
	{
		iter++;
		betaold = _beta;
		sseold = sse;
		//printmat(_beta,"_beta");
		//printmat(sse,"sse");
		//printmat(r, "r");

		for(aml_count k = 0; k < p; k++)
		{
			matrixd delta = zbeta;

			if(_beta(k) == 0)
			{
				double nb = sqrt(norm(_beta));
				delta(k) = fdiffstep * (nb + (nb == 0));
			}
			else
			{
				delta(k) = fdiffstep * _beta(k);
			}

			//printmat(delta,"delta");
			matrixd yplus = model(_beta + delta, _X, _param);
			//printmat(yplus,"yplus");
			matrixd dy = yplus.Spread() - yfit.Spread();
			//printmat(dy,"dy");


			for( aml_count i = 0; i < J.GetRowCount(); i++)
				J(i, k) = dy(i) / delta(k);

			//printmat(J,"J");

		}

		matrixd matTem = summ(power(J, 2));
		//printmat(matTem,"matrix temp");

		matTem = diag(sqrt(matTem * lambda));
		//printmat(matTem,"matrix temp");

		matrixd Jplus = merge(J, matTem);
		//printmat(Jplus,"Jplus");
		matrixd rplus = merge(r, zerosp);
		//printmat(rplus,"rplus");
		matrixd step = leftdivide(Jplus, rplus);
		//printmat(step,"step");
		_beta = _beta.Spread();
		_beta = _beta + step;
		yfit = model(_beta, _X, _param);
		//printmat(yfit,"yfit");
		r = _y.Spread() - yfit.Spread();
		sse = transpose(r) * r;
		//printmat(r,"r");
		//printmat(sse,"sse");

		if(sse < sseold)
			lambda = 0.1 * lambda;
		else
		{
			while(sse > sseold)
			{
				lambda = 10 * lambda;

				if(lambda > 1e16)
				{
					breakOut = true;
					break;
				}

				matTem = summ(power(J, 2));
				matTem = diag(sqrt(matTem * lambda));
				Jplus = merge(J, matTem);
				//printmat(Jplus,"Jplus");
				step = leftdivide(Jplus, rplus);
				//printmat(step,"step");
				_beta = betaold.Spread() + step;
				_beta = _beta.Spread();
				yfit = model(_beta, _X, _param);

				r = _y.Spread() - yfit.Spread();
				//printmat(r, "r");
				sse = transpose(r) * r;
				//printmat(sse,"sse");
			}
		}

		aml_uint verbose = 0;

		if( verbose > 2 )
		{

		}

		if( norm(step) < betatol *(norm(_beta) + sqrteps))
		{
			if(verbose > 1)
			{

			}

			break;
		}
		else if(abs(sse - sseold) <= sse * rtol )
		{
			if(verbose > 1)
			{

			}

			break;
		}
		else if(breakOut)
		{
			break;
		}
		printmat(r, "r");
		printmat(yfit, " yfit");
		printmat(_beta, " beta");
		printmat(J, " J");


	}

	return _beta;

}