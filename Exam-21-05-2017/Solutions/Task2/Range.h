#ifndef RANGE_H
#define RANGE_H

#include<string>
#include<sstream>
#include<stdexcept>

typedef int T;
class Range {
public:
    class ConstValueIterator {
        const Range* range;
        T currentValue;
        size_t countRemaining;
    public:
        ConstValueIterator(const Range* range, T currentValue)
        : range(range)
        , currentValue(currentValue)
        , countRemaining(0) {
            if (*this) {
                this->countRemaining = range->getCount(currentValue);
            }
        }

        operator bool() const {
            return this->currentValue < range->rangeFirst + range->rangeLength && !range->empty();
        }

        const T& operator*() const {
            if (!*this) {
                throw std::range_error("attempting to dereference end() iterator");
            }

            return currentValue;
        }

        ConstValueIterator& operator++() {
            this->countRemaining--;
            if (this->countRemaining <= 0) {
                while (this->countRemaining <= 0 && *this) {
                    this->currentValue++;
                    this->countRemaining = range->getCount(this->currentValue);
                }
            }

            return *this;
        }

        ConstValueIterator operator++(int) {
            ConstValueIterator i = *this;
            this->operator++();
            return i;
        }

        bool operator==(const ConstValueIterator& other) const {
            return this->currentValue == other.currentValue &&
                this->countRemaining == other.countRemaining;
        }

        bool operator!=(const ConstValueIterator& other) const {
            return ! (this->operator==(other));
        }
    };

    Range();

    void add(T value);
    size_t getCount(T value) const;
    void clear();
    void resize(T first, T last);
    bool empty() const;

    Range(const Range& other);
    Range& operator=(const Range& other);
    ~Range();

    ConstValueIterator begin() const {
        return this->empty() ? this->end() : ConstValueIterator(this, rangeFirst);
    }

    ConstValueIterator end() const {
        return ConstValueIterator(this, rangeFirst + rangeLength);
    }

    std::string toString() const {
        std::ostringstream s;

        for (int i = 0; i < this->rangeLength; i++) {
            s << this->valueCounts[i] << " ";
        }

        return s.str();
    }

private:
    T rangeFirst;
    T rangeLength;
    size_t * valueCounts;

    size_t getIndex(T value) const;

    static size_t* copyValues(const Range& other) {
        return copyValues(other.valueCounts, other.rangeLength);
    }

    static size_t* copyValues(size_t* values, size_t length) {
        size_t* copies = new size_t[length];
        for (size_t i = 0; i < length; i++) {
            copies[i] = values[i];
        }

        return copies;
    }
};

#endif // RANGE_H
