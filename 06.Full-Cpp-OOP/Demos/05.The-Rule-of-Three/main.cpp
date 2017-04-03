#include<iostream>
#include<sstream>
#include "SmartArray.h"
using std::string;

class PrimeCalculator {
    int numPrimes;
    int * primes;

public:
    PrimeCalculator(int primesToCalculate) :
        numPrimes(primesToCalculate),
        primes(new int[primesToCalculate]) {
        if (this->numPrimes > 0) {
            primes[0] = 1;

            int primeIndex = 1;
            int currentNumber = primes[primeIndex - 1] + 1;
            while(primeIndex < this->numPrimes) {
                bool isPrime = true;

                // NOTE: a more efficient method will only check against the primes calculated so far, not against all numbers
                for (int divisorCandidate = 2; divisorCandidate < currentNumber; divisorCandidate++) {
                    if (currentNumber % divisorCandidate == 0) {
                        isPrime = false;
                        break;
                    }
                }

                if (isPrime) {
                    primes[primeIndex] = currentNumber;
                    primeIndex++;
                }

                currentNumber++;
            }
        }
    }

    int getPrime(int primeIndex) {
        return this->primes[primeIndex];
    }

    int getLast() {
        return getPrime(this->numPrimes - 1);
    }

    string toString() {
        using std::ostringstream;

        ostringstream stream;
        for (int i = 0; i < this->numPrimes; i++) {
            stream << this->primes[i] << " ";
        }

        return stream.str();
    }

    //Rule of Three:
    ~PrimeCalculator() {
        delete[] this->primes;
    }

    PrimeCalculator(const PrimeCalculator& other) :
        numPrimes(other.numPrimes),
        primes(new int[other.numPrimes]) {

        this->primes = new int[this->numPrimes];
        for (int i = 0; i < this->numPrimes; i++) {
            this->primes[i] = other.primes[i];
        }
    }

    PrimeCalculator& operator=(const PrimeCalculator& other) {
        if(this != &other) {
            delete[] this->primes;

            this->numPrimes = other.numPrimes;
            this->primes = new int[this->numPrimes];
            for (int i = 0; i < this->numPrimes; i++) {
                this->primes[i] = other.primes[i];
            }
        }

        return *this;
    }
};

PrimeCalculator getPrimesSmallerThan(int number) {
    int guessPrimes = 1;

    PrimeCalculator lastPrimes(guessPrimes);

    bool foundAllSmaller = true;
    if (lastPrimes.getLast() > number) {
        return PrimeCalculator(0);
    } else {
        foundAllSmaller = false;
    }

    // NOTE: again, this is an inefficient way of calculating primes, but the purpose of the demo is not to calculate
    // primes, but do demonstrate the Rule of Three. And inefficient approaches illustrate the need for
    // Rule of Three better (and keep the code simpler)
    while(!foundAllSmaller) {
        guessPrimes += 1;

        PrimeCalculator newGuess(guessPrimes);
        if (newGuess.getLast() > number) {
            foundAllSmaller = true;
        } else {
            lastPrimes = newGuess;
        }
    }

    return lastPrimes;
}

int main() {
    using std::cout;
    using std::endl;

    cout << "first 10 primes:" << endl;
    cout << PrimeCalculator(10).toString() << endl;

    cout << "primes smaller than the number 42:" << endl;
    cout << getPrimesSmallerThan(42).toString() << endl;

    // this should print the first 10000 primes... if you're patient enough
    cout << "primes smaller than the number " << 104729 + 1 << ":"<< endl;
    cout << getPrimesSmallerThan(104729 + 1).toString() << endl;

    return 0;
}
