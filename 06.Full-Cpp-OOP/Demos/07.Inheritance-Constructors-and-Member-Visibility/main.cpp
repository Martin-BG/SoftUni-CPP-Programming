#include<iostream>

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
};

class Sheep : public Organism {
public:
    bool isBlack;
    Sheep(bool isBlack, double weight) :
        Organism(weight, true, false),
        isBlack(isBlack) {
    }
};

class Spider : public Organism{
    int numLegs;
public:
    Spider(int numLegs, double weight):
        Organism(weight, false, true),
        numLegs(numLegs) {
    }
};

int main() {
    return 0;
}
