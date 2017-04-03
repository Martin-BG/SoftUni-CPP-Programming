#include "Person.h"

//NOTE: we are forced to initialize these outside of the class
int Person::totalPeople = 0;
int Person::totalAge = 0;

Person::Person(std::string name, int age, double heightMeters, double weightKgs) :
    name(name),
    age(age),
    body(heightMeters, weightKgs) {
    // the following line will cause a compilation error, even if we remove the name(name) initializer - that's
    // because in the ctor body, name has already been initialized, and since it is const it can't be re-assigned
    //this->name = name;

    // NOTE: we can't touch these in the init list - they are not the current object's members
    totalPeople++;
    totalAge += age;
}

void Person::makeOlder(int years) {
    this->age += years;
}

std::string Person::getInfo() {
    std::ostringstream info;
    info << "name: " << this->name << ", age: " << this->age
        << ", " << this->body.getInfo();
    return info.str();
}

double Person::averagePersonAge() {
    return totalAge / (double) totalPeople;
}
