#include<iostream>
using namespace std;

class SmartArray {
private:
    int * data;
    int currentSize;

public:
    SmartArray() :
        data(new int[0]),
        currentSize(0) {
    }

    void changeSize(int newSize) {
        int * oldData = this->data;
        // NOTE: using () after the brackets initializes the int array with 0. This is specific syntax only for initializing arrays with new. So this would make the array have 0s as elements for int
        this->data = new int[newSize]();
        for (int i = 0; i < newSize && i < currentSize; i++) {
            this->data[i] = oldData[i];
        }
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
};

int main() {
    return 0;
}
