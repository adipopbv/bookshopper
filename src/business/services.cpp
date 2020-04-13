#include "./services.h"

BookstoreService::BookstoreService(const Repo<Book> &booksRepo, const Repo<Book> &cart)
{
	// setting fields of BookstoreService instance to parameter values
	this->setBooksRepo(booksRepo);
	this->setCart(cart);
}

BookstoreService::~BookstoreService()
{
	// setting fields of BookstoreService instance to default values
	this->setBooksRepo(Repo<Book>());
	this->setCart(Repo<Book>());
}

std::vector<Book> BookstoreService::GetBooks() const 
{
	if (this->getBooksRepo().Empty()) // throw exception if empty repo
	{ throw EmptyRepoError("empty repo\n"); }
	// returning all books
	return this->getBooksRepo().getElements();
}

void BookstoreService::AddBookToRepo(const std::string &title, const std::string &author, const std::string &genre, const int &releaseYear)
{
	// creating a new book
	Book book = Book(title, author, genre, releaseYear);
	// making a temporary repo to operate on and then setting it in place
	Repo<Book> newRepo = this->getBooksRepo();
	newRepo.Add(book);
	this->setBooksRepo(newRepo);
}

void BookstoreService::ModifyBookInRepo(const std::string &titleSearch, const std::string &authorSearch, const std::string &title, const std::string &author, const std::string &genre, const int &releaseYear)
{
	// validating search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by\n"); }

	// making a clone of the repo
	Repo<Book> newRepo = this->getBooksRepo();

	// getting the old book
	Book oldBook = newRepo.GetElement(
		[&titleSearch, &authorSearch] (Book currentBook)
		{ 
			return (currentBook.getTitle() == titleSearch && currentBook.getAuthor() == authorSearch);
		}
	);
	// making a new book from the old values
	Book newBook = oldBook;

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

	// getting the position of modification
	int position = newRepo.GetIndexOfElement(
		[&oldBook] (Book currentBook)
		{
			return (currentBook == oldBook);
		}
	);
	newRepo.Erase(position); // remove the old book one
	// insert the new book one
	if (position == newRepo.Size())
	{ newRepo.Add(newBook); }
	else
	{ newRepo.Insert(position, newBook); } 
	this->setBooksRepo(newRepo);
}

void BookstoreService::DeleteBookFromRepo(const std::string &titleSearch, const std::string &authorSearch)
{
	// validating search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by\n"); }

	// making a clone of the repo
	Repo<Book> newRepo = this->getBooksRepo();

	// getting the old book
	Book oldBook = newRepo.GetElement(
		[&titleSearch, &authorSearch] (Book currentBook)
		{
			return (currentBook.getTitle() == titleSearch && currentBook.getAuthor() == authorSearch);
		}
	);

	//getting the position of deletion
	int positon = newRepo.GetIndexOfElement(
		[&oldBook] (Book currentBook)
		{
			return (currentBook == oldBook);
		}
	);
	newRepo.Erase(positon); // remove the old one
	this->setBooksRepo(newRepo);
}

