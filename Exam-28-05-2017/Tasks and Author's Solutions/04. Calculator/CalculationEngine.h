#ifndef CALCULATION_ENGINE_H
#define CALCULATION_ENGINE_H

#include <string>
#include <memory>

#include "Operation.h"

class CalculationEngine {
    int result;
    std::shared_ptr<Operation> currentOperation;
public:
    CalculationEngine() : result(0), currentOperation(nullptr) {}

    void pushNumber(int number) {
        if (this->currentOperation) {
            currentOperation->addOperand(number);

            if (currentOperation->isCompleted()) {
                this->result = currentOperation->getResult();
                this->currentOperation.reset();
            }
        } else {
            this->result = number;
        }
    }

    void pushOperation(std::shared_ptr<Operation> operation) {
        if (operation->isCompleted()) {
            this->pushNumber(operation->getResult());
        } else {
            this->currentOperation = operation;
            this->pushNumber(this->result);
        }
    }

    int getCurrentResult() {
        return this->result;
    }
};

#endif // CALCULATION_ENGINE_H
