#include "./clients.h"

BookstoreClient::BookstoreClient(const BookstoreService &bookstoreService) :io(TerminalIO())
{
	this->setBookstoreService(bookstoreService);
}

BookstoreClient::~BookstoreClient()
{
	this->setBookstoreService(BookstoreService());
}

void BookstoreClient::PrintBook(Book const book) const
{
	this->getIO().PrintString(
		"  ┌─Title: " + book.getTitle() + "\n" +
		"  ├─Author: " + book.getAuthor() + "\n" +
		"  ├─Genre: " + book.getGenre() + "\n" +
		"  └─Release year: " + std::to_string(book.getReleaseYear()) + "\n"
	);
}

void BookstoreClient::ListAllBooks() const
{
	std::vector<Book> books = this->getBookstoreService().GetBooks();
	std::for_each(books.begin(), books.end(), [this](Book book){
		this->getIO().PrintString("──────────\n");
		this->PrintBook(book);
	});
	this->getIO().PrintString("──────────\n\n");
}

void BookstoreClient::AddBook()
{
	this->getIO().PrintString("»»Add book\n");
	this->getIO().PrintString("  ╚═Book to be added:\n");
	std::string title = this->getIO().ReadString("    ├─Title: ");
	std::string author = this->getIO().ReadString("    ├─Author: ");
	std::string genre = this->getIO().ReadString("    ├─Genre: ");
	int releaseYear = this->getIO().ReadInt("    └─Release year: ");

	this->getIO().PrintString("\n");
	this->bookstoreService.AddBookToRepo(title, author, genre, releaseYear);
	this->getIO().PrintString("»Operation succesful!\n\n");
}

void BookstoreClient::ModifyBook()
{
	this->getIO().PrintString("»»Modify book\n");
	this->getIO().PrintString("  ╠═Book to be modified:\n");
	std::string titleSearch = this->getIO().ReadString("  ║ ├─Title: ");
	std::string authorSearch = this->getIO().ReadString("  ║ └─Author: ");
	this->getIO().PrintString("  ╚═New book values (leave field empty to not modify):\n");
	std::string title = this->getIO().ReadString("    ├─Title: ");
	std::string author = this->getIO().ReadString("    ├─Author: ");
	std::string genre = this->getIO().ReadString("    ├─Genre: ");
	int releaseYear = this->getIO().ReadInt("    └─Release year: ");

	this->getIO().PrintString("\n");
	this->bookstoreService.ModifyBookInRepo(titleSearch, authorSearch, title, author, genre, releaseYear);
	this->getIO().PrintString("»Operation succesful!\n\n");
}

void BookstoreClient::DeleteBook()
{
	this->getIO().PrintString("»»Delete book\n");
	this->getIO().PrintString("  ╚═Book to be deleted:\n");
	std::string titleSearch = this->getIO().ReadString("    ├─Title: ");
	std::string authorSearch = this->getIO().ReadString("    └─Author: ");

	this->getIO().PrintString("\n");
	this->bookstoreService.DeleteBookFromRepo(titleSearch, authorSearch);
	this->getIO().PrintString("»Operation succesful!\n\n");
}

void BookstoreClient::SearchBook()
{
	this->getIO().PrintString("»»Search book\n");
	this->getIO().PrintString("  ╚═Fields to search by (leave field empty to ignore):\n");
	std::string titleSearch = this->getIO().ReadString("    ├─Title: ");
	std::string authorSearch = this->getIO().ReadString("    ├─Author: ");
	std::string genreSearch = this->getIO().ReadString("    ├─Genre: ");
	int releaseYearSearch = this->getIO().ReadInt("    └─Release year: ");

	this->getIO().PrintString("\n");
	Book searchedBook = this->bookstoreService.SearchBook(titleSearch, authorSearch, genreSearch, releaseYearSearch);
	this->getIO().PrintString("──────────\n");
	this->PrintBook(searchedBook);
	this->getIO().PrintString("──────────\n\n");
}

