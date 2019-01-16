#pragma once
#include "stdafx.h"
#include <iostream>

template <typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node<T>(const T& _data, Node<T>* _next = nullptr)
	{
		this->data = _data;
		this->next = _next;
	};
};

template <class T>
class Queue              // first in -> first out ; 
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;
	void copy(const Queue& other);
	void erase();
public:
	Queue<T>();
	Queue<T>(const Queue& other);
	Queue<T>& operator =(const Queue& other);
	bool isEmpty()const;
	void pop();
	void push(const T& element);
	size_t getSize()const;
	const T getTop()const;
	const T getLast()const;
	~Queue();
};



	template <class T>
	void Queue<T>::copy(const Queue& other)
	{
		Node<T>* toOtherList = other.first;
		for (size_t i = 0; i < other.size; i++)
		{
			this->push(toOtherList);
			toOtherList = toOtherList->next;
		}
	}
	template <class T>
	void Queue<T>::erase()
	{
		while (!this->isEmpty())
		{
			this->pop();
		}
	}
	template <class T>
	Queue<T>::Queue<T>()
	{
		this->size = 0;
		this->first = nullptr;
		this->last = nullptr;
	}
	template <class T>
	Queue<T>::Queue<T>(const Queue& other)
	{
		this->copy(other);
	}
	template <class T>
	Queue<T>& Queue<T>::operator =(const Queue& other)
	{
		if (this != &other)
		{
			this->erase();
			this->copy(other);
		}
		return *this;
	}
	template <class T>
	bool Queue<T>::isEmpty()const
	{
		return !this->size;
	}
	template <class T>
	void Queue<T>::pop()
	{
		if (!this->isEmpty())
		{
			Node<T>* toBeRemoved = this->first;
			this->first = this->first->next;
			delete toBeRemoved;
			this->size--;
		}
	}
	template <class T>
	void Queue<T>::push(const T& element)
	{
		Node<T>* toBeAdd = new Node<T>(element);
		if (this->isEmpty())
		{
			this->first = toBeAdd;
		}
		else
		{
			this->last->next = toBeAdd;
		}
		this->last = toBeAdd;
		this->size++;
	}
	template <class T>
	size_t Queue<T>::getSize()const
	{
		return this->size;
	}
	template <class T>
	const T Queue<T>::getTop()const
	{
		if (!this->isEmpty())
		{
			return this->first->data;
		}

		throw "Empty list";
	}
	template <class T>
	const T Queue<T>::getLast()const
	{
		if (!this->isEmpty())
		{
			return this->last->data;
		}

		throw "Empty list";
	}
	template <class T>
	Queue<T>::~Queue()
	{
		this->erase();
	}

