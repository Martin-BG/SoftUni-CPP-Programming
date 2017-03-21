#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class Person {
    class Body {
        private:
        double heightMeters;
        double weightKgs;

        public:
        Body(double heightMeters, double weightKgs) :
            heightMeters(heightMeters),
            weightKgs(weightKgs) {
        }

        void increaseWeight(double kgs) {
            this->weightKgs += kgs;
        }

        string getInfo() {
            ostringstream info;
            info << "height: " << this->heightMeters
                << ", weight: " << this->weightKgs;
            return info.str();
        }
    };

    private:
    string name;
    int age = 0;
    Body body;

    public:
    Person() :
        body(0, 0) {
    }

    Person(string name, int age, double heightMeters, double weightKgs) :
        name(name),
        age(age),
        body(heightMeters, weightKgs) {
    }

    string getName() {
        return this->name;
    }

    void makeOlder(int years) {
        if (years < 0) {
            throw "years must be a positive number";
        }

        this->age += years;
    }

    void makeHeavier(double kgs) {
        if (kgs < 0) {
            throw "kgs must be a positive number";
        }

        this->body.increaseWeight(kgs);
    }

    string getInfo() {
        ostringstream info;
        info << "name: " << this->name << ", age: " << this->age
            << ", " << this->body.getInfo();
        return info.str();
    }
};

int main() {
    Person p("Enca Psulation", 42, 1.82, 82);

    cout << p.getInfo() << endl;

    p.makeOlder(27);
    p.makeHeavier(87);
    cout << "Some time has passed for " << p.getName()
        << "... and he's a bit out of shape now" << endl;

    cout << p.getInfo() << endl;

    return 0;
}
