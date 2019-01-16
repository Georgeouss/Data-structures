#pragma once
#include "stdafx.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node<T>* previous;
	Node(const T& _data, Node<T>* _next, Node<T>* _prev)
	{
		this->data = _data;
		this->next = _next;
		this->previous = _prev;
	}
};
template <typename T>
class List
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;
	size_t lastIndex;
	Node<T>* lastIndexData;
	void copy(const List& other)
	{
		Note<T>* = other.first;
		for (size_t i = 0; i < other.size; i++)
		{
			this->push_back(temp->data);
			temp = temp->next;
		}
		this->size = other.size;
	}
	void erase()
	{
		while (size > 0)
		{
			this->pop_front();
		}
	}
public:
	List()
	{
		this->first = nullptr;
		this->last = nullptr;
		this->size = 0;
	}
	List(const List& other)
	{
		this->copy(other);
	}
	List& operator = (const List& other)
	{
		if (this != &other)
		{
			this->erase();
			this->copy(other);
		}
		return *this;
	}
	~List()
	{
		this->erase();
	}
	void push_back(T data)
	{
		Node<T>* temp = new Node<T>(data, nullptr, this->last);
		if (temp)
		{
			if (this->size == 0)
			{
				this->first = temp;
				this->last = temp;
			}
			else
			{
				this->last->next = temp;
				this->last = temp;
			}
			this->size++;
		}
	}
	void push_front(T data)
	{

		this->first = new Node<T>(data, first, nullptr);
		if (this->size == 0)
		{
			this->last = first;
		}
		else
		{
			this->first->next->previous = first;
		}
		this->size++;
	}
	void push(T element, size_t index)
	{
		if (index == 0)
		{
			this->push_front(index);
		}
		else
		{
			Node<T>* moveTemp = this->first;
			while (index > 1)
			{
				moveTemp = moveTemp->next;
				index--;
			}
			Node<T>* newTemp = new Node<T>(element, moveTemp->next, moveTemp);
			newTemp->next->previous = newTemp;
			moveTemp->next = newTemp;
			this->size++;
		}
	}
	T& operator [] (size_t index)
	{
		if (index == this->lastIndex + 1)
		{
			this->lastIndex = index;
			this->lastIndexData = this->lastIndexData->next;
			return this->lastIndexData->data;
		}
		Node<T>* temp = this->first;
		while (index > 0)
		{
			temp = temp->next;
			index--;
		}
		this->lastIndex = index;
		this->lastIndexData = temp;
		return temp->data;
	}
	void pop_back()
	{
		if (!this->first)
			return;
		Node<T>* toBeRemoved = this->last;
		Node<T>* moveTemp = this->first;
		while (moveTemp->next != last)
		{
			moveTemp = moveTemp->next;
		}
		this->last = moveTemp;
		this->last->next = nullptr;
		this->size--;
		delete toBeRemoved;
	}
	void pop_front()
	{
		if (!this->first)
			return;
		Node<T>* toBeRemoved = this->first;
		this->first = this->first->next;
		if (this->first)
			this->first->previous = nullptr;
		this->size--;
		delete toBeRemoved;
	}
	void pop(size_t index)
	{
		if (index == 0)
		{
			this->pop_front();
		}
		else
		{
			Node<T>* moveTemp = this->first;
			while (index > 1)
			{
				moveTemp = moveTemp->next;
				index--;
			}
			Node<T>* toBeRemoved = moveTemp->next;
			moveTemp->next = moveTemp->next->next;
			moveTemp->next->previous = moveTemp;
			this->size--;
			delete toBeRemoved;
		}
	}
	size_t getSize()const
	{
		return this->size;
	}
	void printTail()
	{
		Node<T>* temp = this->last;
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->previous;
		}
	}
	bool isMember(const T& element)
	{
		Node<T>* temp = this->first;
		while (temp != nullptr && element != temp->data)
		{
			temp = temp->next;
		}
		return temp != nullptr;
	}
	void reverse()
	{
		if (this->size <= 1)
			return;
		Node<T>* curr = this->first;
		Node<T>* temp = nullptr;

		while (curr != nullptr)
		{
			temp = curr->previous;
			curr->previous = curr->next;
			curr->next = temp;
			curr = curr->previous;
		}

		this->last = this->first;
		this->first = temp->previous;

	}
};