#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "CommandInterface.h"
#include "AdvancedCommandInterface.h"

#include <memory>
#include <string>
/*
std::shared_ptr<CommandInterface> buildCommandInterface(std::string& text) {
    auto interface = std::make_shared<CommandInterface>(text);
    interface->init();
    return interface;
}
*/
std::shared_ptr<CommandInterface> buildCommandInterface(std::string& text) {
    auto interface = std::make_shared<AdvancedCommandInterface>(text);
    interface->init();
    return interface;
}

#endif // INITIALIZATION_H
