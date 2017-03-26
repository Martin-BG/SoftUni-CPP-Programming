/* Write a StringFormatter class, which takes a reference to an output
string as a parameter, as well as a string formatPrefix parameter. The
class should have a void format(string insertArr[], int insertArrSize)
and a void format(int insertArr[], int insertArrSize) method, which
replaces the concatenation of formatPrefix and i with the value of
insertArr[i] (where 0 < i < insertArrSize). NOTE: you can also use
SmartArray or std::vector as a single parameter for the format() method.
Simply said, you have to make a class which takes a string and "formats"
it by replacing the formattable substrings with the values of the passed
in array. The format methods should verify that the insertArr is not
bigger than the number of formatPrefixes in the text and cause an error
if it is. Test your class by calling it from main() (or another function)
with at least 10 examples of input data (including arrays larger than 9
elements, empty arrays, etc.)

//example call
string s = "Dear *:0, Our company *:1 wants to make you a Donation Of *:2 \
    Million *:3 in good faith. Please send us a picture of your credit card"
StringFormatter formatter(s, "*:");
formatter.format(new string[]{"Ben Dover", "Totally Legit NonSpam Ltd", "13", "Leva"}, 4);
cout << s; //should print "Dear Ben Dover, Our company Totally Legit NonSpam
    Ltd wants to make you a Donation Of 13 Million Leva in good faith.
    Please send us a picture of your credit card"
*/

#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

class StringFormatter
{
private:
    string& stringToFormat;
    string formatPrefix;
    bool enableMultipleUseOfReplaceString;

    int countPrefixesInString() const
    {
        int prefixes_found = 0;
        int prefix_size = this->formatPrefix.size();

        if (prefix_size > 0)
        {
            size_t found_index = this->stringToFormat.find(this->formatPrefix);
            while (found_index != string::npos)
            {
                prefixes_found++;
                found_index = this->stringToFormat.find(this->formatPrefix, found_index + prefix_size);
            }
        }

        return prefixes_found;
    }

    size_t findNextInsertPosition(int& insert_array_index, int& chars_to_replace)
    {
        insert_array_index = -1; // Used as a flag

        size_t found_index = this->stringToFormat.find(this->formatPrefix);
        if (found_index != string::npos)
        {
            insert_array_index = stoi(this->stringToFormat.substr(found_index + this->formatPrefix.size()));
            chars_to_replace = this->formatPrefix.size() + to_string(insert_array_index).size();
        }

        return found_index;
    }

    void replacePrefixAndIndex(const int& string_index, const int& chars_to_replace, const int& number)
    {
        this->stringToFormat.replace(string_index, chars_to_replace, to_string(number));
    }

    void replacePrefixAndIndex(const int& string_index, const int& chars_to_replace, const string& str)
    {
        this->stringToFormat.replace(string_index, chars_to_replace, str);
    }

public:
    // Constructor
    StringFormatter(string& stringToFormat, const string& formatPrefix, bool enableMultipleUseOfReplaceString = false):
        stringToFormat(stringToFormat),
        formatPrefix(formatPrefix),
        enableMultipleUseOfReplaceString(enableMultipleUseOfReplaceString) {}

    // Destructor
    ~StringFormatter() {}

    // Copy constructor
    StringFormatter(const StringFormatter& other) :
        stringToFormat(other.stringToFormat),
        formatPrefix(other.formatPrefix),
        enableMultipleUseOfReplaceString(other.enableMultipleUseOfReplaceString) { }

    // Copy-assignment operator
    StringFormatter& operator= (const StringFormatter& other) {
        if (this != &other) {
            this->stringToFormat = other.stringToFormat;
            this->formatPrefix = other.formatPrefix;
            this->enableMultipleUseOfReplaceString = other.enableMultipleUseOfReplaceString;
        }

        return *this;
    }

