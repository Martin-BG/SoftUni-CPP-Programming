#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <memory>

#include "InputInterpreter.h"
#include "CalculationEngine.h"

std::shared_ptr<InputInterpreter> buildInterpreter(CalculationEngine& engine) {
    return std::make_shared<InputInterpreter>(engine);
}

#endif // EXTENSIONS_H
