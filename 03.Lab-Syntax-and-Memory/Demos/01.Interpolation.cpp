#include<iostream>
using namespace std;

int* getSamples(int data[], int dataSize, int numSamples) {
    int* result = new int[numSamples];

    if (numSamples == 0) {
        return result;
    }

    double step = dataSize / (double)numSamples;

    int posInResult = 0;
    for (double pos = 0; pos < dataSize; pos += step) {
        int actualPos = (int)pos;

        result[posInResult] = data[actualPos];
        posInResult++;
    }

    return result;
}

bool test() {
    int testData[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int* actualResult = getSamples(testData, 13, 5);
    bool actualEqualsExpected =
        actualResult[0] == 0
        && actualResult[1] == 2
        && actualResult[2] == 5
        && actualResult[3] == 7
        && actualResult[4] == 10;

    return actualEqualsExpected;
}

int main() {
    int testData[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    int* samples = getSamples(testData, 13, 5);

    for(int i = 0; i < 5; i++) {
        cout << samples[i] << endl;
    }

    delete[] samples;
    samples = getSamples(testData, 13, 10);
    for(int i = 0; i < 5; i++) {
        cout << samples[i] << endl;
    }


    return 0;
}
