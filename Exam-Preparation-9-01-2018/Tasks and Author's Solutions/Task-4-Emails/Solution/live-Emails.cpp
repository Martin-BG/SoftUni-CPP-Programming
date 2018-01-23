#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

using namespace std;

int getSingleNumberFromLine() {
    string line;
    getline(cin, line);

    istringstream lineIn(line);
    int x;
    lineIn >> x;

    return x;
}

int getPriority(const string& message, const string& keyword) {
    istringstream messageIn(message);

    int priority = 0;
    string word;
    while (messageIn >> word) {
        if (word == keyword) {
            priority++;
        }
    }

    return priority;
}

int main() {
    cin.sync_with_stdio(false);

    string keyword;
    getline(cin, keyword);

    int pageSize = getSingleNumberFromLine();

    string line;
    getline(cin, line);

    map<int, string> messagesByPriority;

    while (line != ".") {
        int priority = getPriority(line, keyword);

        if (priority != 0) {
            messagesByPriority[priority] = line;

            if (messagesByPriority.size() > pageSize) {
                messagesByPriority.erase(messagesByPriority.begin());
            }
        }

        getline(cin, line);
    }

    vector<string> resultReverse;
    for (auto keyValuePair : messagesByPriority) {
        resultReverse.push_back(keyValuePair.second);
    }

    for (int i = resultReverse.size() - 1; i >= 0; i--) {
        cout << resultReverse[i] << endl;
    }

    return 0;
}
