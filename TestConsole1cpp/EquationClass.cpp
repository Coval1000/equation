#include "EquationClass.h"

//########
//Equation
//########
Equation::Equation()
{

}

Equation::Equation(const Equation& obj)
{
	element = vector<Element>(obj.element);
}

Equation::~Equation()
{

}

double Equation::answer(double x)
{
	vector<Element> list(element);
	Element::Phrase type;
	Element::Phrase typeNxt;
	for (int i = 0, size = element.size() - 1u; i < size ; ++i)
	{
		type = list[i].GetPhraseType();
		typeNxt = list[i + 1].GetPhraseType();
		if ((type == Element::Phrase::Value ||
			type == Element::Phrase::Unknown) &&
			(typeNxt == Element::Phrase::Bracket_Left ||
				typeNxt == Element::Phrase::Funcion ||
				typeNxt == Element::Phrase::Funcion_With_Base ||
				typeNxt == Element::Phrase::Value ||
				typeNxt == Element::Phrase::Unknown))
		{
			list.insert(list.begin() + i + 1, Element(Element::Operation::Multiplication));
		}
		else if (type == Element::Phrase::Bracket_Right &&
			(typeNxt == Element::Phrase::Funcion ||
				typeNxt == Element::Phrase::Funcion_With_Base ||
				typeNxt == Element::Phrase::Value ||
				typeNxt == Element::Phrase::Unknown))
		{
			list.insert(list.begin() + i + 1, Element(Element::Operation::Multiplication));
		}

	}

	//for (Element e : list)
	//{
	//	e.Value_of_x(x);
	//}

	for (int i = 0, size = list.size(); i < size;++i)
	{
		list[i].Value_of_x(x);
	}

	double d = answer(list);

	return d;
}

string Equation::toString()
{
	std::string s = "";
	for (Element e : element)
	{
		s += e.ToString();
	}
	return s;
}

wstring Equation::toWString()
{
	std::wstring ws = L"";
	for (Element e : element)
	{
		ws += e.ToWString();
	}
	return ws;
}
//############
//Add Elements
//############
bool Equation::Add(Element::Operation op, double base)
{
	return Equation::Add(Element(op, base));
}

bool Equation::Add(double d)
{
	if (element.size() > 0)
	{
		if (element[element.size() - 1].GetPhraseType() == Element::Phrase::Value ||
			element[element.size() - 1].GetPhraseType() == Element::Phrase::Right_Side_Modifer) return false;
	}

	element.push_back(Element(d));
	return true;
}

bool Equation::Add(Element tmp)
{
	if (element.size() > 0)
	{
		Element::Phrase type = element[element.size() - 1u].GetPhraseType();

		switch (tmp.GetPhraseType())
		{
		case Element::Phrase::Bracket_Left:
		case Element::Phrase::Funcion:
		case Element::Phrase::Funcion_With_Base:
			if (type == Element::Phrase::Value ||
				type == Element::Phrase::Funcion ||
				type == Element::Phrase::Funcion_With_Base ||
				type == Element::Phrase::Unknown ||
				type == Element::Phrase::Bracket_Left ||
				type == Element::Phrase::Bracket_Right ||
				type == Element::Phrase::Operation)
			{
				element.push_back(tmp);
				return true;
			}
			break;

		case Element::Phrase::Bracket_Right:
			if (type == Element::Phrase::Value ||
				type == Element::Phrase::Unknown ||
				type == Element::Phrase::Bracket_Left ||
				type == Element::Phrase::Bracket_Right ||
				type == Element::Phrase::Right_Side_Modifer)
			{
				element.push_back(tmp);
				return true;
			}
			break;

		case Element::Phrase::Operation:
			if (type == Element::Phrase::Value ||
				type == Element::Phrase::Unknown ||
				type == Element::Phrase::Bracket_Right ||
				type == Element::Phrase::Right_Side_Modifer)
			{
				element.push_back(tmp);
				return true;
			}
			break;

		case Element::Phrase::Right_Side_Modifer:
			if (type == Element::Phrase::Value ||
				type == Element::Phrase::Unknown ||
				type == Element::Phrase::Bracket_Right)
			{
				element.push_back(tmp);
				return true;
			}
			break;

		case Element::Phrase::Unknown:
			if (type == Element::Phrase::Value ||
				type == Element::Phrase::Funcion ||
				type == Element::Phrase::Funcion_With_Base ||
				type == Element::Phrase::Bracket_Left ||
				type == Element::Phrase::Bracket_Right ||
				type == Element::Phrase::Operation)
			{
				element.push_back(tmp);
				return true;
			}
			break;
		}
	}
	else if (tmp.GetPhraseType() == Element::Phrase::Unknown ||
		tmp.GetPhraseType() == Element::Phrase::Bracket_Left ||
		tmp.GetPhraseType() == Element::Phrase::Funcion ||
		tmp.GetPhraseType() == Element::Phrase::Funcion_With_Base)
	{
		element.push_back(tmp);
		return true;
	}
	return false;
}

