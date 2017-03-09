/* Write a program which does the same as task 8, but instead of printing
to the console, asks the user for the name of an input file and an output
file (each entered on a separate line) and reads the input from the
input file and prints the output in the output file. If the output file
already exists, it should be overwritten. Note: the input and output file
could be the same. Note2: just copy-paste the code from 8 to reuse it */

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

int * parseNumbers(const string&, int&);
int countNumbersInString(const string&);

int main()
{
    string input_file_name, output_file_name;

    cout << "Enter input file name : ";
    cin >> input_file_name;

    cout << "Enter output file name: ";
    cin >> output_file_name;

    ifstream file_input(input_file_name.c_str());
    ostringstream string_stream;
    int number;

    while (file_input >> number)
    {
        string_stream << number << " ";
    }

    string line_of_nums = string_stream.str();

    file_input.close();

    int sum_of_all_array_elements = 0;
    int numbers_in_string;

    int * pArr = parseNumbers(line_of_nums, numbers_in_string);

    for (int i = 0; i < numbers_in_string; i++)
    {
        sum_of_all_array_elements += pArr[i];
    }

    delete[] pArr; // Release array memory

    ofstream fileOutput(output_file_name.c_str());
    fileOutput << sum_of_all_array_elements << endl;
    fileOutput.close();

    cout << endl << "Sum (" << sum_of_all_array_elements
        << ") of numbers from <" << input_file_name
        << "> stored to <" << output_file_name << ">." << endl;

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
