#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <memory>

namespace ALib
{
	template <typename T>
	class Node
	{
	public:
		std::shared_ptr<T> value = std::shared_ptr<T>(new T);
		std::shared_ptr<Node<T>> prevNode = nullptr;
		std::shared_ptr<Node<T>> nextNode = nullptr;
	};

	template <typename T>
	class Vector
	{
	private:
		unsigned int length = 0;
		std::shared_ptr<Node<T>> firstNode = nullptr;
		std::shared_ptr<Node<T>> lastNode = nullptr;
		T& at(int index)
		{
			if (index < 0 || index > length)
			{
				std::cout << std::endl << "vector subscript is out of range!";
				exit(0);
			}

			std::shared_ptr<Node<T>> temp = firstNode;
			for (int i = 0; i < index; i++)
			{
				temp = temp->nextNode;
			}
			return *temp->value;
		};

	public:
		unsigned int size()
		{
			return length;
		};
		void pushBack(T value)
		{
			if (lastNode != nullptr)
			{
				lastNode->nextNode = std::shared_ptr<Node<T>>(new Node<T>);
				lastNode->nextNode->prevNode = lastNode;
				lastNode = lastNode->nextNode;

			}
			else
			{
				lastNode = std::shared_ptr<Node<T>>(new Node<T>);
				firstNode = lastNode;
			}
			length++;
			*lastNode->value = value;
		};
		void popBack()
		{
			lastNode = lastNode->prevNode;
			length--;
		};
		void pushFront(T value)
		{
			if (firstNode != nullptr)
			{
				firstNode->prevNode = std::shared_ptr<Node<T>>(new Node<T>);
				firstNode->prevNode->nextNode = firstNode;
				firstNode = firstNode->prevNode;

			}
			else
			{
				firstNode = std::shared_ptr<Node<T>>(new Node<T>);
				lastNode = firstNode;
			}
			*firstNode->value = value;
			length++;
		};
		T& operator [](int index)
		{
			return at(index);
		};
	};
}