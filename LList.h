#pragma once

#include "stdafx.h"
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node(const T& _data, Node<T>* nxt = nullptr) : data(_data), next(nxt) {}
};

template <typename T>
class List
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;
	void copy(const List<T>& other)
	{
		Node<T>* temp = other.first;
		for (size_t i = 0; i < other.size; i++)
		{
			this->push_back(temp->data);
			temp = temp->next;
		}
		this->size = other.size;
	}
	void erase()
	{
		while (size)
		{
			this->pop_front();
		}
		this->init();
	}
	void init()
	{
		this->first = nullptr;
		this->last = nullptr;
		this->size = 0;
	}
public:
	List()
	{
		this->init();
	}
	List(const List<T>& other)
	{
		this->init();
		this->copy(other);
	}
	List<T>& operator= (const List<T>& other)
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

	void push_back(const T& data)
	{
		Node<T>* toBeAdd = new Node<T>(data);
		if (this->size == 0)
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
	void push_front(const T& _data)
	{
		Node<T>* toBeAdd = new Node<T>(data, this->first);
		if (this->size == 0)
		{
			this->last = toBeAdd;
		}
		this->first = toBeAdd;
		this->size++;
	}
	void pop_front()
	{
		if (this->size)
		{
			Node<T>* toBeDeleted = this->first;
			this->first = this->first->next;
			delete toBeDeleted;
			this->size--;
		}
		else
			throw "Empty list";
	}
	List<T> operator + (const List<T>& other1)
	{
		List<T> mergedList;
		Node<T>* listMoover = this->first;
		Node<T>* listMoover2 = other1.first;
		for (size_t i = 0; i < this->size; i++)
		{
			mergedList.push_back(listMoover->data);
			listMoover = listMoover->next;
		}

		for (size_t i = 0; i < other1.size; i++)
		{
			mergedList.push_back(listMoover2->data);
			listMoover2 = listMoover2->next;
		}
		return mergedList;
	}
	void pop_back()
	{
		Node<T>* toBeRemoved = this->last;
		Node<T>* temp = this->first;
		while (temp->next != last)
		{
			temp = temp->next;
		}
		this->last = temp;
		this->last->next = nullptr;
		delete toBeRemoved;
		this->size--;

	}
	void print()const
	{
		Node<T>* moover = this->first;
		while (moover)
		{
			cout << moover->data << " ";
			moover = moover->next;
		}
		cout << endl;
	}
	void reverse()
	{
		Node<T>* previous = nullptr;
		Node<T>* current = this->first;
		Node<T>* newEnd = this->first;
		Node<T>* nxt;
		while (current)
		{
			nxt = current->next;
			current->next = previous;
			previous = current;
			current = nxt;
		}
		this->first = this->last;
		this->last = newEnd;
	}
	void separateList(List<T>& list2, List<T>& list3)
	{
		Node<T>* moover = this->first;
		for (size_t i = 0; i < this->size; i++)
		{
			if (i % 2 == 0)
			{
				list2.push_back(moover->data);
			}
			else
			{
				list3.push_back(moover->data);
			}
			moover = moover->next;
		}
	}
	List<T>& concatSortList(const List<T>& list1)
	{
		List<T> result;
		Node<T>* moover1 = this->first;
		Node<T>* moover2 = list1.first;
		while (moover1 && moover2)
		{
			if (moover1->data > moover2->data)
			{
				result.push_back(moover2->data);
				moover2 = moover2->next;
			}
			else
			{
				result.push_back(moover1->data);
				moover1 = moover1->next;
			}
		}
		while (moover1)
		{
			result.push_back(moover1->data);
			moover1 = moover1->next;
		}
		while (moover2)
		{
			result.push_back(moover2->data);
			moover2 = moover2->next;
		}
		*this = result;
		return *this;
	}
	List<T>&  sort()
	{
		for (Node<T>* head = this->first; head != nullptr; head = head->next)
			for (Node<T>* headnxt = head->next; headnxt != nullptr; headnxt = headnxt->next)
			{
				if (head->data > headnxt->data)
				{
					swap(head->data, headnxt->data);
				}
			}
		return *this;
	}
	bool isUnique()const
	{
		for (Node<T>* i = this->first; i != nullptr; i = i->next)
			for (Node<T>* j = i->next; j != nullptr; j = j->next)
			{
				if (i->data == j->data)
					return false;
			}
		return true;
	}

	void removeDublicate()
	{
		Node<T>* toBeRemoved, *ptr2;
		for (Node<T>* i = this->first; i != nullptr && i->next != nullptr; i = i->next)
		{
			ptr2 = i;
			while (ptr2->next != nullptr)
			{
				if (i->data == ptr2->next->data)
				{
					toBeRemoved = ptr2->next;
					ptr2->next = ptr2->next->next;
					delete toBeRemoved;
					this->size--;
				}
				else
				{
					ptr2 = ptr2->next;
				}
			}
		}
	}
	Node<T>* getfirst()const
	{
		return this->first;
	}
	void mergeSort()
	{
		List<T> a, b;
		if (this->first == nullptr || (this->first->next == nullptr))
		{
			return;
		}
		this->separateList(a, b);
		a.mergeSort();
		b.mergeSort();
		a.concatSortList(b);
		*this = a;
	}
};