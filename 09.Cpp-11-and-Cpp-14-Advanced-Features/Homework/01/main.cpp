/*Task 1
Implement a doubly-linked List class (like the one for JA2-Task-1-List).
Make it work for any data type, i.e. make it a class template which has
a template argument for the stored data type.
Make it support the C++11 range-based for loop.
Hint: we did something very similar to this in Exercises on OOP and Code Organization.

For example, this code should compile and execute correctly:

    List<int> numbers;
    numbers.add(1);
    numbers.add(-2);
    numbers.add(42);
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    List<std::string> words;
    words.add("Guardians");
    words.add("galaxy");
    for (auto word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

The code above should print out the following lines:

1 -2 42
Guardians galaxy
*/

#include<iostream>

#include "List.h"

int main()
{
    List<int> numbers;
    numbers.add(1);
    numbers.add(-2);
    numbers.add(42);
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    List<std::string> words;
    words.add("Guardians");
    words.add("galaxy");
    for (auto word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
