#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    string search_word;

    cin >> search_word;

    int pages;

    cin >> pages;

    vector<string> my_messages;
    vector<int> hits;
    int entries = 0;

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
            my_messages.push_back(text);
            hits.push_back(hit);
            entries++;
        }

        getline(cin >> ws, text);
    }

    while (entries > 0 && pages > 0)
    {
        int highest = 0;
        int index = -1;
        for (int i = 0; i < hits.size(); i++)
        {
            if (hits[i] > highest)
            {
                index = i;
                highest = hits[i];
            }
        }

        if (index >= 0)
        {
            cout << my_messages[index] << endl;
            hits[index] = 0;
            entries--;
            pages--;
        }
        else
        {
            break;
        }
    }

    return 0;
}