    template <typename T>
    void format(const vector<T> insertArr)
    {
        int prefixes = countPrefixesInString();

        if (prefixes == 0)
        {
            return;
        }

        if (!enableMultipleUseOfReplaceString && prefixes != insertArr.size())
        {
            throw "prefixes and array elements do not match";
        }

        int insert_array_index, chars_to_replace;

        size_t string_index = findNextInsertPosition(insert_array_index, chars_to_replace);
        while (string_index != string::npos)
        {
            if (insert_array_index == -1 || insert_array_index >= insertArr.size())
            {
                throw "invalid array index in string";
            }

            replacePrefixAndIndex(string_index, chars_to_replace, insertArr[insert_array_index]);

            string_index = findNextInsertPosition(insert_array_index, chars_to_replace);
        }
    }
};

int main()
{
    string s = "Dear *:0, Our company *:1 wants to make you a Donation Of *:2 Million *:3 in good faith. Please send us a picture of your credit card";
    StringFormatter formatter(s, "*:");
    formatter.format(vector<string> {"Ben Dover", "Totally Legit NonSpam Ltd", "13", "Leva"});
    cout << s << endl << endl;

    s = "#0 #1 #0 #1 #0 #1 #1 #1 #0 #0";
    cout << "Using the same two replacement strings multiple times:\n" << s << endl;
    formatter = StringFormatter(s, "#", true);
    formatter.format(vector<string> {"Zero", "One"});
    cout << s << endl << endl;

    s = "Zero $0, One $1, Two $2, Three $3, Four $4, Five $5, Six $6, Seven $7, Eight $8, Nine $9, Ten $10, Eleven $11";
    cout << "12 replacements:\n" << s << endl;
    formatter = StringFormatter(s, "$");
    formatter.format(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    cout << s << endl << endl;

    s = "Zero $11, One $10, Two $9, Three $8, Four $7, Five $6, Six $5, Seven $4, Eight $3, Nine $2, Ten $1, Eleven $0";
    cout << "12 replacements (reversed indexes):\n" << s << endl;
    formatter = StringFormatter(s, "$");
    formatter.format(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    cout << s << endl << endl;

    s = "@0 Hello @0 (twice!)";
    cout << s << endl;
    formatter = StringFormatter(s, "@", true);
    formatter.format(vector<string> {"replaced with longer text"});
    cout << s << endl << endl;

    s = "String with no replacements, prefix and array defined";
    formatter = StringFormatter(s, "");
    formatter.format(vector<string> {""});
    cout << s << endl << endl;

    s = "String with no replacements and prefix, but with replacement array (3 elements)";
    formatter = StringFormatter(s, "");
    formatter.format(vector<int> {1, 2, 3});
    cout << s << endl << endl;

    s = "String with no replacements and replacement array, but with prefix set";
    formatter = StringFormatter(s, "hoho");
    formatter.format(vector<int> {});
    cout << s << endl << endl;

    s = "String with no replacements, but with prefix and replacement array defined";
    formatter = StringFormatter(s, "bobo");
    formatter.format(vector<string> {"use me"});
    cout << s << endl << endl;

    cout << "Follows a test with empty string, but with prefix and replacement array defined" << endl;
    s = "";
    formatter = StringFormatter(s, "replace");
    formatter.format(vector<string> {"Test", "completed", ".", "Everything", "seems", "to", "work"});
    cout << "[" << s << "]" << endl << endl;

    s = "Concatenated prefixes: con0con1con2con3";
    cout << s << endl;
    formatter = StringFormatter(s, "con");
    formatter.format(vector<string> {"[one]", "[two]", "[three]", "[four]"});
    cout << s << endl << endl;

    s = "replace0 replace1replace2 replace3 replace4 replace5 replace6";
    cout << s << endl;
    formatter = StringFormatter(s, "replace");
    formatter.format(vector<string> {"Test", "completed", ".", "Everything", "seems", "to", "work"});
    cout << s << endl << endl;

    return 0;
}
