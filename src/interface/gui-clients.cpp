#include "./gui-clients.h"

GraphicalBookstoreClient::GraphicalBookstoreClient(std::shared_ptr<BookstoreService> const &bookstoreService, int argc, char** argv): QApplication(argc, argv)
{
	this->setBookstoreService(bookstoreService);

	this->mainMenu = make_shared<QWidget>();
	this->mainMenuLayout = make_shared<QVBoxLayout>();
	this->mainMenu->setLayout(this->mainMenuLayout.get());

	this->librarySide = make_shared<QGroupBox>(tr("library"), mainMenu.get());
	this->cartSide = make_shared<QGroupBox>(tr("cart"), mainMenu.get());
	this->sidesLayout = make_shared<QHBoxLayout>();
	this->librarySide->setLayout(this->sidesLayout.get());
	this->cartSide->setLayout(this->sidesLayout.get());
	this->mainMenuLayout->addWidget(this->librarySide.get());
	this->mainMenuLayout->addWidget(this->cartSide.get());

	this->mainMenu->show();
}

GraphicalBookstoreClient::~GraphicalBookstoreClient()
{
	this->setBookstoreService(std::make_shared<BookstoreService>());
}

void GraphicalBookstoreClient::AddBook()
{

}

void GraphicalBookstoreClient::ModifyBook()
{

}

void GraphicalBookstoreClient::DeleteBook()
{

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

