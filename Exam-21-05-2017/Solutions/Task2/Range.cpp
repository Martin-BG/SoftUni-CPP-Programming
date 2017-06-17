#include "Range.h"
#include <iostream>

Range::Range() :
	rangeFirst(0),
	rangeLength(0),
	valueCounts(new size_t[0]) {}

void Range::add(T value)
{
	int first = this->rangeFirst;
	int last = this->rangeFirst + this->rangeLength;

	if (this->empty())
	{
		first = value;
		last = value;

		this->resize(first, last);
	}
	else if (value < first || value >= last)
	{
		if (value < first)
		{
			first = value;
		}
		if (value >= last)
		{
			last = value;
		}

		this->resize(first, last);
	}

	this->valueCounts[this->getIndex(value)]++;
}

size_t Range::getCount(T value) const
{
	if (value < this->rangeFirst || value >= this->rangeFirst + this->rangeLength)
	{
		return 0;
	}

	return this->valueCounts[this->getIndex(value)];
}

bool Range::empty() const
{
	return (this->rangeLength == 0);
}

Range::Range(const Range& other):
	rangeFirst(other.rangeFirst),
	rangeLength(other.rangeLength),
	valueCounts(copyValues(other)) {}

Range& Range::operator=(const Range& other)
{
	if (this != &other)
	{
		this->clear();
		this->rangeFirst = other.rangeFirst;
		this->rangeLength = other.rangeLength;
		this->valueCounts = copyValues(other);
	}

	return *this;
}

Range::~Range()
{
	this->clear();
}

void Range::clear()
{
	delete[] this->valueCounts;
	this->rangeFirst = 0;
	this->rangeLength = 0;
	this->valueCounts = new size_t[0];
}

void Range::resize(T first, T last)
{
	size_t newLength = last - first + 1;

	size_t * newArr = new size_t[newLength]();

	for (size_t i = 0; i < newLength; i++)
	{
		newArr[i] = this->getCount(first + i);
	}

	this->clear();
	this->valueCounts = newArr;
	this->rangeFirst = first;
	this->rangeLength = newLength;
}

size_t Range::getIndex(T value) const
{
	return (value - this->rangeFirst);
}
