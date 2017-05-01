#include <iostream>
#include <sstream>
#include <map>
#include <set>

int main() {
    std::map<std::string, int> wordCounts;
    std::set<std::string> uniqueWords;

    std::string text;
    getline(std::cin, text);

    std::istringstream wordsStream(text);
    std::string word;
    while (wordsStream >> word) {
        wordCounts[word]++;
        uniqueWords.insert(word);
    }

    std::cout << "Unique words:" << std::endl;
    for (std::set<std::string>::iterator i = uniqueWords.begin(); i != uniqueWords.end(); i++) {
        std::cout << *i << std::endl;
    }

    std::cout << "Enter a word to display the count:" << std::endl;

    std::string query;
    while(std::cin >> query) {
        std::map<std::string, int>::iterator wordCount = wordCounts.find(query);
        if (wordCount != wordCounts.end()) {
            std::cout << wordCount->first << ": " << wordCount->second << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }

    return 0;
}
