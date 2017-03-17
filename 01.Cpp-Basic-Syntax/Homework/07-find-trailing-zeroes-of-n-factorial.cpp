/*Write a program that calculates for given N how many trailing
zeros present at the end of the number N!. Examples N = 10, N! =
3628800, answer 2; N! = 2432902008176640000, answer: 4. Make
sure your program works for N up to 50 000*/
//trailingZeros = num / 5 + num / 25 + num / 125 + num / 625 + num / 3125 + num / 15625;

#include <iostream>

int main()
{
    int num;

    std::cout << "Enter N: ";

    std::cin >> num;

    int trailingZeros = 0;
    int new_zeros = 1;
    int power_of_five = 1;

    for (int i = 1; new_zeros > 0; i++)
    {
        power_of_five *= 5;
        new_zeros = num / power_of_five;
        trailingZeros += new_zeros;
    }

    std::cout << num << "! has " << trailingZeros << " trailing zero(s)." << std::endl;

    return 0;
}
