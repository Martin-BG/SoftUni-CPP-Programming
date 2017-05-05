#include<iostream>

#pragma GCC optimize ("O3")

const int DNA_STR_LENGTH = 6;
const int BUFFER_SIZE = 10000 * (DNA_STR_LENGTH - 1);

int main()
{
    static char res[DNA_STR_LENGTH];
    static char buffer[BUFFER_SIZE];
    int read_chars, index;

	// Tweaks for faster cin execution
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin.get(buffer, BUFFER_SIZE + 1, '.') && !std::cin.eof())
    {
        read_chars = std::cin.gcount();
        index = 0;

        while (read_chars > index)
        {
            res[0] ^= buffer[index++];
            res[1] ^= buffer[index++];
            res[2] ^= buffer[index++];
            res[3] ^= buffer[index++];
            res[4] ^= buffer[index++];
        }
    }

    std::cout << res;

    return 0;
}
