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

bool personIs45(const Person& p) {
    return p.getAge() == 45;
}

int main() {
    std::list<Person> menInBlack;
    menInBlack.push_back(Person("Bee", 55));
    menInBlack.push_back(Person("Kay", 45));
    menInBlack.push_back(Person("Zed", 55));
    menInBlack.push_back(Person("Ned", 55));
    menInBlack.push_back(Person("Jay", 25));

    // NOTE: in C++11, instead of defining a function, we can do this (we'll discuss it in another lecture):
    //auto personIter = std::find_if(menInBlack.begin(), menInBlack.end(), [&](const Person& p){ return p.getAge() == 45; });
    std::list<Person>::iterator personIter = std::find_if(menInBlack.begin(), menInBlack.end(), personIs45);
    if (personIter != menInBlack.end()) {
        std::cout << *personIter << std::endl;
    } else {
        std::cout << "No such Person" << std::endl;
    }

    return 0;
}
