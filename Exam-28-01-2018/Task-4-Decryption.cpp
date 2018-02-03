#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

#pragma GCC optimize ("O3")

std::string changeLetters(std::string s, std::unordered_map<char, char> letterChangeMap);

int main()
{
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::unordered_map<std::string, std::vector<std::string> > encrypted; // first word, vector of messages starting with it
    std::unordered_map<std::string, std::unordered_map<char, char> > tables; // encrypted match_word, encryption table

    std::ostringstream output;
    std::istringstream input_stream;
    std::string line, word, match_word;

    std::getline(std::cin >> std::ws, match_word);

    std::getline(std::cin >> std::ws, line);
    while (line != "[encryptions]")
    {
        input_stream.clear();

        encrypted[line.substr(0, match_word.length())].push_back(line);

        std::getline(std::cin >> std::ws, line);
    }

    std::getline(std::cin >> std::ws, line);
    while (line != "[end]")
    {
        std::unordered_map<char, char> encryptionMap;

        for (int i = 0; i < line.size(); i++)
        {
            char encryptedChar = line[i];
            auto actualChar = char(int('a') + i);
            encryptionMap[actualChar] = encryptedChar;
        }

        word = changeLetters(match_word, encryptionMap);

        tables[word] = encryptionMap;

        std::getline(std::cin >> std::ws, line);
    }

    int max = -1;
    word = "";
    for (auto table : tables)
    {
        int curr = encrypted[table.first].size();
        if (curr > max)
        {
            max = curr;
            word = table.first;
        }
    }

    std::unordered_map<char, char> encryptionMap;
    for (auto encr : tables[word])
    {
        encryptionMap[encr.second] = encr.first;
    }

    for (const auto &message : encrypted[word])
    {
        output << changeLetters(message, encryptionMap) << std::endl;
    }

    std::cout << output.str();

    return 0;
}

std::string changeLetters(std::string s, std::unordered_map<char, char> letterChangeMap)
{
    std::string changed(s.size(), ' ');
    for (size_t i = 0; i < s.size(); i++)
    {
        char originalChar = s[i];
        if (isalpha(originalChar))
        {
            /// NOTE: we know that every char will have a matching char
            changed[i] = letterChangeMap[originalChar];
        }
        else
        {
            changed[i] = originalChar;
        }
    }

    return changed;
}
