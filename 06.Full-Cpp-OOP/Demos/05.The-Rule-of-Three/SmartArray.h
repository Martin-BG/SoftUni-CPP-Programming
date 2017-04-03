#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include<string>

typedef int DataType;

class SmartArray {
private:
    int length;
	DataType * data;
public:
	SmartArray();
	SmartArray(const SmartArray & other);
	SmartArray(int length);
	~SmartArray();

	DataType getElement(int index);
	void setElement(int index, DataType value);

	void changeLength(int newLength);

	std::string toString();

	SmartArray& operator=(const SmartArray & other);
	DataType& operator[](int index);

	static SmartArray fromString(std::string s);

	SmartArray& operator+=(const SmartArray& other);
private:
	void ensureIndexInBounds(int index);
	static void copyData(DataType * source, int sourceLength,
		DataType * dest, int destLength);
};

#endif // SMARTARRAY_H
