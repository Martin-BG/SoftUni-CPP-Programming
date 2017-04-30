#include<iostream>
#include<sstream>

#include "BigInt.h"

int getSumOfDigits(const std::string &);

int main()
{
    std::string num1, num2;
    std::cin >> num1 >> num2;

    BigInt start_num(num1);
    BigInt end_num(num2);

    int last_digit = num1[num1.size()-1] - '0';
    int correction = 0;
    if (last_digit != 0 && last_digit != 5)
    {
        if(last_digit > 5)
        {
            correction = 10 - last_digit;
        }
        else
        {
            correction = 5 - last_digit;
        }
    }

    if (correction > 0)
    {
        start_num += BigInt(correction);
    }

    BigInt five(5);
    int sum_of_digits = getSumOfDigits(start_num.getDigits());

    while (sum_of_digits % 9 != 0)
    {
        start_num += five;
        sum_of_digits = getSumOfDigits(start_num.getDigits());
    }

    BigInt forty_five(45);
    while (start_num < end_num)
    {
        std::cout << start_num << std::endl;
        start_num += forty_five;
    }

    return 0;
}

int getSumOfDigits(const std::string & digits)
{
    int sum = 0;
    int str_size = digits.size();
    for (int i = 0; i< str_size; i++)
    {
        sum += digits[i] - '0';
    }
    return sum;
}
