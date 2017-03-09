/* Write a program which is given a line of text, another line with a
find string and another line with a replace string. Any part of
text which matches the find string should be replaced with the
replace string. Print the resulting text on the console.

Hint: things like string.find(), string.insert(),
string.replace() might be useful

Example input:
I am the night. Dark Night! No, not the knight
night
day

Example output: I am the day. Dark Night! No, not the kday */

#include<iostream>
#include<string>

using namespace std;

int main()
{
    string text, find_str, replacement_str;

    cout << "Enter some text: ";
    getline(cin, text);

    cout << endl << "Enter string to find: ";
    getline(cin, find_str);

    cout << endl << "Enter replacement string: ";
    getline(cin, replacement_str);

    if (find_str == replacement_str)
    {
        cout << endl << "Invalid input!" << endl;
        return 1;
    }

    int find_str_size = find_str.size();
    size_t found_index = text.find(find_str);

    while (found_index != string::npos)
    {
        text.replace(found_index, find_str_size, replacement_str);
        found_index = text.find(find_str);
    }

    cout << endl << "Result: " << text << endl;

    return 0;
}
