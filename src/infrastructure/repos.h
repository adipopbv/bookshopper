#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include "../domain/exceptions.h"

template <typename ElementType>
class Repo
{
	private:
		/// Implementation of a simple linked list for the repo
		std::vector<ElementType> elements = std::vector<ElementType>();

		/**
		 * Ensures that the given element is not already in repo
		 *
		 * @param element The element to be validated
		 * @throws Exception if element already in repo
		 */
		void ValidateDuplicate(ElementType const &element) const;

		/**
		 * Ensures that the given element is existent in repo
		 *
		 * @param element The element to be validated
		 * @throws Exception if element is not in repo
		 */
		void ValidateExistance(ElementType const &element) const;

		/**
		 * Ensures that the given element is existent in repo
		 *
		 * @param index The index to be validated
		 * @throws Exception if index is out of bounds or not the correct type
		 */
		void ValidateIndex(int const &index) const;

	public:
		/// Repo constructor
		Repo();
		
		/// Repo destructor
		~Repo();

		/// elements getter
		std::vector<ElementType> getElements() const { return this->elements; }
		/// elements setter
		void setElements(std::vector<ElementType> const &value) { this->elements = value; }
		
		/**
		 * Overloading the subscripting operator
		 * Gets the element at a given index
		 *
		 * @param index The index of the element to be returned from the repo
		 * @returns The element at the index position
		 */
		ElementType &operator[](int const &index);

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
		void Swap(const int &first, const int &second);

		/**
		 * Adds element pointer to the begining of the repo
		 *
		 * @param element An element
		 * @param begining Should the adding operation be done at the begining of the list or at the end, defaults to false
		 * @throws Exception if element already in repo
		 */
		void Add(ElementType const &element, bool const &validateDuplicate = true);

		/**
		 * Inserts an element at the given index
		 *
		 * @param index The position for insertion
		 * @param element The element to be inserted
		 * @throws Exception if index is out of bounds or if element already in repo
		 */
		void Insert(int const &index, ElementType const &element);

		/**
		 * Erases the element from the given position
		 *
		 * @param index The index of the element to be removed
		 * @throws Exception if index is out of bounds
		 */
		void Erase(int const &index);

		/**
		 * Gets an element from the repo
		 *
		 * @param isMatching Function used for matching the element
		 * @returns The searched element
		 * @throws Exception if repo is empty or element is not found
		 */
		ElementType GetElement(std::function<bool (ElementType)> isMatching);

		/**
		 * Gets the index of an element from the repo
		 *
		 * @param isMatching Function used for matching the element
		 * @return The index of the searched element
		 * @throws Exception if repo is empty or element is not found
		 */
		int GetIndexOfElement(std::function<bool (ElementType)> const &isMatching) const;

		/**
		 * Sorts the repo
		 *
		 * @param compareElements Element comparation function
		 */
		void Sort(std::function<bool (ElementType, ElementType)> const &compareElements);
};

template <typename ElementType>
void Repo<ElementType>::ValidateDuplicate(ElementType const &element) const
{
	std::for_each(this->elements.begin(), this->elements.end(), 
		[&element] (ElementType currentElement)
		{
			if (element == currentElement)
			{ throw DuplicateError("element already in repo\n"); } // if found throw exception
		}
	);
	/*
	for (int i = 0; i < this->Size(); i++)
		if (element == this->operator[](i)) // search for element in repo
		{ throw DuplicateError("element already in repo\n"); } // if found throw exception
	*/
}

template <typename ElementType>
void Repo<ElementType>::ValidateExistance(ElementType const &element) const
{
	std::for_each(this->elements.begin(), this->elements.end(), 
		[&element] (ElementType currentElement)
		{
			if (element == currentElement)
			{ return; }
		}
	);
	throw NotFoundError("element not found\n"); // if not found throw exception
	/*
	for (int i = 0; i < this->Size(); i++)
		if (element == this->operator[](i)) // search for element in repo
		{ return; } // if found, all is good
	throw NotFoundError("\nelement not found in repository"); // if not found throw exception
	*/
}

