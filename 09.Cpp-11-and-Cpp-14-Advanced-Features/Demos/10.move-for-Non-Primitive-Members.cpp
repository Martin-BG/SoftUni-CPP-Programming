#include <iostream>
#include <list>
#include <algorithm>

class Person {
    class Body {
    public:
        Body() = default;

        Body& operator=(const Body& other) {
            std::cout << "Body copy ";
            return *this;
        }

        Body& operator=(Body&& other) {
            std::cout << "Body move ";
            return *this;
        }
    };
    Body body;
public:
    Person() = default;
    Person& operator=(const Person& other) {
        std::cout << "Person copy ";
        body = other.body;
        return *this;
    }

    Person& operator=(Person&& other) {
        std::cout << "Person move ";
        body = std::move(other.body);
        return *this;
    }
};

int main() {
    Person p;

    p = Person{};

    return 0;
}
