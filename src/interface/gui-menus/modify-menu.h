#pragma once

#include <memory>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QSpinBox>

#include "../../domain/entities.h"
#include "../../business/services.h"

using std::shared_ptr;
using std::make_shared;

class ModifyMenu: public QGroupBox
{
	protected:
		/// Serveice reference
		shared_ptr<BookstoreService> service;

		/// Menu layout
		shared_ptr<QHBoxLayout> menuLayout;

		/// Actions
		shared_ptr<QGroupBox> actions;
		shared_ptr<QGridLayout> actionsLayout;

	public:
		/// Books list
		shared_ptr<QListWidget> booksList;

		/// Book fields
		shared_ptr<QLabel> titleLabel, authorLabel, genreLabel, releaseYearLabel;
		shared_ptr<QLineEdit> titleField, authorField, genreField;
		shared_ptr<QSpinBox> releaseYearField;

		/// Accept and cancel buttons
		shared_ptr<QPushButton> acceptButton, cancelButton;

		/// Constructor
		ModifyMenu(std::shared_ptr<BookstoreService> const &service);

		/**
		 * @brief Shows the modify menu window
		 */
		void Show();

		/**
		 * @brief Hides the modify menu window
		 */
		void Hide();
};

