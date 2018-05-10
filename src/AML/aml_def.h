/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/


#ifndef _INCLUDE_AML_DEFINE_2012_9_5
#define _INCLUDE_AML_DEFINE_2012_9_5

#include <stdio.h>
#include <string>

#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;

/*Version*/
#define AML_VERSION 1
#define AML_MAJOR_VERSION 1
#define AML_MINOR_VERSION 0
#define AML_SUB_VERSION 0


#ifdef AML_COMPILE_DYNAMIC_LIB
	
#ifdef (AML_API_EXPORT && WIN32)
#define AML_API (x) __declspec(dllexport) x
#define AML_API_CLASS __declspec(dllexport) 
#else if(WIN32)
#define AML_API (x)__declspec(dllimport) x
#define AML_API_CLASS __declspec(dllimport) class
#else
#define AML_API(x) x
#define AML_API_CLASS class
#endif

#else

#define AML_API(x) x
#define AML_API_CLASS class 

#endif // AML_COMPILE_DYNAMIC_LIB






#ifndef AML_PATCH
#define AML_PATCH

#define AML_INLINE(x) inline x
#define AML_EXTERN extern
#define AML_CDECL __cdecl
#define AML_STDCALL __stdcall
#define AML_INTERFACE struct 
#define AML_CLASS class   
#define AML_ENUM enum



#define AML_INPUT( x ) x
#define AML_OUTPUT( x) x


#endif


#ifndef AML_DEFINE_TYPES
#define AML_DEFINE_TYPES

#define aml_byte char
#define aml_ubyte unsigned char
#define aml_bit8 char
#define aml_ubit8 unsigned char

#define aml_bit16 short
#define aml_ubit16 unsigned short
#define aml_short short
#define aml_ushort unsigned short

typedef union 
{
	struct  
	{
		aml_ubyte bytehigh;
		aml_ubyte bytemedium;
		aml_ubyte bytelow;
	};

}_unsigned_bit24;

typedef union 
{
	struct  
	{
		aml_byte bithigh;
		aml_byte bitmedium;
		aml_byte bitlow;
	};
	

}_bit24;

#define aml_ubit24 _unsigned_bit24
#define aml_bit24 _bit24

#define aml_bit32 long 
#define aml_ubit32 unsigned long 
#define aml_long long
#define aml_ulong unsigned long

#define aml_int int
#define aml_uint unsigned int 

#define aml_float float 
#define aml_ufloat unsigned float 
#define aml_float32 float
#define aml_ufloat32 unsigned float

#define aml_float64 double 
#define aml_ufloat64 unsigned double 

#define aml_double double
#define aml_udouble unsigned double

#define aml_no int
#define aml_expno int
#define aml_size unsigned int
#define aml_count aml_uint

#define aml_string string

#endif

#ifndef AML_CONSTANTS
#define AML_CONSTANTS

#define AML_SUCCESSED		 1
#define AML_ERROR_UNKOWN	-1
#define AML_ERROR_OVERFLOW	-2
#define AML_ERROR_MEMORY	-3
#define AML_ERROR_PARAM		-4
#define AML_ERROR_TYPE		-5
#define AML_ERROR_OPERATION	-6
#define AML_ERROR_UPDATE	-7
#define AML_ERROR_UNSUPPORT	-8

#define AML_WARRING_NOT_TESTING "This module have not test. so it may include some errors."
#define AML_WARRING_NOT_OLD_METHOD "This module unsupport under the next version. "
#define AML_WARRING_CASTING "This casting may generate some errors."
#endif 


#ifndef WINVER 
#define WINVER	100 
#endif // WINVER

#endif