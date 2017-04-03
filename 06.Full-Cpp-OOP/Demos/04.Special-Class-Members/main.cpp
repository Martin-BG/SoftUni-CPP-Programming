#include<iostream>

class SpecialMethodCallPrinter {
    std::string name;
public:
    SpecialMethodCallPrinter(std::string name) :
        name(name){
        std::cout << this->name << " Constructor" << std::endl;
    }

    SpecialMethodCallPrinter() :
        name("defaultObj") {
        std::cout << this->name << " Default Constructor" << std::endl;
    }

    SpecialMethodCallPrinter(const SpecialMethodCallPrinter& other) {
        this->name = other.name + "(copy)";
        std::cout << this->name << " Copy Constructor" << std::endl;
    }

    SpecialMethodCallPrinter& operator=(SpecialMethodCallPrinter& other) {
        this->name = other.name + "(copy-assigned)";
        std::cout << this->name << " Copy-Assignment Operator" << std::endl;
    }

    ~SpecialMethodCallPrinter() {
        std::cout << this->name << " Destructor" << std::endl;
    }
};

SpecialMethodCallPrinter f(SpecialMethodCallPrinter parameterCopy) {
    std::cout << "... in function..." << std::endl;

    return parameterCopy;
}

int main() {
    SpecialMethodCallPrinter defaultObj;

    // Uncomment these to see copy-assignment. It doesn't happen in the other code - even though it has = operators -
    // because those assignments are equivalent to initializations (notice the objects are declared and directly set a value):
    //SpecialMethodCallPrinter defaultObjCopyAssigned("copy-assigned-obj");
    //defaultObjCopyAssigned = defaultObj;

    SpecialMethodCallPrinter parameter("parameter");
    SpecialMethodCallPrinter parameterCopyCopy = f(parameter);

    return 0;
}
