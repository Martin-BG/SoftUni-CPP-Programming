#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

#include "TextTransform.h"

using TextTransformPtr = std::shared_ptr<TextTransform>;
using Command = std::pair<std::string, TextTransformPtr>;

class CommandInterface {
private:
    class ToUpperTransform : public TextTransform {
    public:
        virtual void invokeOn(std::string& text, int startIndex, int endIndex) override {
            for (int i = startIndex; i < endIndex; i++) {
                text[i] = toupper(text[i]);
            }
        }
    };

    std::map<std::string, std::shared_ptr<TextTransform> > commandTransforms;
    std::string& text;
public:
    CommandInterface(std::string& text) : text{text} {}

    void init() {
        this->commandTransforms.clear();
        for (std::pair<std::string, std::shared_ptr<TextTransform> > p : this->initCommands()) {
            commandTransforms[p.first] = p.second;
        }
    }

    void handleInput(std::string input) {
        std::istringstream parseStream(input);

        std::string commandName;
        int startInd, endInd;

        parseStream >> commandName >> startInd >> endInd;

        this->commandTransforms[commandName]->invokeOn(this->text, startInd, endInd);
    }

	virtual ~CommandInterface() = default;
	
protected:
    virtual std::vector<Command> initCommands() {
        std::vector<Command> commands;

        commands.push_back(Command("uppercase", std::make_shared<ToUpperTransform>()));

        return commands;
    }
};

#endif // COMMAND_INTERFACE_H
