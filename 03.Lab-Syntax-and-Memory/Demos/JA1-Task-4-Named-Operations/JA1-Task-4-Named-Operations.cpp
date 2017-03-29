#include<iostream>
#include<string>
#include<sstream>
using namespace std;

int countNumbers(const string& s) {
    // The input is guaranteed to start with a number, so there will always be at least 1 number -
    // we can count it directly and don't need to look at the 0th symbol in the string

    int numbers = 1;

    for (int i = 1; i < s.size(); i++) {
        if (isspace(s[i - 1]) && isdigit(s[i])) {
            numbers++;
        }
    }

    return numbers;
}

int sum(int numbers[], int startInd, int endInd) {
    int sum = 0;
    for (int i = startInd; i < endInd; i++) {
        sum += numbers[i];
    }

    return sum;
}

int average(int numbers[], int startInd, int endInd) {
    // NOTE: integer division is ok here, since the task requirements state that average should be
    // rounded-down to the nearest integer, e.g. 4.9 should be returned as 4
    return sum(numbers, startInd, endInd) / (endInd - startInd);
}

int findMin(int numbers[], int startInd, int endInd) {
    int minValue = numbers[startInd];

    for (int i = startInd + 1; i < endInd; i++) {
        if (numbers[i] < minValue) {
            minValue = numbers[i];
        }
    }

    return minValue;
}

// NOTE: we could have a single findExtreme() function and make it accept a function for comparison -
// that way we can pass a "less than" function to find min and a "more than" function to find max.
// Another approach would be to just have a bool parameter, which indicates whether we should do
// "<" or ">" comparison. The STL library actually has some functions which follow this design
int findMax(int numbers[], int startInd, int endInd) {
    int maxValue = numbers[startInd];

    for (int i = startInd + 1; i < endInd; i++) {
        if (numbers[i] > maxValue) {
            maxValue = numbers[i];
        }
    }

    return maxValue;
}

int main() {
    string numbersLine;
    // NOTE: mixing getline and cin is a bit tricky, but as long as there are no cin>> calls before the getline, we're ok. More here: http://stackoverflow.com/a/18786719
    getline(cin, numbersLine);
    // Count how many numbers were input, without parsing them.
    int numbersCount = countNumbers(numbersLine);
    // Then initialize an array big enough
    int numbers[numbersCount];
    // Then parse the numbers into the array
    istringstream numbersStream(numbersLine);
    // NOTE: we could read while the stream is valid, but we don't need to, since the input is expected
    // to be correctly formatted and we expect countNumbers to work correctly
    for (int i = 0; i < numbersCount; i++) {
        numbersStream >> numbers[i];
    }

    int namesCount;
    cin >> namesCount;
    // Input function names and the number attached to that name and store them in two "parallel" arrays,
    // i.e. the function number for the name at names[x] is functionNumberForName[x]
    string names[namesCount];
    int functionNumberForName[namesCount];
    for (int i = 0; i < namesCount; i++) {
        cin >> names[i] >> functionNumberForName[i];
    }
    // Create an array with pointers to our functions, ordered as per the task description (sum is index 0, findMax - 3)
    // This way, the values stored in functionNumberForName match the indexes of the functions here.
    // So, if names[42] == "callAverage" && functionNumberForName[42] == 1,
    // then functionsByNumber[functionNumberForName[42]] == functionsByNumber[1] == average
    int (*functionsByNumber[])(int[], int, int) = {sum, average, findMin, findMax};

    // Do the actual operations - read until we reach "end", at each step get the function we need to call
    // by finding its name's matching number and reading it from functionsByNumber
    bool endReached = false;
    ostringstream functionResultsStream;
    int operationsCount = 0;
    while (!endReached) {
        string name;
        cin >> name;

        if (name != "end") {
            operationsCount++;
            int firstInd, endInd;
            cin >> firstInd >> endInd;

            // Find the function we need to call for this line
            int functionNumberToCall;
            for (int functionNameIndex = 0; functionNameIndex < namesCount; functionNameIndex++) {
                if (name == names[functionNameIndex]) {
                    functionNumberToCall = functionNumberForName[functionNameIndex];
                }
            }

            string prefix = operationsCount == 1 ? "" : ",";
            functionResultsStream << prefix << name << "(" << firstInd << "," << endInd << ")="
                << functionsByNumber[functionNumberToCall](numbers, firstInd, endInd);
        } else {
            endReached = true;
        }
    }

    cout << "[" << operationsCount << "]" << "{" << functionResultsStream.str() << "}" << endl;

    return 0;
}
