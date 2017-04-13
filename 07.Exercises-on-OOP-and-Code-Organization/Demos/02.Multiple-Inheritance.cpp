#include<iostream>
#include<sstream>

class Animal {
public:
    double movementSpeed;

    Animal(double movementSpeed) :
        movementSpeed(movementSpeed) {
    }

    std::string getInfo() {
        std::ostringstream infoStream;
        infoStream << "speed: " << this->movementSpeed;
        return infoStream.str();
    }
};

class Plant {
public:
    bool hasSeeds;

    Plant(bool hasSeeds) :
        hasSeeds(hasSeeds) {
    }

    std::string getInfo() {
        std::ostringstream infoStream;
        infoStream << "hasSeeds: " << (this->hasSeeds ? "true" : "false");
        return infoStream.str();
    }
};

class GMO : public Animal, public Plant {
public:
    GMO(double movementSpeed, bool hasSeeds) :
        Animal(movementSpeed),
        Plant(hasSeeds) {
    }

    std::string getInfo() {
        return Animal::getInfo() + std::string(" ") + Plant::getInfo();
    }
};

int main() {
    GMO o(4.2, true);

    std::cout << o.getInfo() << std::endl;

    Animal & asAnimal = o;

    std::cout << asAnimal.getInfo() << std::endl;

    Plant & asPlant = o;

    std::cout << asPlant.getInfo() << std::endl;

    return 0;
}
