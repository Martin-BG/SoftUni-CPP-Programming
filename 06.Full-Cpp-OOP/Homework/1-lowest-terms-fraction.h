#include<ostream>
#include<istream>

class Fraction {
protected:
    int m_nominator;
    int m_denominator;

public:
    Fraction();

    Fraction(int nominator, int denominator);

    friend std::ostream& operator<<(std::ostream& stream, const Fraction &fraction);
    friend std::istream& operator>>(std::istream& stream, Fraction &fraction);

    friend Fraction operator+(const Fraction &a, const Fraction &b);

    // NOTE: this is the prefix ++, i.e. ++f
    Fraction& operator++();

    Fraction operator++(int);
};

Fraction::Fraction() :
    m_nominator(0),
    m_denominator(0) {
}

Fraction::Fraction(int nominator, int denominator) :
    m_nominator(nominator),
    m_denominator(denominator) {
}

// NOTE: this is the prefix ++, i.e. ++f
Fraction& Fraction::operator++() {
    (*this) = (*this) + Fraction(1, 1);
    return *this;
}

Fraction Fraction::operator++(int) {
    Fraction valueBeforeIncrement = *this;
    ++(*this);
    return valueBeforeIncrement;
}

Fraction operator+(const Fraction &a, const Fraction &b) {
    if (a.m_denominator == b.m_denominator) {
        return Fraction(a.m_nominator + b.m_nominator, a.m_denominator);
    } else {
        int commonDenominator = a.m_denominator * b.m_denominator;
        return Fraction(a.m_nominator * b.m_denominator + b.m_nominator * a.m_denominator, commonDenominator);
    }
}

std::ostream& operator<<(std::ostream& stream, const Fraction &fraction) {
    if (fraction.m_nominator == 0 && fraction.m_denominator == 0) {
        stream << "NaN";
    } else {
        stream << fraction.m_nominator << "/" << fraction.m_denominator;
    }

    return stream;
}

std::istream& operator>>(std::istream& stream, Fraction &fraction) {
    stream >> fraction.m_nominator;
    char slash;
    stream >> slash;
    stream >> fraction.m_denominator;

    return stream;
}

