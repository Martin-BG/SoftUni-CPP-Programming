#include <iostream>
#include <string>
#include <vector>
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

bool inOrderByName(const Person& p1, const Person& p2) {
    return p1.getName() < p2.getName();
}

bool inOrderByAge(const Person& p1, const Person& p2) {
    return p1.getAge() < p2.getAge();
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        stream << v[i] << std::endl;
    }

    return stream;
}

int main() {
    std::vector<Person> menInBlack;
    menInBlack.push_back(Person("Bee", 55));
    menInBlack.push_back(Person("Kay", 45));
    menInBlack.push_back(Person("Zed", 55));
    menInBlack.push_back(Person("Ned", 55));
    menInBlack.push_back(Person("Jay", 25));

    std::stable_sort(menInBlack.begin(), menInBlack.end(), inOrderByAge);
    std::cout << "sorted by age:" << std::endl << menInBlack << std::endl;

    std::stable_sort(menInBlack.begin(), menInBlack.end(), inOrderByName);
    // NOTE: in C++11, instead of defining a function, we can do this (we'll discuss it in another lecture):
    //std::stable_sort(menInBlack.begin(), menInBlack.end(), [&](const Person& p1, const Person& p2){ return p1.getName() < p2.getName(); });
    std::cout << "sorted by name:" << std::endl << menInBlack << std::endl;

    return 0;
}
