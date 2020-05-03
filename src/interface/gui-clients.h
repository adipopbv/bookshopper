#pragma once

#include <QApplication>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "./clients.h"

using std::shared_ptr;
using std::make_shared;

class GraphicalBookstoreClient: public BookstoreClient, public QApplication
{
	protected:
		// main menu
		shared_ptr<QWidget> mainMenu;
		shared_ptr<QVBoxLayout> mainMenuLayout;
		// library side and cart side
		shared_ptr<QGroupBox> librarySide, cartSide;
		shared_ptr<QHBoxLayout> librarySideLayout, cartSideLayout;
		// library books list and cart books list
		shared_ptr<QListWidget> libraryBooksList, cartBooksList;
		// library actions and cart actions
		shared_ptr<QWidget> libraryActions, cartActions;
		shared_ptr<QGridLayout> libraryActionsLayout, cartActionsLayout;
		// library actions label and cart actions label
		shared_ptr<QLabel> libraryActionsLabel, cartActionsLabel;
		// library actions buttons and cart actions buttons
		shared_ptr<QPushButton> libraryActionsAddButton, libraryActionsModifyButton, libraryActionsDeleteButton, libraryActionsSearchButton, libraryActionsFilterButton, libraryActionsSortButton, libraryActionsUndoButton, cartActionsEmptyButton, cartActionsAddButton, cartActionsAddRandomButton, cartActionsExportButton, cartActionsTitlesButton;

		void InitLibraryBooksList();
		void InitCartBooksList();

		/// Adds book to the repository
		void AddBook() override;

		/// Modifies a book from the repository
		void ModifyBook() override;

		/// Deletes a book from the repository
		void DeleteBook() override;

		/// Searches a book in the repository
		void SearchBook() override;

		/// Filters books by title and/or release year
		void FilterBooks() override;

		/// Sorts books by title, author or release year and genre
		void SortBooks() override;

		/// Undoes the last basic operation
		void UndoOperation() override;

		/// Empties the cart
		void EmptyCart() override;

		/// Adds book by title to the cart
		void AddToCart() override;

		/// Adds random books to the cart
		void AddRandomBooksToCart() override;

		/// Saves the cart to csv file
		void SaveCartToFile() override;

		/// Lists titles from cart
		void ListAllCartTitles() const override;

		/// Exits application
		void ExitApplication() const override;

	public:
		/// Library client constructor
		GraphicalBookstoreClient(std::shared_ptr<BookstoreService> const &bookstoreService, int argc, char** argv);

		/// Library client destructor
		~GraphicalBookstoreClient();

		/// Main application loop holder
		int RunApplication() override;
};

