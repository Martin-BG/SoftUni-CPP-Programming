#include<iostream>
#include<fstream>
#include "Organisms.h"
#include "OrganismWriter.h"

class ConsoleWriter : public OrganismWriter {
    void write(Organisms::Organism & o) {
        std::cout << o.getInfo() << std::endl;
    }
};

class FileWriter : public OrganismWriter {
    std::ofstream fileStream;
public:
    FileWriter(std::string filename) :
        fileStream(filename) {
    }

    void write(Organisms::Organism & o) {
        fileStream << o.getInfo() << std::endl;
    }
};

OrganismWriter * getWriter() {
    return new FileWriter("output.txt");
}

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

    OrganismWriter * writer = getWriter();
    writer->write(*organismsArr[0]);
    writer->write(*organismsArr[1]);
    writer->write(*organismsArr[2]);

    for (int i = 0; i < 3; i++) {
        delete organismsArr[i];
    }

    return 0;
}

