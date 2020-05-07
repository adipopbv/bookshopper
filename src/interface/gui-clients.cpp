#include "./gui-clients.h"

GraphicalBookstoreClient::GraphicalBookstoreClient(std::shared_ptr<BookstoreService> const &bookstoreService, int argc, char** argv): QApplication(argc, argv)
{
	this->setBookstoreService(bookstoreService);

	this->mainMenu = make_shared<MainMenu>(bookstoreService);
	this->addMenu = make_shared<AddMenu>();
	this->modifyMenu = make_shared<ModifyMenu>(bookstoreService);
	this->deleteMenu = make_shared<DeleteMenu>(bookstoreService);

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

	// add menu buttons
	QObject::connect(this->addMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->AddBook(); this->addMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->addMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->addMenu->Hide(); this->mainMenu->Show(); });

	// modify menu buttons
	QObject::connect(this->modifyMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->ModifyBook(); this->modifyMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->modifyMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->modifyMenu->Hide(); this->mainMenu->Show(); });

	// delete menu buttons
	QObject::connect(this->deleteMenu->acceptButton.get(), &QPushButton::clicked, [this] () { this->DeleteBook(); this->deleteMenu->Hide(); this->mainMenu->Show(); });
	QObject::connect(this->deleteMenu->cancelButton.get(), &QPushButton::clicked, [this] () { this->deleteMenu->Hide(); this->mainMenu->Show(); });
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
	catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage() + "!").c_str())); }
	succesMessage.exec();
}

void GraphicalBookstoreClient::ModifyBook()
{
	QMessageBox succesMessage;

	if (this->modifyMenu->booksList->count() == 0)
	{
		succesMessage.setText(tr("Error:\nempty repo!"));
		succesMessage.exec();
		return;
	}

	if (this->modifyMenu->booksList->currentItem() == NULL)
	{
		succesMessage.setText(tr("Error:\nnothing selected!"));
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
	catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage() + "!").c_str())); }
	succesMessage.exec();
}

void GraphicalBookstoreClient::DeleteBook()
{
	QMessageBox succesMessage;

	if (this->deleteMenu->booksList->count() == 0)
	{
		succesMessage.setText(tr("Error:\nempty repo!"));
		succesMessage.exec();
		return;
	}

	if (this->deleteMenu->booksList->currentItem() == NULL)
	{
		succesMessage.setText(tr("Error:\nnothing selected!"));
		succesMessage.exec();
		return;
	}

	QVariant bookDataVar = this->deleteMenu->booksList->currentItem()->data(Qt::UserRole);
	QList<QVariant> bookData = bookDataVar.toList();
	std::string titleSearch = bookData[0].toString().toStdString();
	std::string authorSearch = bookData[1].toString().toStdString();
	
	succesMessage.setText(tr("Operation succesful!"));
	try { this->bookstoreService->DeleteBookFromRepo(titleSearch, authorSearch); }
	catch (AppException &e) { succesMessage.setText(tr(("Error:\n" + e.getMessage() + "!").c_str())); }
	succesMessage.exec();
}

void GraphicalBookstoreClient::SearchBook()
{

}

void GraphicalBookstoreClient::FilterBooks()
{

}

void GraphicalBookstoreClient::SortBooks()
{

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

