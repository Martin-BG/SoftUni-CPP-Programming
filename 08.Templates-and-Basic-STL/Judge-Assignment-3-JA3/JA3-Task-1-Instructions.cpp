#include<iostream>
#include<string>

int main()
{
	const int MAX_NUM = 50;
	int numbers[MAX_NUM] = {};
	int num_pointer = 0;
    std::string input;

    while (true)
    {
        std::getline(std::cin, input);

        if (input == "sum")
        {
			numbers[num_pointer - 2] += numbers[num_pointer - 1];
			num_pointer--;
        }
        else if (input == "subtract")
        {
			numbers[num_pointer - 2] = numbers[num_pointer - 1] - numbers[num_pointer - 2];
			num_pointer--;
        }
        else if (input == "concat")
        {
			numbers[num_pointer - 2] = std::stoi(std::to_string(numbers[num_pointer - 2]) + std::to_string(numbers[num_pointer - 1]));
			num_pointer--;
        }
        else if (input == "discard")
        {
            num_pointer--;;
        }
        else if (input == "end")
        {
            break;
        }
        else
        {
            numbers[num_pointer++] = std::stoi(input);
        }
    }

    for (int i = 0; i < num_pointer; i++)
    {
        std::cout << numbers[i] << std::endl;
    }

    return 0;
}
