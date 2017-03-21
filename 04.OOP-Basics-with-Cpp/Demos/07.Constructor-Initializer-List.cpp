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
};

void printPersonInfo(Person person) {
    cout << "name: " << person.name << ", age: " << person.age
        << ", height: " << person.body.heightMeters << ", weight: " << person.body.weightKgs
        << endl;
}

int main() {
    printPersonInfo(Person("Prope Rinit", 42, 1.82, 82.3));

    return 0;
}
