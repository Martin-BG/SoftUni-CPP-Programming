#ifndef EXTENDED_INTERPRETER
#define EXTENDED_INTERPRETER

#include <memory>

#include "InputInterpreter.h"
#include "CalculationEngine.h"

#include "DivisionOperation.h"
#include "MemoryStorage.h"
#include "MemoryRecallOperation.h"

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

#endif // EXTENDED_INTERPRETER
