/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/
#ifndef _INCLUDE_AML_CORE_MEMORY_2012_9_5
#define _INCLUDE_AML_CORE_MEMORY_2012_9_5

#include <memory>
#include "aml_def.h"
#include "aml_exception.h"

#define AML_EXTRA_SIZE	8

// AML_ MAIN CLASS 
// That is memory manager.
template <class T>
AML_CLASS aml_allocator
{
public:

	/*  */
	aml_allocator( )
	{
		data = NULL;
		count = 0;
	}

	aml_allocator(const aml_size count )
	{
		data = NULL;
		Resize(count);
	}  

	/*  */
	~aml_allocator()
	{
		if(data)
			free(data);

	}

public:

	/* */
	AML_INLINE (T*) GetBuf() const
	{
		return data;
	}


	AML_INLINE (T*) GetMemSize() const
	{
		return count * sizeof(T);
	}


	aml_size GetCount() const
	{
		return count;
	}
	T GetAt(aml_uint pos) const
	{
		if((pos < 0) || (pos > count))
		{
			throw aml_exception_memory("Invalid parameters.");
		}

		return data[pos];
	}

	void SetAt(aml_uint pos, T value)
	{
		if((pos < 0) || (pos > count))
		{
			throw aml_exception_memory("Invalid parameters.");

		}

		data[pos] = value;
	}
	

	void Alloc(aml_size size) throw()
	{
		if(size < 0)
		{
			throw aml_exception_memory("Invalid parameters.");
		}

		if(data)
		{
			data = (T*) realloc(data, size + AML_EXTRA_SIZE);

			if(!data)
			{
				throw aml_exception_memory("Less the memory.");

			}
		}
		else 
		{
			data = (T*) malloc(size + AML_EXTRA_SIZE);

			if(!data)
			{

				throw aml_exception_memory("Less the memory.");

			}
		}

		memset(data, 0, size);
		*((char*)data + size) = '\0';
		this->count = size / sizeof(T);

	}

	void Resize(aml_int count)
	{
		if(count < 0)
		{

			throw aml_exception_param("Invalid parameters.");

		}

		if(data)
		{
			data = (T*) realloc(data, count * sizeof(T) + AML_EXTRA_SIZE);

			if(!data)
			{
				throw aml_exception_memory("Less the memory.");
			}
		}
		else 
		{
			data = (T*) malloc(count * sizeof(T) + AML_EXTRA_SIZE);

			if(!data)
				throw aml_exception_memory("Less the memory.");

		}
		
		memset(data, 0, count * sizeof(T));
		*((char*)data + count * sizeof(T)) = '\0';
		this->count = count;

	}

#if (WINVER > 0x0400 )
	void SetMemory(const T* pbuf, aml_uint count)
	{
		if(!pBuf)
		{
			throw aml_exception_param("Invalid parameters.");
		}

		if(!data)
		{
			throw aml_exception_memory("Empty memory.");

		}

		if(this->count < count)
		{
			throw aml_exception_overflow("Size of destination's memory  is small.");

		}

		memcpy(data, pBuf, count * sizeof(T));
	}
#endif


	template<class OtherT>
	void SetMemory(const OtherT* pbuf, aml_uint count)
	{
		if(!pbuf)
		{

			throw aml_exception_param("Invalid parameters.");

		}

		if(!data)
		{

			throw aml_exception_memory("Empty memory.");


		}

		if(this->count < count)
		{

			throw aml_exception_overflow("Size of destination's memory  is small.");

		}

		for(aml_count i = 0; i < (aml_count)count; i++ )
			SetAt(i, static_cast<T>(pbuf[i]));

	}
#if (WINVER > 0x0400 )
	void SetMemory(const aml_allocator<T>& src)
	{
		SetMemory(src.data, src.count);
	}
#endif

	template<class OtherT>
	void SetMemory(const aml_allocator<OtherT>& src)
	{
		SetMemory(src.data, src.count);
	}

public:

	T* data;
	aml_size count;

};

#define allocater aml_allocator 

#endif
