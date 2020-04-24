#include "ComplexClass.h"


//#######
//Complex
//#######
Complex::Complex()
{
	modulus = 0;
	arg = 0;
	imaginary = 0;
	real = 0;
}

Complex::~Complex() 
{

}

void Complex::setArg(double fi)
{ 
	if (arg != fi) 
	{
		arg = fi;
		_rcReIm();
	}
	return;
}

void Complex::setModulus(double mod)
{
	if (modulus != mod)
	{
		modulus = mod;
		_rcReIm();
	}
	return;
}

void Complex::setImaginary(double i)
{
	if (imaginary != i)
	{
		imaginary = i;
		_rcArgMod();
	}
	return;
}

void Complex::setReal(double re)
{ 
	if (real != re)
	{
		real = re;
		_rcArgMod();
	}
	return;
}

double Complex::getArg()
{
	return arg;
}

double Complex::getModulus()
{
	return modulus;
}

double Complex::getImaginary()
{
	return imaginary;
}

double Complex::getReal()
{ 
	return real;
}

//########
//Operator
//########

Complex& Complex::operator+=(const Complex& r)
{ 
	*this = *this + r;
	return *this;
}

Complex& Complex::operator-=(const Complex& r)
{
	*this = *this - r;
	return *this;
}

Complex& Complex::operator*=(const Complex& r)
{
	*this = *this * r;
	return *this;
}

//Complex& Complex::operator/=(const Complex& r)
//{ }

Complex Complex::operator+(const Complex& r)
{
	Complex z;
	z.real = real + r.real;
	z.imaginary = imaginary + z.imaginary;
	z._rcArgMod();
	return z;
}

Complex Complex::operator-(const Complex& r)
{
	Complex z;
	z.real = real - r.real;
	z.imaginary = imaginary - z.imaginary;
	z._rcArgMod();
	return z;
}

//Complex Complex::operator/(const Complex& r)
//{ }

Complex Complex::operator*(const Complex& r)
{ 
	Complex z;
	z.real = real * r.real;
	z.imaginary = -(imaginary * z.imaginary);
	z._rcArgMod();
	return z;
}

//######
//Recalc
//######

void Complex::_rcArgMod()
{
	modulus = sqrt(imaginary*imaginary + real*real);
	arg = atan(imaginary / real);
	return;
}

void Complex::_rcReIm()
{
	real = cos(arg) * modulus;
	imaginary = sin(arg) * modulus;
	return;
}

void Complex::_rcReArg()
{ 
	arg = asin(imaginary / modulus);
	real = cos(arg) * modulus;
	return;
}

void Complex::_rcImArg()
{ 
	arg = acos(real / modulus);
	imaginary = sin(arg) * modulus;
	return;
}

void Complex::_rcReMod()
{ 
	modulus = imaginary / sin(arg);
	real = imaginary / tan(arg);
	return;
}

void Complex::_rcImMod()
{ 
	modulus = real / cos(arg);
	imaginary = real * tan(arg);
	return;
}