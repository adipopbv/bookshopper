#pragma once

#include "../business/services.h"
#include "../infrastructure/repos.h"
#include "../domain/entities.h"

class BookstoreClient
{
	protected:
		/// Book service
		std::shared_ptr<BookstoreService> bookstoreService = std::make_shared<BookstoreService>();

		/// Library service getter
		std::shared_ptr<BookstoreService> getBookstoreService() const { return this->bookstoreService; }
		/// Library service setter
		void setBookstoreService(std::shared_ptr<BookstoreService> const value) { this->bookstoreService = value; }

		/// Adds book to the repository
		virtual void AddBook() = 0;

		/// Modifies a book from the repository
		virtual void ModifyBook() = 0;

		/// Deletes a book from the repository
		virtual void DeleteBook() = 0;

		/// Searches a book in the repository
		virtual void SearchBook() = 0;

		/// Filters books by title and/or release year
		virtual void FilterBooks() = 0;

		/// Sorts books by title, author or release year and genre
		virtual void SortBooks() = 0;

		/// Undoes the last basic operation
		virtual void UndoOperation() = 0;

		/// Empties the cart
		virtual void EmptyCart() = 0;

		/// Adds book by title to the cart
		virtual void AddToCart() = 0;

		/// Adds random books to the cart
		virtual void AddRandomBooksToCart() = 0;

		/// Saves the cart to csv file
		virtual void SaveCartToFile() = 0;

		/// Lists titles from cart
		virtual void ListAllCartTitles() const = 0;

		/// Exits application
		virtual void ExitApplication() const = 0;

	public:
		/// Library client constructor
		BookstoreClient() = default;

		/// Library client destructor
		~BookstoreClient() = default;

		/// Main application loop holder
		virtual int RunApplication() = 0;
};

