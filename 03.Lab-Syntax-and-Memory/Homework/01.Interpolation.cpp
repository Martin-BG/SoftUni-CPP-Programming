#include<iostream>
using namespace std;

bool asseteArrayEquals(const int[], const int*, const int&);
int* getSamples(const int[], const int&, const int&);
bool testGetSamples();

int main() {
    testGetSamples());

    return 0;
}

int* getSamples(const int data[], const int& dataSize, const int& numSamples) {
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

bool asseteArrayEquals(const int expected[], const int* actual, const int& arraySize) {
    bool result = true;

    for (int i = 0; i < arraySize && result; i++) {
        result = expected[i] == actual[i];
    }

    return result;
}

bool testGetSamples() {
    int testData[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    bool result = true;
    int testNum = 1;

    // Test #1
    if (result) {
        int expectedArray[] {0, 2, 5, 7, 10};
        int* samples = getSamples(testData, 13, 5);

        result = asseteArrayEquals(expectedArray, samples, 5);

        delete [] samples;
    }

    // Test #2
    if (result) {
        testNum++;
        int expectedArray[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        int* samples = getSamples(testData, 13, 13);

        result = asseteArrayEquals(expectedArray, samples, 13);

        delete [] samples;
    }

    // Test #3
    if (result) {
        testNum++;
        int expectedArray[] {0, 4, 8};// 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        int* samples = getSamples(testData, 13, 3);

        result = asseteArrayEquals(expectedArray, samples, 3);

        delete [] samples;
    }

    // Test #4
    if (result) {
        testNum++;
        int expectedArray[] {0, 1, 2, 3, 5, 6, 7, 9, 10, 11};
        int* samples = getSamples(testData, 13, 10);

        result = asseteArrayEquals(expectedArray, samples, 10);

        delete [] samples;
    }

    // Test #5
    if (result) {
        testNum++;
        int expectedArray[] {0, 1, 3, 5, 7, 9, 11};
        int* samples = getSamples(testData, 13, 7);

        result = asseteArrayEquals(expectedArray, samples, 7);

        delete [] samples;
    }

    if (!result) {
        cout << "Check failed on test " << testNum << endl;
    } else {
        cout << "Test passed!" << endl;
    }

    return result;
}
