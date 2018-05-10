# AML
## Introduction
This is a C++ library convert to c++ codes from the matlab codes.
You can use matlab commands in the c++ sources.

## Usage
Here is a few matlab code lines.

	clc
	load reaction
	betafit = nlinfitc(reactants,rate,@hougen,beta);
	betafit

You can convert it to c++ code as following.

	matrixd  AML_STDCALL hougen(matrixd& beta, matrixd& x)
	{


		 double b1 = beta(0);
		 double b2 = beta(1);
		 double b3 = beta(2);
		 double b4 = beta(3);
		 double b5 = beta(4);

		 matrixd x1 = x.GetCol(0);
		 matrixd x2 = x.GetCol(1);
		 matrixd x3 = x.GetCol(2);

		 matrixd yhat = rightdivide( (x2 * b1 - x3 / b5), (x1 * b2 + 1 + x2 * b3 + x3 * b4));

		 return yhat;
	 }

	int main(int argc, char* argv[])
	{
		matrixd matReact(13, 3);
		matrixd matRate(13, 1);
		matrixd beta(5, 1);

		matReact(0,0) = 470;
		matReact(0,1) = 300;
		matReact(0,2) = 10;

		matReact(1,0) = 285;
		matReact(1,1) = 80;
		matReact(1,2) = 10;

		matReact(2,0) = 470;
		matReact(2,1) = 300;
		matReact(2,2) = 120;

		matReact(3,0) = 470;
		matReact(3,1) = 80;
		matReact(3,2) = 120;

		matReact(4,0) = 470;
		matReact(4,1) = 80;
		matReact(4,2) = 10;

		matReact(5,0) = 100;
		matReact(5,1) = 190;
		matReact(5,2) = 10;

		matReact(6,0) = 100;
		matReact(6,1) = 80;
		matReact(6,2) = 65;

		matReact(7,0) = 470;
		matReact(7,1) = 190;
		matReact(7,2) = 65;

		matReact(8,0) = 100;
		matReact(8,1) = 300;
		matReact(8,2) = 54;

		matReact(9,0) = 100;
		matReact(9,1) = 300;
		matReact(9,2) = 120;

		matReact(10,0) = 100;
		matReact(10,1) = 80;
		matReact(10,2) = 120;

		matReact(11,0) = 285;
		matReact(11,1) = 300;
		matReact(11,2) = 10;

		matReact(12,0) = 285;
		matReact(12,1) = 190;
		matReact(12,2) = 120;

		matRate(0) = 8.55;
		matRate(1) = 3.79;
		matRate(2) = 4.82;
		matRate(3) = 0.02;
		matRate(4) = 2.75;
		matRate(5) = 14.39;
		matRate(6) = 2.54;
		matRate(7) = 4.35;
		matRate(8) = 13.0;
		matRate(9) = 8.5;
		matRate(10) = 0.05;
		matRate(11) = 11.32;
		matRate(12) = 3.13;

		beta(0) = 1.0;
		beta(1) = 0.05;
		beta(2) = 0.02;
		beta(3) = 0.1;
		beta(4) = 2.0;


		matrixd yfit = nlinfit(matReact, matRate, hougen, beta);
		printmat(yfit,"yfit");
		getchar();
		return 0;
	}

This code block will produce same result to the matlab code.


