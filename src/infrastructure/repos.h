#pragma once

#include <iostream>
#include <functional>
#include "../domain/exceptions.h"

template <typename ElementType>
class Repo
{
	private:
		/// Implementation of a simple linked list for the repo
		struct RepoNode
		{
			ElementType element; // the value of the element iteself
			RepoNode* next; // reference to the next element
		};

		/// The head of the repo
		RepoNode* head;

		/**
		 * Gets the node at the given index
		 *
		 * @param index An index
		 * @returns The node at index
		 */
		RepoNode* NodeAtIndex(int index);

	public:
		/**
		 * Ensures that the given element is not already in repo
		 *
		 * @param element The element to be validated
		 * @throws Exception if element already in repo
		 */
		void ValidateDuplicate(ElementType element);

		/**
		 * Ensures that the given element is existent in repo
		 *
		 * @param element The element to be validated
		 * @throws Exception if element is not in repo
		 */
		void ValidateExistance(ElementType element);

		/// Repo constructor
		Repo();
		
		/// Repo destructor
		~Repo();

		/// Frees the nodes of the repo
		void FreeRepo();
		
		/**
		 * Overloading the subscripting operator
		 * Gets the element at a given index
		 *
		 * @param index The index of the element to be returned from the repo
		 * @returns The element at the index position
		 */
		ElementType &operator[](int index);

		/**
		 * Gets the length of the repo
		 *
		 * @returns Number of elements
		 */
		int Size() const;

		/**
		 * Verifies the emptiness of the repo
		 *
		 * @returns True if list is empty of false otherwise
		 */
		bool Empty() const;

		/**
		 * Swaps tow elements
		 *
		 * @param first The firs element's index
		 * @param second The second's element index
		 * @throw Exception if first or secod index are out of bounds or equal
		 */
		void Swap(const int first, const int second);

		/**
		 * Adds element pointer to the begining of the repo
		 *
		 * @param element An element
		 * @param begining Should the adding operation be done at the begining of the list or at the end, defaults to false
		 * @throws Exception if element already in repo
		 */
		void Add(ElementType element, bool begining = false);

		/**
		 * Inserts an element at the given index
		 *
		 * @param element The element to be inserted
		 * @param index The position for insertion
		 * @throws Exception if index is out of bounds or if element already in repo
		 */
		void Insert(ElementType element, int index);

		/**
		 * Erases the element from the given position
		 *
		 * @param index The index of the element to be removed
		 * @throws Exception if index is out of bounds
		 */
		void Erase(int index);

		/**
		 * Gets an element from the repo
		 *
		 * @param isMatching Function used for matching the element
		 * @returns The searched element
		 * @throws Exception if repo is empty or element is not found
		 */
		ElementType &GetElement(std::function<bool(ElementType)> isMatching);

		/**
		 * Gets the index of an element from the repo
		 *
		 * @param isMatching Function used for matching the element
		 * @return The index of the searched element
		 * @throws Exception if repo is empty or element is not found
		 */
		int GetIndexOfElement(std::function<bool(ElementType)> isMatching);
};

template <typename ElementType>
typename Repo<ElementType>::RepoNode* Repo<ElementType>::NodeAtIndex(int index)
{
	if (this->Empty()) // throw exception if repo is empty
	{ throw IndexError("\nindex out of bounds"); }
	RepoNode* currentNode = this->head;
	for (int i = 0; i < index; i++) // iterating nodes until the requested one
	{
		// throw exception if the index is out of bounds
		if (currentNode->next == NULL)
		{ throw IndexError("\nindex out of bounds"); }

		currentNode = currentNode->next; // step to the next node
	}
	return currentNode; // return reference to the node
}

template <typename ElementType>
void Repo<ElementType>::ValidateDuplicate(ElementType element)
{
	for (int i = 0; i < this->Size(); i++)
		if (element == this->operator[](i)) // search for element in repo
		{ throw DuplicateError("\nelement already in repository"); } // if found throw exception
}

template <typename ElementType>
void Repo<ElementType>::ValidateExistance(ElementType element)
{
	for (int i = 0; i < this->Size(); i++)
		if (element == this->operator[](i)) // search for element in repo
		{ return; } // if found, all is good
	throw NotFoundError("\nelement not found in repository"); // if not found throw exception
}

template <typename ElementType>
Repo<ElementType>::Repo()
{
	this->head = NULL; // making the list empty
}

