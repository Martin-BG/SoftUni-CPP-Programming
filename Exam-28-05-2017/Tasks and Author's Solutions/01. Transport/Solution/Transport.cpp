#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> readNumbers(string line) {
    istringstream stream(line);

    vector<int> numbers;

    int number;
    while (stream >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

int toMinutes(int militaryTime) {
    return (militaryTime / 100) * 60 + (militaryTime % 100);
}

int calculateMinutesDiff(int militaryHoursA, int militaryHoursB) {
    return toMinutes(militaryHoursA) - toMinutes(militaryHoursB);
}

int main() {
    string inputLine;
    getline(cin, inputLine);
    vector<int> arrivalTimes = readNumbers(inputLine);

    int trainTime;
    cin >> trainTime;

    int minWaitTimeMinutes = -1;
    for (int arrivalTime : arrivalTimes) {
        int waitTimeMinutes = calculateMinutesDiff(trainTime, arrivalTime);

        if (waitTimeMinutes >= 0 &&
            (minWaitTimeMinutes == -1 || waitTimeMinutes < minWaitTimeMinutes)) {
            minWaitTimeMinutes = waitTimeMinutes;
        }
    }

    cout << minWaitTimeMinutes << endl;

    return 0;
}
