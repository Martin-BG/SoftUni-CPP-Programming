#include "Range.h"

Range::Range() : rangeFirst(0), rangeLength(0), valueCounts(new size_t[0]) {
}

void Range::add(T value) {
    if (this->empty()) {
        this->resize(value, value);
    } else if (value < this->rangeFirst) {
        this->resize(value, this->rangeFirst + this->rangeLength);
    } else if (value >= this->rangeFirst + this->rangeLength) {
        this->resize(this->rangeFirst, value);
    }

    this->valueCounts[this->getIndex(value)]++;
}

void Range::resize(T first, T last) {
    int newLength = (last - first) + 1;
    size_t * arr = new size_t[newLength]{};

    if (newLength > 0) {
        for (int i = 0; i < newLength; i++) {
            arr[i] = this->getCount(first + i);
        }
    }

    this->clear();
    this->rangeFirst = first;
    this->rangeLength = newLength;
    this->valueCounts = arr;
}

bool Range::empty() const {
    return this->rangeLength == 0;
}

void Range::clear() {
    this->rangeFirst = 0;
    this->rangeLength = 0;
    delete[] this->valueCounts;
    this->valueCounts = new size_t[0];
}

size_t Range::getCount(T value) const {
    if (value < this->rangeFirst || value >= this->rangeFirst + this->rangeLength) {
        return 0;
    }

    return this->valueCounts[this->getIndex(value)];
}

Range::Range(const Range& other)
: rangeFirst(other.rangeFirst)
, rangeLength(other.rangeLength)
, valueCounts(copyValues(other)) {}

Range& Range::operator=(const Range& other) {
    if (this != &other) {
        this->clear();

        this->rangeFirst = other.rangeFirst;
        this->rangeLength = other.rangeLength;

        this->valueCounts = copyValues(other);
    }

    return *this;
}

Range::~Range() {
    this->clear();
}

size_t Range::getIndex(T value) const {
    return value - this->rangeFirst;
}
