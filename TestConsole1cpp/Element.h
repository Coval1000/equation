#pragma once

#ifndef _STRING_H_
#include <string>
#endif // !_STRING_H_
 
#define _ELEMENT_H

class Element
{
public:
	enum class Phrase
	{
		None, Operation, Value, Funcion, Bracket_Left, Bracket_Right, Right_Side_Modifer, Unknown, Funcion_With_Base, Constant
	};

	enum class Operation
	{
		None,
		Addition,
		Substraction,
		Multiplication,
		Division,
		Power,
		Equal,
		Bracket_Left,
		Bracket_Right,
		Unknown,
		Factorial,
		Sinus,
		Cosinus,
		Tanges,
		Sinus_Hiperbolide,
		Cosinus_Hiperbolide,
		Tanges_Hiperbolide,
		Root,
		Log,
		Ln,
		Modulo,
		Exponenta,
		Intinger,
		Pi,
		e
	};

private:
	Phrase _phrase;
	double value;
	Operation _operation;
	std::wstring wname;
	std::string name;
public:
	Phrase GetPhraseType();
	Operation operation();

	Element(double d);
	Element(int i);
	Element(Operation op, double base = 1);
	Element(const Element&);

private:
	Element(std::string unknown);
	Element(std::wstring unknown);
	Element(char unknown);
	Element(wchar_t unknown);
	Element(char* unknown);
	Element(wchar_t* unknown);


public:
	std::string ToString();
	std::wstring ToWString();
	void Element::toSubscript(wchar_t* wc);

	double ToValue();
	void Value_of_x(double x);

	
private:
	std::string operation_symbol(Operation symbol);
	std::wstring w_operation_symbol(Operation symbol);
};
