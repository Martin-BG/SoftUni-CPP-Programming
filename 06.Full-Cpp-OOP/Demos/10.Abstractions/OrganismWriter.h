#ifndef WRITER_H
#define WRITER_H

#include "Organisms.h"

class OrganismWriter {
public:
    virtual void write(Organisms::Organism &o) = 0;
};

#endif // WRITER_H

