#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

const char InterferenceSymbol = '?';

double toDouble(string s) {
    istringstream sIn(s);
    double number;
    sIn >> number;
    return number;
}

int toInt(string s) {
    istringstream sIn(s);
    int number;
    sIn >> number;
    return number;
}

class Message {
private:
    string content;
    bool interference;
    int code;
public:
    Message()
    : content(""),
    interference(true),
    code(-1) {
    }

    void update(string updatedContent) {
        if (this->content.empty()) {
            this->content = string(updatedContent.size(), InterferenceSymbol);
        }

        bool interferenceRemains = false;
        for (int i = 0; i < updatedContent.size(); i++) {
            if (this->content[i] == InterferenceSymbol) {
                this->content[i] = updatedContent[i];
            }

            interferenceRemains |= this->content[i] == InterferenceSymbol;
        }

        this->interference = interferenceRemains;

        if (!this->hasInterference() && this->code == -1) {
            this->computeCodeAndMessage();
        }
    }

    bool hasInterference() const {
        return this->interference;
    }

    string getContent() const {
        return this->content;
    }

    int getCode() const {
        return this->code;
    }

private:
    int computeCodeAndMessage() {
        ostringstream codeOut;
        ostringstream messageOut;
        for (int i = 0; i < this->content.size(); i++) {
            if (isdigit(this->content[i])) {
                codeOut << this->content[i];
            } else {
                messageOut << this->content[i];
            }
        }

        this->code = toInt(codeOut.str());
        this->content = messageOut.str();
    }
};

int main() {
    map<double, Message> messagesByFreq;
    priority_queue<int> messageCodesByPriority;
    map<int, Message> messagesByCode;

    string command;
    cin >> command;

    ostringstream output;

    while (command != "end") {
        if (command == "report") {
            if (messageCodesByPriority.empty()) {
                output << "[no new messages]" << endl;
            } else {
                output << messagesByCode[messageCodesByPriority.top()].getContent() << endl;
                messageCodesByPriority.pop();
            }
        } else {
            // the command is a transmission frequency, parse it
            double freq = toDouble(command);
            // read the message from the transmission
            string messageContent;
            cin >> messageContent;

            // NOTE: getting the message as a reference, so that when we edit it, it will change the message in the map
            Message &m = messagesByFreq[freq];
            // only work with messages which haven't yet been cleared of interference (so that we don't re-add messages to the queue after they have already been cleared once)
            if (m.hasInterference()) {
                m.update(messageContent);

                if (!m.hasInterference()) {
                    messageCodesByPriority.push(m.getCode());
                    messagesByCode[m.getCode()] = m;
                }
            }
        }

        cin >> command;
    }

    cout << output.str() << endl;

    return 0;
}
