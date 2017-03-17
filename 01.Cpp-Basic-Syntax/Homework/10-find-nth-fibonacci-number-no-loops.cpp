/*For this task, you are NOT allowed to use any type of loop. Write a
function that calculates the Nth Fibonacci number.*/

#include <iostream>
using namespace std;

unsigned long long getFibonacciNum(int);

int main()
{
    int num;

    cout << "Enter a number (0 to 93): ";

    cin >> num;

    if (num == 0)
    {
        cout << 0;
    }
    else if (num > 0 && num <= 93)
    {
        cout << getFibonacciNum(num) << endl;
    }
    else
    {
        cout << "Invalid input!" << endl;
    }

    return 0;
}

unsigned long long getFibonacciNum(int num)
{
    // NOTE: Works for input numbers up to 93 (ULL overflows above that limit).
    // Verify at: http://planetmath.org/listoffibonaccinumbers

    static unsigned long long n1 = 0ULL;
    static unsigned long long n2 = 1ULL;
    static unsigned long long n3 = 0ULL;

    n3 = n1 + n2;
    n1 = n2;
    n2 = n3;

    if(num > 2)
    {
        getFibonacciNum(num - 1);
    }

    return n3;
}
