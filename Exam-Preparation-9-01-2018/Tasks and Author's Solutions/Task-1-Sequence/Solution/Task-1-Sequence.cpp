#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int numValues;
    cin >> numValues;

    int lastValue;
    cin >> lastValue;
    int maxIncreasingSequence = 1;
    int currentIncreasingSequence = 1;

    for (int i = 1; i < numValues; i++) {
        int value;
        cin >> value;

        if (value > lastValue) {
            currentIncreasingSequence++;

            if (currentIncreasingSequence > maxIncreasingSequence) {
                maxIncreasingSequence = currentIncreasingSequence;
            }
        } else {
            currentIncreasingSequence = 1;
        }

        lastValue = value;
    }

    cout << maxIncreasingSequence << endl;
}
