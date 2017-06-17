#ifndef ADVANCED_COMMAND_INTERFACE_H
#define ADVANCED_COMMAND_INTERFACE_H

#include <string>
#include <memory>
#include "CommandInterface.h"
#include "CutTransform.h"
#include "PasteTransform.h"

class AdvancedCommandInterface : public CommandInterface {
public:
    AdvancedCommandInterface(std::string& text) : CommandInterface{text} {}

    virtual std::vector<Command> initCommands() override {
        std::vector<Command> commands = CommandInterface::initCommands();

        auto cutTransform = std::make_shared<CutTransform>();
        auto pasteTransform = std::make_shared<PasteTransform>(cutTransform);

        commands.push_back(Command("cut", cutTransform));
        commands.push_back(Command("paste", pasteTransform));

        return commands;
    }
};

#endif // ADVANCED_COMMAND_INTERFACE_H
