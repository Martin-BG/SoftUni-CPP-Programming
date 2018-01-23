#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string compressSequence(char letter, size_t sequenceLength) {
    ostringstream compressed;

    compressed << sequenceLength << letter;

    string compressedStr = compressed.str();

    /// NOTE: this can be simplified - if sequenceLength > 2, then compression is guaranteed to be better
    /// than the sequence - we don't need to first generate then compare if we know the sequence is
    /// 1 or 2 symbols - then we can just use the sequence
    if (compressedStr.size() < sequenceLength) {
        return compressedStr;
    } else {
        return string(sequenceLength, letter);
    }
}

string compress(string text) {
    ostringstream compressed;

    char currentSequenceLetter = text[0];
    size_t currentSequenceLength = 1;
    for (int i = 1; i < text.size(); i++) {
        if (text[i] != currentSequenceLetter) {
            compressed << compressSequence(currentSequenceLetter, currentSequenceLength);
            currentSequenceLetter = text[i];
            currentSequenceLength = 1;
        } else {
            currentSequenceLength++;
        }
    }

    compressed << compressSequence(currentSequenceLetter, currentSequenceLength);

    return compressed.str();
}

int main() {
    string text;
    getline(cin, text);

    cout << compress(text) << endl;

    return 0;
}
