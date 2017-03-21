#include<iostream>
#include<string>
#include<sstream>
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

        string getInfo() {
            ostringstream info;
            info << "height: " << this->heightMeters
                << ", weight: " << this->weightKgs;
            return info.str();
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

    void makeOlder(int years) {
        this->age += years;
    }

    string getInfo() {
        ostringstream info;
        info << "name: " << this->name << ", age: " << this->age
            << ", " << this->body.getInfo();
        return info.str();
    }
};

int main() {
    Person person("Refa Ctored", 42, 1.82, 82.3);

    cout << person.getInfo() << endl;
    person.makeOlder(1);
    cout << person.getInfo() << endl;

    return 0;
}
