#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "CommandInterface.h"

#include <memory>
#include <string>


class Cut : public TextTransform
{
public:
	Cut() : clipboard() {}

	virtual void invokeOn(std::string& text, int startIndex, int endIndex) override
	{
		if (startIndex == endIndex)
		{
			this->clipboard = "";
		}
		else
		{
			std::string::iterator startIter = text.begin() + startIndex;
			std::string::iterator endIter = text.begin() + endIndex;

			this->clipboard = std::string(startIter, endIter);
			text.erase(startIter, endIter);
		}
	}

	std::string getClipboard() const
	{
		return this->clipboard;
	}

private:
	std::string clipboard;
};

class Paste : public TextTransform
{
public:
	Paste(std::shared_ptr<Cut> pointer_cut) : pointer_cut(pointer_cut) {}

	virtual void invokeOn(std::string& text, int startIndex, int endIndex) override
	{
		if (endIndex != startIndex)
		{
			text.replace(startIndex, endIndex - startIndex, pointer_cut->getClipboard());
		}
		else
		{
			text.insert(startIndex, pointer_cut->getClipboard());
		}
	}

private:
	std::shared_ptr<Cut> pointer_cut;
};

class NewCommandInterface : public CommandInterface
{
public:
	explicit NewCommandInterface(std::string& text)
		: CommandInterface(text)
	{
	}

	virtual std::vector<Command> initCommands() override
	{
		std::vector<Command> commands = CommandInterface::initCommands();

		std::shared_ptr<Cut> pointer_cut = std::make_shared<Cut>();

		commands.push_back(Command("cut", pointer_cut));
		commands.push_back(Command("paste", std::make_shared<Paste>(pointer_cut)));

		return commands;
	}

	~NewCommandInterface() = default;
};

std::shared_ptr<CommandInterface> buildCommandInterface(std::string& text)
{
	auto interface = std::make_shared<NewCommandInterface>(text);
	interface->init();
	return interface;
}
#endif // INITIALIZATION_H
