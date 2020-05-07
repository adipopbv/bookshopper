#pragma once

#include <QApplication>
#include <QMessageBox>
#include <QObject>

#include "./clients.h"
#include "./gui-menus/main-menu.h"
#include "./gui-menus/add-menu.h"
#include "./gui-menus/modify-menu.h"
#include "./gui-menus/delete-menu.h"

using std::shared_ptr;
using std::make_shared;

class GraphicalBookstoreClient: public BookstoreClient, public QApplication
{
	protected:
		/// Main menu
		shared_ptr<MainMenu> mainMenu;
		/// Add menu
		shared_ptr<AddMenu> addMenu;
		/// Modify menu
		shared_ptr<ModifyMenu> modifyMenu;
		/// Delete menu
		shared_ptr<DeleteMenu> deleteMenu;

		/// Buttons init
		void InitButtons();

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

