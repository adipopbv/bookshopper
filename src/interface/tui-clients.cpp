#include "./tui-clients.h"

TerminalBookstoreClient::TerminalBookstoreClient(std::shared_ptr<BookstoreService> const &bookstoreService)
{
	this->setBookstoreService(bookstoreService);
}

TerminalBookstoreClient::~TerminalBookstoreClient()
{
	this->setBookstoreService(std::make_shared<BookstoreService>());
}

int TerminalBookstoreClient::ReadInt(std::string const &prompt) const
{
	this->PrintString(prompt);
	std::string input = this->ReadString();
	try { return std::stoi(input); } 
	catch (std::exception& e) { return -1; }
	return -1;
}

std::string TerminalBookstoreClient::ReadString(std::string const &prompt) const
{
	this->PrintString(prompt);
	std::string value = "";
	std::getline(std::cin, value, '\n');
	return value;
}

void TerminalBookstoreClient::PrintString(std::string const &message) const
{
	std::cout << message;
}

void TerminalBookstoreClient::PrintBook(Book const &book) const
{
	this->PrintString(
		"  ┌─Title: " + book.getTitle() + "\n" +
		"  ├─Author: " + book.getAuthor() + "\n" +
		"  ├─Genre: " + book.getGenre() + "\n" +
		"  └─Release year: " + std::to_string(book.getReleaseYear()) + "\n"
	);
}

void TerminalBookstoreClient::ListAllBooks() const
{
	std::vector<Book> books = this->getBookstoreService()->GetBooks();
	std::for_each(books.begin(), books.end(), [this](Book book){
		this->PrintString("──────────\n");
		this->PrintBook(book);
	});
	this->PrintString("──────────\n\n");
}

void TerminalBookstoreClient::AddBook()
{
	this->PrintString("»»Add book\n");
	this->PrintString("  ╚═Book to be added:\n");
	std::string title = this->ReadString("    ├─Title: ");
	std::string author = this->ReadString("    ├─Author: ");
	std::string genre = this->ReadString("    ├─Genre: ");
	int releaseYear = this->ReadInt("    └─Release year: ");

	this->PrintString("\n");
	this->bookstoreService->AddBookToRepo(title, author, genre, releaseYear);
	this->PrintString("»Operation succesful!\n\n");
}

void TerminalBookstoreClient::ModifyBook()
{
	this->PrintString("»»Modify book\n");
	this->PrintString("  ╠═Book to be modified:\n");
	std::string titleSearch = this->ReadString("  ║ ├─Title: ");
	std::string authorSearch = this->ReadString("  ║ └─Author: ");
	this->PrintString("  ╚═New book values (leave field empty to not modify):\n");
	std::string title = this->ReadString("    ├─Title: ");
	std::string author = this->ReadString("    ├─Author: ");
	std::string genre = this->ReadString("    ├─Genre: ");
	int releaseYear = this->ReadInt("    └─Release year: ");

	this->PrintString("\n");
	this->bookstoreService->ModifyBookInRepo(titleSearch, authorSearch, title, author, genre, releaseYear);
	this->PrintString("»Operation succesful!\n\n");
}

void TerminalBookstoreClient::DeleteBook()
{
	this->PrintString("»»Delete book\n");
	this->PrintString("  ╚═Book to be deleted:\n");
	std::string titleSearch = this->ReadString("    ├─Title: ");
	std::string authorSearch = this->ReadString("    └─Author: ");

	this->PrintString("\n");
	this->bookstoreService->DeleteBookFromRepo(titleSearch, authorSearch);
	this->PrintString("»Operation succesful!\n\n");
}

void TerminalBookstoreClient::SearchBook()
{
	this->PrintString("»»Search book\n");
	this->PrintString("  ╚═Fields to search by (leave field empty to ignore):\n");
	std::string titleSearch = this->ReadString("    ├─Title: ");
	std::string authorSearch = this->ReadString("    ├─Author: ");
	std::string genreSearch = this->ReadString("    ├─Genre: ");
	int releaseYearSearch = this->ReadInt("    └─Release year: ");

	this->PrintString("\n");
	Book searchedBook = this->bookstoreService->SearchBook(titleSearch, authorSearch, genreSearch, releaseYearSearch);
	this->PrintString("──────────\n");
	this->PrintBook(searchedBook);
	this->PrintString("──────────\n\n");
}

