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
	// throw exception if empty repo
	if (this->getBooksRepo().Empty())
	{ throw EmptyRepoError("empty repo\n"); }

	// return all books
	return this->getBooksRepo().getElements();
}

void BookstoreService::AddBookToRepo(const std::string &title, const std::string &author, const std::string &genre, const int &releaseYear)
{
	// create a new book
	Book book = Book(title, author, genre, releaseYear);

	// make a temporary repo to operate on and then update the original
	Repo<Book> newRepo = this->getBooksRepo();
	newRepo.Add(book);
	this->setBooksRepo(newRepo);
}

void BookstoreService::ModifyBookInRepo(const std::string &titleSearch, const std::string &authorSearch, const std::string &title, const std::string &author, const std::string &genre, const int &releaseYear)
{
	// validate search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by\n"); }

	// make a clone of the repo
	Repo<Book> newRepo = this->getBooksRepo();

	// get the old book
	Book oldBook = newRepo.GetElement(
		[&titleSearch, &authorSearch] (Book currentBook)
		{ 
			return (currentBook.getTitle() == titleSearch && currentBook.getAuthor() == authorSearch);
		}
	);
	// get a new book from the old values
	Book newBook = oldBook;

	// change wanted values of the new book
	if (!title.empty())
	{ newBook.setTitle(title); }
	if (!author.empty())
	{ newBook.setAuthor(author); }
	if (!genre.empty())
	{ newBook.setGenre(genre); }
	if (releaseYear != -1)
	{ newBook.setReleaseYear(releaseYear); }
	// validate new data
	newBook.ValidateData(newBook.getTitle(), newBook.getAuthor(), newBook.getGenre(), newBook.getReleaseYear());

	// get the position of the book to be modified
	int position = newRepo.GetIndexOfElement(
		[&oldBook] (Book currentBook)
		{
			return (currentBook == oldBook);
		}
	);
	// remove the old book
	newRepo.Erase(position);
	// insert the new book
	if (position == newRepo.Size())
	{ newRepo.Add(newBook); }
	else
	{ newRepo.Insert(position, newBook); } 
	this->setBooksRepo(newRepo);
}

void BookstoreService::DeleteBookFromRepo(const std::string &titleSearch, const std::string &authorSearch)
{
	// validate search fields
	if (titleSearch.empty() || authorSearch.empty())
	{ throw SearchFieldsError("nothing to search by\n"); }

	// make a clone of the repo
	Repo<Book> newRepo = this->getBooksRepo();

	// get the old book
	Book oldBook = newRepo.GetElement(
		[&titleSearch, &authorSearch] (Book currentBook)
		{
			return (currentBook.getTitle() == titleSearch && currentBook.getAuthor() == authorSearch);
		}
	);

	//get the position of deletion
	int positon = newRepo.GetIndexOfElement(
		[&oldBook] (Book currentBook)
		{
			return (currentBook == oldBook);
		}
	);
	// remove the old book
	newRepo.Erase(positon);
	this->setBooksRepo(newRepo);
}

Book BookstoreService::SearchBook(const std::string &titleSearch, const std::string &authorSearch, const std::string &genreSearch, const int &releaseYearSearch) const
{
	// validate search fields
	if (titleSearch.empty() && authorSearch.empty() && genreSearch.empty() && releaseYearSearch == -1)
	{ throw SearchFieldsError("no search fields entered\n"); } // throw exception if no searche fields entered

	// make a clone of the repo
	Repo<Book> repo = this->getBooksRepo();

	// search the book
	Book searchedBook = repo.GetElement(
		[&titleSearch, &authorSearch, &genreSearch, &releaseYearSearch] (Book currentBook)
		{
			bool found = true;
			// search by title
			if (!titleSearch.empty())
			{ found = found && currentBook.getTitle() == titleSearch; } 
			// search by author
			if (!authorSearch.empty())
			{ found = found && currentBook.getAuthor() == authorSearch; }
			// search by genre
			if (!genreSearch.empty())
			{ found = found && currentBook.getGenre() == genreSearch; }
			// search by release year
			if (releaseYearSearch != -1)
			{ found = found && currentBook.getReleaseYear() == releaseYearSearch; }
			return found;
		}
	);
	return searchedBook;
}

