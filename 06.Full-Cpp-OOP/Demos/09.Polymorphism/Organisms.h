#include<string>
#include<sstream>

namespace Organisms {

using std::string;
using std::ostringstream;

class Organism {
protected:
    bool eatsPlants;
    bool eatsAnimals;
public:
    double weight;

    Organism(double weight, bool eatsPlants, bool eatsAnimals):
        eatsPlants(eatsPlants),
        eatsAnimals(eatsAnimals),
        weight(weight) {
    }

    virtual string getInfo() const {
        ostringstream stream;
        stream << "weight: " << this->weight << " ";
        if (this->eatsAnimals && this->eatsPlants) {
            stream << "(omnivore)";
        } else if (this->eatsAnimals) {
            stream << "(carnivore)";
        } else if (this->eatsPlants) {
            stream << "(herbivore)";
        } else {
            stream << "(plant)";
        }

        return stream.str();
    }
};

class Sheep : public Organism {
public:
    bool isBlack;
    Sheep(bool isBlack, double weight) :
        Organism(weight, true, false),
        isBlack(isBlack) {
    }

    string getInfo() const {
        ostringstream stream;
        stream << (this->isBlack ? "Black " : "White ") << " Sheep, " << Organism::getInfo();
        return stream.str();
    }
};

class Spider : public Organism{
    int numLegs;
public:
    Spider(int numLegs, double weight):
        Organism(weight, false, true),
        numLegs(numLegs) {
    }

    string getInfo() const {
        ostringstream stream;
        stream << this->numLegs << "-legged" << " Spider, " << Organism::getInfo();
        return stream.str();
    }
};

}
