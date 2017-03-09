/* Write a program that reads two integer arrays from the console and
compares them element by element. The comparing should be done in a
function bool compArr(int arr1, int arr2), which returns true if
they are equal and false if not */

#include<iostream>

using namespace std;

bool compArr(int[], int[]);
void readArray(int[]);
void printArray(int[]);

int array_elements;

int main()
{
    cout << "Enter array size (elements): ";

    cin >> array_elements;

    int array_one[array_elements];
    int array_two[array_elements];

    readArray(array_one);
    readArray(array_two);

    cout << endl << "Elements in both arrays are "
        << (compArr(array_one, array_two) ? "" : "NOT ") << "equal." << endl << endl;

    printArray(array_one);
    printArray(array_two);

    return 0;
}

bool compArr(int arr1[], int arr2[])
{
    for (int i = 0; i < array_elements; i++)
    {
        if (arr1[i] != arr2[i])
        {
            return false;
        }
    }
    return true;
}

void readArray(int arr[])
{
    static int counter = 1;

    cout << endl << "Enter " << array_elements
        << " integer number(s) for array " << counter++ << ": ";

    for (int i = 0; i < array_elements; i++)
    {
        cin >> arr[i];
    }
}

void printArray(int arr[])
{
    static int counter = 1;

    cout << "Array " << counter++ << ": ";

    for (int i = 0; i < array_elements; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}
