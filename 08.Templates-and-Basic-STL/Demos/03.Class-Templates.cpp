#include <iostream>
#include <cmath>

template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair(T1 first, T2 second) :
        first(first),
        second(second) {
    }
};

Pair<double, double> solveQuadraticEquation(double a, double b, double c) {
    double d = b * b - 4 * a * c;

    // https://en.wikipedia.org/wiki/Quadratic_formula
    return Pair<double, double>((-b + sqrt(d)) / (2 * a),
                (-b - sqrt(d)) / (2 * a));
}

int main() {
    using std::cout;
    using std::endl;

    Pair<double, double> roots = solveQuadraticEquation(2, 5, 2);
    cout << "2*x*x + 5*x - 2:" << endl
        << "x1 = " << roots.first << endl
        << "x2 = " << roots.second << endl;

    return 0;
}
