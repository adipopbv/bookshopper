#pragma once

#include <memory>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>

#include "../../business/services.h"

using std::shared_ptr;
using std::make_shared;

class ListCartTitlesMenu: public QGroupBox
{
	protected:
		/// Titles list
		shared_ptr<BookstoreService> service;

		/// Menu layout
		shared_ptr<QVBoxLayout> menuLayout;

	public:
		/// Titles list
		shared_ptr<QListWidget> titlesList;

		/// Accept and cancel buttons
		shared_ptr<QPushButton> okButton;

		/// Constructor
		ListCartTitlesMenu(shared_ptr<BookstoreService> const &service);

		/**
		 * @brief Shows the list cart titles menu window
		 */
		void Show();

		/**
		 * @brief Hides the list cart titles menu window
		 */
		void Hide();
};
