#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

template <typename KeyType>
using hashFunction = size_t(*)(const KeyType&, size_t);

template <typename KeyType, typename ValueType>
struct TableElement
{
	KeyType key;
	ValueType value;
	TableElement<KeyType, ValueType>* next;
	TableElement<KeyType, ValueType>(const KeyType& _key, const ValueType& _value, TableElement<KeyType, ValueType>* _next = nullptr)
	{
		this->key = _key;
		this->value = _value;
		this->next = _next;
	}
};
template<typename KeyType, typename ValueType>
class HashMap;

template<typename KeyType, typename ValueType>
class HashMapIterator
{
private:
	HashMap<KeyType, ValueType> **table;
	size_t size;

	size_t elementIndex;
	TableElement<KeyType, ValueType>* element;
	void findNextKeyValuePair()
	{
		if (this->element != nullptr)
		{
			return;
		}
		while (element == nullptr && elementIndex < tsize)
		{
			elementIndex++;
			if (elementIndex < tsize)
			{
				element = table[elementIndex];
			}
		}
	}
public:
	HashMapIterator<KeyType, ValueType>(TableElement<KeyType, ValueType>** _table, size_t _size, bool end = false)
	{
		this->size = _size;
		this->table = _table;
		if (end)
		{
			this->elementIndex = _size;
			this->element = nullptr;
		}
		else
		{
			this->elementIndex = 0;
			this->element = _table[0];
			this->findNextKeyValuePair();
		}
	}
	KeyType operator * ()
	{
		return this->element->key;
	}
	HashMapIterator<KeyType, ValType>& operator ++ ()
	{
		this->element = this->element->next;
		this->findNextKeyValuePair();
		return *this;
	}

	bool operator != (const HashMapIterator<KeyType, ValType>& other) const
	{
		return this->table != other.table->element || this->elementIndex != other.elementIndex || this->elemnet != other.element;
	}

};

template <typename KeyType, typename ValueType>
class HashMap
{
private:
	size_t size;
	hashFunction<KeyType> hashfn;
	TableElement<KeyType, ValueType> **table;
	TableElement<KeyType, ValueType>* locate(const KeyType& _key)const
	{
		size_t index = this->hashfn(_key, this->size);
		TableElement<KeyType, ValueType>* elementsWithIndex = this->table[index];
		while (elementsWithIndex->next != nullptr && elementsWithIndex->key != _key)
		{
			elementsWithIndex = elementsWithIndex->next;
		}
		return elementsWithIndex;
	}
public:
	HashMap(size_t _size, hashFunction<KeyType> func)
	{
		this->size = _size;
		this->hashFunction = func;
		this->table = new TableElement<KeyType, ValueType>[_size];
		for (size_t i = 0; i < _size; i++)
		{
			this->table[i] = nullptr;
		}
	}
	HashMapIterator<KeyType, ValueType> begin()
	{
		return HashMapIterator<KeyType, ValueType>(this->table, this->size);
	}
	HashMapIterator<KeyType, ValueType> end()
	{
		return HashMapIterator<KeyType, ValueType>(this->table, this->size, true);
	}
	void update(const KeyType& _key, const ValueType& _value)
	{
		TableElement<KeyType, ValueType> elementPosition = this->locate(_key);
		if (elementPosition->value == nullptr)
		{
			elementPosition->value = _value;
		}
		else
		{
			size_t index = this->hashfn(_key, this->size);
			this->table[index] = new TableElement<KeyType, ValueType>(_key, _value, this->table[index]);
		}
	}
	bool  hasKey(const KeyType& _key)const  // checks if there is element on that position
	{
		return this->locate(_key) != nullptr;
	}
	ValueType getValue(const KeyType& _key)const
	{
		TableElement<KeyType, ValueType> element = this->locate(_key);
		if (element != nullptr)
			return element->value;
		else
			throw "Access violation ";
	}
	void remove(const KeyType& _key)
	{
		size_t index = this->hashfn(_key);
		TableElement<KeyType, ValueType> element = this->table[index];
		if (element != nullptr && element->next != nullptr && element->next->key != _key)
		{
			element = element->next;
		}

		TableElement<KeyType, ValueType> toDelete = element->next;
		element->next = element->next->next;
		delete toDelete;
	}
};