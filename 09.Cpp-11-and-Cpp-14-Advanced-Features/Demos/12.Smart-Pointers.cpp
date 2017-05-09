#include <iostream>
#include <list>
#include <algorithm>
#include <memory>

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
    while(true) {
    std::list<std::shared_ptr<Person> > people {
        std::make_shared<Person>("Ben Dover", 55),
        std::make_shared<Person>("Noa Ge"),
        std::make_shared<Person>("Charlie Foxtrot", 69),
        std::make_shared<Person>()
    };

    for (auto p : people) {
        //std::cout << *p << std::endl;
    }

    people.remove_if([](const std::shared_ptr<Person> & p) { return p->getAge() > 65; });
    //std::cout << "-- After removal ---" << std::endl;

    for (auto p : people) {
        //std::cout << *p << std::endl;
    }
    }
    return 0;
}
