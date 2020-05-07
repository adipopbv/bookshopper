#pragma once

#include <memory>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>

#include "../../domain/entities.h"
#include "../../business/services.h"

using std::shared_ptr;
using std::make_shared;

class DeleteMenu: public QGroupBox
{
	protected:
		/// Serveice reference
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
		DeleteMenu(shared_ptr<BookstoreService> const &service);

		/**
		 * @brief Shows the delete menu window
		 */
		void Show();

		/**
		 * @brief Hides the delete menu window
		 */
		void Hide();
};

