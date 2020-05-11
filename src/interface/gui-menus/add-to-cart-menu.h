#pragma once

#include <memory>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>

#include "../../business/services.h"

using std::shared_ptr;
using std::make_shared;

class AddToCartMenu: public QGroupBox
{
	protected:
		/// Service reference
		shared_ptr<BookstoreService> service;

		/// Menu layout
		shared_ptr<QVBoxLayout> menuLayout;

		/// Actions
		shared_ptr<QGroupBox> actions;
		shared_ptr<QHBoxLayout> actionsLayout;

	public:
		/// Books list
		shared_ptr<QListWidget> booksList;

		/// Accept and cancel buttons
		shared_ptr<QPushButton> acceptButton, cancelButton;

		/// Constructor
		AddToCartMenu(shared_ptr<BookstoreService> const &service);

		/**
		 * @brief Shows the add to cart menu window
		 */
		void Show();

		/**
		 * @brief Hides the add to cart menu window
		 */
		void Hide();
};
