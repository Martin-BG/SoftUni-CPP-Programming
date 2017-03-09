/* Write a function
int * parseNumbers(const string& str, int& resultLength) which
returns a pointer to new-allocated array with the numbers parsed from str
(assume you don’t need to handle wrongly-formatted input). str will contain
integer numbers separated by spaces. The function writes the length of the
allocated array in resultLength. Write a program which lets the user enter a
number of lines of integers from the console, and prints their sum. Use the
parseNumbers function in your program, but make sure you delete each array
once you’re done with it.

Example input (note: first line is the count of lines of numbers, in this case: 2 lines):
2
1 2 3
4 5
Expected output (sum of 1 2 3 and 4 5): 15 */

#include<iostream>
#include<string>
#include<sstream>

using namespace std;

int * parseNumbers(const string&, int&);
int countNumbersInString(const string&);
string getALineOfNumbers();

int main()
{
    int lines;

    cout << "Enter line(s) to read: ";
    cin >> lines;

    int sum_of_all_array_elements = 0;
    int numbers_in_string;
    string line_of_nums;
    int * pArr;

    for (int i = 0; i < lines; i++)
    {
        line_of_nums = getALineOfNumbers();

        pArr = parseNumbers(line_of_nums, numbers_in_string);

        for (int i = 0; i < numbers_in_string; i++)
        {
            sum_of_all_array_elements += pArr[i];
        }

        delete[] pArr; // Release array memory
    }

    cout << endl << "The sum of all array elements is: "
        << sum_of_all_array_elements << endl;

    return 0;
}

int * parseNumbers(const string& str, int& result_length)
{
        result_length = countNumbersInString(str);

        int * pArr = new int[result_length];

        istringstream input_stream(str);

        int number;

        for (int i = 0; i < result_length; i++)
        {
            input_stream >> number;
            pArr[i] = number;
        }

        return pArr;
}

string getALineOfNumbers()
{
    static int lines = 1;
    cout << "Enter integer numbers (line " << lines++ << "): ";

    string input_line;

    while (input_line.size() == 0)
    {
        getline(cin, input_line);
    }

    return input_line;
}

int countNumbersInString(const string& str)
{
    int numbers = 0;
    int number;
    istringstream input_stream(str);

    while (input_stream && (input_stream >> number))
    {
        numbers++;
    }

    return numbers;
}
