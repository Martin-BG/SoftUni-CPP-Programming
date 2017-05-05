/* https://lastminutealgo.blogspot.bg/2017/04/find-two-non-repeating-elements-in.html
Given:
  array of size 2n+2 where n element are repeated twice.
Return:
  2 non repeating element.
Algo:
  1. XOR all elements.
  2. Result of 1 will contains bits which are present in either one of the repeating element but not both.
  3. Choose any set bit in above result.
  4. Divide integers in 2 groups such that first group will have all integers where bit is set and second group where it is not set.
  5. Two elements will be in different groups and all element which are repeated will be in same group.
  6. XOR each group and you will get 2 elements.*/

#include<iostream>
#include<iomanip>

#pragma GCC optimize ("O3")

const int DNA_STR_LENGTH = 6;
const int DNA_BITS_COUNT = (DNA_STR_LENGTH - 1) * 8;

int main()
{
    int res = 0;
    int xor_arr_one[DNA_BITS_COUNT] = {};
    int xor_arr_two[DNA_BITS_COUNT] = {};
    int num, mask, index;
    char next[DNA_STR_LENGTH] = {};

    // Tweaks for faster cin execution
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin.get(next, DNA_STR_LENGTH, '.') && !std::cin.eof())
    {
        num = std::stoi(next, nullptr, 16);
        res ^= num;

        mask = 1;
        for (index = DNA_BITS_COUNT - 1; index > 0; index--)
        {
            if (num & mask)
            {
                xor_arr_one[index] ^= num;
            }
            else
            {
                xor_arr_two[index] ^= num;
            }

            mask <<= 1;
        }
    }

    mask = res&(~(res - 1));
    index = DNA_BITS_COUNT;
    while (mask > 0)
    {
        index--;
        mask >>= 1;
    }

    std::cout << std::setw(DNA_STR_LENGTH - 1) << std::setfill('0') << std::hex;

    if (xor_arr_one[index] != 0)
    {
        std::cout << xor_arr_one[index] << std::endl;
    }

    if (xor_arr_two[index] != 0)
    {
        std::cout << xor_arr_two[index] << std::endl;
    }

    return 0;
}
