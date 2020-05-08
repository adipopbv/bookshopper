#include "./gui-clients.h"

GraphicalBookstoreClient::GraphicalBookstoreClient(std::shared_ptr<BookstoreService> const &bookstoreService, int argc, char** argv): QApplication(argc, argv)
{
	this->setBookstoreService(bookstoreService);

	this->mainMenu = make_shared<MainMenu>(bookstoreService);
	this->addMenu = make_shared<AddMenu>();
	this->modifyMenu = make_shared<ModifyMenu>(bookstoreService);
	this->deleteMenu = make_shared<DeleteMenu>(bookstoreService);
	this->searchMenu = make_shared<SearchMenu>();
	this->filterMenu = make_shared<FilterMenu>();
	this->sortMenu = make_shared<SortMenu>();

	this->InitButtons();

	this->mainMenu->Show();
}

GraphicalBookstoreClient::~GraphicalBookstoreClient() { }

void GraphicalBookstoreClient::InitButtons()
{
	// main menu buttons
	QObject::connect(this->mainMenu->libraryAddButton.get(), &QPushButton::clicked, [this] () { this->mainMenu->Hide(); this->addMenu->Show(); });
	QObject::connect(this->mainMenu->libraryModifyButton.get(), &QPushButton::clicked, [this] () { this->mainMenu->Hide(); this->modifyMenu->Show(); });
	QObject::connect(this->mainMenu->libraryDeleteButton.get(), &QPushButton::clicked, [this] () { this->mainMenu->Hide(); this->deleteMenu->Show(); });
	QObject::connect(this->mainMenu->librarySearchButton.get(), &QPushButton::clicked, [this] () { this->mainMenu->Hide(); this->searchMenu->Show(); });
	QObject::connect(this->mainMenu->libraryFilterButton.get(), &QPushButton::clicked, [this] () { this->mainMenu->Hide(); this->filterMenu->Show(); });
	QObject::connect(this->mainMenu->librarySortButton.get(), &QPushButton::clicked, [this] () { this->mainMenu->Hide(); this->sortMenu->Show(); });

	// add menu buttons
	QObject::connect(this->addMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->AddBook(); this->addMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->addMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->addMenu->Hide(); this->mainMenu->Show(); });

	// modify menu buttons
	QObject::connect(this->modifyMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->ModifyBook(); this->modifyMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->modifyMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->modifyMenu->Hide(); this->mainMenu->Show(); });

	// delete menu buttons
	QObject::connect(this->deleteMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->DeleteBook(); this->deleteMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->deleteMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->deleteMenu->Hide(); this->mainMenu->Show(); });

	// search menu buttons
	QObject::connect(this->searchMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->SearchBook(); this->searchMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->searchMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->searchMenu->Hide(); this->mainMenu->Show(); });

	// filter menu buttons
	QObject::connect(this->filterMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->filterMenu->SwitchFocus(); this->FilterBooks(); });
	QObject::connect(this->filterMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->filterMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->filterMenu->okButton.get(), &QPushButton::clicked, [this] () { this->filterMenu->Hide(); this->mainMenu->Show(); });

	// sort menu buttons
	QObject::connect(this->sortMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->SortBooks(); this->sortMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->sortMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->sortMenu->Hide(); this->mainMenu->Show(); });
}

void GraphicalBookstoreClient::AddBook()
{
	std::string title = this->addMenu->titleField->text().toStdString();
	std::string author = this->addMenu->authorField->text().toStdString();
	std::string genre = this->addMenu->genreField->text().toStdString();
	std::string releaseYearStr = this->addMenu->releaseYearField->text().toStdString();
	int releaseYear = -1;
	try { releaseYear = std::stoi(releaseYearStr); } 
	catch (std::exception& e) { releaseYear = -1; }

	QMessageBox succesMessage;
	succesMessage.setText(tr("Operation succesful!"));
	try { this->bookstoreService->AddBookToRepo(title, author, genre, releaseYear); }
	catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage()).c_str())); }
	succesMessage.exec();
}

void GraphicalBookstoreClient::ModifyBook()
{
	QMessageBox succesMessage;

	if (this->modifyMenu->booksList->count() == 0)
	{
		succesMessage.setText(tr("Error:\nempty repo"));
		succesMessage.exec();
		return;
	}

	if (this->modifyMenu->booksList->currentItem() == NULL)
	{
		succesMessage.setText(tr("Error:\nnothing selected"));
		succesMessage.exec();
		return;
	}

	QVariant bookDataVar = this->modifyMenu->booksList->currentItem()->data(Qt::UserRole);
	QList<QVariant> bookData = bookDataVar.toList();
	std::string titleSearch = bookData[0].toString().toStdString();
	std::string authorSearch = bookData[1].toString().toStdString();

	std::string title = this->modifyMenu->titleField->text().toStdString();
	std::string author = this->modifyMenu->authorField->text().toStdString();
	std::string genre = this->modifyMenu->genreField->text().toStdString();
	std::string releaseYearStr = this->modifyMenu->releaseYearField->text().toStdString();
	int releaseYear = -1;
	try { releaseYear = std::stoi(releaseYearStr); } 
	catch (std::exception& e) { releaseYear = -1; }

	succesMessage.setText(tr("Operation succesful!"));
	try { this->bookstoreService->ModifyBookInRepo(titleSearch, authorSearch, title, author, genre, releaseYear); }
	catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage()).c_str())); }
	succesMessage.exec();
}

