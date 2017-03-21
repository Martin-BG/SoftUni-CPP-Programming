#include<iostream>
#include<string>
using namespace std;

class Person {
    class Body {
        public:
        double heightMeters;
        double weightKgs;

        Body(double heightMeters, double weightKgs) :
            heightMeters(heightMeters),
            weightKgs(weightKgs) {
        }
    };

    public:
    string name;
    int age = 0;
    Body body;

    Person(string name, int age, double heightMeters, double weightKgs) :
        name(name),
        age(age),
        body(heightMeters, weightKgs) {
    }

    void makePersonOlder(int years) {
        this->age += years;
    }

    void printPersonInfo() {
    cout << "name: " << this->name << ", age: " << this->age
        << ", height: " << this->body.heightMeters << ", weight: " << this->body.weightKgs
        << endl;
    }
};

int main() {
    Person person("Met Hods", 42, 1.82, 82.3);

    person.printPersonInfo();

    Person * personPointer = &person;
    personPointer->makePersonOlder(1);
    personPointer->printPersonInfo();

    return 0;
}
