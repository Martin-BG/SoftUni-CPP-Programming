#include <iostream>
#include <string>
#include <set>
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

template<typename T, typename C>
std::ostream& operator<<(std::ostream& stream, const std::set<T, C>& s) {
    for(typename std::set<T>::iterator i = s.begin(); i != s.end(); i++) {
        stream << *i << std::endl;
    }

    return stream;
}

class PersonNameComparator {
public:
    bool operator()(const Person& p1, const Person& p2) {
        return p1.getName() < p2.getName();
    }
};

class PersonAgeComparator {
public:
    bool operator()(const Person& p1, const Person& p2) {
        return p1.getAge() < p2.getAge();
    }
};

int main() {
    std::set<Person, PersonNameComparator> menInBlackByName;

    menInBlackByName.insert(Person("Bee", 55));
    menInBlackByName.insert(Person("Kay", 45));
    menInBlackByName.insert(Person("Zed", 55));
    menInBlackByName.insert(Person("Ned", 55));
    menInBlackByName.insert(Person("Jay", 25));

    // this constructs a set with the elements from the start to the end of menInBlackByName
    std::set<Person, PersonAgeComparator> menInBlackByAge(menInBlackByName.begin(), menInBlackByName.end());

    std::cout << "By name: " << std::endl << menInBlackByName << std::endl;

    // NOTE: notice how these will be less than the ones by name - that's because there are people with identical ages, and set removes the identical values
    std::cout << "By age: " << std::endl << menInBlackByAge << std::endl;

    return 0;
}
