#include "Element.h"
//#######
//Element
//#######
Element::Element(double d)
{
	_phrase = Phrase::Value;
	value = d;
}

Element::Element(int i)
{
	_phrase = Phrase::Value;
	value = i;
}

Element::Element(Operation op, double base)
{
	switch (op)
	{
	case Operation::Substraction:
	case Operation::Addition:
	case Operation::Multiplication:
	case Operation::Division:
	case Operation::Power:
	case Operation::Modulo:
		_phrase = Phrase::Operation;
		break;

	case Operation::Bracket_Left:
		_phrase = Phrase::Bracket_Left;
		break;

	case Operation::Bracket_Right:
		_phrase = Phrase::Bracket_Right;
		break;

	case Operation::Factorial:
		_phrase = Phrase::Right_Side_Modifer;
		break;

	case Operation::Unknown:
		_phrase = Phrase::Unknown;
		break;

	case Operation::Sinus:
	case Operation::Sinus_Hiperbolide:
	case Operation::Cosinus:
	case Operation::Cosinus_Hiperbolide:
	case Operation::Tanges:
	case Operation::Tanges_Hiperbolide:
	case Operation::Ln:
	case Operation::Exponenta:
	case Operation::Intinger:
		_phrase = Phrase::Funcion;
		break;

	case Operation::Log:
	case Operation::Root:
		_phrase = Phrase::Funcion_With_Base;
		value = base;
		break;
	case Operation::None:
		_phrase = Phrase::None;
		value = base;
		break;
		
	default:
		//throw new ArgumentException("Undefined Operation: " + op.ToString(), "op in Element");
		break;
	}
	_operation = op;
}

Element::Element(const Element& obj)
{
	this->_phrase = obj._phrase;
	this->value = obj.value;
	this->_operation = obj._operation;
	this->name = obj.name;
	this->wname = obj.wname;
}

Element::Element(std::string unknown) 
{
	_phrase = Phrase::Unknown;
	_operation = Operation::Unknown;
	name = unknown;
}

Element::Element(std::wstring unknown)
{

}
Element::Element(char unknown)
{
	switch (unknown)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		value = unknown - '0';
		_operation = Operation::None;
		_phrase = Phrase::Value;
		break;
	case '+':
		_phrase = Phrase::Operation;
		_operation = Operation::Addition;
		break;
	case '-':
		_phrase = Phrase::Operation;
		_operation = Operation::Substraction;
	case '*':
		_phrase = Phrase::Operation;
		_operation = Operation::Multiplication;
		break;
	case '/':
		_phrase = Phrase::Operation;
		_operation = Operation::Division;
		break;
	case '^':
		_operation = Operation::Power;
		_phrase = Phrase::Operation;
		break;
	case '%':
		_operation = Operation::Modulo;
		_phrase = Phrase::Operation; 
		break;
	case '(':
		_operation = Operation::Bracket_Left;
		_phrase = Phrase::Bracket_Left;
		break;

	case ')':
		_operation = Operation::Bracket_Right;
		_phrase = Phrase::Bracket_Right;
		break;

	case '!':
		_operation = Operation::Factorial;
		_phrase = Phrase::Right_Side_Modifer;
		break;
	default:
		name = unknown;
		wname = unknown;
		_operation = Operation::Unknown;
		_phrase = Phrase::Unknown;
		break;
	}
}

Element::Element(wchar_t unknown) 
{

}
Element::Element(char* unknown)
{

}
Element::Element(wchar_t* unknown)
{

}

Element::Phrase Element::GetPhraseType()
{
	return _phrase;
}

Element::Operation Element::operation()
{
	return _operation;
}
//################
//Display & string
//################
std::string Element::ToString()
{
	if (_phrase == Phrase::Value)
	{
		char buffor[100];
		snprintf(buffor, 100, "%g", value);
		return std::string(buffor);
	}
	else if (_phrase == Phrase::Operation)	return " " + operation_symbol(_operation) + " ";
	else									return operation_symbol(_operation);
}

std::wstring Element::ToWString()
{
	if (_phrase == Phrase::Value)
	{
		wchar_t buffor[100];
		swprintf(buffor, 100, L"%g", value);
		return std::wstring(buffor);
	}
	else if (_phrase == Phrase::Operation)	return L" " + w_operation_symbol(_operation) + L" ";
	else	return w_operation_symbol(_operation);
}

