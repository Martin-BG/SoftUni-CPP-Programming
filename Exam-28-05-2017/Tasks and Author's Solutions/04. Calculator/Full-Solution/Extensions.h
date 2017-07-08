#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <memory>
#include <stack>
#include <string>

#include "InputInterpreter.h"
#include "CalculationEngine.h"

#include "Operation.h"

class DivisionOperation : public Operation {
    std::vector<int> operands;
public:
    void addOperand(int operand) override {
        this->operands.push_back(operand);
    }

    bool isCompleted() override {
        return this->operands.size() == 2;
    }

    int getResult() override {
        return this->operands[0] / this->operands[1];
    }
};

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

class MemoryRecallOperation : public Operation {
    std::shared_ptr<MemoryStorage> memory;
public:
    MemoryRecallOperation(std::shared_ptr<MemoryStorage> memory) : memory(memory) {}

    void addOperand(int operand) {
    }

    bool isCompleted() override {
        return true;
    }

    int getResult() override {
        return this->memory->getResult();
    }
};

class ExtendedInterpreter : public InputInterpreter {
    std::shared_ptr<MemoryStorage> memory;
public:
    ExtendedInterpreter(CalculationEngine& engine) : InputInterpreter(engine) {}

    std::shared_ptr<Operation> getOperation(std::string operation) override {
        if (operation == "/") {
            return std::make_shared<DivisionOperation>();
        } else if (operation == "ms") {
            if (!memory) {
                memory = std::make_shared<MemoryStorage>();
            }

            return this->memory;
        } else if (operation == "mr") {
            return std::make_shared<MemoryRecallOperation>(this->memory);
        } else {
            return InputInterpreter::getOperation(operation);
        }
    }
};

std::shared_ptr<InputInterpreter> buildInterpreter(CalculationEngine& engine) {
    return std::make_shared<ExtendedInterpreter>(engine);
}

#endif // EXTENSIONS_H
