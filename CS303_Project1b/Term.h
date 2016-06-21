#pragma once

class Term
{
public:
	Term(int co, int ex) { coeff = co; exponent = ex; }
	void operator+(Term term2);
	bool operator<(Term term2);
	bool operator>(Term term2);
	bool operator==(Term term2);
	int getExponent() { return exponent; }
	int getCoeff() { return coeff; }
private:
	int exponent;
	int coeff;
};
// used when adding two polynomials
void Term::operator+(Term term2)
{
	coeff += term2.getCoeff();
}

bool Term::operator<(Term term2)
{
	return exponent < term2.exponent;
}


bool Term::operator>(Term term2)
{
	return exponent > term2.exponent;
}


bool Term::operator==(Term term2)
{
	return exponent == term2.exponent;
}