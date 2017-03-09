/* Write a program that finds the longest sequence of equal elements in an
integer array and then prints that sequence on the console (integers
separated by space or newline) */

#include<iostream>

using namespace std;

int main()
{
    int array_elements = 0;

    cout << "Enter array size (elements): ";

    cin >> array_elements;

    int arr[array_elements];

    cout << endl << "Enter " << array_elements << " integer number(s): ";

    for (int i = 0; i < array_elements; i++)
    {
        cin >> arr[i];
    }

    int long_seq_start = 0;
    int long_seq_lenght = 0;
    int last_seq_end = -1;

    for (int i = 1; i < array_elements; i++)
    {
        if (arr[i-1] != arr[i])
        {
            last_seq_end = i - 1;
        }

        if (i - last_seq_end >= long_seq_lenght)
        {
            long_seq_lenght = i - last_seq_end;
            long_seq_start = last_seq_end + 1;
        }
    }

    cout << endl << "The longest sequence (" << long_seq_lenght
        << ") of equal numbers starts at index ["
        << long_seq_start << "]:" << endl << endl;

    for (int i = long_seq_start; i < long_seq_start + long_seq_lenght ; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}
