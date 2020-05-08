#pragma once

#include <memory>
#include <QCheckBox>
#include <QButtonGroup>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>

using std::shared_ptr;
using std::make_shared;

class SortMenu: public QGroupBox
{
	protected:
		/// Menu layout
		shared_ptr<QGridLayout> menuLayout;

	public:
		/// Sort options
		shared_ptr<QButtonGroup> sortOptions;
		shared_ptr<QCheckBox> sortByTitle, sortByAuthor, sortByReleaseYearAndGenre;

		/// Accept and cancel buttons
		shared_ptr<QPushButton> acceptButton, cancelButton;

		/// Constructor
		SortMenu();

		/**
		 * @brief Shows the sort menu window
		 */
		void Show();

		/**
		 * @brief Hides the sort menu window
		 */
		void Hide();
};

