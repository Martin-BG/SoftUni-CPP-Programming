/*Write a program that reads from the console a sequence of N
integer numbers and returns the minimal and maximal of them*/

#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int numbers_to_read, current_num, min_num, max_num;

    min_num = INT_MAX;
    max_num = INT_MIN;

    cout << "Enter total numbers: ";

    cin >> numbers_to_read;

    for (int i = 0; i < numbers_to_read; i++)
    {
        cout << "Enter next number (" << i + 1 << " of " << numbers_to_read << "): ";

        cin >> current_num;

        if (current_num > max_num)
        {
            max_num = current_num;
        }

        if (current_num < min_num)
        {
            min_num = current_num;
        }
    }

    cout << "Min number: " << min_num << endl;
    cout << "Max number: " << max_num << endl;

    return 0;
}
