#include <iostream>
#include <map>
#include <string>

class Fraction {
public:
    int nominator;
    int denominator;

    Fraction(int nominator, int denominator) : nominator(nominator), denominator(denominator) {}

    bool operator<(const Fraction& other) const {
        return this->nominator * other.denominator < other.nominator * this->denominator;
    }
};

std::ostream& operator<<(std::ostream& stream, const Fraction& f) {
    return stream << f.nominator << "/" << f.denominator;
}

int main() {
    auto x = 1 / (double) 3;
    std::cout << x << std::endl;

    std::map<Fraction, std::string> fractionNames;
    fractionNames[Fraction(1, 2)] = "half";
    fractionNames[Fraction(1, 3)] = "a third";
    fractionNames[Fraction(1, 4)] = "a quarter";

    auto f = fractionNames.find(Fraction(1, 3));
    if (f != fractionNames.end()) {
        std::cout << f->second << std::endl;
    }

    for (auto fractionNamePair : fractionNames) {
        std::cout << fractionNamePair.first << " is " << fractionNamePair.second << std::endl;
    }

    for (std::pair<Fraction, std::string> fractionNamePair : fractionNames) {
        std::cout << fractionNamePair.first << " is " << fractionNamePair.second << std::endl;
    }

    return 0;
}
