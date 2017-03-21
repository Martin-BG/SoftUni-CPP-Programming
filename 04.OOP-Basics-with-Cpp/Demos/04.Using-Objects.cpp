#include<iostream>
#include<string>
using namespace std;

class Person {
    class Body {
        public:
        double heightMeters;
        double weightKgs;
    };

    // NOTE: making everything public is not a good approach. We'll discuss access modifiers after a few demos
    public:
    string name;
    int age;

    Body body;
};

// NOTE: A better approach would be methods on the Person class. We'll meet those after a few demos
void printPersonInfo(Person person) {
    cout << "name: " << person.name << ", age: " << person.age
        << ", height: " << person.body.heightMeters << ", weight: " << person.body.weightKgs
        << endl;
}

void makePersonOlder(Person& person, int years) {
    person.age += years;
}

int main() {
    Person person;
    // the name should be empty, as it is a string class. The values of the others are not defined
    cout << "person (not initialized) = ";
    printPersonInfo(person);

    // NOTE: this is not the proper way to initialize an object. The proper way is using constructors - we'll see them after a few demos
    person.name = "Lorem";
    person.age = 42;
    person.body.heightMeters = 1.3;
    person.body.weightKgs = 69;

    Person people[3];
    people[0] = person;

    cout << "people[0] = ";
    printPersonInfo(people[0]);

    makePersonOlder(people[0], 1);
    cout << "people[0] (after aging) = ";
    printPersonInfo(people[0]);

    Person * newPerson = new Person();
    newPerson->name = "Ipsum";
    newPerson->age = 4;
    newPerson->body.heightMeters = 0.4;
    newPerson->body.weightKgs = 4.5;

    cout << "newPerson = ";
    printPersonInfo(*newPerson);
    delete newPerson;

    return 0;
}
