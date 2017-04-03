#include "SmartArray.h"

#include<sstream>

SmartArray::SmartArray() :
	length(0),
	data(new DataType[0]) {
}

SmartArray::SmartArray(int length) :
	length(length),
	data(new DataType[length]) {
}

SmartArray::SmartArray(const SmartArray & other) :
	length(other.length),
	data(new DataType[other.length]) {
	copyData(other.data, other.length, this->data, this->length);
}

SmartArray& SmartArray::operator=(const SmartArray & other) {
	if (this != &other) {
		delete[] this->data;

		this->length = other.length;
		this->data = new DataType[other.length];

		copyData(other.data, other.length, this->data, this->length);
	}

	return *this;
}

SmartArray::~SmartArray() {
	delete[] data;
}

DataType SmartArray::getElement(int index) {
	ensureIndexInBounds(index);

	return this->data[index];
}

void SmartArray::setElement(int index, DataType value) {
	ensureIndexInBounds(index);

	this->data[index] = value;
}

void SmartArray::changeLength(int newLength) {
	DataType * newData = new DataType[newLength]();

	copyData(this->data, this->length, newData, newLength);

	delete[] this->data;

	this->data = newData;
	this->length = newLength;
}

std::string SmartArray::toString() {
	std::stringstream stringResult;

	for (int i = 0; i < this->length; i++) {
		stringResult << this->data[i] << " ";
	}

	return stringResult.str();
}

DataType& SmartArray::operator[](int index) {
	ensureIndexInBounds(index);

	return this->data[index];
}

void SmartArray::ensureIndexInBounds(int index) {
	if (index < 0 || index >= this->length) {
		throw "index out of bounds";
	}
}

void SmartArray::copyData(DataType * source, int sourceLength,
	DataType * dest, int destLength) {
	for (int i = 0; i < sourceLength && i < destLength; i++) {
		dest[i] = source[i];
	}
}

SmartArray SmartArray::fromString(std::string s) {
    SmartArray arr;
    std::istringstream stream(s);

    int number;
    while(stream >> number) {
        // NOTE: this is terribly inefficient, since for each new element we copy all of the others
        arr.changeLength(arr.length + 1);

        arr.setElement(arr.length - 1, number);
    }

    return arr;
}

SmartArray& SmartArray::operator+=(const SmartArray& other) {
    int firstNewElementIndex = this->length;
    this->changeLength(this->length + other.length);

    for(int i = 0; i < other.length; i++) {
        this->data[firstNewElementIndex + i] = other.data[i];
    }

    return *this;
}
