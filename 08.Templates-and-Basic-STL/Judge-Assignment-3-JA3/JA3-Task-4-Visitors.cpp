#include<iostream>
#include<map>
#include<set>
#include<string>
#include<sstream>

int main()
{
    std::map<std::string, int> unique_names; // Name, count
    std::map<int, int> unique_ages; // age, count
    std::set<std::string> unique_user_ids; // ID

    std::map<int, int>::iterator ages_iter;

    std::string line, command, id, name;
    int age, age2, result;

    while (std::getline(std::cin, line))
    {
        if (line == "end")
        {
            break;
        }

        std::stringstream ss(line);

        ss >> command;

        if (command == "entry")
        {
            ss >> id;
            if (unique_user_ids.find(id) == unique_user_ids.end())
            {
                unique_user_ids.insert(id);

                ss >> name;
                unique_names[name]++;

                ss >> age;
                unique_ages[age]++;
            }
        }
        else if (command == "age")
        {
            result = 0;
            ss >> age >> age2;

            for (ages_iter = unique_ages.begin(); ages_iter != unique_ages.end(); ages_iter++)
            {
                if (ages_iter->first >= age && ages_iter->first < age2)
                {
                    result += ages_iter->second;
                }
            }

            std::cout << result << std::endl;
        }
        else if (command == "name")
        {
            result = 0;
            ss >> name;

            if (unique_names.find(name) != unique_names.end())
            {
                result = unique_names[name];
            }

            std::cout << result << std::endl;
        }
    }

    return 0;
}
