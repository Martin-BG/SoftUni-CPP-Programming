#pragma once
class InputReader
{
public:
	virtual bool hasInput() = 0;
	virtual int readInputCode() = 0;

	virtual ~InputReader() {
	}
};

