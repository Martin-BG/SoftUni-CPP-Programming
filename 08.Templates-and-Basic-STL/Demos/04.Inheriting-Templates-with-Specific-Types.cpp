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

class QuadraticRoots : public Pair<double, double> {
public:
    QuadraticRoots() :
        Pair(NAN, NAN) {
    }

    QuadraticRoots(double root1, double root2) :
        Pair(root1, root2) {
    }

    int numRealRoots() {
        if (std::isnan(this->first) && std::isnan(this->second)) {
            return 0;
        } else {
            return this->first != this->second ? 2 : 1;
        }
    }
};

// https://en.wikipedia.org/wiki/Quadratic_formula
QuadraticRoots solveQuadraticEquation(double a, double b, double c) {
    double d = b * b - 4 * a * c;

    if (d < 0) {
        return QuadraticRoots();
    }

    return QuadraticRoots((-b + sqrt(d)) / (2 * a),
                (-b - sqrt(d)) / (2 * a));
}

int main() {
    using std::cout;
    using std::endl;

    QuadraticRoots roots = solveQuadraticEquation(2, 5, 2);
    cout << "2*x*x + 5*x - 2:" << endl
        << "num roots: " << roots.numRealRoots() << endl
        << "x1 = " << roots.first << endl
        << "x2 = " << roots.second << endl;

    return 0;
}
