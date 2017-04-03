#ifndef PERSON_H
#define PERSON_H

#include<string>
#include<sstream>

class Person {
    class Body {
        public:
        double heightMeters;
        double weightKgs;

        Body(double heightMeters, double weightKgs) :
            heightMeters(heightMeters),
            weightKgs(weightKgs) {
        }

        std::string getInfo() {
            std::ostringstream info;
            info << "height: " << this->heightMeters
                << ", weight: " << this->weightKgs;
            return info.str();
        }
    };

    private:
    // enforce name not being able to change - if we accidentally try to change this in our code, we will get a
    // compilation error. Note that this requires initialization in constructor initializer list
    const std::string name;
    int age = 0;
    Body body;

    static int totalPeople;
    static int totalAge;

    public:
    Person(std::string name, int age, double heightMeters, double weightKgs);

    void makeOlder(int years);

    std::string getInfo();

    static double averagePersonAge();
};

#endif // PERSON_H