std::vector<Book> BookstoreService::GetFilteredBooks(const std::string &titleFilter) const
{
	// validate filter
	if (titleFilter.empty())
	{ throw SearchFieldsError("invalid filter\n"); }
	// throw exception if repo empty
	if (this->getBooksRepo().Empty())
	{ throw EmptyRepoError("empty repo\n"); }

	// make a clone of the repo values
	std::vector<Book> repoValues = this->getBooksRepo().getElements();
	// make a new vector to put all needed books into
	std::vector<Book> filteredValues(repoValues.size());

	// copy wanted books in the new vector
	auto iter = std::copy_if(repoValues.begin(), repoValues.end(), filteredValues.begin(),
		[&titleFilter] (Book currentBook)
		{
			// get books with the given title
			if (currentBook.getTitle() == titleFilter)
			{ return true; }
			return false;
		}
	);
	// resize filtered values vector
	filteredValues.resize(std::distance(filteredValues.begin(), iter));

	// if no books whith that title was found, throw exception
	if (filteredValues.empty())
	{ throw NotFoundError("no book has that title\n"); } 
	return filteredValues;
}

std::vector<Book> BookstoreService::GetFilteredBooks(const int &releaseYearFilter) const
{
	// validate filer
	if (releaseYearFilter < 0)
	{ throw SearchFieldsError("\ninvalid filter value\n"); }
	// throw exception if repo empty
	if (this->getBooksRepo().Empty())
	{ throw EmptyRepoError("the repository is empty\n"); }

	// make a clone of the repo values
	std::vector<Book> repoValues = this->getBooksRepo().getElements();
	// make a new vector to put all needed books into
	std::vector<Book> filteredValues(repoValues.size());

	// copy wanted books in the new vector
	auto iter = std::copy_if(repoValues.begin(), repoValues.end(), filteredValues.begin(),
		[&releaseYearFilter] (Book currentBook)
		{
			// get books with the given release year
			if (currentBook.getReleaseYear() == releaseYearFilter)
			{ return true; }
			return false;
		}
	);
	// resize filtered values vector
	filteredValues.resize(std::distance(filteredValues.begin(), iter));

	// if no books whit that title was found, throw exception
	if (filteredValues.empty())
	{ throw NotFoundError("no book has that release year\n"); } 
	return filteredValues;
}

void BookstoreService::SortBooksByTitle()
{
	// get a copy of the repo
	Repo<Book> repo = this->getBooksRepo();
	// sort the repo copy
	repo.Sort(
		[] (Book first, Book second)
		{
			return (first.getTitle() < second.getTitle());
		}
	);
	// update the original repo
	this->setBooksRepo(repo);
}

void BookstoreService::SortBooksByAuthor()
{
	// get a copy of the repo
	Repo<Book> repo = this->getBooksRepo();
	// sort the repo copy
	repo.Sort(
		[] (Book first, Book second)
		{
			return (first.getAuthor() < second.getAuthor());
		}
	);
	// update the original repo
	this->setBooksRepo(repo);
}

void BookstoreService::SortBooksByReleaseYearAndGenre()
{
	// get a copy of the repo
	Repo<Book> repo = this->getBooksRepo();
	// sort the repo copy
	repo.Sort(
		[] (Book first, Book second)
		{
			return (first.getReleaseYear() < second.getReleaseYear()
				|| (first.getReleaseYear() == second.getReleaseYear()
				&& first.getGenre() < second.getGenre()));
		}
	);
	// update the original repo
	this->setBooksRepo(repo);
}

std::vector<Book> BookstoreService::GetCartBooks() const 
{
	// throw exception if empty cart
	if (this->getCart().Empty())
	{ throw EmptyRepoError("empty cart\n"); }

	// return all cart books
	return this->getCart().getElements();
}

void BookstoreService::EmptyCart()
{
	// set cart to empty repo
	this->setCart(Repo<Book>());
}

void BookstoreService::AddToCart(const std::string &title)
{
	// throw exception if repo empty
	if (this->getBooksRepo().Empty())
	{ throw EmptyRepoError("empty repo\n"); }
	// throw exception if title invalid
	if (title.empty())
	{ throw SearchFieldsError("invalid title\n"); }

	// make working copies of repo and cart
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

	// update original cart
	this->setCart(cart);
}

void BookstoreService::AddRandomBooksToCart(const int &count)
{
	// throw exception if repo empty
	if (this->getBooksRepo().Empty())
	{ throw EmptyRepoError("empty repo\n"); }
	// throw exception if count invalid
	if (count <= 0)
	{ throw ParameterError("invalid books count\n"); }

	// make working copies of repo and cart
	Repo<Book> repo = this->getBooksRepo();
	Repo<Book> cart = this->getCart();

	for (int i = 0; i < count; i++)
	{
		// generate random index for repo elements
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, repo.Size()-1);
		int index = dist(mt);

		// add book to cart
		cart.Add(repo[index], false);
	}
	// update original repo
	this->setCart(cart);
}

