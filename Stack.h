#pragma once
#include "stdafx.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template<typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node<T>(const T& _data, Node<T>* _next = nullptr)
	{
		this->data = _data;
		this->next = _next;
	}

};

template<class T>
class Stack                 // first in -> last out
{
private:
	Node<T>* first;
	size_t size;
	void copy(const Stack<T>& other);
	void erase();
public:
	Stack();
	Stack(const Stack& other);
	Stack& operator = (const Stack& other);
	~Stack();
	bool empty()const;
	void pop();
	void push(const T& element);
	const T& top()const;
	size_t getSize()const;
};


	template<class T>
	void Stack<T>::copy(const Stack& other)
	{
		if (!other.first)
		{
			this->first = nullptr;
			this->size = 0;
		}
		else
		{
			this->size = other.size;
			this->first = new Node<T>(other.first->data, other.first->next);
			Node<T>* temp1 = other.first;                       // a node that will be moved around the stack
			Node<T>* temp2 = this->first;
			while (temp1->next)                  // while the 2nd Stack(from where we copy ) is not empty 
			{
				temp2->next = new Node<T>(temp1->next->data, temp2->next->next);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
	}

	template<class T>
	void Stack<T>::erase()
	{
		while (!this->empty())
		{
			this->pop();
		}
	}

	template<class T>
	Stack<T>::Stack()
	{
		this->first = nullptr;
		this->size = 0;
	}
	template<class T>
	Stack<T>::Stack(const Stack& other)
	{
		this->copy(other);
	}
	template <typename T>
	Stack<T>& Stack<T>::operator= (const Stack<T>& other)
	{
		if (this != &other)
		{
			this->erase();
			this->copy(other);
		}
		return *this;
	}
	template<class T>
	Stack<T>::~Stack()
	{
		this->erase();
	}
	template<class T>
	bool Stack<T>::empty()const
	{
		return !this->size;
	}
	template<class T>
	void Stack<T>::pop()
	{
		if (!this->empty())
		{
			Node<T>* toBeRemoved = this->first;
			this->first = this->first->next;
			this->size--;
			delete toBeRemoved;
		}
	}
	template<class T>
	void Stack<T>::push(const T& element)
	{
		Node<T>* toBeAdd = new Node<T>(element);
		if (this->empty())
		{
			this->first = toBeAdd;
		}
		else
		{
			toBeAdd->next = this->first;
			this->first = toBeAdd;
		}
		this->size++;
	}
	template<class T>
	const T& Stack<T>::top()const
	{
		if (!this->empty())
		{
			return this->first->data;
		}
		throw "Empty stack";
	}
	template<class T>
	size_t Stack<T>::getSize()const
	{
		return this->size;
	}
	