#include <iostream>
#include <cstdlib>
#include <sstream>

template<typename DataType>
class SmartArray {
private:
    DataType * data;
    size_t length;
public:
    SmartArray(const SmartArray & other) : data(new DataType[other.length]), length(other.length) {
        std::cout << "copy ctor" << std::endl;
        copyData(other.data, other.length, this->data, this->length);
    }

    SmartArray(SmartArray &&other) : data(other.data), length(other.length) {
        std::cout << "move ctor" << std::endl;
        other.data = nullptr;
    }

    SmartArray(size_t length) :
        data(new DataType[length]),
        length(length) {}

    SmartArray() : SmartArray(0) {}

    SmartArray(std::initializer_list<DataType> initList) : SmartArray(initList.size()) {
        size_t index = 0;
        for (DataType item : initList) {
            this->set(index, item);
            index++;
        }
    }

    ~SmartArray() {
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

    void add(DataType element) {
        this->changeLength(this->getLength() + 1);
        this->set(this->getLength() - 1, element);
    }

    size_t getLength() {
        return this->length;
    }

    void changeLength(size_t newLength) {
        DataType * newData = new DataType[newLength]();

        copyData(this->data, this->length, newData, newLength);

        delete[] this->data;

        this->data = newData;
        this->length = newLength;
    }

    std::string toString() {
        std::stringstream stringResult;

        for(size_t i = 0; i < this->length; i++) {
            stringResult << this->data[i] << " ";
        }

        return stringResult.str();
    }

    SmartArray& operator=(const SmartArray & other) {
        std::cout << "copy assigment" << std::endl;
        if (this != &other) {
            delete[] this->data;

            this->length = other.length;
            this->data = new DataType[other.length];

            copyData(other.data, other.length, this->data, this->length);
        }

        return *this;
    }

    SmartArray& operator=(SmartArray &&other) {
        std::cout << "move assignment" << std::endl;
        if (this != &other) {
            delete[] this->data;

            this->data = other.data;
            this->length = other.length;

            other.data = nullptr;
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

SmartArray<int> f(SmartArray<int> & a) {
    return {a[0], a[1]};
}

int main() {
    SmartArray<int> a {1,2};
    a = f(a);

    return 0;
}
