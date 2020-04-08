#include "./services.h"

BookstoreService::BookstoreService(const std::vector<Book> &booksRepo)
{
	// setting fields of BookstoreService instance to parameter values
	this->setBooksRepo(booksRepo);
}

BookstoreService::~BookstoreService()
{
	// setting fields of BookstoreService instance to default values
	this->setBooksRepo(std::vector<Book>());
}

std::vector<Book> BookstoreService::GetBooks() const 
{
	if (this->getBooksRepo().empty()) // throw exception if empty repo
	{ throw EmptyRepoError("no book in repository\n"); }
	// returning all books
	return this->getBooksRepo();
}

void BookstoreService::AddBookToRepo(const std::string &title, const std::string &author, const std::string &genre, const int &releaseYear)
{
	Book book = Book(title, author, genre, releaseYear);
	std::for_each(this->booksRepo.begin(), this->booksRepo.end(), [&book](Book currentBook){ 
		if (currentBook == book)
			throw DuplicateError("book already in repo\n");
	});
	std::vector<Book> newRepo = this->getBooksRepo();
	newRepo.push_back(book);
	this->setBooksRepo(newRepo); // adding a new book to the end of the repo
}

void BookstoreService::ModifyBookInRepo(const std::string &titleSearch, const std::string &authorSearch, const std::string &title, const std::string &author, const std::string &genre, const int &releaseYear)
{
	// validating search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by\n"); }

	std::vector<Book> newRepo = this->getBooksRepo();
	for (int i = 0; i < static_cast<int>(newRepo.size()); i++) // searching for the book with the given title and author
	{
		if (newRepo[i].getTitle() == titleSearch && newRepo[i].getAuthor() == authorSearch) // change book if found
		{
			Book newBook = newRepo[i]; // copying the book to be modified

			// changing wanted values
			if (!title.empty())
			{ newBook.setTitle(title); }
			if (!author.empty())
			{ newBook.setAuthor(author); }
			if (!genre.empty())
			{ newBook.setGenre(genre); }
			if (releaseYear != -1)
			{ newBook.setReleaseYear(releaseYear); }
			newBook.ValidateData(newBook.getTitle(), newBook.getAuthor(), newBook.getGenre(), newBook.getReleaseYear());

			newRepo.erase(newRepo.begin() + i); // remove the old one
			for (int i = 0; i < static_cast<int>(this->getBooksRepo().size()); i++)
				if (newRepo[i] == newBook)
					throw DuplicateError("book already in repo\n");
			newRepo.insert(newRepo.begin() + i, newBook); // insert the new one
			this->setBooksRepo(newRepo);

			return;
		}
	}
	throw NotFoundError("book not found in repo\n"); // exception if book not found
}

void BookstoreService::DeleteBookFromRepo(const std::string &titleSearch, const std::string &authorSearch)
{
	// validating search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by\n"); }

	std::vector<Book> newRepo = this->getBooksRepo();
	for (int i = 0; i < static_cast<int>(newRepo.size()); i++) // searching for the book with the given title and author
	{
		if (newRepo[i].getTitle() == titleSearch && newRepo[i].getAuthor() == authorSearch) // change book if found
		{
			newRepo.erase(newRepo.begin() + i); // remove the old one
			this->setBooksRepo(newRepo);
			return;
		}
	}
	throw NotFoundError("book not found in repo\n"); // exception if book not found
}

Book BookstoreService::SearchBook(const std::string &titleSearch, const std::string &authorSearch, const std::string &genreSearch, const int &releaseYearSearch)
{
	if (titleSearch.empty() && authorSearch.empty() && genreSearch.empty() && releaseYearSearch == -1)
	{ throw SearchFieldsError("no search fields entered\n"); } // throw exception if no searche fields entered
	Book searchedBook = Book();
	for (int i = 0; i < static_cast<int>(this->getBooksRepo().size()); i++)
	{ 
		searchedBook = this->getBooksRepo()[i];
		bool found = true;
		if (!titleSearch.empty()) // search by title
		{ found = found && searchedBook.getTitle() == titleSearch; } 
		if (!authorSearch.empty()) // search by author
		{ found = found && searchedBook.getAuthor() == authorSearch; }
		if (!genreSearch.empty()) // search by genre
		{ found = found && searchedBook.getGenre() == genreSearch; }
		if (releaseYearSearch != -1) // search by release year
		{ found = found && searchedBook.getReleaseYear() == releaseYearSearch; }

		if (found)
			return searchedBook;
	}
	throw NotFoundError("book not found\n");
}

