/*Write a program that shows the sign (+ or -) of the product of
three real numbers without calculating it. Use a sequence of if
statements.*/

#include <iostream>
using namespace std;

int main()
{
    double num1;
    double num2;
    double num3;

    cout << "Enter 3 real numbers: ";

    cin >> num1 >> num2 >> num3;

    int negative_numbers = 0;

    if (num1 != 0.0 && num2 != 0.0 && num3 != 0.0)
    {
        if (num1 < 0.0)
        {
            negative_numbers++;
        }

        if (num2 < 0.0)
        {
            negative_numbers++;
        }

        if (num3 < 0.0)
        {
            negative_numbers++;
        }
    }

    cout << ((negative_numbers % 2 == 0) ? "+" : "-") << endl;

	return 0;
}
