/*Write a bool function that tests the function from task 8 with
different values. It should call the function from 8 for a value and
check the result against the expected answer. Make the function
check at least 10 numbers of different length and return true if
all were correct or false if any of them was wrong. Call that this
checking function from main() and print its result*/

#include <iostream>
using namespace std;

unsigned long long reversedNumber(unsigned long long);
bool testReversedNumber();

int main()
{
    cout << boolalpha << testReversedNumber() << endl;

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

bool testReversedNumber()
{
    const int INPUT_DATA = 10;
    unsigned long long inputData[]    = {123456789, 22446688, 10021, 786, 3451, 12, 8, 0, 51895, 5858758};
    unsigned long long expectedData[] = {987654321, 88664422, 12001, 687, 1543, 21, 8, 0, 59815, 8578585};

    for (int i = 0; i < INPUT_DATA; i++)
    {
        if (reversedNumber(inputData[i]) != expectedData[i])
        {
            return false;
        }

    }

    return true;
}
