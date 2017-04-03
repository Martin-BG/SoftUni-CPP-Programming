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

        std::string getInfo() const {
            std::ostringstream info;
            info << "height: " << this->heightMeters
                << ", weight: " << this->weightKgs;
            return info.str();
        }
    };

    private:
    std::string name;
    int age = 0;
    Body body;

    static int totalPeople;
    static int totalAge;

    public:
    Person();
    Person(std::string name, int age, double heightMeters, double weightKgs);

    void makeOlder(int years);

    std::string getInfo() const;

    static double averagePersonAge();

    // NOTE: since we declare the friend here, we also tell the compiler that such a method exists - so we don't need to declare it
    // outside the class too (i.e. this has the same effect as the declaration for operator>> after this class plus giving private access)
    friend std::istream& operator>>(std::istream &inputStream, Person &p);
};

// NOTE: we need to declare that such an operation exists - otherwise (even if we define it in the cpp) the compiler won't know to look for it
// Also note that we declare it OUTSIDE the class - that's because this operation is not part of our Person class, it is rather a part of the
// ostream class (which e.g. cout is an object of), because the ostream stands to the left of the operator (e.g. cout << p;)
std::ostream& operator<<(std::ostream &outputStream, const Person &p);

#endif // PERSON_H
