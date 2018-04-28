#include <iostream>
#include <sstream>
#include <unordered_map>

#pragma GCC optimize ("O3")

int main()
{
    std::ostream::sync_with_stdio(false);
    std::istream::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::unordered_map<std::string, std::unordered_map<std::string, int> > data;
    std::unordered_map<int, std::string> mapper;

    std::istringstream input_stream;
    std::string line, word;

    std::getline(std::cin >> std::ws, line);
    input_stream.str(line);
    int index = 0;
    while (input_stream && (input_stream >> word))
    {
        mapper[index++] = word;
        data[word];
    }

    std::getline(std::cin >> std::ws, line);
    while (line != "end")
    {
        input_stream.clear();
        input_stream.str(line);

        index = 0;

        while (input_stream && (input_stream >> word))
        {
            data[mapper[index++]][word]++;
        }

        std::getline(std::cin >> std::ws, line);
    }

    std::cin >> std::ws >> word;

    int most = -1;
    std::string best;
    for (auto entry : data[word])
    {
        if (entry.second > most)
        {
            most = entry.second;
            best = entry.first;
        }
    }

    std::cout << best << " " << most << std::endl;

    return 0;
}
