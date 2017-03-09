/*Write a program that enters the coefficients a, b and c of a
quadratic equation a*x2 + b*x + c = 0 and calculates and
prints its real roots. Note that quadratic equations may have 0, 1
or 2 real roots.*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c;

    cout << "Enter a, b and c: ";

    cin >> a >> b >> c;

    double D = b * b - 4.0 * a * c;

    if (D < 0)
    {
        cout << "No real roots." << endl;
    }
    else if (D == 0)
    {
        double root = -b / 2.0 * a;
        cout << "One real root: " << root << endl;
    }
    else
    {
        D = sqrt(D);
        double root_one = (-b - D) / 2.0 * a;
        double root_two = (-b + D) / 2.0 * a;
        cout << "First real root is: " << root_one << endl;
        cout << "Second real root is: " << root_two << endl;
    }

    return 0;
}
