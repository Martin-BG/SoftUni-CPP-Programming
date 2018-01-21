#include <iostream>
#include <queue>
#include <sstream>
#include <map>

#pragma GCC optimize ("O3")

int main()
{
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    typedef std::pair<int, std::string> decoded;

    auto decoded_comparator = [](const decoded &lhs, const decoded &rhs)
    {
        return lhs.first <= rhs.first;
    };

    std::map<std::string, std::string> for_decoding;
    std::priority_queue<decoded, std::vector<decoded>, decltype(decoded_comparator)> messages(decoded_comparator);
    std::string line, from, message, current;

    std::getline(std::cin >> std::ws, line);
    while (line != "end")
    {
        if (line == "report")
        {
            if (!messages.empty())
            {
                std::cout << messages.top().second << std::endl;
                messages.pop();
            }
            else
            {
                std::cout << "[no new messages]" << std::endl;
            }
        }
        else
        {
            std::stringstream ss(line);

            if (ss && (ss >> std::ws >> from >> std::ws >> message))
            {
                if (for_decoding.find(from) == for_decoding.end())
                {
                    for_decoding[from] = message;
                }

                if (for_decoding[from].length() == message.length())
                {
                    bool completed = true;
                    current = for_decoding[from];
                    for (int i = 0; i < current.length(); i++)
                    {
                        if (current[i] == '?')
                        {
                            if (message[i] != '?')
                            {
                                current[i] = message[i];
                            }
                            else
                            {
                                completed = false;
                            }
                        }
                    }

                    if (completed)
                    {
                        std::size_t prio_start = current.find_first_of("0123456789");
                        std::size_t prio_end = current.find_last_of("0123456789");

                        if (prio_start != std::string::npos && prio_end != std::string::npos)
                        {
                            int priority = std::stoi(current.substr(prio_start, prio_end + 1));
                            current.erase(prio_start, prio_end - prio_start + 1);
                            messages.push(decoded(priority, current));
                        }
                    }

                    for_decoding[from] = current;
                }
            }
        }

        std::getline(std::cin >> std::ws, line);
    }

    return 0;
}
