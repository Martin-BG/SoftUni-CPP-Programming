#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int distance(int a, int b) {
    return std::abs(a - b);
}

int main() {
    int extremesDist;
    cin >> extremesDist;

    int numValues;
    cin >> numValues;

    vector<int> values;
    for (int i = 0; i < numValues; i++) {
        int value;
        cin >> value;
        values.push_back(value);
    }

    /// NOTE: you could do this with std::min and std::max instead
    int minValue = values[0],
        maxValue = values[0];
    for (int value : values) {
        if (value < minValue) {
            minValue = value;
        }

        if (value > maxValue) {
            maxValue = value;
        }
    }

    int sum = 0;
    int numActual = 0;
    for (int value : values) {
        if (distance(value, minValue) > extremesDist
            && distance(value, maxValue) > extremesDist) {
            sum += value;
            numActual++;
        }
    }

    cout << sum / ((double) numActual) << endl;

    return 0;
}
