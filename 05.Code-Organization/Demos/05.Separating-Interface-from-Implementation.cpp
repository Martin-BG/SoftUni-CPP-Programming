#include<iostream>
#include<sstream>
using namespace std;

typedef int DataType;

class SmartArray {
private:
    DataType * data;
    int length;
public:
    SmartArray();
    SmartArray(const SmartArray & other);
    SmartArray(int length);
    ~SmartArray();

    DataType getElement(int index);
    void setElement(int index, DataType value);

    void changeLength(int newLength);

    string toString();

    SmartArray& operator=(const SmartArray & other);
    DataType& operator[](int index);
    void x();
private:
    void ensureIndexInBounds(int index);
    void copyData(DataType * source, int sourceLength,
                  DataType * dest, int destLength);
};

int main() {
    SmartArray arr(3);
    arr.changeLength(1);
    arr[0] = 1;
    cout << arr[0] << endl;

    return 0;
}

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

string SmartArray::toString() {
    stringstream stringResult;

    for(int i = 0; i < this->length; i++) {
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
    for(int i = 0; i < sourceLength && i < destLength; i++) {
        dest[i] = source[i];
    }
}
