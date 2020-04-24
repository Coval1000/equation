#pragma once

#ifndef _STRING_H_
#include <string>
#endif // !_STRING_H_

#include <cmath>
#include <vector>

#ifndef _ELEMENT_H_
#include "Element.h"
#endif // !_ELEMENT_H_

#define _EQUATIONCLASS_H_
using namespace std;

class Equation
{
private:
	vector<Element> element;

public:
	void Clear();

	Equation();
	Equation(const Equation&);
	~Equation();

	/// <summary>
	/// Add element to equation. Returns true if successed
	/// </summary>
	/// <param name="d"></param>
	/// <returns></returns>
	bool Add(double d);
	bool Add(Element::Operation op, double base = 1);
	bool Add(Element tmp);

	string toString();
	wstring toWString();

	double answer(double x = 0);	
private:
	double answer(vector<Element> piece);

	vector<Element> calc_operator(vector<Element> piece, Element::Operation op);
	vector<Element> calc_funcion(vector<Element> piece, Element::Operation funcion);
};
