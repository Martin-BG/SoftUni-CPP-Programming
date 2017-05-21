/*Task 2
Add C++11 list-initialization of elements to the List class you implemented in Task 1.
The following code should compile and execute correctly,
and it should have the same result as the code in Task 1.

List<int> numbers {1, -2, 42};
for (int n : numbers) {
    std::cout << n << " ";
}
std::cout << std::endl;

List<std::string> words {"Guardians", "galaxy"};
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
	List<int> numbers {1, -2, 42};
	for (int n : numbers) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	List<std::string> words {"Guardians", "galaxy"};
	for (auto word : words) {
		std::cout << word << " ";
	}
	std::cout << std::endl;

    return 0;
}
