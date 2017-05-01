#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include "Container.h"

#include<string>
#include<sstream>

template<typename DataType>
class SmartArray : public Container<DataType> {
private:
    DataType * data;
    size_t length;
public:
    SmartArray() :
        data(new DataType[0]),
        length(0) {
    }

    SmartArray(const SmartArray & other) :
        data(new DataType[other.length]),
        length(other.length) {
            copyData(other.data, other.length, this->data, this->length);
    }

    SmartArray(size_t length) :
        data(new DataType[length]),
        length(length) {
    }

    ~SmartArray() override {
        delete[] data;
    }

    DataType get(size_t index) {
        ensureIndexInBounds(index);

        return this->data[index];
    }

    void set(size_t index, DataType value) {
        ensureIndexInBounds(index);

        this->data[index] = value;
    }

    void add(DataType element) override {
        this->changeLength(this->getLength() + 1);
        this->set(this->getLength() - 1, element);
    }

    size_t getLength() override {
        return this->length;
    }

    void changeLength(size_t newLength) {
        DataType * newData = new DataType[newLength]();

        copyData(this->data, this->length, newData, newLength);

        delete[] this->data;

        this->data = newData;
        this->length = newLength;
    }

    std::string toString() override {
        std::stringstream stringResult;

        for(size_t i = 0; i < this->length; i++) {
            stringResult << this->data[i] << " ";
        }

        return stringResult.str();
    }

    SmartArray& operator=(const SmartArray & other) {
        if (this != &other) {
            delete[] this->data;

            this->length = other.length;
            this->data = new DataType[other.length];

            copyData(other.data, other.length, this->data, this->length);
        }

        return *this;
    }

    DataType& operator[](size_t index) {
        ensureIndexInBounds(index);

        return this->data[index];
    }

private:
    void ensureIndexInBounds(size_t index) {
        if (index < 0 || index >= this->length) {
            throw "index out of bounds";
        }
    }

    static void copyData(DataType * source, size_t sourceLength, DataType * dest, size_t destLength) {
        for(size_t i = 0; i < sourceLength && i < destLength; i++) {
            dest[i] = source[i];
        }
    }
};

#endif // SMARTARRAY_H
