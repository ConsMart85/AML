// calcN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "aml_exception.h"

using namespace aml_exception;

void testException();

void testException()
{
	throw aml_exception_base("¶ÊË÷»¨ÂéËÓ³£³Þ.\n");
}

int main(int argc, char* argv[])
{
	try
	{
		testException();
		testException();
	}
	catch (aml_exception_base e)
	{
		string str;
		printf(e.GetString().c_str());
	}

	return 0;
}
