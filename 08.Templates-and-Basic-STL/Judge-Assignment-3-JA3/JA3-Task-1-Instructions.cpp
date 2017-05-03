#include<iostream>
#include<string>

const int MAX_NUM = 50;
int numbers[MAX_NUM];
int num_pointer;


void addNum(const std::string &);
void sum();
void subtract();
void concat();
void discard();

int main()
{
    std::string input;

    while (true)
    {
        std::getline(std::cin, input);

        if (input == "sum")
        {
            sum();
        }
        else if (input == "subtract")
        {
            subtract();
        }
        else if (input == "concat")
        {
            concat();
        }
        else if (input == "discard")
        {
            discard();
        }
        else if (input == "end")
        {
            break;
        }
        else
        {
            addNum(input);
        }
    }

    for (int i = 0; i < num_pointer; i++)
    {
        std::cout << numbers[i] << std::endl;
    }

    return 0;
}

void addNum(const std::string & input)
{
    numbers[num_pointer++] = std::stoi(input);
}

void sum()
{
    numbers[num_pointer - 2] += numbers[num_pointer - 1];
    num_pointer--;
}

void subtract()
{
    numbers[num_pointer - 2] = numbers[num_pointer - 1] - numbers[num_pointer - 2];
    num_pointer--;
}

void concat()
{
    numbers[num_pointer - 2] = std::stoi(std::to_string(numbers[num_pointer - 2]) + std::to_string(numbers[num_pointer - 1]));
    num_pointer--;
}

void discard()
{
    num_pointer--;
}
