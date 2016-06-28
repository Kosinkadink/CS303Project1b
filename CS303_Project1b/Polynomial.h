#pragma once

#include "Term.h"
#include "PolynomialException.h"
#include <list>
#include <iostream>

using namespace std;

class Polynomial
{
public:
    Polynomial() { ; }
    Polynomial(string input) { createFromString(input); }
    void addTerm(Term newterm);
    Polynomial operator+(const Polynomial& rhs);
    void createFromString(string input);
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
    // polynomial contains some terms, placement matters
    else
    {
        list<Term>::iterator iter;
        // find correct spot to insert term by iterating over the list
        for (iter = terms.begin(); iter != terms.end(); iter++)
        {
            // nex exponent already exists, adjust coefficent term appropriately
            if (*iter == newterm)
            {
                // add coefficents of like terms
                *iter + newterm;
                // remove terms from polynomial if their coefficent's become 0
                if (iter->getCoeff() == 0)
                    terms.erase(iter);
                return;
            }
            // place into correct position in the list
            else if (*iter < newterm)
            {
                // create a new term in the correctly located spot
                terms.insert(iter, newterm);
                return;
            }
        }
        // term needs to be placed at the end of the list
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
    // print as we iterate over the terms
    for (iter1 = terms.begin(); iter1 != terms.end(); iter1++)
    {
        // positive coefficent
        if (iter1->getCoeff() > 0)
        {
            // special case, don't print 1 in 1x situations
            if (iter1->getCoeff() == 1 && iter1->getExponent() != 0)
            {
                //special case, don't print + if first term
                if (iter1 != terms.begin())
                    cout << "+";
            }
            else
            {
                //special case, don't print + if first term
                if (iter1 != terms.begin())
                    cout << "+";
                cout << iter1->getCoeff();
            }
        }
        // negative coefficent
        else if (iter1->getCoeff() < 0)
        {
            // special case, don't print 1 in -1x situations
            if (iter1->getCoeff() == -1 && iter1->getExponent() != 0)
                cout << "-";
            else
                cout << iter1->getCoeff();
        }
        // 0 exponent, associated with a constant.  i.e. no X in this term
        if (iter1->getExponent() == 0)
        {
            cout << " ";
        }
        // exponent of 1, format for no ^
        else if (iter1->getExponent() == 1)
        {
            cout << "X ";
        }
        // normal exponent formatting
        else if (iter1->getExponent() != 0)
        {
            cout << "X^" << iter1->getExponent() << " ";
        }
    }
    cout << endl;
}

// deconstuctor
Polynomial::~Polynomial()
{
    // if the polynomial contains a list of terms, clear them
    if (!terms.empty())
    {
        terms.clear();
    }
}

// copy constructor
Polynomial::Polynomial(const Polynomial& other)
{
    *this = other;
}

// assignment operator
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
    // return
    return *this;
}

