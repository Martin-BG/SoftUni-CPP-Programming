#include <iostream>
#include <string>
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

class PersonAgeChecker {
    // Note: this could be const int, since we don't intend to change it
    int expectedAge;
public:
    PersonAgeChecker(int expectedAge) : expectedAge(expectedAge) {}

    bool operator()(const Person& p) {
        return p.getAge() == this->expectedAge;
    }
};

int main() {
    std::list<Person> menInBlack;
    menInBlack.push_back(Person("Bee", 55));
    menInBlack.push_back(Person("Kay", 45));
    menInBlack.push_back(Person("Zed", 55));
    menInBlack.push_back(Person("Ned", 55));
    menInBlack.push_back(Person("Jay", 25));

    std::list<Person>::iterator personIter = std::find_if(menInBlack.begin(), menInBlack.end(), PersonAgeChecker(45));
    if (personIter != menInBlack.end()) {
        std::cout << *personIter << std::endl;
    } else {
        std::cout << "No such Person" << std::endl;
    }

    return 0;
}
