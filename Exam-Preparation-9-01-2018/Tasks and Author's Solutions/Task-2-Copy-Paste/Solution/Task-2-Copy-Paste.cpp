#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

int getWordBegin(string text, int index) {
    while(index - 1 >= 0 && isalpha(text[index - 1])) {
        index--;
    }

    return index;
}

int getWordEnd(string text, int index) {
    // NOTE: no +1 on index because we use end as exclusive

    while(index <= text.size() && isalpha(text[index])) {
        index++;
    }

    return index;
}

int main() {
    string text;
    getline(cin, text);

    stack<string> clipboard;
    string command;
    getline(cin, command);
    while (command != "end") {
        istringstream commandIn(command);

        string action;
        commandIn >> action;

        if (action == "copy") {
            int from, to;
            commandIn >> from >> to;

            int beginInd = getWordBegin(text, from);
            int endInd = getWordEnd(text, to);

            clipboard.push(text.substr(beginInd, endInd - beginInd));
        } else if (action == "paste" && !clipboard.empty()) {
            int position;
            commandIn >> position;

            string pasteText = clipboard.top();
            clipboard.pop();
            if (!isalpha(text[position])) {
                pasteText = string(" ") + pasteText;
            }

            text.insert(position, pasteText);
        }

        getline(cin, command);
    }

    cout << text << endl;

    return 0;
}
