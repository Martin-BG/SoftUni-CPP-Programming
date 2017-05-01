#include <iostream>

int calcPercentage(int a, int b) {
    return (a * 100) / b;
}

double calcPercentage(double a, double b) {
    return (a * 100) / b;
}

int main() {
    std::cout << "5 out of 10 = " << calcPercentage(5, 10) << "%" << std::endl;
    std::cout << "1.2 out of 4.8 = " << calcPercentage(1.2, 4.8) << "%" << std::endl;
    std::cout << "5 out of 4 = " << calcPercentage(5, 4) << "%" << std::endl;

    return 0;
}
