#include "aml_exception.h"
#include "aml_type.h"

using namespace aml_type;


template <class T>
aml_complex<T>::aml_complex()
{
	re = 0;
	im = 0;
}

template <class T>
aml_complex<T>::aml_complex(T re, T im)
{
	this->re = re;
	this->im = im;
}

// template <class T>
// aml_complex<T>::aml_complex(const aml_complex<T>& src )
// {
// 	this->re = src.re;
// 	this->im = src.im;
// }


template <class T, class OtherT>
aml_complex<T>::aml_complex(const aml_complex<OtherT>& src )
{
	this->re = static_cast<T>(src.re);
	this->im = static_cast<T>(src.im);
}



template <class T>
T aml_complex<T>::GetReal() const
{
	return re;
}

template <class T> 
T aml_complex<T>::GetImagin() const
{
	return im;
}


template <class T> 
void aml_complex<T>::SetReal(T re)
{
	this->re = re;
}

template <class T>
void aml_complex<T>::SetImagin(T im)
{
	this->im = im;
}


template <class T> 
void aml_complex<T>::Set(T re, T im)
{
	this->re = re;
	this->im = im;
}


template <class T> 
aml_size aml_complex<T>::Size() const
{
	return sizeof(T);
}


template <class T> 
aml_complex<T>& aml_complex<T>::operator =(const aml_complex<T>& src)
{
	this->re = src.re;
	this->im = src.im;
	return *this;
}

template <class T> 
bool aml_complex<T>::operator ==(const aml_complex<T>& match)
{
	if((this->re == match.re) && (this->im == match.im) )
		return true;
	else
		return false;
}

template <class T> 
bool aml_complex<T>::operator !=(const aml_complex<T>& match)
{
	if((this->re == match.re) && (this->im == match.im) )
		return false;
	else
		return true;
}

template <class T>
aml_complex<T> aml_complex<T>::operator +(const aml_complex<T>& tgt)
{
	return aml_complex<T>(this->re + tgt.re, this->im + tgt.im);
	
}

template <class T> 
aml_complex<T> aml_complex<T>::operator -(const aml_complex<T>& tgt)
{
	return aml_complex<T>(this->re - tgt.re, this->im - tgt.im);
}
 
template <class T>
aml_complex<T> aml_complex<T>::operator *(const aml_complex<T>& tgt)
{
	return aml_complex<T>(this->re * tgt.re, this->im * tgt.im);
}

template <class T> 
aml_complex<T> aml_complex<T>::operator /(const aml_complex<T>& tgt)
{
	return aml_complex<T>(this->re / tgt.re, this->im / tgt.im);
}

