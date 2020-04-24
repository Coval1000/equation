#ifndef _IOSTREAM_H_
#include <iostream>
#endif // !_IOSTREAM_H_

#ifndef _EQUATIONCLASS_H_
#include "EquationClass.h"
#endif // !_EQUATIONCLASS_H_

#ifndef _TIME_H_
#include <time.h>
#define _TIME_H_
#endif // !_TIME_H_


#include <io.h>
#include <fcntl.h>

int main()
{
	Equation eq;
	std::string str;
	int cpms = CLOCKS_PER_SEC / 1000;
	int timeB, time;
	eq.Add(0.1);
	eq.Add(Element::Operation::Multiplication);
	eq.Add(0.05);
	eq.Add(Element::Operation::Addition);
	eq.Add(Element::Operation::Bracket_Left);
	eq.Add(12);
	eq.Add(Element::Operation::Division);
	eq.Add(8);
	eq.Add(Element::Operation::Bracket_Right);
	eq.Add(Element::Operation::Power);
	eq.Add(3);

	//_setmode(_fileno(stdout), _O_U16TEXT);
	timeB = clock() / cpms;
	for(int r = 0;r<1000;++r)
		str = eq.toString();
	time = clock() / cpms - timeB;
	std::cout <<  "f(x)=" << eq.toString() << " | " << time << "ms " << std::endl;

	int i;
	std::cin >> i;
	double a;
	timeB = clock() / cpms;
	for (int r = 0; r<1000; ++r)
		a = eq.answer(i);
	time = clock() / cpms - timeB;
	std::cout << "f("<< i <<")=" << a << " | " << time << "ms " << std::endl;
	std::cin >> i;
}