template <typename ElementType>
void Repo<ElementType>::ValidateIndex(int const &index) const
{
	if (this->Empty())
	{ throw EmptyRepoError("repo is empty\n"); }
	if (index > this->Size() - 1 || index < 0)
	{ throw IndexError("index out of bounds\n"); }
}

template <typename ElementType>
Repo<ElementType>::Repo()
{
	// empty vector
	this->elements = std::vector<ElementType>();
}

template <typename ElementType>
Repo<ElementType>::~Repo()
{
	// empty vector
	this->elements = std::vector<ElementType>();
}

template <typename ElementType>
ElementType &Repo<ElementType>::operator[](int const &index)
{
	this->ValidateIndex(index);
	return this->elements[index];
}

template <typename ElementType>
int Repo<ElementType>::Size() const
{
	// return the number of elements
	return this->elements.size();
}

template <typename ElementType>
bool Repo<ElementType>::Empty() const
{
	// return the emptyness state of the vector
	return this->elements.empty();
}

template <typename ElementType>
void Repo<ElementType>::Swap(const int &first, const int &second)
{
	this->ValidateIndex(first);
	this->ValidateIndex(second);
	if (first == second)
	{ throw IndexError("indexes are identical\n"); }
	// swaping elements
	ElementType temp = this->operator[](first);
	this->operator[](first) = this->operator[](second);
	this->operator[](second) = temp;
}

template <typename ElementType>
void Repo<ElementType>::Add(ElementType const &element, bool const &validateDuplicate)
{
	// validating element
	if (validateDuplicate)
	{ this->ValidateDuplicate(element); }
	// adding element
	this->elements.push_back(element);
}

template <typename ElementType>
void Repo<ElementType>::Insert(int const &index, ElementType const &element)
{
	// validating element
	this->ValidateDuplicate(element);
	// validating index
	this->ValidateIndex(index);
	// inserting element at index
	this->elements.insert(this->elements.begin() + index, element);
}

template <typename ElementType>
void Repo<ElementType>::Erase(int const &index)
{
	// validating index
	this->ValidateIndex(index);
	// erasing the element at index
	this->elements.erase(this->elements.begin() + index);
}

template <typename ElementType>
ElementType Repo<ElementType>::GetElement(std::function<bool(ElementType)> isMatching)
{
	if (this->Empty())
	{ throw EmptyRepoError("empty repo\n"); }

	int index = -1, count = 0;
	std::vector<ElementType> vect = this->getElements();
	std::for_each(vect.begin(), vect.end(), 
		[&isMatching, &index, &count] (ElementType currentElement)
		{
			if (isMatching(currentElement) && index == -1)
			{ index = count; }
			count++;
		}
	);
	if (index != -1)
	{ return vect[index]; }
	throw NotFoundError("element not found\n");
}

template <typename ElementType>
int Repo<ElementType>::GetIndexOfElement(std::function<bool(ElementType)> const &isMatching) const
{
	if (this->Empty())
	{ throw EmptyRepoError("empty repo\n"); }

	int index = -1, counter = 0;
	std::vector<ElementType> vect = this->getElements();
	std::for_each(vect.begin(), vect.end(), 
		[&isMatching, &index, &counter] (ElementType currentElement)
		{
			if (isMatching(currentElement) && index == -1)
			{ index = counter; }
			counter++;
		}
	);
	if (index != -1)
	{ return index; }
	throw NotFoundError("element not found\n");
	/*
	throw NotFoundError("element not found\n");
	for (int i = 0; i < this->Size(); i++)
		if (isMatching(this->operator[](i)))
		{ return i; }
	throw NotFoundError("\nelement not found in repository");
	*/
}

template <typename ElementType>
void Repo<ElementType>::Sort(std::function<bool (ElementType, ElementType)> const &compareElements)
{
	if (this->Empty())
	{ throw EmptyRepoError("empty repo\n"); }
	std::vector<ElementType> newVector = this->getElements();
	std::sort(newVector.begin(), newVector.end(), compareElements);
	this->setElements(newVector);
}

