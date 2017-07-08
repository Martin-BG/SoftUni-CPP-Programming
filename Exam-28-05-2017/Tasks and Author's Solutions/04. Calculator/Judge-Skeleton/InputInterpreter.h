#ifndef INPUT_INTERPRETER
#define INPUT_INTERPRETER

#include <memory>
#include <string>
#include <vector>
#include "Operation.h"
#include "CalculationEngine.h"
#include "MultiplicationOperation.h"

class InputInterpreter {
    CalculationEngine& engine;
public:
    InputInterpreter(CalculationEngine& engine) : engine(engine) {}

    bool interpret(std::string input) {
        std::istringstream numberParseStream(input);
        int number;
        if (numberParseStream >> number) {
            engine.pushNumber(number);
        } else {
            engine.pushOperation(this->getOperation(input));
        }

        return true;
    }

    virtual std::shared_ptr<Operation> getOperation(std::string operation) {
        if (operation == "*") {
            return std::make_shared<MultiplicationOperation>();
        }

        return std::shared_ptr<Operation>(nullptr);
    }
};

#endif // INPUT_INTERPRETER
