#include "List.h"
#include<sstream>

List::Node::Node(T value, Node * prev, Node * next) :
            value(value),
            prev(prev),
            next(next){}

T List::Node::getValue() const
{
	return this->value;
}

void List::Node::setValue(T value)
{
    this->value = value;
}

List::Node * List::Node::getNext() const
{
    return this->next;
}

void List::Node::setNext(Node * next)
{
    this->next = next;
}

List::Node * List::Node::getPrev() const
{
    return this->prev;
}

void List::Node::setPrev(Node * prev)
{
    this->prev = prev;
}

List::List():
    head(nullptr),
    tail(nullptr),
    size(0) {}

List::List(const List& other) :
    head(nullptr),
    tail(nullptr),
    size(0) { addAll(other); }

T List::first() const
{
	if (this->head == nullptr)
	{
		throw "Null pointer";
	}
    return this->head->getValue();
}

void List::add(T value)
{
    Node * newNode = new Node(value, this->tail, nullptr);

    if (this->size > 0)
    {
        this->tail->setNext(newNode);
        this->tail = newNode;
    }
    else
    {
        this->head = newNode;
        this->tail = newNode;
    }

    this->size++;
}

void List::addAll(const List& other)
{
    if (other.size > 0)
    {
        Node * node = other.head;
        while (node != nullptr)
        {
            add(node->getValue());
            node = node->getNext();
        }
    }
}

void List::removeFirst()
{
    Node * to_delete = this->head;

    if (to_delete != nullptr)
    {
        Node * next = to_delete->getNext();
        if (next != nullptr)
        {
            next->setPrev(nullptr);
            this->head = next;
        }

        delete to_delete;
        this->size--;

        if (this->size == 0)
        {
            this->head = nullptr;
            this->tail = nullptr;
        }
    }
}

void List::removeAll()
{
    Node * node = this->head;
    Node * to_delete = nullptr;

    while (node != nullptr)
    {
        to_delete = node;
        node = node->getNext();
        delete to_delete;
    }

    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

size_t List::getSize() const
{
    return this->size;
}

bool List::isEmpty() const
{
    return this->size == 0;
}

List List::getReversed(List l)
{
    List reversed;

    if (l.size > 0)
    {
        Node * node = l.tail;
        while (node != nullptr)
        {
            reversed.add(node->getValue());
            node = node->getPrev();
        }
    }

    return reversed;
}

std::string List::toString() const
{
    std::stringstream ss;

    Node * node = this->head;
    while (node != nullptr)
    {
        ss << node->getValue() << " ";
        node = node->getNext();
    }

    return ss.str();
}

List& List::operator<<(const T& value)
{
    bool added = false;

    if (this->head != nullptr && this->head->getValue() >= value)
    {
		Node * new_node = new Node(value, nullptr, this->head);
        this->head = new_node;
        new_node->getNext()->setPrev(new_node);
        this->size++;
        added = true;
    }
	else if (this->size > 0 && this->tail->getValue() > value )
	{
		Node * new_node = new Node(value, nullptr, nullptr);
		Node * curr_node = this->head;

		while (curr_node != nullptr)
		{
			if (curr_node->getValue() >= value)
			{
			    new_node->setPrev(curr_node->getPrev());
				curr_node->setPrev(new_node);
				new_node->setNext(curr_node);

				if (new_node->getPrev() != nullptr)
				{
					new_node->getPrev()->setNext(new_node);
				}

				added = true;

				this->size++;

				break;
			}

			curr_node = curr_node->getNext();
		}
	}

	if (!added)
	{
		this->add(value);
	}

	return *this;
}

List& List::operator<<(const List& other)
{
	this->addAll(other);
	return *this;
}

List& List::operator=(const List& other)
{
    removeAll();
    addAll(other);
    return *this;
}

List::~List()
{
    removeAll();
}
