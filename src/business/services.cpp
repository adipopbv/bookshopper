#include "./services.h"

BookstoreService::BookstoreService(const std::vector<Book> &booksRepo, const std::vector<Book> &cart)
{
	// setting fields of BookstoreService instance to parameter values
	this->setBooksRepo(booksRepo);
	this->setCart(cart);
}

BookstoreService::~BookstoreService()
{
	// setting fields of BookstoreService instance to default values
	this->setBooksRepo(std::vector<Book>());
	this->setCart(std::vector<Book>());
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
		{ throw DuplicateError("book already in repo\n"); }
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

	try
	{
		std::vector<Book> newRepo = this->getBooksRepo();
		Book oldBook = *std::find_if(
			newRepo.begin(),
			newRepo.end(),
			[&titleSearch, &authorSearch](Book currentBook)
			{ return (currentBook.getTitle() == titleSearch && currentBook.getAuthor() == authorSearch); }
		);
		std::vector<Book>::iterator oldIter = std::find(newRepo.begin(), newRepo.end(), oldBook);
    
		Book newBook = oldBook; // copying the book to be modified
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
    
		newRepo.erase(oldIter); // remove the old one
		std::vector<Book>::iterator newIter = std::find(newRepo.begin(), newRepo.end(), newBook);
		if (newBook == *newIter)
		{ throw DuplicateError("book already in repo\n"); }
		newRepo.insert(oldIter, newBook); // insert the new one
		this->setBooksRepo(newRepo);
	}
	catch (std::exception& e) 
	{
		throw NotFoundError("book not found in repo\n"); // exception if book not found
	}
}

void BookstoreService::DeleteBookFromRepo(const std::string &titleSearch, const std::string &authorSearch)
{
	// validating search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by\n"); }

	try
	{
		std::vector<Book> newRepo = this->getBooksRepo();
		Book oldBook = *std::find_if(
			newRepo.begin(),
			newRepo.end(),
			[&titleSearch, &authorSearch](Book currentBook)
			{ return (currentBook.getTitle() == titleSearch && currentBook.getAuthor() == authorSearch); }
		);
		std::vector<Book>::iterator oldIter = std::find(newRepo.begin(), newRepo.end(), oldBook);
    
		newRepo.erase(oldIter); // remove the old one
		this->setBooksRepo(newRepo);
	}
	catch (std::exception& e)
	{
		throw NotFoundError("book not found in repo\n"); // exception if book not found
	}
}

Book BookstoreService::SearchBook(const std::string &titleSearch, const std::string &authorSearch, const std::string &genreSearch, const int &releaseYearSearch)
{
	if (titleSearch.empty() && authorSearch.empty() && genreSearch.empty() && releaseYearSearch == -1)
	{ throw SearchFieldsError("no search fields entered\n"); } // throw exception if no searche fields entered

	std::vector<Book> repo = this->getBooksRepo();
	try
	{
		Book searchedBook = *std::find_if(
			repo.begin(),
			repo.end(),
			[&titleSearch, &authorSearch, &genreSearch, &releaseYearSearch]
			(Book currentBook)
			{
				bool found = true;
				if (!titleSearch.empty()) // search by title
				{ found = found && currentBook.getTitle() == titleSearch; } 
				if (!authorSearch.empty()) // search by author
				{ found = found && currentBook.getAuthor() == authorSearch; }
				if (!genreSearch.empty()) // search by genre
				{ found = found && currentBook.getGenre() == genreSearch; }
				if (releaseYearSearch != -1) // search by release year
				{ found = found && currentBook.getReleaseYear() == releaseYearSearch; }
				return found;
			}
		);
		return searchedBook;
	}
	catch (std::exception& e)
	{
		throw NotFoundError("book not found\n");
	}
}

