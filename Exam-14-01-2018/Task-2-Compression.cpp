#include <iostream>

#pragma GCC optimize ("O3")

int main()
{
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::cin >> input;

    char current_char = input[0];
    int count_char = 0;

    for (char ch : input)
    {
        if (current_char != ch)
        {
            if (count_char > 2)
            {
                std::cout << count_char << current_char;
            }
            else
            {
                for (int i = 0; i < count_char; ++i)
                {
                    std::cout << current_char;
                }
            }
            current_char = ch;
            count_char = 1;
        }
        else
        {
            count_char++;
        }
    }

    if (count_char > 2)
    {
        std::cout << count_char << current_char;
    }
    else
    {
        for (int i = 0; i < count_char; ++i)
        {
            std::cout << current_char;
        }
    }

    return 0;
}
