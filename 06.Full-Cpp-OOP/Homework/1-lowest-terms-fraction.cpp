/*Add operators and methods to the LowestTermsFraction class from the exercises for:
Multiplying by a number (i.e. multiplying its nominator), both a * and a *= variant.
Try to reuse the implementation of one into the other
Multiplying by another LowestTermsFraction, again - both a * and a *= variant
Dividing by a number and dividing by another LowestTermsFraction, again - as the above
Getting the reciprocal of a LowestTermsFraction (if the fraction is f, the reciprocal is 1 / f)

So, the code below should compile and run correctly:

LowestTermsFraction a, b;
cin >> a >> b;

a *= 3;
a /= 3;
a *= b;
a /= b;
LowestTermsFraction multBy3 = a * 3;
LowestTermsFraction multByB = a * b;
LowestTermsFraction divBy3 = a / 3;
LowestTermsFraction divByB = a / b;
LowestTermsFraction reciprocalA = a.getReciprocal();

cout << a << b << multBy3 << multByB << divBy3 << divByB;

If you are unsure how one of the operations should work -
check the mathematical definitions on the Internet. */

#include<iostream>
#include "1-lowest-terms-fraction.h"

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

	// Homework part
    friend LowestTermsFraction operator*(const LowestTermsFraction &a, const LowestTermsFraction &b);
    friend LowestTermsFraction operator*(const LowestTermsFraction &a, const int &b);
    LowestTermsFraction& operator*=(const LowestTermsFraction &a);
    LowestTermsFraction& operator*=(const int &a);

    friend LowestTermsFraction operator/(const LowestTermsFraction &a, const LowestTermsFraction &b);
    friend LowestTermsFraction operator/(const LowestTermsFraction &a, const int &b);
    LowestTermsFraction& operator/=(const LowestTermsFraction &a);
    LowestTermsFraction& operator/=(const int &a);

    LowestTermsFraction getReciprocal() const
    {
        return LowestTermsFraction(this->m_denominator, this->m_nominator);
    }
};

LowestTermsFraction operator+(const LowestTermsFraction &a, const LowestTermsFraction &b) {
    int lcm = leastCommonMultiple(a.m_denominator, b.m_denominator);

    return LowestTermsFraction(a.m_nominator * (lcm / a.m_denominator) + b.m_nominator * (lcm / b.m_denominator), lcm);
}

// Homework part
LowestTermsFraction operator*(const LowestTermsFraction &a, const LowestTermsFraction &b) {
    return LowestTermsFraction(a.m_nominator * b.m_nominator, a.m_denominator * b.m_denominator);
}

LowestTermsFraction operator*(const LowestTermsFraction &a, const int &b) {
    return LowestTermsFraction(a.m_nominator * b, a.m_denominator);
}

LowestTermsFraction& LowestTermsFraction::operator*=(const LowestTermsFraction &a)
{
    *this = *this * a;
    return *this;
}

LowestTermsFraction& LowestTermsFraction::operator*=(const int &a)
{
    *this = *this * a;
    return *this;
}

LowestTermsFraction operator/(const LowestTermsFraction &a, const LowestTermsFraction &b) {
    return LowestTermsFraction(a.m_nominator * b.m_denominator, a.m_denominator * b.m_nominator);
}

LowestTermsFraction operator/(const LowestTermsFraction &a, const int &b) {
    return LowestTermsFraction(a.m_nominator, a.m_denominator * b);
}

LowestTermsFraction& LowestTermsFraction::operator/=(const LowestTermsFraction &a) {
    *this = *this / a;
    return *this;
}

LowestTermsFraction& LowestTermsFraction::operator/=(const int &a) {
    *this = *this / a;
    return *this;
}

int main() {
    LowestTermsFraction a(4, 6);
    LowestTermsFraction b(3, 4);

//    LowestTermsFraction a, b;
//    std::cin >> a >> b;
    a *= 3;
    a /= 3;
    a *= b;
    a /= b;
    LowestTermsFraction multBy3 = a * 3;
    LowestTermsFraction multByB = a * b;
    LowestTermsFraction divBy3 = a / 3;
    LowestTermsFraction divByB = a / b;
    LowestTermsFraction reciprocalA = a.getReciprocal();

    std::cout << a << std::endl << b << std::endl
        << multBy3 << std::endl << multByB << std::endl
        << divBy3 << std::endl << divByB << std::endl
        << reciprocalA << std::endl;

    return 0;
}
