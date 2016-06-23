#pragma once

#include <string>
#include <sstream>
#include "Term.h"
#include "Polynomial.h"
#include "PolynomialException.h"

using namespace std;

class UserInterface
{
public:
	UserInterface() {}
	Polynomial parsePolynomial(string input);
private:
	void parseAfterX(int& coeff, int& exp, stringstream& inputstream, Polynomial& poly, char& ch);

};

// take a valid string input and return an ordered polynomial
 Polynomial UserInterface::parsePolynomial(string input)
{
	 return Polynomial(input);
}