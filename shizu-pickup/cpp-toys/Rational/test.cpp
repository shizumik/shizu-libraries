#include <iostream>

#include "rational.h"

using namespace std;

void display(const Rational &lhs, const Rational &rhs)
{
	cout << "+ : " << lhs + rhs << " swap : " << rhs + lhs << endl;
	cout << "- : " << lhs - rhs << " swap : " << rhs - lhs << endl;
	cout << "* : " << lhs * rhs << " swap : " << rhs * lhs << endl;
	cout << "/ : " << lhs / rhs << " swap : " << rhs / lhs << endl;
}

int main()
{
	Rational r1(3, 4);
	Rational r2(4, 3);
	display(r1, r2);
}