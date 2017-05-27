#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;
int main()
{
    // Tweaks for faster cin execution
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::map<std::string, int> wordCounts;

    string word;
    cin >> ws >> word;
    while (word != ".")
    {
        if (wordCounts.find(word) == wordCounts.end())
        {
            wordCounts[word] = 0;
        }
        wordCounts[word]++;
        cin >> ws >> word;
    }

    std::multimap<int, std::string> wordsByCount;

    for (auto word : wordCounts)
    {
        wordsByCount.insert(std::pair<int, std::string>(word.second,word.first));
    }

    int queries;

    cin >> queries;

    for (int i = 0; i < queries; ++i)
    {
        int occurrenceCount, index;

        cin >> occurrenceCount >> index;

        std::multimap<int, std::string>::iterator wordCount = wordsByCount.find(occurrenceCount);

        int count = 0;
        bool found = false;
        while (wordCount != wordsByCount.end() && wordCount->first == occurrenceCount)
        {
            if (count == index)
            {
                cout << wordCount->second << endl;
                found = true;
                break;
            }
            count++;
            wordCount++;
        }

        if (!found)
        {
            cout << "." << endl;
        }
    }

    return 0;
}