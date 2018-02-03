#include <iostream>
#include <string>
using namespace std;

int main() {
    string input;

    cin >> input;

    const int numLetters = ('z' - 'a') + 1;

    bool usedLetterCode[numLetters]{};

    for (int i = 0; i < input.size(); i++) {
        usedLetterCode[input[i] - 'a'] = true;
    }

    for (char i = 'a'; i <= 'z'; i++) {
        if (!usedLetterCode[i - 'a']) {
            cout << i;
        }
    }

    cout << endl;

    return 0;
}
