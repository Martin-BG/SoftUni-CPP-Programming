#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

int getActualFrom(const string& text, int from) {
    while (from > 0 && isalnum(text[from - 1])) {
        from--;
    }

    return from;
}

int getActualTo(const string& text, int to) {
    while (to < text.size() - 1 && isalnum(text[to + 1])) {
        to++;
    }

    return to;
}

int main() {
    string text;

    getline(cin, text);

    string line;
    getline(cin, line);

    stack<string> clipboard;

    while(line != "end") {
        istringstream lineIn(line);

        string command;
        lineIn >> command;

        if (command == "copy") {
            int from, to;
            lineIn >> from >> to;

            from = getActualFrom(text, from);
            to = getActualTo(text, to);

            string copied = text.substr(from, 1 + (to - from));

            clipboard.push(copied);
        } else if (command == "paste" && !clipboard.empty()) {
            int position;
            lineIn >> position;
            string clipboardLast = clipboard.top();
            clipboard.pop();

            if (!isalnum(text[position])) {
                /// space
                text.insert(position, string(" ") + clipboardLast);
            } else {
                /// in word
                text.insert(position, clipboardLast);
            }
        } else if (command == "print") {
            cout << "---" << text << "---" << endl;
        }

        getline(cin, line);
    }

    cout << text << endl;

    return 0;
}
