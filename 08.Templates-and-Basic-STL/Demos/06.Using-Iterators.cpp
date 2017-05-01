#include <iostream>
#include <vector>
#include <list>

int main() {
    #ifdef VECTOR_EXAMPLE
    std::vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    std::vector<int>::iterator i;
    #else
    std::list<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    std::list<int>::iterator i;
    #endif // VECTOR_EXAMPLE

    for (i = numbers.begin(); i != numbers.end(); i++) {
        (*i)++;
    }

    for (i = numbers.begin(); i != numbers.end(); i++) {
        std::cout << *i << std::endl;
    }
}