Book BookstoreService::SearchBook(const std::string &titleSearch, const std::string &authorSearch, const std::string &genreSearch, const int &releaseYearSearch) const
{
	if (titleSearch.empty() && authorSearch.empty() && genreSearch.empty() && releaseYearSearch == -1)
	{ throw SearchFieldsError("no search fields entered\n"); } // throw exception if no searche fields entered

	// making a clone of the repo
	Repo<Book> repo = this->getBooksRepo();

	// searching the book
	Book searchedBook = repo.GetElement(
		[&titleSearch, &authorSearch, &genreSearch, &releaseYearSearch] (Book currentBook)
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

std::vector<Book> BookstoreService::GetFilteredBooks(const std::string &titleFilter) const
{
	if (titleFilter.empty()) // exception if filter invalid
	{ throw SearchFieldsError("invalid filter\n"); }
	if (this->getBooksRepo().Empty()) // exception if repo empty
	{ throw EmptyRepoError("empty repo\n"); }

	// making a clone of the repo values
	std::vector<Book> repoValues = this->getBooksRepo().getElements();
	// making a new vector to put all needed books into
	std::vector<Book> filteredValues(repoValues.size());

	// copying wanted books in the new vector
	auto iter = std::copy_if(repoValues.begin(), repoValues.end(), filteredValues.begin(),
		[&titleFilter] (Book currentBook)
		{
			if (currentBook.getTitle() == titleFilter) // getting books with the given title
			{ return true; }
			return false;
		}
	);
	// resizing filtered values vector
	filteredValues.resize(std::distance(filteredValues.begin(), iter));

	if (filteredValues.empty()) // if no books whit that title was found, throw exception
	{ throw NotFoundError("no book has that title\n"); } 
	return filteredValues;
}

std::vector<Book> BookstoreService::GetFilteredBooks(const int &releaseYearFilter) const
{
	if (releaseYearFilter < 0) // exception if filer invalid
	{ throw SearchFieldsError("\ninvalid filter value\n"); }
	if (this->getBooksRepo().Empty()) // exception if repo empty
	{ throw EmptyRepoError("the repository is empty\n"); }

	// making a clone of the repo values
	std::vector<Book> repoValues = this->getBooksRepo().getElements();
	// making a new vector to put all needed books into
	std::vector<Book> filteredValues(repoValues.size());

	// copying wanted books in the new vector
	auto iter = std::copy_if(repoValues.begin(), repoValues.end(), filteredValues.begin(),
		[&releaseYearFilter] (Book currentBook)
		{
			if (currentBook.getReleaseYear() == releaseYearFilter) // getting books with the given release year
			{ return true; }
			return false;
		}
	);
	// resizing filtered values vector
	filteredValues.resize(std::distance(filteredValues.begin(), iter));

	if (filteredValues.empty()) // if no books whit that title was found, throw exception
	{ throw NotFoundError("no book has that release year\n"); } 
	return filteredValues;
}

void BookstoreService::SortBooksByTitle()
{
	// getting a copy of the repo
	Repo<Book> repo = this->getBooksRepo();
	// sorting it
	repo.Sort(
		[] (Book first, Book second)
		{
			return (first.getTitle() < second.getTitle());
		}
	);
	// updating the original repo
	this->setBooksRepo(repo);
}

void BookstoreService::SortBooksByAuthor()
{
	// getting a copy of the repo
	Repo<Book> repo = this->getBooksRepo();
	// sorting it
	repo.Sort(
		[] (Book first, Book second)
		{
			return (first.getAuthor() < second.getAuthor());
		}
	);
	// updating the original repo
	this->setBooksRepo(repo);
}

void BookstoreService::SortBooksByReleaseYearAndGenre()
{
	// getting a copy of the repo
	Repo<Book> repo = this->getBooksRepo();
	// sorting it
	repo.Sort(
		[] (Book first, Book second)
		{
			return (first.getReleaseYear() < second.getReleaseYear()
				|| (first.getReleaseYear() == second.getReleaseYear()
				&& first.getGenre() < second.getGenre()));
		}
	);
	// updating the original repo
	this->setBooksRepo(repo);
}

std::vector<Book> BookstoreService::GetCartBooks() const 
{
	if (this->getCart().Empty()) // throw exception if empty cart
	{ throw EmptyRepoError("empty cart\n"); }
	// returning all cart books
	return this->getCart().getElements();
}

void BookstoreService::EmptyCart()
{
	// setting cart to empty repo
	this->setCart(Repo<Book>());
}

void BookstoreService::AddToCart(const std::string &title)
{
	// exception if repo empty
	if (this->getBooksRepo().Empty())
	{ throw EmptyRepoError("empty repo\n"); }
	// exception if title invalid
	if (title.empty())
	{ throw SearchFieldsError("invalid title\n"); }

	// making working copies of repo and cart
	Repo<Book> repo = this->getBooksRepo();
	Repo<Book> cart = this->getCart();

	// find the first book with that title
	Book book = repo.GetElement(
		[&title] (Book currentBook)
		{
			return (currentBook.getTitle() == title);
		}
	);
	// add found book to cart
	cart.Add(book, false);

	// updating original cart
	this->setCart(cart);
}

void BookstoreService::AddRandomBooksToCart(const int &count)
{
	// exception if repo empty
	if (this->getBooksRepo().Empty())
	{ throw EmptyRepoError("empty repo\n"); }
	// exception if count invalid
	if (count <= 0)
	{ throw ParameterError("invalid books count\n"); }

	Repo<Book> repo = this->getBooksRepo();
	Repo<Book> cart = this->getCart();

	for (int i = 0; i < count; i++)
	{
		// random index for repo elements
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, repo.Size()-1);
		int index = dist(mt);

		// add book to cart
		cart.Add(repo[index], false);
	}
	this->setCart(cart);
}

