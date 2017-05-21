#ifndef LIST_H
#define LIST_H

#include<string>

template <typename T> class List
{
public:
    class Iterator;
private:
    class Node
    {
    private:
        T m_value;
        Node *m_prev;
        Node *m_next;
        friend class Iterator;
    public:
        Node(const T &value, Node *prev, Node *next) :
            m_value(value),
            m_prev(prev),
            m_next(next)
        {}

        Node(const T &value) :
            m_value(value),
            m_prev(nullptr),
            m_next(nullptr)
        {}

        Node(const Node &other) = delete;

        Node& operator=(const Node &other) = delete;

        ~Node()
        {
            if (this->m_prev != nullptr)
            {
                this->m_prev->setNext(this->m_next);
            }

            if (this->m_next != nullptr)
            {
                this->m_next->setPrev(this->m_prev);
            }
        }

        T getValue() const
        {
            return this->m_value;
        }

        void setValue(const T &value)
        {
            this->m_value = value;
        }

        Node* getNext() const
        {
            return this->m_next;
        }

        void setNext(Node *next)
        {
            this->m_next = next;
        }

        Node* getPrev() const
        {
            return this->m_prev;
        }

        void setPrev(Node *prev)
        {
            this->m_prev = prev;
        }
    };

    Node *m_head;
    Node *m_tail;
    size_t m_size;
public:
    class Iterator
    {
    private:
        Node *m_current;
    public:
        Iterator(Node *start) :
            m_current(start)
        {}

        Iterator& operator++()
        {
            this->m_current = this->m_current->getNext();
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return this->m_current != other.m_current;
        }

        T& operator*()
        {
            return this->m_current->m_value;
        }
    };

    Iterator begin()
    {
        return Iterator(this->m_head);
    }

    Iterator begin() const
    {
        return Iterator(this->m_head);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

    List() :
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0)
    {}

    List(const List &other) : List()
    {
        addAll(other);
    }

    List& operator=(const List &other)
    {
        if (this != &other)
        {
            removeAll();

            addAll(other);
        }

        return *this;
    }

    List(std::initializer_list<T> initList) : List()
    {
        for(T item: initList)
        {
            this->add(item);
        }
    }

    List(List &&other) :
        m_head(other.m_head),
        m_tail(other.m_tail),
        m_size(other.m_size)
    {
        std::cout << "move ctor" << std::endl;

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    List& operator=(List &&other)
    {
        std::cout << "move assignment" << std::endl;
        if (this != &other)
        {
            removeAll();

            this->m_head = other.m_head;
            this->m_tail = other.m_tail;
            this->m_size = other.m_size;

            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }

        return *this;
    }

    ~List()
    {
        removeAll();
    }

    List& operator<<(const T& value)
    {
        this->add(value);

        return *this;
    }

    List& operator<<(const List& other)
    {
        this->addAll(other);

        return *this;
    }

    void add(const T &value)
    {
        Node* newNode = new Node(value);

        if (this->m_size > 0)
        {
            this->m_tail->setNext(newNode);
            this->m_tail = newNode;
        }
        else
        {
            this->m_head = newNode;
            this->m_tail = newNode;
        }

        this->m_size++;
    }

    size_t getSize() const
    {
        return this->m_size;
    }

    void removeAll()
    {
        Node *node = this->m_head;
        Node *to_delete = nullptr;

        while (node != nullptr)
        {
            to_delete = node;
            node = node->getNext();
            delete to_delete;
        }

        this->m_head = nullptr;
        this->m_tail = nullptr;

        this->m_size = 0;
    }

    void addAll(const List &other)
    {
        for (auto value : other)
        {
            add(value);
        }
    }
};

#endif // LIST_H
