// https://judge.softuni.bg/Contests/Compete/Index/502#1

#include<iostream>
#include<sstream>
#include<string>

using namespace std;

int main()
{
    string text;
    getline(cin, text);

    string control_word;
    cin >> control_word;

    double percentage;
    cin >> percentage;

    ostringstream out_streem;
    for (int i = 0; i< text.length(); i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            out_streem << text[i];
        }
        else
        {
            out_streem << " ";
        }
    }

    int similar_words = 0;
    int control_word_size = control_word.size();

    istringstream input_stream(out_streem.str());
    string input_word;

    while (input_stream >> input_word)
    {
        if(input_word.size() == control_word_size
           && input_word[0] == control_word[0] )
        {
            int matches = 1;
            for (int i = 1; i < control_word_size; i++)
            {
                if (input_word[i] == control_word[i])
                {
                    matches++;
                }
            }

            if (matches * 100.0 / control_word_size >= percentage)
            {
                similar_words++;
            }
        }

    }

    cout << similar_words;

    return 0;
}
