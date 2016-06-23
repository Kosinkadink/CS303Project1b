#include "UserInterface.h"
#include "Polynomial.h"
#include <string>

using namespace std;

int main()
{
	string example = "-X+5+X^2-10";
	string example2 = "5X-5X^-2+10-5X+X^2";
	Polynomial pleasework;

	UserInterface ui;
	ui.parsePolynomial(example2);
	

	return 0;
}