#pragma once

#include <string>
using namespace std;

class PolynomialException : public exception
{
public:
	PolynomialException(string e = "Error occured in Polynomial class") { msg = e; }
	string what();
private:
	string msg;
};


string PolynomialException::what()
{
	return msg;
}