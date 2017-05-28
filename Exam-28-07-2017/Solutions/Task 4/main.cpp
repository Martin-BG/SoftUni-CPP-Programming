#include <iostream>
#include <sstream>
#include <string>

#include "CalculationEngine.h"
#include "InputInterpreter.h"

#include "Extensions.h"

int main() {
    std::string input;

    CalculationEngine engine;
    std::shared_ptr<InputInterpreter> interpreter = buildInterpreter(engine);
    while (std::cin >> input) {
        if (input == "end") {
            break;
        } else {
            interpreter->interpret(input);
        }
    }

    std::cout << engine.getCurrentResult() << std::endl;

    return 0;
}
