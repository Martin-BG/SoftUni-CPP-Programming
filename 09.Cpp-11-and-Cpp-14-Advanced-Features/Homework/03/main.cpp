/*Task 3
Implement move semantics (Move Constructor and Move Assignment Operator) for the List.
Check to see that they are called correctly when initializing or assigning a List with
rvalues and make sure that you have no memory leaks.
*/

#include<iostream>

#include "List.h"

List<int> getIntList();
List<std::string> getStringList();

template <typename T> void printList(const List<T> &lst)
{
    for (auto value : lst)
    {
		std::cout << value << " ";
	}

	std::cout << std::endl;
}

int main()
{
	List<int> numbers {1, -2, 42};
	numbers << 45 << 76 << getIntList();
	printList(numbers);

    numbers = {1, 2};
	printList(numbers);

    numbers = getIntList();
	printList(numbers);

	List<int> numbers2(std::move(getIntList()));
	printList(numbers2);

	List<std::string> words {"Guardians", "galaxy"};
	printList(words);

	words << "Hello" << "World" << getStringList();
	printList(words);

    return 0;
}

List<int> getIntList()
{
    return List<int> {7, 8};
}

List<std::string> getStringList()
{
    return List<std::string> {"String", "List"};
}
