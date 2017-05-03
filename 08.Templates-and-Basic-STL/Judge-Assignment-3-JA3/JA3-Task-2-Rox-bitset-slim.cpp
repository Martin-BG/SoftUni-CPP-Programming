#include<iostream>
#include<iomanip>
#include<bitset>

const int MAX_DNA_TYPES = 0xFFFFF;
const int DNA_STR_LENGTH = 6;

int main()
{
    std::bitset<MAX_DNA_TYPES> uniqueDNA;

    char next[DNA_STR_LENGTH] = {};

    while (std::cin.get(next, DNA_STR_LENGTH, '.') && !std::cin.eof())
    {
        uniqueDNA.flip(std::stoi(next, nullptr, 16) - 1);
    }

    for (int i = MAX_DNA_TYPES - 1; i >= 0; i--)
    {
        if (uniqueDNA.test(i))
        {
            std::cout << std::setw(DNA_STR_LENGTH - 1) << std::setfill('0') << std::hex << i + 1;
            break;
        }
    }

    return 0;
}
