#pragma once
#include "stdafx.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template <typename T>

class Vector
{
private:
	T* currentData;
	size_t currentSize;
	size_t capacity;
	void resize()
	{
		this->capacity = this->capacity * 2 + 1;
		T* temp = new T[this->capacity];
		for (size_t i = 0; i < this->currentSize; i++)
		{
			temp[i] = this->currentData[i];
		}
		this->erase();
		this->currentData = temp;

	}
	void erase()
	{
		delete[] this->currentData;
	}
	void copy(const Vector& other)
	{
		this->currentData = new T[other.capacity];
		for (size_t i = 0; i < other.currentSize; i++)
		{
			this->currentData[i] = other.currentData[i];
		}
		this->currentSize = other.currentSize;
		this->capacity = other.capacity;
	}
public:
	Vector()
	{
		this->currentSize = 0;
		this->capacity = 4;
		this->currentData = new T[this->capacity];
	}
	Vector(const Vector& other)
	{
		copy(other);
	}
	Vector& operator += (const Vector& other)
	{
		T* temp = new T[this->currentSize + other.currentSize];
		for (size_t i = 0; i < this->currentSize; i++)
		{
			temp[i] = this->currentData[i];
		}
		for (size_t i = this->currentSize,j=0; i < this->currentSize + other.currentSize; i++,j++)
		{
			temp[i] = other.currentData[j];
		}
		this->erase(); 

		this->currentSize += other.currentSize;
		this->capacity +=  other.capacity; 
		this->currentData = new T[this->capacity];
		this->currentData = temp; 
		delete[] temp;

		return *this;
	}
	
	Vector& operator = (const Vector& other)
	{
		if (this != &other)
		{
			this->erase();
			this->copy(other);
		}
		return *this;
	}
	Vector operator + (const Vector& other)
	{
		Vector temp = *this;
		temp += other; 
		return temp;
	}

	~Vector()
	{
		this->erase();
	}
	void push_back(T element)
	{
		if (this->currentSize >= this->capacity)
			this->resize();
		this->currentData[currentSize++] = element;
	}
	void pop_back()
	{
		this->currentSize--;
	}
	void pop_front()
	{
		if (this->currentSize > 0)
		{
			for (size_t i = 0; i < this->currentSize - 1; i++)
			{
				this->currentData[i] = this->currentData[i + 1];
			}
			this->pop_back();
		}
	}
	size_t size()const
	{
		return this->currentSize;
	}
	size_t max_size()const
	{
		return this->capacity;
	}
	T& operator [] (size_t index) const
	{
		return this->currentData[index];
	}
	void pop(const size_t index)
	{
		if (index >= this->currentSize)
			return;
		for (size_t i = index; i < this->currentSize - 1; i++)
		{
			this->currentData[i] = this->currentData[i + 1];
		}
		this->pop_back();
	}
	void push_front(T element)
	{
		if (++this->currentSize >= this->capacity)
			this->resize();
		for (size_t i = this->currentSize; i > 0; i--)
		{
			this->currentData[i] = this->currentData[i - 1];
		}
		this->currentData[0] = element;
	}
	void push(size_t index, T element)
	{
		if (index == 0)
		{
			this->push_front(element);
		}
		else if (index == this->currentSize - 1)
		{
			this->push_back(element); 
		}
		else if (index < this->currentSize)
		{
			if (++this->currentSize >= this->capacity)
			{
				this->resize();
			}
			for (size_t i = this->currentSize; i > index + 1; i--)
			{
				this->currentData[i] = this->currentData[i - 1];
			}
			this->currentData[index] = element;
		}
	}
	bool isEmpty()const
	{
		return this->currentSize == 0; 
	}
	bool isElement(const T& data)
	{
		for (size_t i = 0; i < this->currentSize; i++)
		{
			if (this->currentData[i] == data)
				return true;
		}
		return false; 
	}

	void clear()
	{
		while(this->currentSize)
			this->pop_back(); 
	}
	friend std::ostream &operator <<(std::ostream &output, const Vector<T>&  other)
	{
		for (size_t i = 0; i < other.size(); i++)
			output << other[i] << " ";
		return output;
	}
};
