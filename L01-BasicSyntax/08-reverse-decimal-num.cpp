/*Write a function that reverses the digits of given positive decimal
number. Example: 256 -> 652*/

#include <iostream>
using namespace std;

unsigned long long reversedNumber(unsigned long long);

int main()
{
    unsigned long long num;

    cout << "Enter a positive decimal number: ";

    cin >> num;

    cout << "Reversed number: " << reversedNumber(num) << endl;

    return 0;
}

unsigned long long reversedNumber(unsigned long long number)
{
    unsigned long long reversed_number = 0ULL;

    while (number > 0)
    {
        reversed_number *= 10;
        reversed_number += number % 10;
        number /= 10;
    }

    return reversed_number;
}
