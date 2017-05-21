/*Task 5*
Bonus Task - this task is not mandatory and will not count towards
your homework score. You can submit your homework without it.
Allow your List class to be inserted in an unordered_set.
Two Lists are considered equal if and only if they have the same
length and have the same elements in the same order.
The hash code of a List is calculated based on the sum of the hash
codes of each of its elements, but before adding an item's hash
code to the sum, it is multiplied by its position (starting from 1) -
for example, the List {13, 42, 69} will have the hash code:
std::hash(13) * 1 + std::hash(42) * 2 + std::hash(69) * 3.
*/

#include<iostream>
#include<unordered_set>

#include "List.h"
//#include "UnorderedSetOfLists.h"

List<int> getIntList();
List<std::string> getStringList();

template <typename T> void printList(const List<T> &lst)
{
    for (auto value : lst)
    {
		std::cout << value << " ";
	}

	std::cout << "[Hash = " << lst.calcHash() << "]" << std::endl;
}

namespace std {
    template<typename T> struct hash<List<T> >
    {
        size_t operator()(const List<T> &lst) const
        {
            return lst.calcHash();
        }
    };
}

template <typename T> struct ListHasher
{
    size_t operator()(const List<T> & lst) const
    {
        return lst.calcHash();
    }
};

template <typename T> struct ListComparator
{
    bool operator()(const List<T> & list1, const List<T> & list2) const
    {
        if (&list1 == &list2)
        {
            return true;
        }

        if (list1.getSize() != list2.getSize())
        {
            return false;
        }

        typename List<T>::Iterator it_this = list1.begin();
        typename List<T>::Iterator it_other = list2.begin();

        for (std::size_t i = 0; i < list1.getSize(); i++)
        {
            if(*it_this != *it_other)
            {
                return false;
            }

            ++it_this;
            ++it_other;
        }

        return true;
    }
};


template <typename T> struct UnorderdSetOfLists
{
public:
    static  std::unordered_set<List<int>> lists;
  //  static  std::unordered_set<List<T> > lists;
private:

bool operator()(const List<T> &other) const
{
    if (this == &other)
    {
        return true;
    }

    if (this->m_size != other.m_size)
    {
        return false;
    }

    typename List<T>::Iterator it_this = this->begin();
    typename List<T>::Iterator it_other = other.begin();
    for (std::size_t i = 0; i < this->m_size; i++)
    {
        if(*it_this != *it_other)
        {
            return false;
        }
        ++it_this;
        ++it_other;
    }

    return true;
}
};

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

	std::unordered_set<List<std::string>> u_set;
 //   UnorderdSetOfLists <std::string>u_set;

	u_set.insert(getStringList());
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