std::string Element::operation_symbol(Operation symbol)
{
	std::string txt;
	char buffor[100];
	switch (symbol)
	{
	case Operation::Addition:
		txt = "+";
		break;
	case Operation::Substraction:
		txt = "-";
		break;
	case Operation::Multiplication:
		txt = "*";
		break;
	case Operation::Division:
		txt = "÷";
		break;
	case Operation::Power:
		txt = "^";
		break;
	case Operation::None:
		txt = " ";
		break;
	case Operation::Equal:
		txt = "=";
		break;
	case Operation::Unknown:
		txt = "x";
		break;
	case Operation::Bracket_Left:
		txt = "(";
		break;
	case Operation::Bracket_Right:
		txt = ")";
		break;
	case Operation::Cosinus:
		txt = "cos";
		break;
	case Operation::Cosinus_Hiperbolide:
		txt = "cosh";
		break;
	case Operation::Sinus:
		txt = "sin";
		break;
	case Operation::Sinus_Hiperbolide:
		txt = "sinh";
		break;
	case Operation::Tanges:
		txt = "tan";
		break;
	case Operation::Tanges_Hiperbolide:
		txt = "tanh";
		break;
	case Operation::Log:
		snprintf(buffor, 100, "%g", value);
		txt = "log" + std::string(buffor) + "_";
		break;
	case Operation::Exponenta:
		txt = "Exp";
		break;
	case Operation::Intinger:
		txt = "Int";
		break;
	case Operation::Ln:
		txt = "ln";
		break;
	case Operation::Root:		
		snprintf(buffor, 100, "%g", value);
		txt = "root" + std::string(buffor) + "_";
		break;
	case Operation::Factorial:
		txt = "!";
		break;
	case Operation::Modulo:
		txt = "%";
		break;
	default:
		txt = "";
		break;
	}
	return txt;
}

std::wstring Element::w_operation_symbol(Operation symbol)
{
	std::wstring txt;
	wchar_t buffor[100];
	switch (symbol)
	{
	case Operation::Addition:
		txt = L"+";
		break;
	case Operation::Substraction:
		txt = L"-";
		break;
	case Operation::Multiplication:
		txt = L"∙";
		break;
	case Operation::Division:
		txt = L"÷";
		break;
	case Operation::Power:
		txt = L"^";
		break;
	case Operation::None:
		txt = L" ";
		break;
	case Operation::Equal:
		txt = L"=";
		break;
	case Operation::Unknown:
		txt = L"x";
		break;
	case Operation::Bracket_Left:
		txt = L"(";
		break;
	case Operation::Bracket_Right:
		txt = L")";
		break;
	case Operation::Cosinus:
		txt = L"cos";
		break;
	case Operation::Cosinus_Hiperbolide:
		txt = L"cosh";
		break;
	case Operation::Sinus:
		txt = L"sin";
		break;
	case Operation::Sinus_Hiperbolide:
		txt = L"sinh";
		break;
	case Operation::Tanges:
		txt = L"tan";
		break;
	case Operation::Tanges_Hiperbolide:
		txt = L"tanh";
		break;
	case Operation::Log:
		swprintf(buffor, 100, L"%g", value);
		toSubscript(buffor);
		txt = L"log" + std::wstring(buffor) + L"_";
		break;
	case Operation::Exponenta:
		txt = L"Exp";
		break;
	case Operation::Intinger:
		txt = L"Int";
		break;
	case Operation::Ln:
		txt = L"ln";
		break;
	case Operation::Root:
		swprintf(buffor, 100, L"%g", value);
		txt = L"_"+ std::wstring(buffor) + L"√";
		break;
	case Operation::Factorial:
		txt = L"!";
		break;
	case Operation::Modulo:
		txt = L"%";
		break;
	default:
		txt = L"";
		break;
	}
	return txt;
}

void Element::toSubscript(wchar_t* wc)
{
	for (int i = 0; wc[i] != L'\0' ; i++)
	{
		switch (wc[i])
		{
		case L'0':
			wc[i] = L'₀';
			break;
		case L'1':
			wc[i] = L'₁';
			break;
		case L'2':
			wc[i] = L'₂';
			break;
		case L'3':
			wc[i] = L'₃';
			break;
		case L'4':
			wc[i] = L'₄';
			break;
		case L'5':
			wc[i] = L'₅';
			break;
		case L'6':
			wc[i] = L'₆';
			break;
		case L'7':
			wc[i] = L'₇';
			break;
		case L'8':
			wc[i] = L'₈';
			break;
		case L'9':
			wc[i] = L'₉';
			break;
		default:

			break;
		}
	}
}

double Element::ToValue()
{
	if (_phrase == Phrase::Value || _phrase == Phrase::Funcion_With_Base || _phrase == Phrase::Unknown)
		return value;
	else
		return NAN;
}
//
//
//
void Element::Value_of_x(double x)
{
	if (_phrase == Phrase::Unknown)
	{
		value = x;
	}
}