/************************************************************************/
// 2012 S. Konstantin Martinov : UK. KIEV  
/************************************************************************/


#ifndef _INCLUDE_AML_GENERAL_TYPE_2012_9_5
#define _INCLUDE_AML_GENERAL_TYPE_2012_9_5


template <class T>
AML_CLASS aml_complex
{
public:

	aml_complex()
	{
		re = 0;
		im = 0;
	}

	aml_complex(T re, T im)
	{
		this->re = re;
		this->im = im;
	}


#if (WINVER > 0x0400 )

	aml_complex(const aml_complex<T>& src )
	{
		this->re = src.re;
		this->im = src.im;
	}

#endif

	template <class OtherT>
	aml_complex(const aml_complex<OtherT>& src )
	{
		this->re = static_cast<T>(src.re);
		this->im = static_cast<T>(src.im);
	}



	T GetReal() const
	{
		return re;
	}


	T GetImagin() const
	{
		return im;
	}


	void SetReal(T re)
	{
		this->re = re;
	}


	void SetImagin(T im)
	{
		this->im = im;
	}


	void Set(T re, T im)
	{
		this->re = re;
		this->im = im;
	}


	AML_INLINE(aml_size) SizeOfType() const
	{
		return sizeof(T);
	}


	template <class OtherT>
	AML_INLINE(bool) About(const aml_complex<OtherT>& tgt) const
	{
		 return (std::abs(re - tgt.re) < EPSILON) && (std::abs(im - tgt.im) < EPSILON);
	}

	aml_complex<T>& operator =(const aml_complex<T>& src)
	{
		this->re = src.re;
		this->im = src.im;
		return *this;
	}

	aml_complex<T> operator +(const aml_complex<T>& tgt)
	{
		return aml_complex<T>(this->re + tgt.re, this->im + tgt.im);

	}

	aml_complex<T> operator -(const aml_complex<T>& tgt)
	{
		return aml_complex<T>(this->re - tgt.re, this->im - tgt.im);
	}

	aml_complex<T> operator *(const aml_complex<T>& tgt)
	{
		return aml_complex<T>(this->re * tgt.re, this->im * tgt.im);
	}

	aml_complex<T> operator /(const aml_complex<T>& tgt)
	{
		return aml_complex<T>(this->re / tgt.re, this->im / tgt.im);
	}

	aml_complex<T>& operator+=(const aml_complex<T>& tgt)
	{
		re += tgt.re;
		im += tgt.im;

		return *this;
	}

	aml_complex<T>& operator-=(const aml_complex<T>& tgt)
	{
		re -= tgt.re;
		im -= tgt.im;

		return *this;
	}

	aml_complex<T>& operator *=(const aml_complex<T>& tgt)
	{
		re *= tgt.re;
		im *= tgt.im;

		return *this;
	}

	aml_complex<T>& operator/=(const aml_complex<T>& tgt)
	{
		re /= tgt.re;
		im /= tgt.im;

		return *this;
	}

	bool operator ==(const aml_complex<T>& match) const
	{
		if((this->re == match.re) && (this->im == match.im) )
			return true;
		else
			return false;
	}

	bool operator !=(const aml_complex<T>& match) const
	{
		if((this->re == match.re) && (this->im == match.im) )
			return false;
		else
			return true;
	}
	

public:
	
	T re; 
	T im; 
	
};

#define complex aml_complex
#define complexi  aml_complex<aml_int>
#define complexd aml_complex<aml_double>
#define complexf aml_complex<aml_float>

/************************************************************************/
/*
/************************************************************************/

