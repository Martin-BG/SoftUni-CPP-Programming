/*Write a program that calculates the greatest common divisor
(GCD) of given two numbers. Use the Euclidean algorithm (find it
in Internet)*/
// http://www.calculatorsoup.com/calculators/math/gcf.php

#include <iostream>
using namespace std;

int findGreatesCommonDivisor(int, int);

int main()
{
    int num1, num2, gcd;

    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    if (num1 == 0 || num2 == 0)
    {
        if (num1 == num2) // GCF(0,0) is undefined
        {
            gcd = 0;
        }
        else  // GCF(x,0) = x
        {
            gcd = (num1 != 0) ? num1 : num2;
        }
    }
    else
    {
        gcd = findGreatesCommonDivisor(num2, num1);
    }

    if (gcd < 0)
    {
        gcd = -gcd;

    }

    if (gcd != 0)
    {
        cout << "The greatest common divisor of "<< num1 << " and " << num2 << " is: " << gcd << endl;
    }
    else // GCF(0,0) is undefined
    {
        cout << "Undefined" << endl;
    }
    return 0;
}

int findGreatesCommonDivisor(int num1, int num2)
{
    if (num1 == 0)
    {
        return num2;
    }

    return findGreatesCommonDivisor(num2 % num1, num1);
}
