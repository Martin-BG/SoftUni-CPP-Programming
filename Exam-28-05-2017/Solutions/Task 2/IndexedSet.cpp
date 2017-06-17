#include "IndexedSet.h"

IndexedSet::IndexedSet() :
	valuesSet(),
	valuesArray(nullptr)
{
}

IndexedSet::IndexedSet(const IndexedSet& other):
	valuesSet(),
	valuesArray(nullptr)
{
	for (auto value : other.valuesSet)
	{
		this->valuesSet.insert(value);
	}
}

void IndexedSet::add(const Value& v)
{
	this->valuesSet.insert(v);
}

size_t IndexedSet::size() const
{
	return this->valuesSet.size();
}

const Value& IndexedSet::operator[](size_t index)
{
	if (this->valuesArray == nullptr)
	{
		this->buildIndex();
	}

	return this->valuesArray[index];
}

IndexedSet& IndexedSet::operator=(const IndexedSet& other)
{
	if (this != &other)
	{
		if (this->valuesSet.size() > 0)
		{
			this->valuesSet.erase(this->valuesSet.begin(), this->valuesSet.end());
			this->clearIndex();
		}

		for (auto value : other.valuesSet)
		{
			this->valuesSet.insert(value);
		}
	}

	return *this;
}

IndexedSet::~IndexedSet()
{
	this->clearIndex();
}

// Optional
void IndexedSet::buildIndex()
{
	if (this->valuesArray == nullptr)
	{
		this->clearIndex();
		this->valuesArray = new Value[this->valuesSet.size()];
		int index = 0;
		for (Value value : this->valuesSet)
		{
			this->valuesArray[index++] = value;
		}
	}
}

void IndexedSet::clearIndex()
{
	delete[] this->valuesArray;
	this->valuesArray = nullptr;
}