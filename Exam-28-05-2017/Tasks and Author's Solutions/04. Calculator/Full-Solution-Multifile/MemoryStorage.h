#ifndef MEMORY_STORAGE_H
#define MEMORY_STORAGE_H

#include <memory>
#include <stack>
#include <string>

#include "InputInterpreter.h"
#include "CalculationEngine.h"

#include "Operation.h"

class MemoryStorage : public Operation {
    std::stack<int> memory;
public:
    void addOperand(int operand) override {
        this->memory.push(operand);
    }

    bool isCompleted() override {
        return false;
    }

    int getResult() override {
        int memoryTop = this->memory.top();
        this->memory.pop();
        return memoryTop;
    }
};

#endif // MEMORY_STORAGE_H
