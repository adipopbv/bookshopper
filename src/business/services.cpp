#include "./services.h"

BookstoreService::BookstoreService(const Repo<Book> &booksRepo)
{
	// setting fields of BookstoreService instance to parameter values
	this->setBooksRepo(booksRepo);
}

BookstoreService::~BookstoreService()
{
	// setting fields of BookstoreService instance to default values
	this->setBooksRepo(Repo<Book>());
}

Repo<Book> BookstoreService::GetBooks() const 
{
	if (this->getBooksRepo().Empty()) // throw exception if empty repo
	{ throw EmptyRepoError("no book in repository"); }
	// returning all books
	return this->getBooksRepo();
}

void BookstoreService::AddBookToRepo(const std::string &title, const std::string &author, const std::string &genre, const int &releaseYear)
{
	Book book = Book(title, author, genre, releaseYear);
	this->booksRepo.Add(book); // adding a new book to the end of the repo
}

void BookstoreService::ModifyBookInRepo(const std::string &titleSearch, const std::string &authorSearch, const std::string &title, const std::string &author, const std::string &genre, const int &releaseYear)
{
	// validating search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by"); }

	// making a working copy of the repo
	Repo<Book> tempRepo = this->getBooksRepo();

	// getting the book to be modified's index
	int oldBookIndex = this->getBooksRepo().GetIndexOfElement(
		[ &titleSearch, &authorSearch ]
		( Book searchedBook ) 
		{ return searchedBook.getTitle() == titleSearch && searchedBook.getAuthor() == authorSearch; }
	);

	// making a new one with the wanted values changed
	Book newBook = tempRepo[oldBookIndex];
	if (!title.empty())
	{ newBook.setTitle(title); }
	if (!author.empty())
	{ newBook.setAuthor(author); }
	if (!genre.empty())
	{ newBook.setGenre(genre); }
	if (releaseYear != -1)
	{ newBook.setReleaseYear(releaseYear); }
	newBook.ValidateData(newBook.getTitle(), newBook.getAuthor(), newBook.getGenre(), newBook.getReleaseYear());

	// removing the old one and inserting the new one in place
	tempRepo.ValidateDuplicate(newBook);
	tempRepo.Erase(oldBookIndex); // remove the old one
	tempRepo.Insert(newBook, oldBookIndex); // insert the new one
	// set the new state
	this->setBooksRepo(tempRepo);
}

void BookstoreService::DeleteBookFromRepo(const std::string &titleSearch, const std::string &authorSearch)
{
	// validating search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by"); }

	// making a working copy of the repo
	Repo<Book> tempRepo = this->getBooksRepo();

	// getting the book to be modified's index
	int oldBookIndex = this->getBooksRepo().GetIndexOfElement(
		[ &titleSearch, &authorSearch ]
		( Book searchedBook ) 
		{ return searchedBook.getTitle() == titleSearch && searchedBook.getAuthor() == authorSearch; }
	);

	tempRepo.Erase(oldBookIndex); // removing the book
	// set the new state
	this->setBooksRepo(tempRepo);
}

Book BookstoreService::SearchBook(const std::string &titleSearch, const std::string &authorSearch, const std::string &genreSearch, const int &releaseYearSearch)
{
	if (titleSearch.empty() && authorSearch.empty() && genreSearch.empty() && releaseYearSearch == -1)
	{ throw SearchFieldsError("\nno search fields entered"); } // throw exception if no searche fields entered

	Book searchedBook = this->getBooksRepo().GetElement(
		[ &titleSearch, &authorSearch, &genreSearch, &releaseYearSearch ]
		( Book searchedBook ) 
		{ 
			bool found = true;
			if (!titleSearch.empty()) // search by title
			{ found = found && searchedBook.getTitle() == titleSearch; } 
			if (!authorSearch.empty()) // search by author
			{ found = found && searchedBook.getAuthor() == authorSearch; }
			if (!genreSearch.empty()) // search by genre
			{ found = found && searchedBook.getGenre() == genreSearch; }
			if (releaseYearSearch != -1) // search by release year
			{ found = found && searchedBook.getReleaseYear() == releaseYearSearch; }
			return found;
		}
	);
	return searchedBook;
}

Repo<Book> BookstoreService::GetFilteredBooks(const std::string &titleFilter)
{
	if (titleFilter.empty()) // exception if filter invalid
	{ throw SearchFieldsError("\ninvalid filter value"); }
	if (this->getBooksRepo().Empty()) // exception if repo empty
	{ throw EmptyRepoError("\nthe repository is empty"); }

	Repo<Book> filteredBooks = Repo<Book>(); // making a new repo to put all needed books into

	for (int i = 0; i < this->getBooksRepo().Size(); i++) // iterating all books
	{
		if (this->getBooksRepo()[i].getTitle() == titleFilter) // getting books with the given title
		{ filteredBooks.Add(this->getBooksRepo()[i]); }
	}
	if (filteredBooks.Empty()) // if no books whit that title was found, throw exception
	{ throw NotFoundError("\nno book has that title"); } 
	return filteredBooks;
}

Repo<Book> BookstoreService::GetFilteredBooks(const int &releaseYearFilter)
{
	if (releaseYearFilter < 0) // exception if filer invalid
	{ throw SearchFieldsError("\ninvalid filter value"); }
	if (this->getBooksRepo().Empty()) // exception if repo empty
	{ throw EmptyRepoError("\nthe repository is empty"); }

	Repo<Book> filteredBooks = Repo<Book>(); // making a new repo to put all needed books into

	for (int i = 0; i < this->getBooksRepo().Size(); i++) // iterating all books
	{
		if (this->getBooksRepo()[i].getReleaseYear() == releaseYearFilter) // getting books with the given release year
		{ filteredBooks.Add(this->getBooksRepo()[i]); }
	}
	if (filteredBooks.Empty()) // if no books whit that release year was found, throw exception
	{ throw NotFoundError("no book has that release year"); }
	return filteredBooks;
}

void BookstoreService::SortBooksByTitle()
{
	// getting a copy of the repo
	Repo<Book> tempRepo = this->getBooksRepo();
	for (int i = 0; i < tempRepo.Size() - 1; i++)
	{
		for (int j = i + 1; j < tempRepo.Size(); j++)
		{
			if (tempRepo[i].getTitle() > tempRepo[j].getTitle())
			{ tempRepo.Swap(i, j); } // swap books
		}
	}
	this->setBooksRepo(tempRepo);
}

void BookstoreService::SortBooksByAuthor()
{
	Repo<Book> tempRepo = this->getBooksRepo();
	for (int i = 0; i < tempRepo.Size() - 1; i++)
	{
		for (int j = i + 1; j < tempRepo.Size(); j++)
		{
			if (tempRepo[i].getAuthor() > tempRepo[j].getAuthor())
			{ tempRepo.Swap(i, j); } // swap books
		}
	}
	this->setBooksRepo(tempRepo);
}

void BookstoreService::SortBooksByReleaseYearAndGenre()
{
	Repo<Book> tempRepo = this->getBooksRepo();
	for (int i = 0; i < tempRepo.Size() - 1; i++)
	{
		for (int j = i + 1; j < tempRepo.Size(); j++)
		{
			if (tempRepo[i].getReleaseYear() > tempRepo[j].getReleaseYear()
					|| (tempRepo[i].getReleaseYear() == tempRepo[j].getReleaseYear()
					&& tempRepo[i].getGenre() > tempRepo[j].getGenre()))
			{ tempRepo.Swap(i, j); } // swap books if release years differ or if equal and genres differ
		}
	}
	this->setBooksRepo(tempRepo);
}

