/* Implement a LineParser class, which takes in a string and has methods to parse
 the string into an array of numbers, an array of strings (by getting the words
 separated by spaces) and an array of chars (by getting only non-whitespace chars).
 The return type of the methods can either be pointers to arrays (along with a
 int& parameter to get the length of the returned array - remember the parseNumbers
 function from one of the previous exercises?), or the SmartArray class we
 implemented, or the std::vector class.
 Test your class by calling it from main() (or another function) with at least 10
 examples of input data (including empty strings, strings which would yield 1-element
 arrays, bigger strings, etc.). You don't need to handle incorrect input - assume
 that if getNumbers() is called, the entire string can be parsed into an array of
 numbers (i.e. there won't be words mixed with the numbers).
*/

#include<iostream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class LineParser
{
private:
    string line;

public:
    LineParser(const string& line): line(line) {}

    vector<int> getNumbers() const
    {
        vector<int> nums {};

        int number;

        istringstream string_stream(this->line);

        while (string_stream >> number)
        {
            nums.push_back(number);
        }

        return nums;
    }

    vector<string> getStrings() const
    {
        vector<string> words {};

        string word;

        istringstream string_stream(this->line);

        while (string_stream >> word)
        {
            words.push_back(word);
        }

        return words;
    }

    vector<char> getChars() const
    {
        vector<char> chars {};

        char character;

        istringstream string_stream(this->line);

        while (string_stream >> character)
        {
            if (!isspace(character))
            {
                chars.push_back(character);
            }
        }

        return chars;
    }

    void changeLine(const string& line)
    {
        this->line = line;
    }

    template <typename T>
    string getInfo(const vector<T> data) const
    {
        ostringstream info;
        for (int i = 0; i < data.size(); i++)
        {
            info << data[i] << " ";
        }
        info << endl;

        return info.str();
    }

    string getInfoForAllTypes() const
    {
        ostringstream info;
        info << getInfo(getNumbers())
            << getInfo(getStrings())
            << getInfo(getChars());
        return info.str();
    }
};

int main()
{
    LineParser line_parser = LineParser("1 2 3");
    vector<int> nums = line_parser.getNumbers();
    cout << line_parser.getInfo(nums);

    line_parser.changeLine("  Hello       World!  ");
    vector<string> words = line_parser.getStrings();
    cout << line_parser.getInfo(words);

    vector<char> chars = line_parser.getChars();
    cout << line_parser.getInfo(chars);

    line_parser.changeLine("9");
    cout << line_parser.getInfo(line_parser.getNumbers());
    cout << line_parser.getInfo(line_parser.getStrings());
    cout << line_parser.getInfo(line_parser.getChars());

    line_parser.changeLine("");
    cout << line_parser.getInfoForAllTypes();

    line_parser.changeLine("6876 786876 6123 667 66 -12312 \
        -123213444      6876 666    131 1111 1116876868    7");
    cout << line_parser.getInfoForAllTypes();

    line_parser.changeLine("Lorem ipsum dolor sit amet, consectetur \
       adipiscing elit, sed do eiusmod tempor incididunt ut \
       labore et dolore magna aliqua. Ut enim ad minim veniam, \
       quis nostrud exercitation ullamco laboris nisi ut aliquip \
       ex ea commodo consequat. Duis aute irure dolor in reprehenderit \
       in voluptate velit esse cillum dolore eu fugiat nulla pariatur. \
       Excepteur sint occaecat cupidatat non proident, sunt in culpa \
       qui officia deserunt mollit anim id est laborum.");
    cout << line_parser.getInfoForAllTypes();

    return 0;
}
