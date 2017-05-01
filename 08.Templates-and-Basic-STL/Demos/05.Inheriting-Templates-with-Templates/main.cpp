#include <iostream>
#include <sstream>

#include "Container.h"
#include "SmartArray.h"

template<typename T>
void readFromConsole(Container<T> * destination) {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream inputStream(line);

    T element;
    while (inputStream >> element) {
        destination->add(element);
    }
}

int main () {
    SmartArray<int> numbers;
    readFromConsole(&numbers);

    std::cout << numbers.toString() << std::endl;

    SmartArray<std::string> words;
    readFromConsole(&words);

    std::cout << words.toString() << std::endl;

    return 0;
}
