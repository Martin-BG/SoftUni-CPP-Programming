#ifndef DIVISION_OPERATION_H
#define DIVISION_OPERATION_H

#include <memory>
#include <vector>

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

#endif // DIVISION_OPERATION_H
