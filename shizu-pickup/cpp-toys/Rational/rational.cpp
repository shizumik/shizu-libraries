#pragma once
#include "rational.h"

/*constructor*/
Rational::Rational(int numerator, int denominator) : 
	numerator_(numerator),denominator_(denominator)	{ }

/*basic member function*/
int Rational::numerator() const
{
	return this->numerator_;
}

int Rational::denominator() const
{
	return this->denominator_;
}

/*overload iostream*/
std::ostream& operator<<(std::ostream &os, const Rational &r)
{
	os << r.numerator() << "/" << r.denominator();
	return os;
}


/*Rational operators */
const Rational operator*(const Rational &lhs, const Rational &rhs)
{
	return Rational(lhs.numerator() * rhs.numerator(),
		lhs.denominator() * rhs.denominator());
}

const Rational operator/(const Rational &lhs, const Rational &rhs)
{
	return lhs * Rational(rhs.denominator(),rhs.numerator());
}

const Rational operator+(const Rational &lhs, const Rational &rhs)
{
	return Rational(lhs.numerator() * rhs.denominator() + rhs.numerator() * lhs.denominator(),
		lhs.denominator() * rhs.denominator());
}

const Rational operator-(const Rational &lhs, const Rational &rhs)
{
	return Rational(lhs.numerator() * rhs.denominator() - rhs.numerator() * lhs.denominator(),
		lhs.denominator() * rhs.denominator());
}
