#pragma once
#ifndef _COMPLEXCLASS_H_
#define _COMPLEXCLASS_H_
#endif

#ifndef _MATH_H_
#include <math.h>
#define _MATH_H_
#endif 


class Complex
{
public:
	Complex();
	~Complex();

	void setArg(double);
	void setModulus(double);
	void setImaginary(double);
	void setReal(double);
	double getArg();
	double getModulus();
	double getImaginary();
	double getReal();

	Complex& operator+=(const Complex&);
	Complex& operator-=(const Complex&);
	Complex& operator*=(const Complex&);
	Complex& operator/=(const Complex&);

	Complex operator+(const Complex&);
	Complex operator-(const Complex&);
	Complex operator/(const Complex&);
	Complex operator*(const Complex&);

private:
	//Recalcs
	void _rcArgMod();
	void _rcReIm();
	void _rcReArg();
	void _rcImArg();
	void _rcReMod();
	void _rcImMod();
	//Values
	double arg;
	double real;
	double imaginary;
	double modulus;


};

