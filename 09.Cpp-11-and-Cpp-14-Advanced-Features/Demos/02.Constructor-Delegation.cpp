#include <iostream>

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
    std::cout << Person("Ben Dover", 55) << std::endl;
    std::cout << Person("Noa Ge") << std::endl;
    std::pair<std::string, int> p("Pai Rinit", 42);
    std::cout << Person(p) << std::endl;
    std::cout << Person() << std::endl;

    return 0;
}
