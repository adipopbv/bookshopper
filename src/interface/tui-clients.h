#pragma once

#include <string>

#include "./clients.h"

class TerminalBookstoreClient: public BookstoreClient
{
	protected:
		/**
		 * @brief Reads an integer from the terminal
		 *
		 * @param prompt Message to print before reading input
		 *
		 * @return The read integer
		 */
		int ReadInt(std::string const &prompt = "") const;

		/**
		 * @brief Reads a line of characters from the terminal
		 *
		 * @param prompt Message to print before reading input
		 *
		 * @return The read string of characters
		 */
		std::string ReadString(std::string const &prompt = "") const;

		/**
		 * @brief Prints a message in the terminal
		 *
		 * @param message The message to be displayed
		 */
		void PrintString(std::string const &message) const;

		/**
		 * @brief Prints a book's data
		 *
		 * @param book The book to be printed
		 */
		void PrintBook(Book const &book) const;

		/// Lists all books
		void ListAllBooks() const;

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

		/// Lists all books in the cart
		void ListAllCartBooks() const;

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
		TerminalBookstoreClient(std::shared_ptr<BookstoreService> const &bookstoreService);

		/// Library client destructor
		~TerminalBookstoreClient();

		/// Main application loop holder
		int RunApplication() override;
};

