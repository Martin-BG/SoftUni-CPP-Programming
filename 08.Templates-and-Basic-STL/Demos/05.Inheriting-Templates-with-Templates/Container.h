#ifndef CONTAINER_H
#define CONTAINER_H

#include<cstddef>
#include<string>

template<typename T>
class Container {
public:
    virtual size_t getLength() = 0;
    virtual void add(T value) = 0;
    virtual std::string toString() = 0;

    virtual ~Container() {
    }
};

#endif // CONTAINER_H
