#include<iostream>
#include "Organisms.h"

int main() {
    using std::cout;
    using std::endl;
    using namespace Organisms;

    typedef Organism * OrganismPtr;

    // create a normal array of pointers to Organism objects (Oranism*) and fill it with objects of derived classes
    OrganismPtr organismsArr[3] {
        new Sheep(false, 80.0),
        new Spider(6, 80.0),
        new Sheep(true, 90.0)
    };

    for (int i = 0; i < 3; i++) {
        cout << organismsArr[i]->getInfo() << endl;
    }

    for (int i = 0; i < 3; i++) {
        delete organismsArr[i];
    }

    return 0;
}