void TerminalBookstoreClient::FilterBooks()
{
	this->PrintString("»»Filter books\n");
	this->PrintString("  ╚═Fields to filter by:\n");
	this->PrintString("    ╠═[1]: Title\n");
	this->PrintString("    ╚═[2]: Release year\n");

	std::string titleFilter;
	int releaseYearSearch;
	std::vector<Book> filteredBooks;

	this->PrintString("\n");
	int option = this->ReadInt("»Enter option: ");
	this->PrintString("\n");
	switch (option)
	{
		case 1:
			titleFilter = this->ReadString("»Enter title: ");
			this->PrintString("\n");
			filteredBooks = this->getBookstoreService()->GetFilteredBooks(titleFilter);
			break;

		case 2:
			releaseYearSearch = this->ReadInt("»Enter release year: ");
			this->PrintString("\n");
			filteredBooks = this->getBookstoreService()->GetFilteredBooks(releaseYearSearch);
			break;

		default:
			this->PrintString("»Invalid command!\n\n");
			return;
			break;
	}
	std::for_each(filteredBooks.begin(), filteredBooks.end(), [this](Book filteredBook){
		this->PrintString("──────────\n");
		this->PrintBook(filteredBook);
	});
	this->PrintString("──────────\n\n");
}

void TerminalBookstoreClient::SortBooks()
{
	this->PrintString("»»Sort books\n");
	this->PrintString("  ╚═Fields to sort by:\n");
	this->PrintString("    ╠═[1]: Title\n");
	this->PrintString("    ╠═[2]: Author\n");
	this->PrintString("    ╚═[3]: Release year and genre\n");

	this->PrintString("\n");
	int option = this->ReadInt("»Enter option: ");
	this->PrintString("\n");
	std::shared_ptr<BookstoreService> service = this->getBookstoreService();
	switch (option)
	{
		case 1:
			this->PrintString("\n");
			service->SortBooksByTitle();
			break;

		case 2:
			this->PrintString("\n");
			service->SortBooksByAuthor();
			break;

		case 3:
			this->PrintString("\n");
			service->SortBooksByReleaseYearAndGenre();
			break;

		default:
			this->PrintString("»Invalid command!\n\n");
			return;
			break;
	}

	this->setBookstoreService(service);
	this->ListAllBooks();
}

void TerminalBookstoreClient::UndoOperation()
{
	this->PrintString("»»Undo last operation\n");
	this->PrintString("  ╚═Are you sure?\n");
	this->PrintString("    ╠═[1]: Yes\n");
	this->PrintString("    ╚═[2]: No\n");

	this->PrintString("\n");
	int option = this->ReadInt("»Enter option: ");
	this->PrintString("\n");
	std::shared_ptr<BookstoreService> service = this->getBookstoreService();
	switch (option)
	{
		case 1:
			service->UndoOperation();
			this->setBookstoreService(service);
			this->PrintString("»Operation succesful!\n\n");
			break;

		case 2:
			this->PrintString("»Operation aborted!\n\n");
			return;
			break;

		default:
			this->PrintString("»Invalid command!\n\n");
			return;
			break;
	}
}

void TerminalBookstoreClient::ListAllCartBooks() const
{
	std::vector<Book> booksInCart = this->getBookstoreService()->GetCartBooks();
	std::for_each(booksInCart.begin(), booksInCart.end(), [this](Book book){
		this->PrintString("──────────\n");
		this->PrintBook(book);
	});
	this->PrintString("──────────\n");
	this->PrintString("»Books in cart: " + std::to_string(this->getBookstoreService()->getCart()->Size()) + ".\n\n");
}

void TerminalBookstoreClient::EmptyCart()
{
	std::shared_ptr<BookstoreService> service = this->getBookstoreService();
	service->EmptyCart();
	this->setBookstoreService(service);
	this->PrintString("»Operation succesful!\n");
	this->PrintString("»Books in cart: " + std::to_string(this->getBookstoreService()->getCart()->Size()) + ".\n\n");
}

void TerminalBookstoreClient::AddToCart()
{
	this->PrintString("»»Add book to cart\n");
	this->PrintString("  ╚═Book to be added:\n");
	std::string title = this->ReadString("    └─Title: ");

	this->PrintString("\n");
	std::shared_ptr<BookstoreService> service = this->getBookstoreService();
	service->AddToCart(title);
	this->setBookstoreService(service);
	this->PrintString("»Operation succesful!\n");
	this->PrintString("»Books in cart: " + std::to_string(this->getBookstoreService()->getCart()->Size()) + ".\n\n");
}

