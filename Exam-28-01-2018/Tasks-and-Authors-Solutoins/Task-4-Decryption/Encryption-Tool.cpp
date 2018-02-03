#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

string changeLetters(string s, unordered_map<char, char> letterChangeMap) {
    string changed(s.size(), ' ');
    for (size_t i = 0; i < s.size(); i++) {
        char originalChar = s[i];
        if (isalpha(originalChar)) {
            /// NOTE: we know that every char will have a matching char
            changed[i] = letterChangeMap[originalChar];
        } else {
            changed[i] = originalChar;
        }
    }

    return changed;
}

int main() {
    string message;
    getline(cin, message);

    string encryption;
    getline(cin, encryption);

    unordered_map<char, char> encryptionMap;

    for (int i = 0; i < encryption.size(); i++) {
        char encryptedChar = encryption[i];
        char actualChar = 'a' + i;
        encryptionMap[actualChar] = encryptedChar;
    }

    cout << changeLetters(message, encryptionMap) << endl;

    return 0;
}
