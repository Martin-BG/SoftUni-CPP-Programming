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

const int DNA_STR_LENGTH = 5;
const int BITS_PER_CHAR = 8;
const int DNA_BITS_COUNT = DNA_STR_LENGTH * BITS_PER_CHAR;
const int BUFFER_SIZE = DNA_STR_LENGTH * 10000;

int main()
{
    static char buffer[BUFFER_SIZE];
    static char res[DNA_STR_LENGTH + 1];
    static char xor_arr_one[DNA_BITS_COUNT * DNA_STR_LENGTH];
    static char xor_arr_two[DNA_BITS_COUNT * DNA_STR_LENGTH];
    int mask, index, index_2, index_3, read_chars;

    // Tweaks for faster cin execution
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin.get(buffer, BUFFER_SIZE + 1, '.') && !std::cin.eof())
    {
        read_chars = std::cin.gcount();

        for (index = 0; index < read_chars; index += DNA_STR_LENGTH)
        {
            for (index_2 = 0; index_2 < DNA_STR_LENGTH; index_2++)
            {
                res[index_2] ^= buffer[index + index_2];
            }

            for (index_2 = 0; index_2 < DNA_BITS_COUNT; index_2++)
            {
                mask = 1<<(index_2 % BITS_PER_CHAR);

                if (buffer[index + index_2 / BITS_PER_CHAR] & mask)
                {
                    for (index_3 = 0; index_3 < DNA_STR_LENGTH; index_3++)
                    {
                        xor_arr_one[index_2 * DNA_STR_LENGTH + index_3] ^= buffer[index + index_3];
                    }
                }
                else
                {
                    for (index_3 = 0; index_3 < DNA_STR_LENGTH; index_3++)
                    {
                        xor_arr_two[index_2 * DNA_STR_LENGTH + index_3] ^= buffer[index + index_3];
                    }
                }
            }
        }
    }

    index = 0;
    mask = 0;
    do
    {
        mask = res[index]&(~(res[index] - 1));
        index++;
    } while (mask == 0 && index < DNA_STR_LENGTH);

    if (mask == 0)
    {
        return 0;
    }

    index = (index -1) * BITS_PER_CHAR;
    while (mask > 0)
    {
        index++;
        mask >>= 1;
    }

    index *= DNA_STR_LENGTH;

    bool show = false;
    for (index_2 = 0; index_2 < DNA_STR_LENGTH; index_2++)
    {
        res[index_2] = xor_arr_one[index + index_2];

        if (res[index_2] != 0)
        {
            show = true;
        }
    }

    if (show)
    {
        for (index_2 = 0; index_2 < DNA_STR_LENGTH; index_2++)
        {
            std::cout << res[index_2];
        }

        std::cout << std::endl;
    }

    show = false;
    for (index_2 = 0; index_2 < DNA_STR_LENGTH; index_2++)
    {
        res[index_2] = xor_arr_two[index + index_2];

        if (res[index_2] != 0)
        {
            show = true;
        }
    }

    if (show)
    {
        for (index_2 = 0; index_2 < DNA_STR_LENGTH; index_2++)
        {
            std::cout << res[index_2];
        }

        std::cout << std::endl;
    }

    return 0;
}
