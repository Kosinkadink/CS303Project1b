#pragma once

#include "Term.h"
#include <list>

using namespace std;

class Polynomial
{
public:
	Polynomial() {}
	void addTerm(Term newterm);
	const Polynomial& operator+(const Polynomial& rhs);
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