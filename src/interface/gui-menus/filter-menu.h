#pragma once

#include <memory>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>

using std::shared_ptr;
using std::make_shared;

class FilterMenu: public QGroupBox
{
	protected:
		/// Menu layout
		shared_ptr<QHBoxLayout> menuLayout;

		/// Visualizer
		shared_ptr<QGroupBox> rezult;
		shared_ptr<QVBoxLayout> rezultLayout;

		/// Actions
		shared_ptr<QGroupBox> actions;
		shared_ptr<QGridLayout> actionsLayout;

	public:
		/// Books list
		shared_ptr<QListWidget> booksList;

		/// Book fields
		shared_ptr<QCheckBox> searchByYear;
		shared_ptr<QLabel> titleLabel, releaseYearLabel;
		shared_ptr<QLineEdit> titleField;
		shared_ptr<QSpinBox> releaseYearField;

		/// Buttons
		shared_ptr<QPushButton> acceptButton, cancelButton, okButton;

		/// Constructor
		FilterMenu();

		/**
		 * @brief Shows the filter menu window
		 */
		void Show();

		/**
		 * @brief Hides the filter menu window
		 */
		void Hide();

		/**
		 * @brief Switches focus from action side to rezult side
		 */
		void SwitchFocus();
};

