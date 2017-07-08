#ifndef MEMORY_RECALL_OPERATION
#define MEMORY_RECALL_OPERATION

#include <memory>

#include "Operation.h"
#include "MemoryStorage.h"

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

#endif // MEMORY_RECALL_OPERATION
