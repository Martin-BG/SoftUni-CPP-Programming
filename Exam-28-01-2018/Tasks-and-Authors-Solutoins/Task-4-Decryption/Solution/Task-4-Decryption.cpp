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
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    string knownPrefix;
    getline(cin, knownPrefix);

    unordered_map<string, vector<string> > messagesByPrefix;

    string message;
    getline(cin, message);

    while (message != "[encryptions]") {
        messagesByPrefix[message.substr(0, knownPrefix.size())].push_back(message);

        getline(cin, message);
    }

    string encryption;
    getline(cin, encryption);

    int maxMessages = 0;
    string maxMessagesEncryptedPrefix;
    unordered_map<char, char> maxMessagesDecryptionMap;

    while (encryption != "[end]") {
        unordered_map<char, char> decryptionMap;
        unordered_map<char, char> encryptionMap;

        for (int i = 0; i < encryption.size(); i++) {
            char encryptedChar = encryption[i];
            char actualChar = 'a' + i;
            decryptionMap[encryptedChar] = actualChar;
            encryptionMap[actualChar] = encryptedChar;
        }

        string encryptedPrefix = changeLetters(knownPrefix, encryptionMap);

        int numMessages = messagesByPrefix[encryptedPrefix].size();

        if (numMessages > maxMessages) {
            maxMessages = numMessages;
            maxMessagesEncryptedPrefix = encryptedPrefix;
            maxMessagesDecryptionMap = decryptionMap;
        }

        getline(cin, encryption);
    }

    for (auto message : messagesByPrefix[maxMessagesEncryptedPrefix]) {
        cout << changeLetters(message, maxMessagesDecryptionMap) << endl;
    }

    return 0;
}
