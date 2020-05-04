#pragma once

#include <QApplication>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "./clients.h"

using std::shared_ptr;
using std::make_shared;

class GraphicalBookstoreClient: public BookstoreClient, public QApplication
{
	protected:
		/// Main menu
		shared_ptr<QWidget> mainMenu;
		shared_ptr<QVBoxLayout> mainMenuLayout;
		/// Library side and cart side
		shared_ptr<QGroupBox> librarySide, cartSide;
		shared_ptr<QHBoxLayout> librarySideLayout, cartSideLayout;
		/// Library books list and cart books list
		shared_ptr<QListWidget> libraryBooksList, cartBooksList;
		/// Library actions and cart actions
		shared_ptr<QWidget> libraryActions, cartActions;
		shared_ptr<QGridLayout> libraryActionsLayout, cartActionsLayout;
		/// Library actions label and cart actions label
		shared_ptr<QLabel> libraryActionsLabel, cartActionsLabel;
		/// Library actions buttons and cart actions buttons
		shared_ptr<QPushButton> libraryActionsAddButton, libraryActionsModifyButton, libraryActionsDeleteButton, libraryActionsSearchButton, libraryActionsFilterButton, libraryActionsSortButton, libraryActionsUndoButton, cartActionsEmptyButton, cartActionsAddButton, cartActionsAddRandomButton, cartActionsExportButton, cartActionsTitlesButton;

		/// Add menu
		shared_ptr<QGroupBox> addMenu;
		shared_ptr<QGridLayout> addMenuLayout;
		/// Book fields
		shared_ptr<QLabel> addTitleLabel, addAuthorLabel, addGenreLabel, addReleaseYearLabel;
		shared_ptr<QLineEdit> addTitle, addAuthor, addGenre;
		shared_ptr<QSpinBox> addReleaseYear;
		/// Accept and cancel buttons
		shared_ptr<QPushButton> addAccept, addCancel;

		/// Modify menu
		shared_ptr<QGroupBox> modifyMenu;
		shared_ptr<QHBoxLayout> modifyMenuLayout;
		/// Books list
		shared_ptr<QListWidget> modifyBooksList;
		/// Actions
		shared_ptr<QWidget> modifyActions;
		shared_ptr<QGridLayout> modifyActionsLayout;
		/// Book fields
		shared_ptr<QLabel> modifyTitleLabel, modifyAuthorLabel, modifyGenreLabel, modifyReleaseYearLabel;
		shared_ptr<QLineEdit> modifyTitle, modifyAuthor, modifyGenre, modifyReleaseYear;
		/// Accept and cancel buttons
		shared_ptr<QPushButton> modifyAccept, modifyCancel;

		/// Delete menu
		shared_ptr<QGroupBox> deleteMenu;
		shared_ptr<QVBoxLayout> deleteMenuLayout;
		/// Books list
		shared_ptr<QListWidget> deleteBooksList;
		/// Actions
		shared_ptr<QWidget> deleteActions;
		shared_ptr<QHBoxLayout> deleteActionsLayout;
		/// Accept and cancel buttons
		shared_ptr<QPushButton> deleteAccept, deleteCancel;

		/// Menus inits
		void InitMainMenu();
		void InitAddMenu();
		void InitModifyMenu();
		void InitDeleteMenu();

		/// Show menus
		void ShowMainMenu();
		void ShowAddMenu();
		void ShowModifyMenu();
		void ShowDeleteMenu();

		/// Repos updates
		void UpdateLibraryBooksList();
		void UpdateCartBooksList();

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

