#pragma once
#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational
{
public:
	Rational(int numerator = 0, int denominator = 1);
	int numerator() const;
	int denominator() const;
	
	//overload iostream
	friend std::ostream& operator<<(std::ostream &os, const Rational &r);
	friend std::istream& operator>>(std::istream &is, const Rational &r);
private:
	int numerator_;
	int denominator_;
};

// Rational operators
const Rational operator*(const Rational &lhs, const Rational &rhs);
const Rational operator/(const Rational &lhs, const Rational &rhs);
const Rational operator+(const Rational &lhs, const Rational &rhs);
const Rational operator-(const Rational &lhs, const Rational &rhs);

#endif // !RATIONAL_H
