#pragma once

#include "Term.h"
#include <list>
#include <iostream>

using namespace std;

class Polynomial
{
public:
    Polynomial() { ; }
	void addTerm(Term newterm);
	const Polynomial& operator+(const Polynomial& rhs);
	void printPolynomial();
    ~Polynomial();
    Polynomial(const Polynomial& other);
    const Polynomial& operator= (const Polynomial& rhs);
private:
	list<Term> terms;
};


void Polynomial::addTerm(Term newterm)
{
	if (terms.empty())
	{
		terms.push_front(newterm);
	}
	else
	{
		list<Term>::iterator iter;
		for (iter = terms.begin(); iter != terms.end(); iter++)
		{
			if (*iter == newterm)
			{
				*iter + newterm;
				if (iter->getCoeff() == 0)
					terms.erase(iter);
				return;
			}
			else if (*iter < newterm)
			{
				terms.insert(iter, newterm);
				return;
			}
		}
		terms.push_back(newterm);
	}
}


const Polynomial& Polynomial::operator+(const Polynomial& rhs)
{
	list<Term>::iterator iter1;
	list<Term>::const_iterator iter2 = rhs.terms.begin();
	Polynomial newPoly;

	for (iter1 = terms.begin(); iter1 != terms.end(); iter1++)
	{
		newPoly.addTerm(*iter1);
	}
	for (iter2 = terms.begin(); iter2 != terms.end(); iter2++)
	{
		newPoly.addTerm(*iter2);
	}
	return newPoly;
}

void Polynomial::printPolynomial()
{
	list<Term>::iterator iter1;
    // print as we iterate over out terms
	for (iter1 = terms.begin(); iter1 != terms.end(); iter1++)
	{
        if (iter1->getCoeff() > 0)
        {
            // special case, don't print 1 in 1x situations
            if (iter1->getCoeff() == 1 && iter1->getExponent() != 0)
                cout << "+";
            else
                cout << "+" << iter1->getCoeff();
        }
        else if (iter1->getCoeff() < 0)
        {
            // special case, don't print 1 in -1x situations
            if (iter1->getCoeff() == -1 && iter1->getExponent() != 0)
                cout << "-";
            else
                cout  << iter1->getCoeff();
        }
		if (iter1->getExponent() == 0)
		{
			cout << " ";
		}
        else if (iter1->getExponent() == 1)
        {
            cout << "X ";
        }
		else if (iter1->getExponent() != 0)
		{
			cout << "X^" << iter1->getExponent() << " ";
		}
	}
    cout << endl;
}

Polynomial::~Polynomial()
{
    if (!terms.empty())
    {
        terms.clear();
    }
}


Polynomial::Polynomial(const Polynomial& other)
{
    *this = other;
}

const Polynomial& Polynomial::operator= (const Polynomial& rhs)
{
    if (this != &rhs)
    {
        if (!terms.empty())
        {
            terms.clear();
        }
        if (!rhs.terms.empty())
        {
            // make a deep copy of the data
            list<Term>::const_iterator iter1;
            for (iter1 = rhs.terms.begin(); iter1 != rhs.terms.end(); iter1++)
            {
                terms.push_back(*iter1);
            }
        }
    }
    return *this;
}