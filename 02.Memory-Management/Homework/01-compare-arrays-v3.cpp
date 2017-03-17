/* Write a program that reads two integer arrays from the console and compares them
element by element. For better code reusability, you could do the comparison in a
bool compArr(int arr1[], int length1, int arr2[], int length2)
function, which returns true if they are equal and false if not */

#include<iostream>
#include<string>
#include<sstream>

bool compArr(const int* arr1, const int& length1, int* arr2, const int& length2);
int* readArrayOfInt(int&);
int countIntegerNumbersInString(const std::string&);
void printArray(const int[], const int&);

int main()
{
    int array_one_size = 0;
    int array_two_size = 0;
    int* pArrOne = readArrayOfInt(array_one_size);
    int* pArrTwo = readArrayOfInt(array_two_size);

    bool are_arrays_equal = compArr(pArrOne, array_one_size, pArrTwo, array_two_size);

    std::cout << std::endl << "Elements in both arrays are "
        << (are_arrays_equal ? "" : "NOT ") << "equal." << std::endl << std::endl;

    printArray(pArrOne, array_one_size);
    printArray(pArrTwo, array_two_size);

    delete [] pArrOne;
    delete [] pArrTwo;

    return 0;
}

bool compArr(const int* arr1, const int& length1, int* arr2, const int& length2)
{
    bool comp_result = (length1 == length2);
    int counter = 0;

    while (comp_result && counter < length1)
    {
        comp_result = (arr1[counter] == arr2[counter]);
        counter++;
    }

    return comp_result;
}

int* readArrayOfInt(int& array_size)
{
    static int counter = 1;

    std::cout << "Enter integer number(s) for array " << counter++ << ": ";

    std::string input_string;

    getline(std::cin, input_string);

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
