#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

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

Person getRandomPerson() {
    static std::vector<std::string> names {"Solstice", "Varus", "Germanica", "Victrix"};

    std::string name = names[rand() % names.size()];
    int age = rand() % 100;

    return {name, age};
}

int main() {
    Person ben{"Ben Dover", 55};
    Person noa{"Noa Ge"};
    Person pai{std::pair<std::string, int>{"Pai Rinit", 42}};
    Person def{};

    std::cout << ben << std::endl << noa << std::endl << pai << std::endl << def << std::endl;

    std::cout << "----------" << std::endl;

    Person peopleArr[] {ben, noa, pai, def, getRandomPerson()};

    for (auto p : peopleArr) {
        std::cout << p << std::endl;
    }

    std::cout << "----------" << std::endl;

    std::vector<Person> people {ben, noa, pai, def, getRandomPerson()};

    for (auto p : people) {
        std::cout << p << std::endl;
    }

    std::cout << "----------" << std::endl;

    for (auto p : {ben, noa, pai, def, getRandomPerson()}) {
        std::cout << p << std::endl;
    }

    std::cout << "----------" << std::endl;

    std::map<std::string, Person> peopleByName {
        { ben.getName(), ben },
        { noa.getName(), noa },
        { pai.getName(), pai },
        { def.getName(), def }
    };

    std::cout << peopleByName["Ben Dover"] << std::endl;
    std::cout << peopleByName["Pai Rinit"] << std::endl;

    return 0;
}