void GraphicalBookstoreClient::DeleteBook()
{
	QMessageBox succesMessage;

	if (this->deleteMenu->booksList->count() == 0)
	{
		succesMessage.setText(tr("Error:\nempty repo"));
		succesMessage.exec();
		return;
	}

	if (this->deleteMenu->booksList->currentItem() == NULL)
	{
		succesMessage.setText(tr("Error:\nnothing selected"));
		succesMessage.exec();
		return;
	}

	QVariant bookDataVar = this->deleteMenu->booksList->currentItem()->data(Qt::UserRole);
	QList<QVariant> bookData = bookDataVar.toList();
	std::string titleSearch = bookData[0].toString().toStdString();
	std::string authorSearch = bookData[1].toString().toStdString();
	
	succesMessage.setText(tr("Operation succesful!"));
	try { this->bookstoreService->DeleteBookFromRepo(titleSearch, authorSearch); }
	catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage()).c_str())); }
	succesMessage.exec();
}

void GraphicalBookstoreClient::SearchBook()
{
	std::string titleSearch = this->searchMenu->titleField->text().toStdString();
	std::string authorSearch = this->searchMenu->authorField->text().toStdString();
	std::string genreSearch = this->searchMenu->genreField->text().toStdString();
	std::string releaseYearStr = this->searchMenu->releaseYearField->text().toStdString();
	int releaseYearSearch = -1;
	try { releaseYearSearch = std::stoi(releaseYearStr); } 
	catch (std::exception& e) { releaseYearSearch = -1; }

	QMessageBox rezultMessage;
	Book searchedBook;
	try 
	{
		searchedBook = this->bookstoreService->SearchBook(titleSearch, authorSearch, genreSearch, releaseYearSearch); 
		rezultMessage.setText(tr(("Rezult:\n  Title: " + searchedBook.getTitle() + 
					"\n  Author: " + searchedBook.getAuthor() + 
					"\n  Genre: " + searchedBook.getGenre() +
					"\n  Release year: " + std::to_string(searchedBook.getReleaseYear())).c_str()));
	}
	catch (AppException &e) { rezultMessage.setText(tr(("Error:\n" + e.getMessage()).c_str())); }
	rezultMessage.exec();
}

void GraphicalBookstoreClient::FilterBooks()
{
	std::string title = this->filterMenu->titleField->text().toStdString();
	std::string releaseYearStr = this->filterMenu->releaseYearField->text().toStdString();
	int releaseYear = -1;
	try { releaseYear = std::stoi(releaseYearStr); } 
	catch (std::exception& e) { releaseYear = -1; }

	QMessageBox succesMessage;
	succesMessage.setText(tr("Operation succesful!"));
	std::vector<Book> books;
	if (this->filterMenu->searchByYear->isChecked())
	{
		try { books = this->bookstoreService->GetFilteredBooks(releaseYear); }
		catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage()).c_str())); }
	}
	else
	{
		try { books = this->bookstoreService->GetFilteredBooks(title); }
		catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage()).c_str())); }
	}

	for (Book const &book: books)
		this->filterMenu->booksList->addItem(tr(("Title: " + book.getTitle() + 
						"\n  Author: " + book.getAuthor() + 
						"\n  Genre: " + book.getGenre() +
						"\n  Release year: " + std::to_string(book.getReleaseYear())).c_str()));
	succesMessage.exec();
}

void GraphicalBookstoreClient::SortBooks()
{
	QMessageBox succesMessage;

	succesMessage.setText(tr("Operation succesful!"));
	try
	{
		if (this->sortMenu->sortByTitle->isChecked())
			this->bookstoreService->SortBooksByTitle();
		else if (this->sortMenu->sortByAuthor->isChecked())
			this->bookstoreService->SortBooksByAuthor();
		else
			this->bookstoreService->SortBooksByReleaseYearAndGenre();
	}
	catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage()).c_str())); }

	succesMessage.exec();
}

void GraphicalBookstoreClient::UndoOperation()
{

}

void GraphicalBookstoreClient::EmptyCart()
{

}

void GraphicalBookstoreClient::AddToCart()
{

}

void GraphicalBookstoreClient::AddRandomBooksToCart()
{

}

void GraphicalBookstoreClient::SaveCartToFile()
{

}

void GraphicalBookstoreClient::ListAllCartTitles() const
{

}

void GraphicalBookstoreClient::ExitApplication() const
{

}

int GraphicalBookstoreClient::RunApplication()
{
	return this->exec();
}

