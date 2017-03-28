#include<iostream>
#include<cmath>
using namespace std;

namespace Math {
    int abs(int value) {
        return value < 0 ? -value : value;
    }

    namespace Geometry {
        class Vector2D {
            double x;
            double y;

            public:
            Vector2D(double x, double y) {
                this->x = x;
                this->y = y;
            }

            double length() {
                return sqrt(this->x * this->x + this->y * this->y);
            }
        };
    }
}

int main() {
    cout << abs(-13) << endl;
    cout << Math::abs(-42) << endl;

    using Math::Geometry::Vector2D;
    cout << Vector2D(1, 1).length() << endl;

    return 0;
}
