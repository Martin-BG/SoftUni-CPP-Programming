/*Write a program that calculates the greatest common divisor
(GCD) of given two numbers. Use the Euclidean algorithm (find it
in Internet)*/

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
        gcd = 0;
    }
    else
    {
        gcd = findGreatesCommonDivisor(num2, num1);

        if (gcd < 0)
        {
            gcd = -gcd;

        }
    }

    cout << "The greatest common divisor of "<< num1 << " and " << num2 << " is: " << gcd << endl;

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
