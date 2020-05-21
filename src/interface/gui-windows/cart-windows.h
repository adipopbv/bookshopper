#pragma once

#include <memory>
#include <QGroupBox>
#include <QPainter>
#include <random>

#include "../../infrastructure/observers.h"
#include "../../domain/entities.h"
#include "../../business/services.h"

using namespace std;

class CartReadOnlyWindow: public QGroupBox, public Observer
{
	protected:
		/// Service reference
		shared_ptr<BookstoreService> service;

	public:
		/**
		 * @brief CartReadOnlyWindow constructor
		 *
		 * @param service Service reference
		 */
		CartReadOnlyWindow(shared_ptr<BookstoreService> service);

		/// CartReadOnlyWindow destructor
		~CartReadOnlyWindow();

		/**
		 * @brief Invoked when service books changed
		 */
		void Update() override;

		/// Repaints window
		void paintEvent(QPaintEvent* ev) override;

		void Show();

		void Hide();
};

class CartReadWriteWindow: public QGroupBox, public Observer
{
	protected:
		/// Service reference
		shared_ptr<BookstoreService> service;

	public:
		/**
		 * @brief CartReadWriteWindow constructor
		 *
		 * @param service Service reference
		 */
		CartReadWriteWindow(shared_ptr<BookstoreService> service);

		/// CartReadWriteWindow destructor
		~CartReadWriteWindow();

		/**
		 * @brief Invoked when service books changed
		 */
		void Update() override;

		/**
		 * @brief Reloads books list
		 */
		void ReloadList();

		void Show();

		void Hide();
};

