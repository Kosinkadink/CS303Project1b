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
// used when comparing two polynomials for less than
bool Term::operator<(Term term2)
{
    return exponent < term2.exponent;
}
// used when comparing two polynomials for greater than
bool Term::operator>(Term term2)
{
    return exponent > term2.exponent;
}
// used to compare two polynomials for equals to
bool Term::operator==(Term term2)
{
    return exponent == term2.exponent;
}