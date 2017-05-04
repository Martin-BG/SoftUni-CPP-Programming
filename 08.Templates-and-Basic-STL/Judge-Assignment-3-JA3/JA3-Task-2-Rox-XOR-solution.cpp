#include<iostream>
#include<iomanip>

const int DNA_STR_LENGTH = 6;

int main()
{
    int res = 0;
    char next[DNA_STR_LENGTH] = {};

	// Tweaks for faster cin execution
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
	
    while (std::cin.get(next, DNA_STR_LENGTH, '.') && !std::cin.eof())
    {
        res ^= std::stoi(next, nullptr, 16);
    }

    std::cout << std::setw(DNA_STR_LENGTH - 1) << std::setfill('0') << std::hex << res;

    return 0;
}
