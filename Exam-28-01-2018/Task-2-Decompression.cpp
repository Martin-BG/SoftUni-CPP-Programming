#include <iostream>
#include <sstream>

#pragma GCC optimize ("O3")

int main()
{
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ostringstream output;
    std::ostringstream digits;

    std::string input;
    std::cin >> input;

    bool decompress = false;
    for (char ch : input)
    {
        if (std::isdigit(ch))
        {
            digits << ch;
            decompress = true;
        }
        else
        {
            if (decompress)
            {
                int chars = std::stoi(digits.str());
                digits.str("");
                digits.clear();
                for (int i = 0; i < chars; i++)
                {
                    output << ch;
                }
                decompress = false;
            }
            else
            {
                output << ch;
            }
        }
    }

    std::cout << output.str() << std::endl;

    return 0;
}
