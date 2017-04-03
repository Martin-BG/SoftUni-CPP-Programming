#include "Person.h"

#include<ostream>

//NOTE: we are forced to initialize these outside of the class
int Person::totalPeople = 0;
int Person::totalAge = 0;

Person::Person() :
    age(0),
    body(0, 0) {
}

Person::Person(std::string name, int age, double heightMeters, double weightKgs) :
    name(name),
    age(age),
    body(heightMeters, weightKgs) {
    // NOTE: we can't touch these in the init list - they are not the current object's members
    totalPeople++;
    totalAge += age;
}

void Person::makeOlder(int years) {
    this->age += years;
}

std::string Person::getInfo() const {
    std::ostringstream info;
    info << "name: " << this->name << ", age: " << this->age
        << ", " << this->body.getInfo();
    return info.str();
}

double Person::averagePersonAge() {
    return totalAge / (double) totalPeople;
}

std::istream& operator>>(std::istream &inputStream, Person &p) {
    // NOTE: another approach - read these into 4 variables, then use Person setters to set them - that would negate
    // the need for this method to be declared a friend of Person - but it would also require Person to have setters
    // for all of these fields, so it's a trade-off
    inputStream >> p.name >> p.age >> p.body.heightMeters >> p.body.weightKgs;

    return inputStream;
}

std::ostream& operator<<(std::ostream &outputStream, const Person &p) {
    outputStream << p.getInfo();
    return outputStream;
}
