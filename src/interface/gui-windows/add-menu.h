#pragma once

#include <memory>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

using std::shared_ptr;
using std::make_shared;

class AddMenu: public QGroupBox
{
	protected:
		/// Menu layout
		shared_ptr<QGridLayout> menuLayout;

	public:
		/// Book fields
		shared_ptr<QLabel> titleLabel, authorLabel, genreLabel, releaseYearLabel;
		shared_ptr<QLineEdit> titleField, authorField, genreField;
		shared_ptr<QSpinBox> releaseYearField;

		/// Accept and cancel buttons
		shared_ptr<QPushButton> acceptButton, cancelButton;

		/// Constructor
		AddMenu();

		/**
		 * @brief Shows the add menu window
		 */
		void Show();

		/**
		 * @brief Hides the add menu window
		 */
		void Hide();
};

