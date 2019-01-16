#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct Node
{

	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>(const T& _data, Node<T>* _left = nullptr, Node<T>* _right = nullptr)
	{
		this->data = _data;
		this->left = _left;
		this->right = _right;
	}
};

template <class T>
class Tree
{
private:
	size_t size;
	Node<T>* root;

	bool isLeaf(const Node<T>* node)const
	{
		
		return node->left == nullptr && node->right == nullptr
		
	}
	void putNodesDataInVectorHelper(Node<T>* root, vector<T>& nodesData)
	{
		if (root == nullptr)
		{
			return;
		}
		putNodesDataInVectorHelper(root->left, nodesData);
		nodesData.push_back(root->data);
		putNodesDataInVectorHelper(root->right, nodesData);
	}
	Node<T>* createTreeFromSortedArrayHelper(vector<T> nodesData, int start, int end)
	{
		if (start > end)
			return nullptr;
		int mid = (start + end) / 2;
		Node<T>* root = new Node<T>(nodesData[mid]);

		root->left = createTreeFromSortedArrayHelper(nodesData, start, mid - 1);
		root->right = createTreeFromSortedArrayHelper(nodesData, mid + 1, end);

		return root;
	}
	Node<T>* minNode(Node<T>* root)const
	{
		Node<T>* result = root;
		while (result->left != nullptr)
		{
			result = result->left;
		}
		return result;
	}
	void printHelper(std::ostream& out, Node<T>* node)const
	{
		if (node == nullptr)
		{
			return;
		}

		out << (long)node
			<< "[label=\""
			<< node->data
			<< "\"];\n";

		if (node->left != nullptr)
		{
			out << (long)node
				<< "->"
				<< (long)node->left
				<< "[color=\"red\"];" << std::endl;
		}
		if (node->right != nullptr)
		{
			out << (long)node
				<< "->"
				<< (long)node->right
				<< "[color=\"green\"];" << std::endl;
		}

		printHelper(out, node->left);
		printHelper(out, node->right);
	}
	bool compareTrees(Node<T> *root1, Node<T> *root2)
	{
		if (root1 == nullptr || root2 == nullptr)
		{
			return root1 == root2;
		}

		return root1->data == root2->data &&
			compareTrees(root1->left, root2->left) &&
			compareTrees(root1->right, root2->right);

	}
	Node<T>* findHelper(Node<T>* _root, const T& value)
	{
		if (_root == nullptr || _root->data == value)
		{
			return _root;
		}
		else if (_root->data < value)
			return this->findHelper(_root->right, value);
		else
			return this->findHelper(_root->left, value);
	}
	Node<T>* insertHelper(Node<T>* &_root, const T& value)
	{
		if (_root == nullptr)
		{
			_root = new Node<T>(value);
		}
		else if (root->data == value)
		{
			return root;
		}

		else if (_root->data < value)
		{
			return this->insertHelper(_root->right, value);
		}
		else
		{
			return this->insertHelper(_root->left, value);
		}
	}
	void eraseHelper(Node<T>* &currentHead, const T& value)
	{
		if (currentHead == nullptr)
		{
			throw "No elemenet to delete";
		}
		else if (currentHead->data == value)
		{
			if (currentHead->left == nullptr && currentHead->right == nullptr)
			{
				delete currentHead;
				currentHead = nullptr;
			}
			else if (currentHead->left == nullptr && currentHead->right != nullptr)
			{
				Node<T>* toDelete = currentHead;
				currentHead = currentHead->right;
				delete toDelete;
			}
			else if (currentHead->left != nullptr && currentHead->right == nullptr)
			{
				Node<T>* toDelete = currentHead;
				currentHead = currentHead->left;

				delete toDelete;
			}
			else if (currentHead->left != nullptr && currentHead->right != nullptr && currentHead->right->left == nullptr)
			{
				Node<T>* toDelete = currentHead;
				Node<T>* _left = currentHead->left;
				currentHead = currentHead->right;
				currentHead->left = _left;
				delete toDelete;
			}
			else if (currentHead->left != nullptr && currentHead->right != nullptr && currentHead->right->left != nullptr)
			{
				Node<T>* toDelete = currentHead;
				Node<T>* _left = currentHead->left;
				Node<T>* temp = currentHead->right;
				if (currentHead->right->left->left)
				{
					while (temp->left->left != nullptr)
					{
						temp = temp->left;
					}
				}
				Node<T>* _right = currentHead->right;
				currentHead = temp->left;
				currentHead->right = _right;
				currentHead->left = _left;
				temp->left = nullptr;
				delete toDelete;
			}
		}
		else if (currentHead->left->data < value)
		{
			return this->eraseHelper(currentHead->right, value);
		}
		else
		{
			return this->eraseHelper(currentHead->left, value);
		}
	}
	Node<T>* copy(const Node<T>* other)
	{
		if (other == nullptr)
		{
			return this->root;
		}
		return new Node<T>(other->data, copy(other->left), copy(other->right));
	}
	void destroy(Node<T>* _root)
	{
		if (_root == nullptr)
		{
			return;
		}
		this->destroy(_root->left);
		this->destroy(_root->right);
		delete _root;
	}

public:
	Tree<T>()
	{
		this->root = nullptr;
		this->size = 0;
	}
	Tree<T>(const vector<T>& nodes)
	{
		this->root = this->createTreeFromSortedArrayHelper(nodes, 0, nodes.size() - 1);
		this->size = nodes.size();
	}
	Tree<T>(const Tree<T>& other)
	{
		this->root = this->copy(other.root);
		this->size = other.size;
	}
	Tree<T>& operator = (const Tree<T>& other)
	{
		if (this != &other)
		{
			this->destroy(this->root);
			this->root = this->copy(other.root);
			this->size = other.size;
		}
		return *this;
	}
	Node<T>* getRoot()const
	{
		return this->root;
	}
	size_t getSize()const
	{
		return this->size;
	}
	~Tree<T>()
	{
		this->destroy(this->root);
	}
	T minElement()const
	{
		Node<T>* result = this->minNode(this->root);
		return result->data;
	}

	T maxElement()const
	{
		Node<T>* result = this->root;
		while (result->right != nullptr)
		{
			result = result->right;
		}
		return result->data;
	}
	Node<T>* find(const T& value)
	{
		return findHelper(this->root, value);
	}
	void insert(const T& value)
	{
		this->insertHelper(this->root, value);
		this->size++;
	}
	void putNodesDataInVector(vector<T>& nodesData)
	{
		putNodesDataInVectorHelper(this->root, nodesData);
	}
	void erase(const T& value)
	{
		if (this->size != 0)
		{
			this->eraseHelper(this->root, value);
			this->size--;
		}
	}

	bool operator == (const Tree<T> &other)
	{
		return compareTrees(root, other.root);
	}
	void print()const
	{
		this->printHelper(cout, this->root);
	}
};