std::vector<Book> BookstoreService::GetFilteredBooks(const std::string &titleFilter)
{
	if (titleFilter.empty()) // exception if filter invalid
	{ throw SearchFieldsError("invalid filter value\n"); }
	if (this->getBooksRepo().empty()) // exception if repo empty
	{ throw EmptyRepoError("the repository is empty\n"); }

	std::vector<Book> filteredBooks = std::vector<Book>(); // making a new repo to put all needed books into

	for (int i = 0; i < static_cast<int>(this->getBooksRepo().size()); i++) // iterating all books
	{
		if (this->getBooksRepo()[i].getTitle() == titleFilter) // getting books with the given title
		{ filteredBooks.push_back(this->getBooksRepo()[i]); }
	}
	if (filteredBooks.empty()) // if no books whit that title was found, throw exception
	{ throw NotFoundError("no book has that title\n"); } 
	return filteredBooks;
}

std::vector<Book> BookstoreService::GetFilteredBooks(const int &releaseYearFilter)
{
	if (releaseYearFilter < 0) // exception if filer invalid
	{ throw SearchFieldsError("\ninvalid filter value\n"); }
	if (this->getBooksRepo().empty()) // exception if repo empty
	{ throw EmptyRepoError("the repository is empty\n"); }

	std::vector<Book> filteredBooks = std::vector<Book>(); // making a new repo to put all needed books into

	for (int i = 0; i < static_cast<int>(this->getBooksRepo().size()); i++) // iterating all books
	{
		if (this->getBooksRepo()[i].getReleaseYear() == releaseYearFilter) // getting books with the given release year
		{ filteredBooks.push_back(this->getBooksRepo()[i]); }
	}
	if (filteredBooks.empty()) // if no books whit that release year was found, throw exception
	{ throw NotFoundError("no book has that release year\n"); }
	return filteredBooks;
}

void BookstoreService::SortBooksByTitle()
{
	// getting a copy of the repo
	std::vector<Book> tempRepo = this->getBooksRepo();
	for (int i = 0; i < static_cast<int>(tempRepo.size()) - 1; i++)
	{
		for (int j = i + 1; j < static_cast<int>(tempRepo.size()); j++)
		{
			if (tempRepo[i].getTitle() > tempRepo[j].getTitle())
			{ std::swap(tempRepo[i], tempRepo[j]); } // swap books
		}
	}
	this->setBooksRepo(tempRepo);
}

void BookstoreService::SortBooksByAuthor()
{
	std::vector<Book> tempRepo = this->getBooksRepo();
	for (int i = 0; i < static_cast<int>(tempRepo.size()) - 1; i++)
	{
		for (int j = i + 1; j < static_cast<int>(tempRepo.size()); j++)
		{
			if (tempRepo[i].getAuthor() > tempRepo[j].getAuthor())
			{ std::swap(tempRepo[i], tempRepo[j]); } // swap books
		}
	}
	this->setBooksRepo(tempRepo);
}

void BookstoreService::SortBooksByReleaseYearAndGenre()
{
	std::vector<Book> tempRepo = this->getBooksRepo();
	for (int i = 0; i < static_cast<int>(tempRepo.size()) - 1; i++)
	{
		for (int j = i + 1; j < static_cast<int>(tempRepo.size()); j++)
		{
			if (tempRepo[i].getReleaseYear() > tempRepo[j].getReleaseYear()
					|| (tempRepo[i].getReleaseYear() == tempRepo[j].getReleaseYear()
					&& tempRepo[i].getGenre() > tempRepo[j].getGenre()))
			{ std::swap(tempRepo[i], tempRepo[j]); } // swap books if release years differ or if equal and genres differ
		}
	}
	this->setBooksRepo(tempRepo);
}

