#pragma once

#include <memory>
#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>

#include "../../business/services.h"

using std::shared_ptr;
using std::make_shared;

class MainMenu: public QGroupBox
{
	protected:
		/// Service reference
		shared_ptr<BookstoreService> service;

		/// Menu layout
		shared_ptr<QVBoxLayout> menuLayout;

		/// Library side and cart side
		shared_ptr<QGroupBox> librarySide, cartSide;
		shared_ptr<QHBoxLayout> librarySideLayout, cartSideLayout;

		/// Library books list and cart books list
		shared_ptr<QListWidget> libraryBooksList, cartBooksList;

		/// Library actions and cart actions
		shared_ptr<QGroupBox> libraryActions, cartActions;
		shared_ptr<QGridLayout> libraryActionsLayout, cartActionsLayout;

		/// Library books as buttons list
		shared_ptr<QGroupBox> booksAsButtons;
		shared_ptr<QVBoxLayout> booksAsButtonsLayout;
		std::vector<shared_ptr<QPushButton>> booksAsButtonsList;

		/**
		 * @brief Initializes the library side of the main menu
		 */
		void InitLibrarySide();

		/**
		 * @brief Initializes the cart side of the main menu
		 */
		void InitCartSide();

	public:
		/// Quit button
		shared_ptr<QPushButton> exitAppButton;

		/// Library buttons and cart buttons
		shared_ptr<QPushButton> libraryAddButton, libraryModifyButton, libraryDeleteButton, librarySearchButton, libraryFilterButton, librarySortButton, libraryUndoButton, cartEmptyButton, cartAddButton, cartAddRandomButton, cartExportButton, cartTitlesButton, cartReadOnlyButton, cartReadWriteButton;

		/// Constructor
		MainMenu(shared_ptr<BookstoreService> const &service);

		/**
		 * @brief Updates the libray side book list
		 */
		void UpdateLibraryList();

		/**
		 * @brief Updates the cart side book list
		 */
		void UpdateCartList();

		/**
		 * @brief Shows the main menu window
		 */
		void Show();

		/**
		 * @brief Hides the main menu window
		 */
		void Hide();
};
