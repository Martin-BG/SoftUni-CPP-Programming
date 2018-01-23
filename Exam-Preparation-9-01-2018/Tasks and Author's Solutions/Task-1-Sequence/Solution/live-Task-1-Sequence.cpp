#include <iostream>

using namespace std;

int main() {
    int sequenceLength;
    cin >> sequenceLength;

    int maxSequence;
    int currentSequence;
    int lastNumber;

    cin >> lastNumber;
    currentSequence = 1;
    maxSequence = currentSequence;

    for (int i = 1; i < sequenceLength; i++) {
        int currentNumber;
        cin >> currentNumber;

        if (lastNumber < currentNumber) {
            currentSequence++;
        } else {
            if (maxSequence < currentSequence) {
                maxSequence = currentSequence;
            }

            currentSequence = 1;
        }

        lastNumber = currentNumber;
    }

    if (maxSequence < currentSequence) {
        maxSequence = currentSequence;
    }

    cout << maxSequence << endl;

    return 0;
}
