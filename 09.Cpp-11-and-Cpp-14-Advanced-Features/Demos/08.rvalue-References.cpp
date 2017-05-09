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
        #ifdef SHOW_COPY_CALLS
        std::cout << "copy ctor " << other.toString() << std::endl;
        #endif // SHOW_COPY_CTOR_CALLS

        copyData(other.data, other.length, this->data, this->length);
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

    DataType get(size_t index) const {
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

    size_t getLength() const {
        return this->length;
    }

    void changeLength(size_t newLength) {
        DataType * newData = new DataType[newLength]();

        copyData(this->data, this->length, newData, newLength);

        delete[] this->data;

        this->data = newData;
        this->length = newLength;
    }

    std::string toString() const {
        std::stringstream stringResult;

        for(size_t i = 0; i < this->length; i++) {
            stringResult << this->data[i] << " ";
        }

        return stringResult.str();
    }

    SmartArray& operator=(const SmartArray & other) {
        #ifdef SHOW_COPY_CALLS
        std::cout << "copy assign " << other.toString() << std::endl;
        #endif // SHOW_COPY_CTOR_CALLS
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
    void ensureIndexInBounds(size_t index) const {
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

//#define SHOW_INVALID_LVALUE_REF
//#define SHOW_INVALID_RVALUE_REF

int main() {
    int w = 70;
    const int & constRefToRValue = (w - 1);

    #ifdef SHOW_INVALID_LVALUE_REF
    int & invalidRefToRValue = (w - 1);
    #endif // SHOW_INVALID_LVALUE_REF

    int && rvalueRef = (w - 1);

    #ifdef SHOW_INVALID_RVALUE_REF
    int && invalidRValueRefToLValue = w;
    #endif // SHOW_INVALID_RVALUE_REF

    SmartArray<int> && arrRef = {1, 2, 3, 4, 5};
    #ifdef SHOW_INVALID_LVALUE_REF
    SmartArray<int> & invalidArrLValueRef = {1, 2, 3, 4, 5};
    #endif // SHOW_INVALID_LVALUE_REF

    for (int i = 0; i < arrRef.getLength(); i++) {
        arrRef[i] *= 2;
        std::cout << arrRef[i] << std::endl;
    }

    return 0;
}
