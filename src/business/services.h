#pragma once

#include <string>

#include "../domain/entities.h"
#include "../domain/exceptions.h"
#include "../infrastructure/repos.h"

class BookstoreService
{
	private:
		/// The books repository
		Repo<Book> booksRepo = Repo<Book>();

	public:
		/// Library service constructor
		BookstoreService(const Repo<Book> &booksRepo = Repo<Book>());

		/// Library service destructor
		~BookstoreService();

		/// Books repository getter
		Repo<Book> getBooksRepo() const { return this->booksRepo; }
		/// Books repository setter
		void setBooksRepo(Repo<Book> const &value) { this->booksRepo = value; }

		/// Gets all books from the repo
		Repo<Book> GetBooks() const;

		/**
		 * Adds a book to the repo
		 *
		 * @param title The title of the book
		 * @param author The author of the book
		 * @param genre The genre of the book
		 * @param releaseYear The release year of the book
		 * @throws Exception if book invalid or is duplicate
		 */
		void AddBookToRepo(const std::string &title = "", const std::string &author = "", const std::string &genre = "", const int &releaseYear = 0);

		/**
		 * Modifies a book from the repo, searching by title and author
		 *
		 * @param titleSearch The title to search by
		 * @param authorSearch The author to search by
		 * @param title The new title of the book
		 * @param author The new author of the book
		 * @param genre The new genre of the book
		 * @param releaseYear The new release year of the book
		 * @throws Exception if the search fields are invalid, if the new book is invalid, if it becomes duplicated after the modification or if book was not found
		 */
		void ModifyBookInRepo(const std::string &titleSearch, const std::string &authorSearch, const std::string &title = "", const std::string &author = "", const std::string &genre = "", const int &releaseYear = 0);

		/**
		 * Deletes a book from the repo, searching by title and author
		 *
		 * @param titleSearch The title to search by
		 * @param authorSearch The author to search by
		 * @throws Exception if the search fields are invalid or if book was not found
		 */
		void DeleteBookFromRepo(const std::string &titleSearch, const std::string &authorSearch);

		/**
		 * Searches a book in the repo by title, author, genre and/or release year
		 *
		 * @param titleSearch The title to search by
		 * @param authorSearch The author to search by
		 * @param genreSearch The genre to search by
		 * @param releaseYearSearch The release year to search by
		 * @returns The first book match from the repo
		 * @throws Exception if empty repo, if no fields valid or book not found
		 */
		Book SearchBook(const std::string &titleSearch, const std::string &authorSearch, const std::string &genreSearch, const int &releaseYearSearch);

		/**
		 * Gets books from the repo, filtered by title
		 *
		 * @param titleFilter The title to filter with
		 * @returns The books repo, filtered by title
		 * @throws Exception if there are no books in repo, if filter is invalid or no books remain after filtering
		 */
		Repo<Book> GetFilteredBooks(const std::string &titleFilter);

		/**
		 * Gets books from the repo, filtered by release year
		 *
		 * @param releaseYearFilter The release year to filter with
		 * @returns The books repo, filtered by release year
		 * @throws Exception if there are no books in repo, if filter is invalid or no books remain after filtering
		 */
		Repo<Book> GetFilteredBooks(const int &releaseYearFilter);

		/// Sorts the books repo by title
		void SortBooksByTitle();

		/// Sorts the books repo by author
		void SortBooksByAuthor();

		/// Sorts the books repo by release year and genre
		void SortBooksByReleaseYearAndGenre();
};