template <class T>
AML_CLASS aml_vector2d
{
	
public:

	aml_vector2d()
	{
		x = 0;
		y = 0;
	}

	aml_vector2d(T x, T y)
	{
		this->x = x;
		this->y = y;
	}



#if (WINVER > 0x0400 )
	
	aml_vector2d(const aml_vector2d<T>& src)
	{
		x = src.x;
		y = src.y;
	}

#endif

	template <class OtherT>
	aml_vector2d(const aml_vector2d<OtherT>& src)
	{
		x = static_cast<T>(src.x);
		y = static_cast<T>(src.y);
	}
		

	void Set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}
	

	aml_size SizeOfType() const
	{
		return sizeof(T);
	}

	template <class OtherT>
	AML_INLINE(bool) About(const aml_vector2d<OtherT>& tgt) const
	{
		return (std::abs(x - tgt.x) < EPSILON) && (std::abs(y - tgt.y) < EPSILON);
	}

	aml_vector2d<T>& operator =(const aml_vector2d<T>& src)
	{
		this->x = src.y;
		this->y = src.y;
		return *this;
	}

	aml_vector2d<T> operator +(const aml_vector2d<T>& tgt)
	{
		return aml_vector2d<T>(this->x + tgt.x, this->y + tgt.y);

	}

	aml_vector2d<T> operator -(const aml_vector2d<T>& tgt)
	{
		return aml_vector2d<T>(this->x - tgt.x, this->y - tgt.y);
	}

	aml_vector2d<T> operator *(const aml_vector2d<T>& tgt)
	{
		return aml_vector2d<T>(this->x * tgt.x, this->y * tgt.y);
	}

	aml_vector2d<T> operator /(const aml_vector2d<T>& tgt)
	{
		return aml_vector2d<T>(this->x / tgt.x, this->y / tgt.y);
	}

	aml_vector2d<T>& operator +=(const vector2d<T>& tgt)
	{
		x += tgt.x;
		y += tgt.y;
		return *this;
	}

	aml_vector2d<T>& operator -=(const vector2d<T>& tgt)
	{
		x -= tgt.x;
		y -= tgt.y;
		return *this;
	}

	aml_vector2d<T>& operator *=(const vector2d<T>& tgt)
	{
		x *= tgt.x;
		y *= tgt.y;
		return *this;
	}

	aml_vector2d<T>& operator /=(const vector2d<T>& tgt)
	{
		x /= tgt.x;
		y /= tgt.y;
		return *this;
	}
	
	bool operator ==(const aml_vector2d<T>& match)
	{
		if((this->x == match.x) && (this->y == match.y) )
			return true;
		else
			return false;
	}
	
	bool operator !=(const aml_vector2d<T>& match)
	{
		if((this->x == match.x) && (this->x == match.x) )
			return false;
		else
			return true;
	}
	
	
public:
	

	union
	{
		T x; 
		T s;
	};

	union
	{
		T y;
		T t;
	};

};

#define vector2 aml_vector2d
#define vector2i aml_vector2d<aml_int>
#define vector2d aml_vector2d<aml_double>
#define vector2f aml_vector2d<aml_float>


template <class T>
AML_CLASS aml_vector3d
{

public:

	aml_vector3d()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	aml_vector3d(T x,  T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

#if (WINVER > 0x0400 )

	aml_vector3d(const aml_vector3d<T>& src)
	{
		x = src.x;
		y = src.y;
		z = src.z;
	}

#endif

	template <class OtherT>
	aml_vector3d(const aml_vector3d<OtherT>& src)
	{
		x = static_cast<T>(src.x);
		y = static_cast<T>(src.y);
		z = static_cast<T>(src.z);
	}

	void Set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	aml_size SizeOfType() const
	{
		return sizeof(T);
	}

	template <class OtherT>
	bool About(const aml_vector3d<OtherT>& tgt) const
	{
		return (std::abs(x - tgt.x) < EPSILON) && (std::abs(y - tgt.y) < EPSILON);
	}

	aml_vector3d<T>& operator =(const aml_vector3d<T>& src)
	{
		this->x = src.y;
		this->y = src.y;
		return *this;
	}

	aml_vector3d<T> operator +(const aml_vector3d<T>& tgt)
	{
		return aml_vector3d<T>(this->x + tgt.x, this->y + tgt.y, this->z + tgt.z );

	}

	aml_vector3d<T> operator -(const aml_vector3d<T>& tgt)
	{
		return aml_vector3d<T>(this->x - tgt.x, this->y - tgt.y, this->z - tgt.z);
	}

	aml_vector3d<T> operator *(const aml_vector3d<T>& tgt)
	{
		return aml_vector3d<T>(this->x * tgt.x, this->y * tgt.y, this->z * tgt.z);
	}

	aml_vector3d<T> operator /(const aml_vector3d<T>& tgt)
	{
		return aml_vector3d<T>(this->x / tgt.x, this->y / tgt.y, this->z / tgt.z);
	}

	aml_vector3d<T>& operator +=(const vector3d<T>& tgt)
	{
		x += tgt.x;
		y += tgt.y;
		z += tgt.z;
		return *this;
	}

	bool operator ==(const aml_vector3d<T>& match)
	{
		if((this->x == match.x) && (this->y == match.y)  && (this->z == match.z) )
			return true;
		else
			return false;
	}

	bool operator !=(const aml_vector3d<T>& match)
	{
		if((this->x == match.x) && (this->y == match.y)  && (this->z == match.z) )
			return false;
		else
			return true;
	}

public:

	union
	{
		T x; 
		T s;
	};

	union
	{
		T y;
		T t;
	};

	union
	{
		T z;
		T u;
	};

};

#define vector3 aml_vector3d
#define vector3i aml_vector3d<aml_int>
#define vector3d aml_vector3d<aml_double>
#define vector3f aml_vector3d<aml_float>


#endif