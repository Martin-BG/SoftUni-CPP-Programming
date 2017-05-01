#include <iostream>
#include <stack>
#include <queue>

int main() {
    std::stack<int> s;
    s.push(42);
    s.push(13);
    s.push(69);
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << "------------" << std::endl;

    std::queue<int> q;
    q.push(42);
    q.push(13);
    q.push(69);
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "------------" << std::endl;

    std::priority_queue<int> priorityQ;
    priorityQ.push(42);
    priorityQ.push(13);
    priorityQ.push(69);
    while (!priorityQ.empty()) {
        std::cout << priorityQ.top() << " ";
        priorityQ.pop();
    }

    return 0;
}
