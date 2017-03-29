#include<iostream>
#include<string>
using namespace std;

int countSimilar(const string &text, const string &word, int requiredPercentage) {
    int similarWords = 0;

    int candidateStartInd = text.find(word[0]);

    while (candidateStartInd != string::npos) {
        int matches = 0;

        int candidateEndInd = candidateStartInd + word.size();
        // Ensure the found candidate position is the start of a word and that word is the same length as the search word
        if (!isalpha(text[candidateStartInd - 1])
            && (candidateEndInd == text.size() || !isalpha(text[candidateEndInd]))) {
            // Walk the word to count matches
            for (int offset = 0; offset < word.size(); offset++) {
                int checkPos = candidateStartInd + offset;
                if (checkPos >= text.size() || !isalpha(text[checkPos])) {
                    matches = 0;
                    break;
                }

                if (word[offset] == text[checkPos]) {
                    matches++;
                }
            }

            double candidatePercentage = (matches / (double)word.size()) * 100;

            if (candidatePercentage >= requiredPercentage) {
                similarWords++;
            }
        }

        candidateStartInd = text.find(word[0], candidateStartInd + 1);
    }

    return similarWords;
}

int main() {
    string text;

    getline(cin, text);

    string word;
    int matchPercentage;
    cin >> word >> matchPercentage;
    cout << countSimilar(text, word, matchPercentage) << endl;

}
