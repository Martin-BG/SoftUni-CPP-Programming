#include <iostream>
#include <vector>

template<typename T>
T calcPercentage(T a, T b) {
    return (a * 100) / b;
}

template<typename T1, typename T2> void printValues(const T1 a, const T2 b) {
    std::cout << a << " " << b << std::endl;
}

template<typename T>
void swapValues(T& a, T& b) {
    T aBeforeSwap = a;
    a = b;
    b = aBeforeSwap;
}

int main() {
    printValues("5 out of 10 = ", calcPercentage(5, 10));
    printValues("1.2 out of 4.8 = ", calcPercentage(1.2, 4.8));
    printValues("5 out of 4 = ", calcPercentage(5, 4));
    printValues("0.5 out of 1 = ", calcPercentage<double>(0.5, 1));

    int a = 13, b = 42;
    swapValues(a, b);

    printValues(a, b);

    std::vector<double> vectorA, vectorB;
    vectorA.push_back(113);
    vectorB.push_back(142);
    swapValues(vectorA, vectorB);

    printValues(vectorA[0], vectorB[0]);


    return 0;
}

