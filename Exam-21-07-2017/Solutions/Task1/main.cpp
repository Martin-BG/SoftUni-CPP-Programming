#include<iostream>
#include<string>
#include<sstream>

#pragma GCC optimize ("O3")

const int MEASUREMENTS = 500;

int main()
{
	// Tweaks for faster cin execution
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
	
    int measure_one[MEASUREMENTS] = {};
    int result[MEASUREMENTS] = {};

    std::string input_string;

    getline(std::cin, input_string);

    std::istringstream input_stream(input_string);

    int number, step;
    int numbers = 0;

    while (input_stream >> number)
    {
        measure_one[numbers] = number;
        numbers++;
    }

    getline(std::cin, input_string);
    std::istringstream input_stream_two(input_string);

    for (int i = 0; i < numbers; i++)
    {
        input_stream_two >> number;

        step = measure_one[i] - number;

        result[i] = number / step;

    }

    for (int i = 0; i < numbers; i++)
    {
        std::cout << result[i] << " ";
    }

    return 0;
}
