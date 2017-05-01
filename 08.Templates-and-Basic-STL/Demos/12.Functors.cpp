#include <iostream>

template<typename T>
class PrintFunctor {
    T value;
public:
    PrintFunctor(T value) : value(value) {}
    void operator()() const {
        std::cout << this->value << std::endl;
    }
};

int main() {
    PrintFunctor<int> a(13);
    PrintFunctor<std::string> b("42");

    a();
    b();

    return 0;
}
