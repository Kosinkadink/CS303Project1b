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
	Polynomial operator+(const Polynomial& rhs);
	void printPolynomial();
    ~Polynomial();
    Polynomial(const Polynomial& other);
    const Polynomial& operator= (const Polynomial& rhs);
private:
	list<Term> terms;
};

// add a term in the correct position in a polynomial's list
void Polynomial::addTerm(Term newterm)
{
    // polynomial is empty
	if (terms.empty())
	{
		terms.push_front(newterm);
	}
	else
	{
		list<Term>::iterator iter;
        // find correct spot to insert term
		for (iter = terms.begin(); iter != terms.end(); iter++)
		{
			if (*iter == newterm)
			{
                // add coefficents of like terms
				*iter + newterm;
                // remove terms from polynomial if their coefficent's become 0
				if (iter->getCoeff() == 0)
					terms.erase(iter);
				return;
			}
            // place into correct position
			else if (*iter < newterm)
			{
				terms.insert(iter, newterm);
				return;
			}
		}
		terms.push_back(newterm);
	}
}

// add two polynomials and return a new polynomial
Polynomial Polynomial::operator+(const Polynomial& rhs)
{
	list<Term>::iterator iter1;
	list<Term>::const_iterator iter2;
	Polynomial newPoly;
    // add all items from first polynomial
	for (iter1 = terms.begin(); iter1 != terms.end(); iter1++)
	{
		newPoly.addTerm(*iter1);
	}
    // add all items from second polynomial
	for (iter2 = rhs.terms.begin(); iter2 != rhs.terms.end(); iter2++)
	{
		newPoly.addTerm(*iter2);
	}
	return newPoly;
}

// print ordered polynomial to the screen in legible fashion
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
    // check self assignment
    if (this != &rhs)
    {
        // clear old data if any exists
        if (!terms.empty())
        {
            terms.clear();
        }
        // copy new data if any exists
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