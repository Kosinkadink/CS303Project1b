#pragma once

#include <string>
#include <sstream>
#include "Term.h"
#include "Polynomial.h"

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
	stringstream inputstream(input);
	Polynomial poly;

	int coeff, exp = NULL;
	char ch,ch2;

	while (inputstream >> ch)
	{
		if (isdigit(ch)) //starts with a digit; only occurs when the first term entered is positive
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
					poly.addTerm(Term(coeff, exp));
				}
				else if (ch == 'X')
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
								poly.addTerm(Term(coeff, exp));
							}
							else if (ch == '-')
							{
								inputstream >> ch;
								if (isdigit(ch))
								{
									inputstream.putback(ch);
									inputstream >> exp;
									poly.addTerm(Term(coeff, -exp)); //making exponent negative because of minus sign
								}
								else
								{
									// THROW polynomial exception; no exponent value when expected
								}
							}
							else
							{
								// THROW polynomial exception; expected exponent or start of next term
							}
						}
						else if (ch == '+' || ch == '-')
						{
							inputstream.putback(ch);
							exp = 1;
							poly.addTerm(Term(coeff, exp));
						}
						else
						{
							// THROW polynomial exception; expected ^ or start of next term
						}
					}
					else
					{
						exp = 1;
						poly.addTerm(Term(coeff, exp));
					}
				}
				else
				{
					// THROW polynomial exception; expected +/-, X or start of next term
				}
			}
			else
			{
				exp = 1;
				poly.addTerm(Term(coeff, exp));
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

						if (ch == 'X')
						{
							// determine if next character is X or part of the next term
							if (inputstream >> ch) // if something to read
							{
								if (ch == '+' || ch == '-')
								{
									inputstream.putback(ch);
									exp = 1;
									poly.addTerm(Term(coeff, exp));
								}
								// check if there is a carrot with value
								else if (ch == '^')
								{
									inputstream >> ch;
									if (isdigit(ch))
									{
										inputstream.putback(ch);
										inputstream >> exp;
										poly.addTerm(Term(coeff, exp));
									}
									else if (ch == '-')
									{
										inputstream >> ch;
										if (isdigit(ch))
										{
											inputstream.putback(ch);
											inputstream >> exp;
											poly.addTerm(Term(coeff, -exp)); //making exponent negative because of minus sign
										}
										else
										{
											// THROW polynomial exception; no exponent value when expected
										}
									}
									else
									{
										// THROW polynomial exception; expected exponent or start of next term
									}
								}
								else
								{
									// THROW polynomial exception; expected ^ or start of next term
								}
							}
							else
							{
								exp = 1;
								poly.addTerm(Term(coeff, exp));
							}
						}
						else if (ch == '+' || ch == '-')
						{
							inputstream.putback(ch);
							exp = 0;
							poly.addTerm(Term(coeff, exp));
						}
						else
						{
							// THROW polynomial exception; expected X or start of next term
						}
					}
					else
					{
						exp = 0;
						poly.addTerm(Term(coeff, exp));
					}
				}
				else if (ch2 == 'X')
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
							poly.addTerm(Term(coeff, exp));
						}


						// check if there is a carrot with value
						else if (ch == '^')
						{
							inputstream >> ch;
							if (isdigit(ch))
							{
								inputstream.putback(ch);
								inputstream >> exp;
								poly.addTerm(Term(coeff, exp));
							}
							else if (ch == '-')
							{
								inputstream >> ch;
								if (isdigit(ch))
								{
									inputstream.putback(ch);
									inputstream >> exp;
									poly.addTerm(Term(coeff, -exp)); //making exponent negative because of minus sign
								}
								else
								{
									// THROW polynomial exception; no exponent value when expected
								}
							}
							else
							{
								// THROW polynomial exception; expected exponent or start of next term
							}
						}

						else
						{
							// THROW polynomial exception; expected ^ or start of next term
						}
					}
					else
					{
						exp = 1;
						poly.addTerm(Term(coeff, exp));
					}
				}
				else
				{
					// THROW polynomial exception; expected coefficient or X
				}
			}
			else if (ch == 'X')
			{
				coeff = 1;
				// determine if next character is X or part of the next term
				if (inputstream >> ch) // if something to read
				{
					if (ch == '+' || ch == '-')
					{
						inputstream.putback(ch);
						exp = 1;
						poly.addTerm(Term(coeff, exp));
					}
					// check if there is a carrot with value
					else if (ch == '^')
					{
						inputstream >> ch;
						if (isdigit(ch))
						{
							inputstream.putback(ch);
							inputstream >> exp;
							poly.addTerm(Term(coeff, exp));
						}
						else if (ch == '-')
						{
							inputstream >> ch;
							if (isdigit(ch))
							{
								inputstream.putback(ch);
								inputstream >> exp;
								poly.addTerm(Term(coeff, -exp)); //making exponent negative because of minus sign
							}
							else
							{
								// THROW polynomial exception; no exponent value when expected
							}
						}
						else
						{
							// THROW polynomial exception; expected exponent or start of next term
						}
					}
					else
					{
						// THROW polynomial exception; expected ^ or start of next term
					}
				}
				else
				{
					exp = 1;
					poly.addTerm(Term(coeff, exp));
				}
			}

		}
		if (coeff == NULL || exp == NULL)
		{
			// THROW polynomial exception; coefficient or exponent was not understood
		}

		//set coeff adn exp to null again
		coeff = exp = NULL;
	}

	return poly;
}