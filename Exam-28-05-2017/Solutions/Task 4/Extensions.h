#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <memory>
#include <vector>
#include <stack>

#include "InputInterpreter.h"
#include "CalculationEngine.h"

class MemoryStore : public Operation
{
	std::shared_ptr<std::stack<int> > pointer_memory_store;
	std::vector<int> operands;
	int result;
public:
	MemoryStore(std::shared_ptr<std::stack<int> > pointer_memory_store) :
		pointer_memory_store(pointer_memory_store)
	{}

	void addOperand(int operand) override
	{
		this->operands.push_back(operand);

		if (this->isCompleted())
		{
			this->pointer_memory_store->push(this->operands[0]);
		}
	}

	bool isCompleted() override
	{
		return this->operands.size() == 1;
	}

	int getResult() override
	{
		return this->operands[0];
	}
};

class DummyOperation : public Operation
{
	std::vector<int> operands;
	int result;
public:
	void addOperand(int operand) override
	{
		this->operands.push_back(operand);

		if (this->isCompleted())
		{
			this->result = this->operands[0];
		}
	}

	bool isCompleted() override
	{
		return this->operands.size() == 1;
	}

	int getResult() override
	{
		return this->result;
	}
};
class DivisionOperation : public Operation
{
	std::vector<int> operands;
	int result;
public:
	void addOperand(int operand) override
	{
		this->operands.push_back(operand);

		if (this->isCompleted())
		{
			this->result = this->operands[0] / this->operands[1];
		}
	}

	bool isCompleted() override
	{
		return this->operands.size() == 2;
	}

	int getResult() override
	{
		return this->result;
	}
};

class AdvancedInputInterpreter : public InputInterpreter
{
public:
	const std::shared_ptr<std::stack<int> > memory = std::make_shared<std::stack<int> >();
	AdvancedInputInterpreter(CalculationEngine& engine) : InputInterpreter(engine)
	{}
	
	virtual std::shared_ptr<Operation> getOperation(std::string operation) override
	{
		if (operation == "*")
		{
			return std::make_shared<MultiplicationOperation>();
		}
		else if (operation == "/")
		{
			return std::make_shared<DivisionOperation>();
		}
		else if(operation == "ms")
		{
			return std::make_shared<MemoryStore>(memory);
		}
		else if (operation == "mr")
		{
			interpret(std::to_string(memory->top()));
		    memory->pop();

			return std::make_shared<DummyOperation>();
		}

		return std::shared_ptr<Operation>(nullptr);
	}
};

std::shared_ptr<InputInterpreter> buildInterpreter(CalculationEngine& engine) {
    return std::make_shared<AdvancedInputInterpreter>(engine);
}

#endif // EXTENSIONS_H
