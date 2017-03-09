/* Write a program which checks if the lines of two text files are the same
(same number of lines and each line from the first file should be equal
to the line of the second file). */

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

int main()
{
    string file_name_one, file_name_two;

    cout << "Enter first file name : ";
    cin >> file_name_one;

    cout << "Enter second file name: ";
    cin >> file_name_two;

    ifstream file_one_input(file_name_one.c_str());
    string file_one_line;

    ifstream file_two_input(file_name_two.c_str());
    string file_two_line;

    bool are_files_identical = true;
    while (are_files_identical)
    {
        // Read next line and check if both reads are successful
        if(getline(file_one_input, file_one_line).eof()
           != getline(file_two_input, file_two_line).eof())
        {
            are_files_identical = false;
            break;
        }

        // Check if any of the files has reached the end
        // Note: eof() is true only after a failed next line read
        if (file_one_input.eof() || file_two_input.eof())
        {
            break;
        }

        // Compare both lines
        if (file_one_line.compare(file_two_line) != 0)
        {
            are_files_identical = false;
            break;
        }
    }

    cout << endl << "Text in both files is "
        << (are_files_identical ? "" : "NOT ") << "the same." << endl;

    return 0;
}
