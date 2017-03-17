/* Write a function
int occurrences(const string& text, const string& search)
which returns the number of times search is contained in text.

Example call:

string text = "Write a function int occurrences(const string& text, const
    string& search) which returns the number of times search is contained in text"

string search = "on";

occurrences(text, search);

Expected result: 4

Make a program which reads two lines of text from the console - first the
text, then the search string and prints the number of times search is
contained in text */

#include<iostream>
#include<string>

using namespace std;

int occurences(const string&, const string&);

int main()
{
    string text, search_text;

    cout << "Enter some text: ";
    getline(cin, text);

    cout << endl << "Enter string to search: ";
    getline(cin, search_text);

    cout << endl << "String found " << occurences(text, search_text)
        << " time(s)." << endl;

    return 0;
}

int occurences(const string& text, const string& search_text)
{
    int text_occurences = 0;
    int search_text_size = search_text.size();

    size_t found_index = text.find(search_text);

    while (found_index != string::npos)
    {
        text_occurences++;
        found_index = text.find(search_text, found_index + search_text_size);
    }

    return text_occurences;
}
