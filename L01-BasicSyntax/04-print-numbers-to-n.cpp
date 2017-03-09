/*Write a program that prints all the numbers from 1 to N*/

#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter N: ";

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cout << i << endl;
    }

    return 0;
}