void TerminalBookstoreClient::AddRandomBooksToCart()
{
	this->PrintString("»»Add random books to cart\n");
	this->PrintString("  ╚═Number of books to be added:\n");
	int count = this->ReadInt("    └─Books count: ");

	this->PrintString("\n");
	std::shared_ptr<BookstoreService> service = this->getBookstoreService();
	service->AddRandomBooksToCart(count);
	this->setBookstoreService(service);
	this->PrintString("»Operation succesful!\n");
	this->PrintString("»Books in cart: " + std::to_string(this->getBookstoreService()->getCart()->Size()) + ".\n\n");
}

void TerminalBookstoreClient::SaveCartToFile()
{
	this->PrintString("»»Save cart to file\n");
	this->PrintString("  ╚═Select file:\n");
	std::string fileName = this->ReadString("    └─Name: ");

	this->PrintString("\n");
	this->getBookstoreService()->SaveCartToFile(fileName);
	this->PrintString("»Operation succesful!\n");
	this->PrintString("»Books in cart: " + std::to_string(this->getBookstoreService()->getCart()->Size()) + ".\n\n");
}

void TerminalBookstoreClient::ListAllCartTitles() const
{
	std::vector<std::string> booksTitles = this->getBookstoreService()->GetCartTitles();
	std::string rezult;
	rezult = std::accumulate(booksTitles.begin(), booksTitles.end(), rezult, 
		[] (std::string str1, std::string str2)
		{
			return str1 + "──────────\n" + str2 + "\n";
		}
	);
	this->PrintString(rezult + "──────────\n\n");
}

void TerminalBookstoreClient::ExitApplication() const
{
	this->PrintString("»Exiting application...\n\n");
}

int TerminalBookstoreClient::RunApplication()
{
	this->PrintString("═════ Bookshopper ═════\n\n");
	while (true)
	{
		try
		{
			this->PrintString(std::string(
				"»»Menu\n") +
				"  ╠═[0]: Exit app\n" + 
				"  ╠═Basic operations:\n" + 
				"  ║ ╠═[1]: List all books\n" + 
				"  ║ ╠═[2]: Add book\n" +
				"  ║ ╠═[3]: Modify book\n" +
				"  ║ ╠═[4]: Delete book\n" +
				"  ║ ╠═[5]: Search book\n" +
				"  ║ ╠═[6]: Filter books\n" +
				"  ║ ╠═[7]: Sort books\n" +
				"  ║ ╚═[8]: Undo operation\n" +
				"  ╚═Shopping cart:\n" +
				"    ╠═[9]: List cart\n" +
				"    ╠═[10]: Empty cart\n" +
				"    ╠═[11]: Add book to cart\n" +
				"    ╠═[12]: Add random books to cart\n" +
				"    ╠═[13]: Save cart to file\n" +
				"    ╚═[14]: List all cart titles\n"
			);
			this->PrintString("\n");
			int command = this->ReadInt("»Please input a command: ");
			this->PrintString("\n═══════════════════════\n\n");
			switch (command)
			{
				case 0: 
					this->ExitApplication();
					return 0;
					break;
	
				case 1:
					this->ListAllBooks();
					break;
	
				case 2:
					this->AddBook();
					break;
	
				case 3:
					this->ModifyBook();
					break;
	
				case 4:
					this->DeleteBook();
					break;

				case 5:
					this->SearchBook();
					break;

				case 6:
					this->FilterBooks();
					break;

				case 7:
					this->SortBooks();
					break;

				case 8:
					this->UndoOperation();
					break;

				case 9:
					this->ListAllCartBooks();
					break;

				case 10:
					this->EmptyCart();
					break;

				case 11:
					this->AddToCart();
					break;

				case 12:
					this->AddRandomBooksToCart();
					break;

				case 13:
					this->SaveCartToFile();
					break;

				case 14:
					this->ListAllCartTitles();
					break;
	
				default:
					this->PrintString("»Invalid command!\n\n");
					break;
			}
		}
		catch (AppException& e)
		{
			this->PrintString("»Error:\n" + e.getMessage() + "\n");
		}
		this->PrintString("═══════════════════════\n\n");
	}
	return 0;
}
