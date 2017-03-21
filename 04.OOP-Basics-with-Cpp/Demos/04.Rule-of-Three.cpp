#include<iostream>
using namespace std;

/// NOTE: This is not a thread-safe and exception-safe implementation of the Rule of Three

class SmartArray {
private:
    int * data;
    int currentSize;

public:
    SmartArray() :
        data(new int[0]),
        currentSize(0) {
    }

    // copy constructor - initializes SmartArray with a copy of another object
    SmartArray(const SmartArray& other) :
        data(new int[other.currentSize]),
        currentSize(other.currentSize) {
        this->copyDataFrom(other.data, currentSize);
    }

    // destructor - releases the memory when a SmartArray object goes out of scope
    ~SmartArray() {
        // delete the internal data array
        delete[] data;
    }

    // copy-assignment operator - assigns this SmartArray by copying the value of
    // another array. Note that unlike the copy-constructor, here we could already
    // have some memory allocated for this object, so we first need to free that and
    // THEN copy the other object's data
    SmartArray& operator= (const SmartArray& other) {
        // NOTE: the standard says that self-assignment should do nothing,
        // that's why we check if other's memory address is different
        // than this' memory address, and only do the copy then
        if (this != &other) {
            delete[] this->data;

            this->currentSize = other.currentSize;
            this->data = new int[other.currentSize];

            this->copyDataFrom(other.data, other.currentSize);
        }

        return *this;
    }

    int getSize() {
        return this->currentSize;
    }

    void changeSize(int newSize) {
        int * oldData = this->data;
        // NOTE: using () after the brackets initializes the int array with 0. This is specific syntax only for initializing arrays with new. So this would make the array have 0s as elements for int
        this->data = new int[newSize]();
        this->copyDataFrom(oldData, currentSize);
        this->currentSize = newSize;
        delete[] oldData;
    }

    void setElement(int index, int value) {
        if (index < this->currentSize) {
            this->data[index] = value;
            return;
        }
        // Cause a crash so the programmer knows illegal access was attempted (we'll discuss how to handle these in code in another lecture)
        throw "index out of bounds";
    }

    int getElement(int index) {
        if (index < this->currentSize) {
            return this->data[index];
        }
        // Cause a crash so the programmer knows illegal access was attempted (we'll discuss how to handle these in code in another lecture)
        throw "index out of bounds";
    }

private:
    void copyDataFrom(int * source, int sourceSize) {
        for (int i = 0; i < this->currentSize && i < sourceSize; i++) {
            this->data[i] = source[i];
        }
    }
};

SmartArray multiplyBy2(SmartArray arr) {
    for(int i = 0; i < arr.getSize(); i++) {
        arr.setElement(i, 2 * arr.getElement(i));
    }

    return arr;
}

int main() {
    SmartArray arr;
    arr.changeSize(3);
    arr.setElement(0, 13);
    arr.setElement(1, 42);
    arr.setElement(2, 69);

    cout << arr.getElement(0) << endl;
    cout << arr.getElement(1) << endl;
    cout << arr.getElement(2) << endl;

    SmartArray multiplied = multiplyBy2(arr);

    cout << multiplied.getElement(0) << endl;
    cout << multiplied.getElement(1) << endl;
    cout << multiplied.getElement(2) << endl;

    return 0;
}
