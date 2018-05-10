

/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/

#ifndef _INCLUDE_aml_message_2012_9_5
#define _INCLUDE_aml_message_2012_9_5


	AML_ENUM __aml_message_type
	{
		_MESSAGE,
		_ERROR,
		_WARRING
	};

	/************************************************************************/
	/* 
	/************************************************************************/
	AML_CLASS aml_message
	{
	public:
		aml_message()   
		{
			
		}

		aml_message(aml_string str)
		{

#ifdef _WIN32

		MessageBox(NULL,"Message", str.c_str(), MB_OK );
		
#else
			fprintf(stdout, str.c_str());
			fprintf(stdout, "\n");
#endif // _WIN32

		}

		aml_message(aml_string str, __aml_message_type disType)
		{
			
			switch(disType)
			{
			case _MESSAGE:

#ifdef _WIN32

		MessageBox(NULL,"Message", str.c_str(), MB_OK );
				
#else
				fprintf(stdout, str.c_str());
				fprintf(stdout, "\n");
#endif // _WIN32

				break;

			case _ERROR:

#ifdef _WIN32
				MessageBox(NULL,"error", str.c_str(), MB_OK );				
#else
				fprintf(stderr, str.c_str());
				fprintf(stderr, "\n");
#endif // _WIN32
				break;

			case _WARRING:
#ifdef _WIN32

				MessageBox(NULL,"Message", str.c_str(), MB_OK );
				
#else
				fprintf(stdout, str.c_str());
				fprintf(stdout, "\n");
#endif // _WIN32
				break;

			default:

#ifdef _WIN32
				MessageBox(NULL,"Message", str.c_str(), MB_OK );				
#else
				fprintf(stdout, str.c_str());
				fprintf(stdout, "\n");
#endif // _WIN32
			}
		}

	public:



	};





#endif

