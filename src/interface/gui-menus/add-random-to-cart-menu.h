#pragma once

#include <memory>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

using std::shared_ptr;
using std::make_shared;

class AddRandomToCartMenu: public QGroupBox
{
	protected:
		/// Menu layout
		shared_ptr<QGridLayout> menuLayout;

	public:
		/// Options
		shared_ptr<QLabel> countLabel;
		shared_ptr<QSpinBox> countField;

		/// Accept and cancel buttons
		shared_ptr<QPushButton> acceptButton, cancelButton;

		/// Constructor
		AddRandomToCartMenu();

		/**
		 * @brief Shows the add random to cart menu window
		 */
		void Show();

		/**
		 * @brief Hides the add random to cart menu window
		 */
		void Hide();
};