void BookstoreClient::FilterBooks()
{
	this->getIO().PrintString("»»Filter books\n");
	this->getIO().PrintString("  ╚═Fields to filter by:\n");
	this->getIO().PrintString("    ╠═[1]: Title\n");
	this->getIO().PrintString("    ╚═[2]: Release year\n");

	std::string titleFilter;
	int releaseYearSearch;
	std::vector<Book> filteredBooks;

	this->getIO().PrintString("\n");
	int option = this->getIO().ReadInt("»Enter option: ");
	this->getIO().PrintString("\n");
	switch (option)
	{
		case 1:
			titleFilter = this->getIO().ReadString("»Enter title: ");
			this->getIO().PrintString("\n");
			filteredBooks = this->getBookstoreService().GetFilteredBooks(titleFilter);
			break;

		case 2:
			releaseYearSearch = this->getIO().ReadInt("»Enter release year: ");
			this->getIO().PrintString("\n");
			filteredBooks = this->getBookstoreService().GetFilteredBooks(releaseYearSearch);
			break;

		default:
			this->getIO().PrintString("»Invalid command!\n\n");
			return;
			break;
	}
	std::for_each(filteredBooks.begin(), filteredBooks.end(), [this](Book filteredBook){
		this->getIO().PrintString("──────────\n");
		this->PrintBook(filteredBook);
	});
	this->getIO().PrintString("──────────\n\n");
}

void BookstoreClient::SortBooks()
{
	this->getIO().PrintString("»»Sort books\n");
	this->getIO().PrintString("  ╚═Fields to sort by:\n");
	this->getIO().PrintString("    ╠═[1]: Title\n");
	this->getIO().PrintString("    ╠═[2]: Author\n");
	this->getIO().PrintString("    ╚═[3]: Release year and genre\n");

	this->getIO().PrintString("\n");
	int option = this->getIO().ReadInt("»Enter option: ");
	this->getIO().PrintString("\n");
	BookstoreService service = this->getBookstoreService();
	switch (option)
	{
		case 1:
			this->getIO().PrintString("\n");
			service.SortBooksByTitle();
			break;

		case 2:
			this->getIO().PrintString("\n");
			service.SortBooksByAuthor();
			break;

		case 3:
			this->getIO().PrintString("\n");
			service.SortBooksByReleaseYearAndGenre();
			break;

		default:
			this->getIO().PrintString("»Invalid command!\n\n");
			return;
			break;
	}

	this->setBookstoreService(service);
	this->ListAllBooks();
}

void BookstoreClient::ExitApplication() const
{
	this->getIO().PrintString("»Exiting application...\n\n");
}

void BookstoreClient::RunApplication()
{
	this->getIO().PrintString("═════ Bookshopper ═════\n\n");
	std::string options = "";
	options = options + 
		"  ╠═[0]: Exit application\n" + 
		"  ╠═[1]: List all books\n" + 
		"  ╠═[2]: Add book\n" +
		"  ╠═[3]: Modify book\n" +
		"  ╠═[4]: Delete book\n" +
		"  ╠═[5]: Search book\n" +
		"  ╠═[6]: Filter books\n" +
		"  ╚═[7]: Sort books\n";
	while (true)
	{
		try
		{
			this->getIO().PrintMenu(options);
			int command = this->getIO().ReadInt("»Please input a command: ");
			this->getIO().PrintString("\n═══════════════════════\n\n");
			switch (command)
			{
				case 0: 
					this->ExitApplication();
					return;
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
	
				default:
					this->getIO().PrintString("»Invalid command!\n\n");
					break;
			}
		}
		catch (AppException& e)
		{
			this->getIO().PrintString("»Error:\n" + e.getMessage() + "\n");
		}
		this->getIO().PrintString("═══════════════════════\n\n");
	}
}

