#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "../domain/entities.h"

using namespace std;

class Observer
{
	public:
		Observer() = default;

		~Observer() = default;

		/**
		 * @brief Invoked when Observable changed state
		 */
		virtual void Update() = 0;
};

class Observable
{
	protected:
		/// Observers list
		vector<Observer*> observers;

		/**
		 * @brief Notifies all observers of changed state
		 */
		virtual void Notify() = 0;

	public:
		Observable() = default;

		~Observable() = default;

		/**
		 * @brief Adds observer to list
		 *
		 * @param observer Observer to add
		 */
		void AddObserver(Observer* observer);

		/**
		 * @brief Removes observer from list
		 *
		 * @param observer Observer to be removed
		 */
		void RemoveObserver(Observer* observer);
};

