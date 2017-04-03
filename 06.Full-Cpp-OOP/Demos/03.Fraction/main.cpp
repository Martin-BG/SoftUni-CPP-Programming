#include<iostream>
#include "Fraction.h"

int main() {
    Fraction a(4, 6);
    Fraction b(3, 4);

    Fraction sum = a + b;
    std::cout << sum << std::endl;

    std::cout << ++sum << std::endl;

    std::cout << sum++ << std::endl;
    std::cout << sum << std::endl;



    return 0;
}