std::vector<Book> BookstoreService::GetFilteredBooks(const std::string &titleFilter)
{
	if (titleFilter.empty()) // exception if filter invalid
	{ throw SearchFieldsError("invalid filter value\n"); }
	if (this->getBooksRepo().empty()) // exception if repo empty
	{ throw EmptyRepoError("the repository is empty\n"); }

	std::vector<Book> filteredBooks = std::vector<Book>(); // making a new repo to put all needed books into
	std::vector<Book> repo = this->getBooksRepo();
	std::for_each(repo.begin(), repo.end(),
		[&filteredBooks, &titleFilter]
		(Book currentBook)
		{
			if (currentBook.getTitle() == titleFilter) // getting books with the given title
			{ filteredBooks.push_back(currentBook); }
		}
	);

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
	std::vector<Book> repo = this->getBooksRepo();
	std::for_each(repo.begin(), repo.end(),
		[&filteredBooks, &releaseYearFilter]
		(Book currentBook)
		{
			if (currentBook.getReleaseYear() == releaseYearFilter) // getting books with the given title
			{ filteredBooks.push_back(currentBook); }
		}
	);

	if (filteredBooks.empty()) // if no books whit that release year was found, throw exception
	{ throw NotFoundError("no book has that release year\n"); }
	return filteredBooks;
}

void BookstoreService::SortBooksByTitle()
{
	// getting a copy of the repo
	std::vector<Book> repo = this->getBooksRepo();
	std::sort(repo.begin(), repo.end(), [](Book first, Book second){ return (first.getTitle() < second.getTitle()); });
	this->setBooksRepo(repo);
}

void BookstoreService::SortBooksByAuthor()
{
	// getting a copy of the repo
	std::vector<Book> repo = this->getBooksRepo();
	std::sort(repo.begin(), repo.end(), [](Book first, Book second){ return (first.getAuthor() < second.getAuthor()); });
	this->setBooksRepo(repo);
}

void BookstoreService::SortBooksByReleaseYearAndGenre()
{
	// getting a copy of the repo
	std::vector<Book> repo = this->getBooksRepo();
	std::sort(repo.begin(), repo.end(), [](Book first, Book second){ 
		return (first.getReleaseYear() < second.getReleaseYear()
				|| (first.getReleaseYear() == second.getReleaseYear()
				&& first.getGenre() < second.getGenre()));
	});
	this->setBooksRepo(repo);
}

std::vector<Book> BookstoreService::GetCartBooks() const 
{
	if (this->getCart().empty()) // throw exception if empty cart
	{ throw EmptyRepoError("no book in cart\n"); }
	// returning all cart books
	return this->getCart();
}

void BookstoreService::EmptyCart()
{
	this->setCart(std::vector<Book>());
}

void BookstoreService::AddToCart(const std::string &title)
{
	// exception if repo empty
	if (this->getBooksRepo().empty())
	{ throw EmptyRepoError("the book repo is empty\n"); }
	// exception if title invalid
	if (title.empty())
	{ throw SearchFieldsError("invalid title\n"); }

	try
	{
		std::vector<Book> repo = this->getBooksRepo();
		std::vector<Book> cart = this->getCart();
		// find the first book with that title
		Book book = *std::find_if(repo.begin(), repo.end(), [&title](Book currentBook){ return currentBook.getTitle() == title; });

		cart.push_back(book);
		this->setCart(cart);
	}
	catch (std::exception& e)
	{
		throw NotFoundError("book not found\n");
	}
}

void BookstoreService::AddRandomBooksToCart(const int &count)
{
	// exception if repo empty
	if (this->getBooksRepo().empty())
	{ throw EmptyRepoError("the book repo is empty\n"); }
	// exception if count invalid
	if (count <= 0)
	{ throw ParameterError("invalid books count\n"); }

	std::vector<Book> repo = this->getBooksRepo();
	std::vector<Book> cart = this->getCart();

	for (int i = 0; i < count; i++)
	{
		// random index for repo elements
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, repo.size()-1);
		int index = dist(mt);

		// add book to cart
		cart.push_back(repo[index]);
	}
	this->setCart(cart);
}

