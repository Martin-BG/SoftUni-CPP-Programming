/*Write a program that calculates for given N how many trailing
zeros present at the end of the number N!. Examples N = 10, N! =
3628800, answer 2; N! = 2432902008176640000, answer: 4. Make
sure your program works for N up to 50 000*/

#include <iostream>
using namespace std;

int main()
{
    int num;

    cout << "Enter N: ";

    cin >> num;

    int trailingZeroes = num / 5 + num / 25 + num / 125 + num / 625 + num / 3125 + num / 15625;

    cout << num << "! has " << trailingZeroes << " trailing zero(s)." << endl;

    return 0;
}
