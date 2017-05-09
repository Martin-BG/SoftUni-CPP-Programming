#include <iostream>
#include <list>
#include <algorithm>

class Person {
    std::string name;
    int age;

public:
    Person(std::string name, int age) :
        name(name),
        age(age) {
    }

    Person(std::string name) : Person(name, 0) {}

    Person() : Person("[unknown]", 0) {}

    Person(std::pair<std::string, int> nameAgePair) : Person(nameAgePair.first, nameAgePair.second) {}

    std::string getName() const {
        return this->name;
    }

    int getAge() const {
        return this->age;
    }

    friend std::ostream& operator<<(std::ostream&, const Person&);
};

std::ostream& operator<<(std::ostream& stream, const Person& p) {
    stream << p.name << " " << p.age;
    return stream;
}

int main() {
    // NOTE: writing Person before each item's init list is actually not necessary - it's only necessary for the std::list<Person>, from there on the compiler knows the type of each item
    std::list<Person> people {Person{"Ben Dover", 55}, Person{"Noa Ge"}, Person{"Charlie Foxtrot", 69}, Person{}};

    std::string name;
    std::getline(std::cin, name);

    auto p = std::find_if(people.begin(), people.end(), [=](const Person& p) {
                          return p.getName() == name;
                          } );

    if (p != people.end()) {
        std::cout << *p << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }

    std::cout << "----------" << std::endl;

    int numSortComparisons = 0;
    people.sort([&numSortComparisons](const Person& a, const Person& b) {
                numSortComparisons++;
                return a.getAge() < b.getAge();
                });

    std::cout << "sorted with " << numSortComparisons << " comparisons:" << std::endl;

    for (auto p : people) {
        std::cout << p << std::endl;
    }

    return 0;
}