template <typename ElementType>
Repo<ElementType>::~Repo()
{
	this->head = NULL;
}

template <typename ElementType>
void Repo<ElementType>::FreeRepo()
{
	RepoNode* currentNode = this->head;
	this->head = NULL;
	while (currentNode) // iterating all nodes
	{
		RepoNode* nextNode = currentNode->next; // getting the next node

		// freeing current node
		currentNode->next = NULL;
		delete currentNode;

		currentNode = nextNode; // stepping to the next node
	}
}

template <typename ElementType>
ElementType &Repo<ElementType>::operator[](int index)
{
	if (this->Empty()) // throw exception if repo is empty
	{ throw IndexError("\nindex out of bounds"); }
	RepoNode* currentNode = this->head;
	for (int i = 0; i < index; i++) // iterating nodes until the requested one
	{
		// throw exception if the index is out of bounds
		if (currentNode->next == NULL)
		{ throw IndexError("\nindex out of bounds"); }

		currentNode = currentNode->next; // step to the next node
	}
	return currentNode->element; // return reference to the element
}

template <typename ElementType>
int Repo<ElementType>::Size() const
{
	RepoNode* currentNode = this->head;
	int count = 0;
	while (currentNode != NULL) // iterating all nodes
	{
		count++; // counting iterated nodes
		currentNode = currentNode->next;
	}
	return count;
}

template <typename ElementType>
bool Repo<ElementType>::Empty() const
{
	return (this->head == NULL) ? true : false; // repo empty if there are no nodes
}

template <typename ElementType>
void Repo<ElementType>::Swap(const int first, const int second)
{
	if (first > this->Size() - 1 || first < 0 || second > this->Size() - 1 || second < 0 || first == second)
	{ throw IndexError("\ninvalid indexes"); }
	// swaping elements
	ElementType temp = this->operator[](first);
	this->operator[](first) = this->operator[](second);
	this->operator[](second) = temp;
}

template <typename ElementType>
void Repo<ElementType>::Add(ElementType element, bool begining)
{
	// validating element
	this->ValidateDuplicate(element);

	// making a new node
	RepoNode* newNode = new RepoNode();
	newNode->element = element;
	newNode->next = NULL;

	if (this->Empty())
	{ head = newNode; } // set the first node to the given one
	else if (begining) // add to the begining of the repo
	{
		newNode->next = this->head; // making the new node's next element the repo's old head node
		this->head = newNode; // making the new node the head of the repo
	}
	else // add to the end
	{
		this->NodeAtIndex(this->Size() - 1)->next = newNode; // attaching the new node to the end of the repo
	}
}

template <typename ElementType>
void Repo<ElementType>::Insert(ElementType element, int index)
{
	// validating element
	this->ValidateDuplicate(element);

	// making a new node
	RepoNode* newNode = new RepoNode();
	newNode->element = element;
	newNode->next = NULL;

	if (index == 0) // adding from the begining
	{
		newNode->next = this->head;
		this->head = newNode;
	}
	else // inserting at index
	{
		if (index > this->Size())
		{ delete newNode; }
		newNode->next = this->NodeAtIndex(index - 1)->next;
		this->NodeAtIndex(index - 1)->next = newNode;
	}
}

template <typename ElementType>
void Repo<ElementType>::Erase(int index)
{
	// getting the node to be erased
	RepoNode* node = this->NodeAtIndex(index);
	
	if (index == 0)
	{ this->head = this->head->next; } // exclude the first node
	else
	{ this->NodeAtIndex(index - 1)->next = this->NodeAtIndex(index)->next; } // exclude any other node
	
	// erase the node
	node->next = NULL;
	delete node;
}

template <typename ElementType>
ElementType &Repo<ElementType>::GetElement(std::function<bool(ElementType)> isMatching)
{
	if (this->Empty())
	{ throw EmptyRepoError("\nempty repository"); }
	for (int i = 0; i < this->Size(); i++)
		if (isMatching(this->operator[](i)))
		{ return this->operator[](i); }
	throw NotFoundError("\nelement not found in repository");
}

template <typename ElementType>
int Repo<ElementType>::GetIndexOfElement(std::function<bool(ElementType)> isMatching)
{
	if (this->Empty())
	{ throw EmptyRepoError("\nempty repository"); }
	for (int i = 0; i < this->Size(); i++)
		if (isMatching(this->operator[](i)))
		{ return i; }
	throw NotFoundError("\nelement not found in repository");
}
