/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/


#ifndef _INCLUDE_AML_EXCEPTION_2012_9_4
#define _INCLUDE_AML_EXCEPTION_2012_9_4



	/************************************************************************/
	/*
	/************************************************************************/
	AML_INTERFACE aml_exception
	{
		aml_expno exceptNo;
		aml_string infoStr;
		
	};
	
#define exception aml_exception

	AML_CLASS  aml_exception_base  : public aml_exception
	{

	public:
		aml_exception_base()
			: aml_exception()
		{
			exceptNo = AML_ERROR_UNKOWN;
			infoStr = "Unknown error !";		
		}

		aml_exception_base(aml_string str)
		{
			infoStr = str;
			exceptNo = AML_ERROR_UNKOWN;
		}

	protected :

		aml_exception_base(aml_string str, aml_expno expNo)
		{
			infoStr = str;
			exceptNo = expNo;
		}

	public:
		

		virtual aml_expno GetErrorNo() const
		{
			return exceptNo;
		}
		

		virtual aml_string GetString() const
		{
			return infoStr;
		}
	};

	#define exception_base aml_exception_base

	/************************************************************************/

	AML_CLASS aml_exception_memory : public aml_exception_base
	{
	public:

		aml_exception_memory(aml_string str)
			:aml_exception_base(str, AML_ERROR_MEMORY)
		{
		
		}	
		
	};

	#define exception_memory aml_exception_memory


	AML_CLASS aml_exception_overflow : public aml_exception_base
	{
	public:

		aml_exception_overflow(aml_string str)
			:aml_exception_base(str, AML_ERROR_OVERFLOW)
		{
			
		}

	};

	#define exception_overflow aml_exception_overflow

	AML_CLASS aml_exception_type : public aml_exception_base 
	{
	public:

		aml_exception_type(aml_string str)
			:aml_exception_base(str, AML_ERROR_TYPE)
		{

		}
	};

	#define exception_type aml_exception_type

	AML_CLASS aml_exception_param : public aml_exception_base
	{
	public:

		aml_exception_param(aml_string str)
			:aml_exception_base(str, AML_ERROR_PARAM)
		{
			
		}
	};

	#define exception_param aml_exception_param


#endif




















