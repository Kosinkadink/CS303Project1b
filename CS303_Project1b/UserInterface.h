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
    void polyInput();
private:
    string poly1, poly2, select;
};

// take a valid string input and return an ordered polynomial
Polynomial UserInterface::parsePolynomial(string input)
{
    return Polynomial(input);
}

//has no parameters, displays option menu and gets input from user on what polynomial to parse
void UserInterface::polyInput() {

    bool a = true;
    bool b = true;
    Polynomial polyEntry1, polyEntry2, polyTotal;

    //prints out menu options
    cout << "~~~~~ POLYNOMIAL ADDITION PROGRAM ~~~~~\n\n";
    cout << "1. Input First Polynomial\n" << "2. Input Second Polynomial\n" << "3. Addition Of First And Second Polynomials\n"
        << "4. Quit\n\n" << "Please Enter Your Selection: ";
    cin >> select; cout << endl;

    while (b) // loops thru valid user selection 
    {
        while (a) //loops thru selection option if user input is invalid 
        {
            if (select == "1" || select == "2" || select == "3" || select == "4") { a = false; }
            else
            {
                cout << "Selection Is Invalid. Please Enter 1, 2, 3, or 4: ";
                cin >> select;
                cout << endl;
            }
        }

        // get first polynomial from user and parse polynomial
        if (select == "1")
        {
            cout << "Enter Your First Polynomial: ";
            cin >> poly1;
            polyEntry1 = parsePolynomial(poly1);
            cout << endl;
        }

        // get second polynomial from user and parse polynomial
        if (select == "2")
        {
            cout << "Enter Your Second Polynomial: ";
            cin >> poly2;
            polyEntry2 = parsePolynomial(poly2);
            cout << endl;
        }

        // adds poly1 and poly2, displays total polynomial
        if (select == "3")
        {
            cout << "The Addition Of The First and Second Polynomial Is:\n\n";
            polyTotal = polyEntry1 + polyEntry2;
            polyTotal.printPolynomial();
            cout << endl;
        }

        // quits program
        if (select == "4") { b = false; }

        // keep asking user for selection until user chooses to quit
        if (b)
        {
            a = true;
            cout << "Please Enter Another Selection(1, 2, 3, or 4): ";
            cin >> select;
            cout << endl;
        }

    }

}
