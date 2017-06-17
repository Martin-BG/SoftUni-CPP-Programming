#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class MessageRelevance {
public:
    string message;
    int relevance;

    MessageRelevance(const string& message, int relevance) : message{message}, relevance{relevance} {
    }

    bool operator>(const MessageRelevance& other) const {
        return this->relevance > other.relevance;
    }
};

int calculateRelevance(const string& message, const string& queryWord) {
    // NOTE: this approach will actually be slower than just doing consecutive string.find() operations and
    // incrementing until we get .end() - but it is a bit more readable.
    istringstream messageStream(message);

    vector<string> messageWords;
    string word;
    while(messageStream >> word) {
        messageWords.push_back(word);
    }

    int relevance = count(messageWords.begin(), messageWords.end(), queryWord);

    return relevance;
}

int main() {
    cin.sync_with_stdio(false);
    string query;
    getline(cin, query);

    string pageSizeLine;
    getline(cin, pageSizeLine);
    int pageSize;
    istringstream(pageSizeLine) >> pageSize;

    // We keep a priority queue, in which the "top" element is actually the lowest priority - that way we can add to
    // the queue and if it gets bigger than the page size, we just remove the "top" element (which a priority queue
    // does fast) and we're left with elements which are higher priority than it. At the end the queue will contain at
    // most pageSize elements, and those will be the highest-relevance (priority) elements of all the input.
    // A priority queue would use std::less to order largest element on top, so by using std::greater we make the
    // smallest element go on top. This whole concept matches the author's solution for JA3-Task-3-Minerals
    priority_queue<MessageRelevance, vector<MessageRelevance>, greater<MessageRelevance> > topMessagesByMinRelevance;

    string message;
    getline(cin, message);
    while (message != ".") {
        int relevance = calculateRelevance(message, query);

        if (relevance > 0) {
            topMessagesByMinRelevance.push(MessageRelevance(message, relevance));

            if (topMessagesByMinRelevance.size() > pageSize) {
                topMessagesByMinRelevance.pop();
            }
        }

        getline(cin, message);
    }

    vector<string> pageInReverse;
    while (!topMessagesByMinRelevance.empty()) {
        pageInReverse.push_back(topMessagesByMinRelevance.top().message);
        topMessagesByMinRelevance.pop();
    }

    for (int i = pageInReverse.size() - 1; i >= 0; i--) {
        cout << pageInReverse[i] << endl;
    }

    return 0;
}