// parse a polynomial from an input string
void Polynomial::createFromString(string input)
{
    // clear current polynomial information if any exists
    if (!terms.empty())
        terms.clear();
    // a blank string = poly with a zero constant term
    if (input.empty()) 
    {
        // format for blank input
        addTerm(Term(0, 0));
        return;
    }
    // declare stringsteam for parsing
    stringstream inputstream(input);
    // variables to be used in parsing
    int coeff, exp = NULL;
    char ch, ch2;
    // parse entire string input
    while (inputstream >> ch)
    {
        //starts with a digit; only occurs when the first term entered is positive
        if (isdigit(ch)) 
        {
            inputstream.putback(ch);
            // read integer into coeff
            inputstream >> coeff;
            // determine if next character is X or part of the next term
            if (inputstream >> ch) // if something to read
            {
                if (ch == '+' || ch == '-')
                {
                    inputstream.putback(ch);
                    exp = 0;
                    addTerm(Term(coeff, exp));
                }
                else if (ch == 'X' || ch == 'x')
                {
                    if (inputstream >> ch) //if something to read
                    {
                        // check if there is a carrot with value
                        if (ch == '^')
                        {
                            inputstream >> ch;
                            if (isdigit(ch))
                            {
                                inputstream.putback(ch);
                                inputstream >> exp;
                                addTerm(Term(coeff, exp));
                            }
                            else if (ch == '-')
                            {
                                inputstream >> ch;
                                if (isdigit(ch))
                                {
                                    inputstream.putback(ch);
                                    inputstream >> exp;
                                    addTerm(Term(coeff, -exp)); //making exponent negative because of minus sign
                                }
                                else
                                {
                                    // THROW polynomial exception; no exponent value when expected
                                    throw PolynomialException("no exponent value when expected, got: " + ch);
                                }
                            }
                            else
                            {
                                // THROW polynomial exception; expected exponent or start of next term
                                throw PolynomialException("expected exponent or start of next term, got: " + ch);
                            }
                        }
                        else if (ch == '+' || ch == '-')
                        {
                            inputstream.putback(ch);
                            exp = 1;
                            addTerm(Term(coeff, exp));
                        }
                        else
                        {
                            // THROW polynomial exception; expected ^ or start of next term
                            throw PolynomialException("expected ^ or start of next term, got: " + ch);
                        }
                    }
                    else
                    {
                        exp = 1;
                        addTerm(Term(coeff, exp));
                    }
                }
                else
                {
                    // THROW polynomial exception; expected +/-, X or start of next term
                    throw PolynomialException("expected +/-, X or start of next term, got: " + ch);
                }
            }
            else
            {
                exp = 0;
                addTerm(Term(coeff, exp));
            }
        }
        else // used for all non-first terms
        {
            if (ch == '+' || ch == '-')
            {
                inputstream >> ch2;
                if (isdigit(ch2))
                {
                    inputstream.putback(ch2);
                    inputstream >> coeff;
                    if (ch == '-')
                        coeff *= -1;
                    //determine if next character is X, or start of next term
                    if (inputstream >> ch) //if something to read
                    {

                        if (ch == 'X' || ch == 'x')
                        {
                            // determine if next character is X or part of the next term
                            if (inputstream >> ch) // if something to read
                            {
                                if (ch == '+' || ch == '-')
                                {
                                    inputstream.putback(ch);
                                    exp = 1;
                                    addTerm(Term(coeff, exp));
                                }
                                // check if there is a carrot with value
                                else if (ch == '^')
                                {
                                    inputstream >> ch;
                                    if (isdigit(ch))
                                    {
                                        inputstream.putback(ch);
                                        inputstream >> exp;
                                        addTerm(Term(coeff, exp));
                                    }
                                    else if (ch == '-')
                                    {
                                        inputstream >> ch;
                                        if (isdigit(ch))
                                        {
                                            inputstream.putback(ch);
                                            inputstream >> exp;
                                            addTerm(Term(coeff, -exp)); //making exponent negative because of minus sign
                                        }
                                        else
                                        {
                                            // THROW polynomial exception; no exponent value when expected
                                            throw PolynomialException("no exponent value when expected, got: " + ch);
                                        }
                                    }
                                    else
                                    {
                                        // THROW polynomial exception; expected exponent or start of next term
                                        throw PolynomialException("expected exponent or start of next term, got: " + ch);
                                    }
                                }
                                else
                                {
                                    // THROW polynomial exception; expected ^ or start of next term
                                    throw PolynomialException("expected ^ or start of next term, got: " + ch);
                                }
                            }
                            else
                            {
                                exp = 1;
                                addTerm(Term(coeff, exp));
                            }
                        }
                        else if (ch == '+' || ch == '-')
                        {
                            inputstream.putback(ch);
                            exp = 0;
                            addTerm(Term(coeff, exp));
                        }
                        else
                        {
                            // THROW polynomial exception; expected X or start of next term
                            throw PolynomialException("expected X or start of next term, got: " + ch);
                        }
                    }
                    else
                    {
                        exp = 0;
                        addTerm(Term(coeff, exp));
                    }
                }
                else if (ch2 == 'X' || ch2 == 'x')
                {
                    coeff = 1;
                    if (ch == '-')
                        coeff *= -1;
                    // determine if next character is X or part of the next term
                    if (inputstream >> ch) // if something to read
                    {
                        if (ch == '+' || ch == '-')
                        {
                            inputstream.putback(ch);
                            exp = 1;
                            addTerm(Term(coeff, exp));
                        }


                        // check if there is a carrot with value
                        else if (ch == '^')
                        {
                            inputstream >> ch;
                            if (isdigit(ch))
                            {
                                inputstream.putback(ch);
                                inputstream >> exp;
                                addTerm(Term(coeff, exp));
                            }
                            else if (ch == '-')
                            {
                                inputstream >> ch;
                                if (isdigit(ch))
                                {
                                    inputstream.putback(ch);
                                    inputstream >> exp;
                                    addTerm(Term(coeff, -exp)); //making exponent negative because of minus sign
                                }
                                else
                                {
                                    // THROW polynomial exception; no exponent value when expected
                                    throw PolynomialException("no exponent value when expected, got: " + ch);

                                }
                            }
                            else
                            {
                                // THROW polynomial exception; expected exponent or start of next term
                                throw PolynomialException("expected exponent or start of next term, got: " + ch);
                            }
                        }

                        else
                        {
                            // THROW polynomial exception; expected ^ or start of next term
                            throw PolynomialException("expected ^ or start of next term, got: " + ch);
                        }
                    }
                    else
                    {
                        exp = 1;
                        addTerm(Term(coeff, exp));
                    }
                }
                else
                {
                    // THROW polynomial exception; expected coefficient or X
                    throw PolynomialException("expected coefficient or X, got: " + ch);
                }
            }
            else if (ch == 'X' || ch == 'x')
            {
                coeff = 1;
                // determine if next character is X or part of the next term
                if (inputstream >> ch) // if something to read
                {
                    if (ch == '+' || ch == '-')
                    {
                        inputstream.putback(ch);
                        exp = 1;
                        addTerm(Term(coeff, exp));
                    }
                    // check if there is a carrot with value
                    else if (ch == '^')
                    {
                        inputstream >> ch;
                        if (isdigit(ch))
                        {
                            inputstream.putback(ch);
                            inputstream >> exp;
                            addTerm(Term(coeff, exp));
                        }
                        else if (ch == '-')
                        {
                            inputstream >> ch;
                            if (isdigit(ch))
                            {
                                inputstream.putback(ch);
                                inputstream >> exp;
                                addTerm(Term(coeff, -exp)); //making exponent negative because of minus sign
                            }
                            else
                            {
                                // THROW polynomial exception; no exponent value when expected
                                throw PolynomialException("no exponent value when expected, got: " + ch);
                            }
                        }
                        else
                        {
                            // THROW polynomial exception; expected exponent or start of next term
                            throw PolynomialException("expected exponent or start of next term, got: " + ch);
                        }
                    }
                    else
                    {
                        // THROW polynomial exception; expected ^ or start of next term
                        throw PolynomialException("expected ^ or start of next term, got: " + ch);
                    }
                }
                else
                {
                    exp = 1;
                    addTerm(Term(coeff, exp));
                }
            }

        }
        if (coeff == NULL || exp == NULL && coeff != 0 && exp != 0)
        {
            // THROW polynomial exception; coefficient or exponent was not understood
            throw PolynomialException("coefficient or exponent was not understood");

        }

        //set coeff adn exp to null again
        coeff = exp = NULL;
    }

    // all done
}
