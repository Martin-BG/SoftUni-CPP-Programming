#include <iostream>
#include <sstream>
#include <unordered_map>
#include <queue>

#pragma GCC optimize ("O3")

int main()
{
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::unordered_map<std::string, std::unordered_map<std::string, std::string> > data;
    std::string main_key, main_value, line, key, value;

    std::cin >> main_key;

    std::getline(std::cin >> std::ws, line);
    while (line != "[queries]")
    {
        std::queue<std::string> elements;
        bool main_key_found = false;

        std::stringstream ss(line);

        while (ss && (ss >> std::ws >> key >> std::ws >> value))
        {
            if (key == main_key)
            {
                main_value = value;
                main_key_found = true;
            }
            else
            {
                elements.push(key);
                elements.push(value);
            }
        }

        if (main_key_found)
        {
            while (!elements.empty())
            {
                key = elements.front();
                elements.pop();
                value = elements.front();
                elements.pop();

                if (data[main_value].find(key) == data[main_value].end())
                {
                    data[main_value][key] = value;
                }
                else
                {
                    data[main_value][key] += " " + value;
                }
            }
        }

        std::getline(std::cin >> std::ws, line);
    }

    std::getline(std::cin >> std::ws, line);
    while (line != "end")
    {
        std::stringstream ss(line);
        ss >> std::ws >> key >> std::ws >> value;

        if (data.find(key) == data.end())
        {
            std::cout << "[not found]";
        }
        else if (data[key].find(value) != data[key].end())
        {
            std::cout << data[key][value];
        }

        std::cout << std::endl;
        std::getline(std::cin >> std::ws, line);
    }

    return 0;
}
