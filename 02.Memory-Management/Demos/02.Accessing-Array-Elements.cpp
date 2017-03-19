#include<iostream>
#include<cmath>

int main() {
    double vector2d[2] = {};
    std::cin >> vector2d[0] >> vector2d[1];
    double length = sqrt(vector2d[0] * vector2d[0] + vector2d[1] * vector2d[1]);
    vector2d[0] /= length;
    vector2d[1] /= length;

    std::cout << vector2d[0] << " " << vector2d[1] << std::endl;

    return 0;
}
