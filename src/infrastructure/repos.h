#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "../domain/exceptions.h"

template <typename ElementType>
class Repo
{
	private:
		/// Implementation of stl vector for the repo
		std::map<int, ElementType> elements = std::map<int, ElementType>();

		/**
		 * Ensures that the given element is not already in repo
		 *
		 * @param element The element to be validated
		 * @throws Exception if element already in repo
		 */
		void ValidateDuplicate(ElementType const &element);

		/**
		 * Ensures that the given element is existent in repo
		 *
		 * @param element The element to be validated
		 * @throws Exception if element is not in repo
		 */
		void ValidateExistance(ElementType const &element);

		/**
		 * Ensures that the given key is valid
		 *
		 * @param index The index to be validated
		 * @throws Exception if index is out of bounds or not the correct type
		 */
		void ValidateIndex(int const &index);

	public:
		/// Repo constructor
		Repo();
		
		/// Repo destructor
		~Repo();

		/// Elements getter
		std::map<int, ElementType> getElements() const { return this->elements; }
		/// Elements setter
		void setElements(std::map<int, ElementType> const &value) { this->elements = value; }
		
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
		 * Swaps two elements
		 *
		 * @param first The firs element's index
		 * @param second The second's element index
		 * @throw Exception if first or secod index are out of bounds or equal
		 */
		void Swap(int const &first, int const &second);

		/**
		 * Adds element at the end of the repo
		 *
		 * @param element An element
		 * @param validateDuplicate Should the function check for duplicate in repo?
		 * @throws Exception if element already in repo
		 */
		void Add(ElementType const &element, bool const &validateDuplicate = true);

		/**
		 * Modifies an element at the given index
		 *
		 * @param index The position for modification
		 * @param element The element to be modified
		 * @throws Exception if index is not valid or if the modified element is already in repo
		 */
		void Insert(int const &index, ElementType const &element);

		/**
		 * Erases the element from the given position
		 *
		 * @param index The index of the element to be removed
		 * @throws Exception if index is not valid
		 */
		void Erase(int const &index);

		/**
		 * Finds an element in the repo
		 *
		 * @param isMatching Function used for matching the element
		 * @returns Iterator to the searched element
		 * @throws Exception if repo is empty or element is not found
		 */
		int FindIf(std::function<bool (ElementType)> const &isMatching);
		//Repo<ElementType>::Iterator FindIf(std::function<bool (ElementType)> const &isMatching);

		/**
		 * Sorts the repo
		 *
		 * @param compareElements Element comparation function
		 */
		void Sort(std::function<bool (ElementType, ElementType)> const &compareElements);

		/**
		 * Returns the repo values in a stl vector
		 *
		 * @returns A stl vector with the repo values
		 */
		std::vector<ElementType> toVector();
};

template <typename ElementType>
void Repo<ElementType>::ValidateDuplicate(ElementType const &element)
{
	// search in all elements
	for (int i = 0; i < this->Size(); i++)
		// throw exception if element found
		if (this->operator[](i) == element)
		{ throw DuplicateError("element already in repo\n"); }
}

template <typename ElementType>
void Repo<ElementType>::ValidateExistance(ElementType const &element)
{
	// search in all elements
	for (int i = 0; i < this->Size(); i++)
		// return if element found
		if (this->operator[](i) == element)
		{ return; }
	// throw exception if element not found
	throw NotFoundError("element not found\n");
}

template <typename ElementType>
void Repo<ElementType>::ValidateIndex(int const &index)
{
	// if empty repo throw exception
	if (this->Empty())
	{ throw EmptyRepoError("empty repo\n"); }
	// if index out of bounds throw exception
	if (index < 0 || index > this->Size() - 1)
	{ throw IndexError("index out of bounds\n"); }
}

template <typename ElementType>
Repo<ElementType>::Repo()
{
	// init with empty container
	this->elements = std::map<int, ElementType>();
}

template <typename ElementType>
Repo<ElementType>::~Repo()
{
	// set to default value (empty container)
	this->elements = std::map<int, ElementType>();
}

template <typename ElementType>
ElementType &Repo<ElementType>::operator[](int const &index)
{
	// validate index
	this->ValidateIndex(index);

	// return the element at index location
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
	// return the emptyness state of the container
	return this->elements.empty();
}

template <typename ElementType>
void Repo<ElementType>::Swap(int const &first, int const &second)
{
	// validate first index
	this->ValidateIndex(first);
	// validate second index
	this->ValidateIndex(second);
	// if indexes are equal throw exception
	if (first == second)
	{ throw IndexError("indexes are identical\n"); }

	// swap elements
	ElementType temp = this->elements[first];
	this->elements[first] = this->elements[second];
	this->elements[second] = temp;
}

template <typename ElementType>
void Repo<ElementType>::Add(ElementType const &element, bool const &validateDuplicate)
{
	// validate element
	if (validateDuplicate)
	{ this->ValidateDuplicate(element); }

	// add element to end of repo
	this->elements[this->Size()] = element;
}

template <typename ElementType>
void Repo<ElementType>::Insert(int const &index, ElementType const &element)
{
	// validate index
	this->ValidateIndex(index);
	// validate element
	this->ValidateDuplicate(element);

	// shift elements to the right
	int end = this->Size();
	for (int i = end; i > index; i--)
		this->elements[i] = this->elements[i - 1];

	// insert element at index
	this->elements[index] = element;
}

template <typename ElementType>
void Repo<ElementType>::Erase(int const &index)
{
	// validate index
	this->ValidateIndex(index);

	// shift elements to the left
	int end = this->Size();
	for (int i = index; i < end; i++)
		this->elements[i] = this->elements[i + 1];

	// erase the last 2 elements because one was newly created when shifting
	this->elements.erase(this->Size() - 1);
	this->elements.erase(this->Size() - 1);
}

template <typename ElementType>
int Repo<ElementType>::FindIf(std::function<bool(ElementType)> const &isMatching)
{
	// validate repo emptyness
	if (this->Empty())
	{ throw EmptyRepoError("empty repo\n"); }

	// search the index of the wanted element
	for (int i = 0; i < this->Size(); i++)
		if (isMatching(this->elements[i]))
			return i;

	// if not found throw exception
	throw NotFoundError("element not found\n");
}

template <typename ElementType>
void Repo<ElementType>::Sort(std::function<bool (ElementType, ElementType)> const &compareElements)
{
	// validate repo emptyness
	if (this->Empty())
	{ throw EmptyRepoError("empty repo\n"); }

	// sort the vector of values using the given compare function
	std::vector<ElementType> newVector = this->toVector();
	std::sort(newVector.begin(), newVector.end(), compareElements);

	// replace the old values with the sorted ones
	for (int i = 0; i < this->Size(); i++)
		this->elements[i] = newVector[i];
}

template <typename ElementType>
std::vector<ElementType> Repo<ElementType>::toVector()
{
	// make a new vector to store the values into
	std::vector<ElementType> newVector = std::vector<ElementType>();
	// add all repo values in te vector
	for (int i = 0; i < this->Size(); i++)
		newVector.push_back(this->elements[i]);
	// retur the vector with the repo values
	return newVector;
}

