#include<iostream>

typedef int T;
class LinkedList {
    class Node {
    public:
        T value;
        Node * next;

        Node(T value, Node * next) :
            value(value),
            next(next) {
        }

        Node(T value) :
            value(value),
            next(nullptr) {
        }

        void setNext(Node * n) {
            this->next = n;
        }
    };

    Node * head;
    Node * tail;
    size_t numItems;
public:
    class Iterator {
        Node* current;
    public:
        Iterator(Node* start) :
            current(start) {
        }

        Iterator& operator++() {
            this->current = this->current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return this->current != other.current;
        }

        T& operator*() {
            return current->value;
        }
    };

    LinkedList() :
        head(nullptr),
        tail(nullptr),
        numItems(0) {
    }

    Iterator begin() {
        return Iterator(this->head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    void add(T value) {
        Node * newNode = new Node(value);

        if (this->numItems > 0) {
            tail->setNext(newNode);
            tail = newNode;
        } else {
            head = newNode;
            tail = newNode;
        }

        this->numItems++;
    }

    size_t getSize() {
        return this->numItems;
    }
};

int main() {
    LinkedList myList;

    myList.add(13);
    myList.add(42);
    myList.add(69);

    for (int& value : myList) {
        value = 1;
    }

    for (int& value : myList) {
        std::cout << value << std::endl;
    }

    std::cout << myList.getSize() << std::endl;

    return 0;
}
