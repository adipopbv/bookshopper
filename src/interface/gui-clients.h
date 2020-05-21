#pragma once

#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

#include "./clients.h"
#include "./gui-windows/add-menu.h"
#include "./gui-windows/add-to-cart-menu.h"
#include "./gui-windows/add-random-to-cart-menu.h"
#include "./gui-windows/delete-menu.h"
#include "./gui-windows/filter-menu.h"
#include "./gui-windows/list-cart-titles-menu.h"
#include "./gui-windows/main-menu.h"
#include "./gui-windows/modify-menu.h"
#include "./gui-windows/search-menu.h"
#include "./gui-windows/sort-menu.h"
#include "./gui-windows/cart-windows.h"

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
		/// Search menu
		shared_ptr<SearchMenu> searchMenu;
		/// Filter menu
		shared_ptr<FilterMenu> filterMenu;
		/// Sort menu
		shared_ptr<SortMenu> sortMenu;
		/// Add to cart menu
		shared_ptr<AddToCartMenu> addToCartMenu;
		/// Add random to cart menu
		shared_ptr<AddRandomToCartMenu> addRandomToCartMenu;
		/// List cart titles menu
		shared_ptr<ListCartTitlesMenu> listCartTitlesMenu;
		/// Cart windows
		vector<shared_ptr<CartReadOnlyWindow>> cartReadOnlyWindows;
		vector<shared_ptr<CartReadWriteWindow>> cartReadWriteWindows;

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

