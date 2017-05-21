#include <iostream>
#include <vector>
#include <sstream>
#include <string>

std::vector<int> parseNumbers(std::string line) {
    std::vector<int> numbers;

    std::istringstream lineStream(line);
    int number;
    while(lineStream >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::vector<int> firstYearValues = parseNumbers(line);

    std::getline(std::cin, line);
    std::vector<int> secondYearValues = parseNumbers(line);

    for (int i = 0; i < firstYearValues.size(); i++) {
        int damagePerYear = firstYearValues[i] - secondYearValues[i];
        int yearsRemaining = secondYearValues[i] / damagePerYear;

        std::cout << yearsRemaining << " ";
    }

    std::cout << std::endl;

    return 0;
}