//
//
//
double Equation::answer(vector<Element> piece)
{
	if (piece.size() == 0) return 0;

	int left, right, i, size;

	for (i = 0, size = piece.size() - 1; i < size; ++i)
	{
		
		if (piece[i].GetPhraseType() == Element::Phrase::Bracket_Left)
		{
			left = i;
			right = i;
			for (int j = 1, size = piece.size() - 1; j > 0 && size != right;)
			{
				++right;
				if (piece[right].GetPhraseType() == Element::Phrase::Bracket_Left) ++j;
				if (piece[right].GetPhraseType() == Element::Phrase::Bracket_Right) --j;
			}
			if (right == piece.size() - 1 && piece[right].GetPhraseType() != Element::Phrase::Bracket_Right) return -1;

			vector<Element> part(piece);
			//part.assign(part.begin() + left + 1, part.begin() + right - left - 1);
			part.erase(part.begin(), part.begin() + left + 1);
			part.erase(part.begin() + (right - left - 1), part.end());

			piece.erase(piece.begin() + left, piece.begin() + right + 1);
			piece.insert(piece.begin() + left, Element(answer(part)));
			size = piece.size() - 1;
		}
	}

	piece = calc_funcion(piece, Element::Operation::Sinus);
	piece = calc_funcion(piece, Element::Operation::Sinus_Hiperbolide);
	piece = calc_funcion(piece, Element::Operation::Cosinus);
	piece = calc_funcion(piece, Element::Operation::Cosinus_Hiperbolide);
	piece = calc_funcion(piece, Element::Operation::Tanges);
	piece = calc_funcion(piece, Element::Operation::Tanges_Hiperbolide);
	piece = calc_funcion(piece, Element::Operation::Ln);
	piece = calc_funcion(piece, Element::Operation::Log);
	piece = calc_funcion(piece, Element::Operation::Exponenta);
	piece = calc_funcion(piece, Element::Operation::Intinger);
	piece = calc_operator(piece, Element::Operation::Power);
	piece = calc_funcion(piece, Element::Operation::Root);
	piece = calc_operator(piece, Element::Operation::Division);
	piece = calc_operator(piece, Element::Operation::Modulo);
	piece = calc_operator(piece, Element::Operation::Multiplication);
	piece = calc_operator(piece, Element::Operation::Substraction);
	piece = calc_operator(piece, Element::Operation::Addition);

	//if (piece.size() > 1) throw new ArgumentException("Remains in equation:" + piece.size(), "piece in answer");
	return piece[piece.size() - 1].ToValue();
}

vector<Element> Equation::calc_operator(vector<Element> piece, Element::Operation op)
{

	for (int i = 0; i < piece.size() - 1; ++i)
	{
		if (piece[i].GetPhraseType() == Element::Phrase::Operation && piece[i].operation() == op)
		{
			double d1 = piece[i - 1].ToValue();
			double d2 = piece[i + 1].ToValue();
			piece.erase(piece.begin() + i - 1, piece.begin() + i + 2);

			Element el(1.);
			
			switch (op)
			{
			case Element::Operation::Addition:
				el = Element(d1 + d2);
				break;

			case Element::Operation::Substraction:
				el = Element(d1 - d2);
				break;

			case Element::Operation::Multiplication:
				el = Element(d1 * d2);
				break;

			case Element::Operation::Division:
				el = Element(d1 / d2);
				break;

			case Element::Operation::Modulo:
				el = Element(fmod(d1, d2));
				break;

			case Element::Operation::Power:
				el = Element(pow(d1, d2));
				break;

			default:
				//throw new ArgumentException("Unexpected operator: " + op.ToString(), "type in calc_operator");
				break;
			}
			if (piece.size() > i - 1)
			{
				piece.insert(piece.begin() + i - 1, el);
			}
			else piece.push_back(el);
			--i;
		}
	}
	return piece;
}

vector<Element> Equation::calc_funcion(vector<Element> piece, Element::Operation funcion)
{
	for (int i = 0; i < piece.size() - 1; ++i)
	{
		
		if ((piece[i].GetPhraseType() == Element::Phrase::Funcion || piece[i].GetPhraseType() == Element::Phrase::Funcion_With_Base) && piece[i].operation() == funcion)
		{
			double bas = 0;
			if (piece[i + 1].GetPhraseType() == Element::Phrase::Funcion)
			{
				vector<Element> part(piece);
				part.assign(part.begin() + i + 2, part.end() - 1 - i);
				piece.erase(piece.begin() + i, piece.end() - 1 - i);
				piece.insert(piece.begin() + i, Element(answer(part)));
			}		
			else if (piece[i].GetPhraseType() == Element::Phrase::Funcion_With_Base) bas = piece[i].ToValue();

			double d1 = piece[i + 1].ToValue();
			piece.erase(piece.begin() + i, piece.begin() + i + 2);

			Element el(1.);

			switch (funcion)
			{
			case Element::Operation::Sinus:
				el = Element(sin(d1));
				break;

			case Element::Operation::Sinus_Hiperbolide:
				el = Element(sinh(d1));
				break;

			case Element::Operation::Cosinus:
				el = Element(cos(d1));
				break;

			case Element::Operation::Cosinus_Hiperbolide:
				el = Element(cosh(d1));
				break;

			case Element::Operation::Tanges:
				el = Element(tan(d1));
				break;

			case Element::Operation::Tanges_Hiperbolide:
				el = Element(tanh(d1));
				break;

			case Element::Operation::Ln:
				el = Element(log(d1));
				break;

			case Element::Operation::Exponenta:
				el =  Element(exp(d1));
				break;

			case Element::Operation::Intinger:
				el = Element(round(d1));
				break;

			case Element::Operation::Root:
				el = Element(pow(d1, 1.0f / bas));
				break;

			case Element::Operation::Log:
				el = Element(log(d1) / log(bas));
				break;
			default:
				//throw new ArgumentException("Unexpected funcion: " + funcion, "funcion in calc_funcion");
				break;
			}
			if (piece.size() > i)
			{
				piece.insert(piece.begin() + i, el);
			}
			else piece.push_back(el);
		}
	}
	return piece;
}

void Equation::Clear()
{
	element.clear();
	element.shrink_to_fit();
}


