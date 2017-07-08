#include <map>
#include <stdexcept>
#include "IndexedSet.h"

IndexedSet::IndexedSet() : valuesSet(), valuesArray(nullptr) {
}

IndexedSet::IndexedSet(const IndexedSet& other) : valuesSet(other.valuesSet) {
    this->valuesArray = new Value[other.size()];

    if (other.valuesArray != nullptr) {
        for (size_t i = 0; i < other.size(); i++) {
            this->valuesArray[i] = other.valuesArray[i];
        }
    } else {
        this->valuesArray = nullptr;
    }
}

void IndexedSet::add(const Value& v) {
    this->valuesSet.insert(v);

    this->clearIndex();
}

size_t IndexedSet::size() const {
    return this->valuesSet.size();
}

const Value& IndexedSet::operator[](size_t index) {
    if (index < 0 || index >= this->size()) {
        throw std::out_of_range("Index out of range");
    }

    if (this->valuesArray == nullptr) {
        this->buildIndex();
    }

    return this->valuesArray[index];
}

IndexedSet& IndexedSet::operator=(const IndexedSet& other) {
    if (this != &other) {
        this->clearIndex();

        this->valuesSet = other.valuesSet;

        if (other.valuesArray != nullptr) {
            this->valuesArray = new Value[other.size()];
            for (size_t i = 0; i < other.size(); i++) {
                this->valuesArray[i] = other.valuesArray[i];
            }
        }
    }

    return *this;
}

IndexedSet::~IndexedSet() {
    this->clearIndex();
}

void IndexedSet::buildIndex() {
    this->clearIndex();

    this->valuesArray = new Value[this->size()];
    int index = 0;
    for(std::set<Value>::iterator i = this->valuesSet.begin(); i != this->valuesSet.end(); i++) {
        this->valuesArray[index] = *i;
        index++;
    }
}

void IndexedSet::clearIndex() {
    delete[] this->valuesArray;
    this->valuesArray = nullptr;
}
