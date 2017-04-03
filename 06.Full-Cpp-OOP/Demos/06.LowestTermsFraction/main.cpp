#include<iostream>
#include "Fraction.h"

static int greatestCommonDivisor(const int &a, const int &b) {
    int divisorCand = a < b ? a : b;

    // NOTE: there is a better algorithm for gcd, but we're trying to keep things simple
    while((a % divisorCand != 0) || (b % divisorCand != 0)) {
        divisorCand--;
    }

    return divisorCand;
}

static int leastCommonMultiple(const int &a, const int &b) {
    return (a * b) / greatestCommonDivisor(a, b);
}

class LowestTermsFraction : public Fraction {
public:
    LowestTermsFraction(int nominator, int denominator) :
        Fraction(nominator / greatestCommonDivisor(nominator, denominator),
                 denominator / greatestCommonDivisor(nominator, denominator)) {
    }

    friend LowestTermsFraction operator+(const LowestTermsFraction &a, const LowestTermsFraction &b);
};

LowestTermsFraction operator+(const LowestTermsFraction &a, const LowestTermsFraction &b) {
    int lcm = leastCommonMultiple(a.denominator, b.denominator);

    return LowestTermsFraction(a.nominator * (lcm / a.denominator) + b.nominator * (lcm / b.denominator), lcm);
}

int main() {
    LowestTermsFraction a(4, 6);
    LowestTermsFraction b(3, 4);

    LowestTermsFraction sum = a + b;

    // The following operations use Fraction's operators (LowestTermsFractions is auto-cast up to a Fraction). Be
    // careful though - this doesn't pass through our LowestTermsFraction constructor which reduces the fraction
    std::cout << sum << std::endl;

    std::cout << ++sum << std::endl;

    std::cout << sum++ << std::endl;
    std::cout << sum << std::endl;

    sum = sum + LowestTermsFraction(1, 12);

    std::cout << sum << std::endl;

    return 0;
}
