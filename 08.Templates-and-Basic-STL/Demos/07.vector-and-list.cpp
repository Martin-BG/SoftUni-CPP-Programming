#include <iostream>
#include <vector>
#include <list>
#include <sstream>

int main() {
    std::list<int> input;

    std::string itemString;
    std::cin >> itemString;
    while (itemString != "end") {
        std::stringstream itemParser(itemString);
        int itemValue;
        itemParser >> itemValue;

        input.push_back(itemValue);

        std::cin >> itemString;
    }

    std::vector<int> numbers;
    for (std::list<int>::iterator i = input.begin(); i != input.end(); i++) {
        numbers.push_back(*i);
    }

    int maxAbsDifference = 0;
    for (int a = 0; a < numbers.size(); a++) {
        for (int b = 0; b < numbers.size(); b++) {
            int currentDiff = numbers[a] - numbers[b];
            if (currentDiff > maxAbsDifference) {
                maxAbsDifference = currentDiff;
            }
        }
    }

    std::cout << "max abs difference: " << maxAbsDifference << std::endl;

    return 0;
}
