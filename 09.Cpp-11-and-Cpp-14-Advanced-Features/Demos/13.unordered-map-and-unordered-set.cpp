#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
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

typedef std::shared_ptr<Person> PersonPtr;

int main() {
    std::vector<PersonPtr> people {
        std::make_shared<Person>("Ben Dover", 25),
        std::make_shared<Person>("Noa Ge"),
        std::make_shared<Person>("Charlie Foxtrot", 69),
        std::make_shared<Person>("Oscar Lima Delta", 55),
        std::make_shared<Person>("Whiskey Tango Foxtrot", 125),
        std::make_shared<Person>("Bo Hica", 25),
        std::make_shared<Person>("Ones Heep", 69)
    };

    std::unordered_map<std::string, PersonPtr> peopleByName;
    std::unordered_map<int, int> ageCounts;
    std::unordered_set<char> uniqueLettersInNames;

    for (PersonPtr p : people) {
        peopleByName[p->getName()] = p;
        ageCounts[p->getAge()]++;

        for (char letter : p->getName()) {
            if (isalpha(letter)) {
                uniqueLettersInNames.insert(tolower(letter));
            }
        }
    }

    std::cout << "Person with name " << "Bo Hica" << " is: " << *(peopleByName["Bo Hica"]) << std::endl;
    std::cout << "Number of people at age " << 69 << " is: " << ageCounts[69] << std::endl;

    std::cout << "All letters used in names (lowercase, without duplicates, not ordered):" << std::endl;
    for (char letter : uniqueLettersInNames) {
        std::cout << letter << " ";
    }
    std::cout << std::endl;

    return 0;
}
