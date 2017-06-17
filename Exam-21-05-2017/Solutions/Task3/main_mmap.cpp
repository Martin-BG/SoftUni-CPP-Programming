#include <iostream>
#include <string>
#include <map>
#include <sstream>

#pragma GCC optimize ("O3")

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	
    string search_word;

    cin >> search_word;

    int pages;

    cin >> pages;

    multimap<int, string> mails;

    string text;
    getline(cin >> ws, text);

    while (text != ".")
    {
        int hit = 0;

        istringstream wordsStream(text);
        string word;

        while (wordsStream >> word)
        {
            if (word == search_word)
            {
                hit++;
            }
        }

        if (hit > 0)
        {
            mails.insert(make_pair(hit,text));
        }

        getline(cin >> ws, text);
    }


    for (multimap<int,string>::reverse_iterator it=mails.rbegin(); it!=mails.rend() && pages > 0; ++it)
    {
        cout << (*it).second << endl;
        pages--;
    }

    return 0;
}
