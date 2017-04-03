#include<iostream>

class Organism {
protected:
    bool eatsPlants;
    bool eatsAnimals;

    friend std::ostream& operator<<(std::ostream& stream, const Organism &o);
public:
    double weight;
};

std::ostream& operator<<(std::ostream& stream, const Organism &o) {
    stream << "weight: " << o.weight << " ";
    if (o.eatsAnimals && o.eatsPlants) {
        stream << "(omnivore)";
    } else if (o.eatsAnimals) {
        stream << "(carnivore)";
    } else if (o.eatsPlants) {
        stream << "(herbivore)";
    } else {
        stream << "(plant)";
    }

    return stream;
}

class Spider : public Organism{
    int numLegs;
public:
    double weight;
    Spider(int numLegs, double weight) {
        this->numLegs = numLegs;
        this->weight = weight;
    }
};

int main() {
    Spider s(6, 0.01);

    Organism o = s;

    // we will get a random object, because Spider sets it's own weight, not Organism::weight, and because s gets sliced into o
    std::cout << o << std::endl;

    return 0;
}

