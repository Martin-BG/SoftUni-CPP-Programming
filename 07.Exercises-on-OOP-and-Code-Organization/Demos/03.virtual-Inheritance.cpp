#include<iostream>
#include<sstream>

class Organism {
public:
    double weight;
    Organism(double weight) :
        weight(weight) {
        std::cout << "Organism ctor" << std::endl;
    }
};

class Animal : public virtual Organism {
    double movementSpeed;
public:
    Animal(double movementSpeed, double weight) :
        // NOTE: Organism ctor will ONLY be called when creating an Animal - it won't be called when creating any inheriting class (like GMO)
        Organism(weight),
        movementSpeed(movementSpeed) {
        std::cout << "Animal ctor" << std::endl;
    }

    std::string getInfo() {
        std::ostringstream infoStream;
        infoStream << "speed: " << this->movementSpeed;
        return infoStream.str();
    }
};

class Plant : public virtual Organism {
    bool hasSeeds;
public:
    Plant(bool hasSeeds, double weight) :
        // NOTE: Organism ctor will ONLY be called when creating a Plant - it won't be called when creating any inheriting class (like GMO)
        Organism(weight),
        hasSeeds(hasSeeds) {
        std::cout << "Plant ctor" << std::endl;
    }

    std::string getInfo() {
        std::ostringstream infoStream;
        infoStream << "hasSeeds: " << (this->hasSeeds ? "true" : "false");
        return infoStream.str();
    }
};

class GMO : public Animal, public Plant {
public:
    GMO(double movementSpeed, bool hasSeeds, double weight) :
        // NOTE: We need to call Organism, because due to virtual inheritance Animal and Plant WON'T call it (that's why we're passing 0 weight to them - the only value that will matter is the one passed to the Organism)
        Organism(weight),
        Animal(movementSpeed, 0),
        Plant(hasSeeds, 0) {
    }

    std::string getInfo() {
        return Animal::getInfo() + std::string(" ") + Plant::getInfo();
    }
};

int main() {
    GMO gmo(4.2, true, 6.9);

    std::cout << gmo.getInfo() << std::endl;
    std::cout << gmo.weight << std::endl;

    Animal animal(1.3, 3);
    std::cout << animal.getInfo() << std::endl;
    std::cout << animal.weight << std::endl;

    return 0;
}
