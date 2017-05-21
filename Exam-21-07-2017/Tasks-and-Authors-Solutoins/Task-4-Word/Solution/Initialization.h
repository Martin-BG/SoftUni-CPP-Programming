#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <string>
#include <memory>
#include "CommandInterface.h"
#include "TextTransform.h"

class CutTransform : public TextTransform {
    std::string lastCut;
public:
    void invokeOn(std::string& text, int startInd, int endInd) override {
        // NOTE: this can be done with indices instead of iterators, but the author wants to show another approach to working with strings
        std::string::iterator startIter = text.begin() + startInd;
        std::string::iterator endIter = text.begin() + endInd;

        this->lastCut = std::string(startIter, endIter);
        text.erase(startIter, endIter);
    }

    std::string getLastCut() {
        return this->lastCut;
    }
};

class PasteTransform : public TextTransform {
    std::shared_ptr<CutTransform> cutTransform;
public:
    PasteTransform(std::shared_ptr<CutTransform> cutTransform) : cutTransform{cutTransform} {}

    void invokeOn(std::string& text, int startInd, int endInd) override {
        // NOTE: this can be done with indices instead of iterators, but the author wants to show another approach to working with strings
        std::string::iterator startIter = text.begin() + startInd;
        std::string::iterator endIter = text.begin() + endInd;

        text.replace(startIter, endIter, this->cutTransform->getLastCut());
    }
};

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

std::shared_ptr<CommandInterface> buildCommandInterface(std::string& text) {
    auto interface = std::make_shared<AdvancedCommandInterface>(text);
    interface->init();
    return interface;
}

#endif // INITIALIZATION_H
