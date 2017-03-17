/* Write a program that reads two integer arrays from the console and
compares them element by element. The comparing should be done in a
function bool compArr(int arr1, int arr2), which returns true if
they are equal and false if not */

#include<iostream>
#include<string>
#include<sstream>

bool compArr(const int&, const int&);
int* readArrayOfInt(int&);
int countIntegerNumbersInString(const std::string&);
void printArray(const int[], const int&);

int main()
{
    int array_one_size = 0;
    int array_two_size = 0;
    int * pArrOne = readArrayOfInt(array_one_size);
    int * pArrTwo = readArrayOfInt(array_two_size);

    bool are_arrays_equal = array_one_size == array_two_size;

    if (are_arrays_equal)
    {
        for (int i = 0; are_arrays_equal && i < array_one_size; i++)
        {
            are_arrays_equal = compArr(pArrOne[i], pArrTwo[i]);
        }
    }

    std::cout << std::endl << "Elements in both arrays are "
        << (are_arrays_equal ? "" : "NOT ") << "equal." << std::endl << std::endl;

    printArray(pArrOne, array_one_size);
    printArray(pArrTwo, array_two_size);

    delete [] pArrOne;
    delete [] pArrTwo;

    return 0;
}

bool compArr(const int& arr1, const int& arr2)
{
    return (arr1 == arr2);
}

int* readArrayOfInt(int& array_size)
{
    static int counter = 1;

    std::cout << "Enter integer number(s) for array " << counter++ << ": ";

    std::string input_string;

    while (input_string.size() == 0) // Disallow creation of empty arrays
    {
        getline(std::cin, input_string);
    }

    array_size = countIntegerNumbersInString(input_string);

    int* pArr = new int[array_size];

    std::istringstream input_stream(input_string);

    int number;

    for (int i = 0; i < array_size; i++)
    {
        input_stream >> number;
        pArr[i] = number;
    }

    return pArr;
}

void printArray(const int arr[], const int& array_array_size)
{
    static int counter = 1;

    std::cout << "Array " << counter++ << ": ";

    for (int i = 0; i < array_array_size; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
}

int countIntegerNumbersInString(const std::string& str)
{
    int numbers = 0;
    int number;
    std::istringstream input_stream(str);

    while (input_stream >> number)
    {
        numbers++;
    }

    return numbers;
}
