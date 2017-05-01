#include <iostream>
#include <sstream>
#include <map>
#include <set>

int main() {
    std::map<std::string, int> menInBlackAges;
    menInBlackAges["Kay"] = 45;
    menInBlackAges["Zed"] = 55;
    menInBlackAges["Jay"] = 25;

    std::cout << menInBlackAges["Kay"] << std::endl;
    std::cout << menInBlackAges["Jay"] << std::endl;
    // NOTE: there is no "Ay" right now, but accessing it with operator[] will insert a default value and return a reference to it:
    std::cout << menInBlackAges["Ay"] << std::endl;

    std::cout << "Here come the men in black: " << std::endl;
    for (std::map<std::string, int>::iterator i = menInBlackAges.begin(); i != menInBlackAges.end(); i++) {
        std::cout << i->first << ": " << i->second << std::endl;
    }

    std::cout << "---------------------------" << std::endl;

    std::set<std::string> uniqueWords;
    std::istringstream wordsStream("she sells sea shells on the seashore, the shells she sells are very shiny.");
    std::string word;
    while (wordsStream >> word) {
        uniqueWords.insert(word);
    }

    std::cout << "Unique words: " << std::endl;
    for (auto i = uniqueWords.begin(); i != uniqueWords.end(); i++) {
        std::cout << *i << std::endl;
    }

    return 0;
}
