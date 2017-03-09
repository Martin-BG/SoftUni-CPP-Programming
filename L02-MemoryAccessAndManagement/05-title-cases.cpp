/* Write a function void makeTitleCase(string& text)
which changes each word in text to start with a capital letter
(don’t bother with the exact title-case rules about not capitalizing
things like in, from, etc.). Assume the first letter of a word is an
English alphabetical symbol preceded by a non-alphabetical
symbol (so in “we will--rock you”, “we”, “will”, “rock”
and “you” are all considered words which need to be
capitalized). Call the function from main() with a line of text read
from the console and then print the modified line of text.

Example input: On the south Carpathian mountains,a tree is swinging
Expected output: On The South Carpathian Mountains,A Tree Is Swinging */

#include<iostream>
#include<string>
#include<cctype>

using namespace std;

void makeTitleCase(string&);

int main()
{
    string sentence;

    cout << "Enter a sentence: ";
    getline(cin, sentence);

    makeTitleCase(sentence);

    cout << "Titled sentence : " << sentence << endl;

    return 0;
}

void makeTitleCase(string& text)
{
    char upper_case;
    bool make_letter_capital = true;

    for (int i = 0; i < text.size(); i++)
    {
        if (isalpha(text[i]))
        {
            if (make_letter_capital)
            {
                upper_case = toupper(text[i]);
                text[i] = upper_case;
                make_letter_capital = false;
            }
        }
        else
        {
            make_letter_capital = true;
        }
    }
}
