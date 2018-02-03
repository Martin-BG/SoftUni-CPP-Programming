#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string input;

    cin >> input;

    ostringstream currentNumStream;
    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i])) {
            currentNumStream << input[i];
        } else {
            if (currentNumStream.str().empty()) {
                cout << input[i];
            } else {
                int repetitions;
                istringstream currentNumStreamIn(currentNumStream.str());
                currentNumStreamIn >> repetitions;

                cout << string(repetitions, input[i]);

                currentNumStream.clear();
                currentNumStream.str("");
            }
        }
    }

    cout << endl;

    return 0;
}
