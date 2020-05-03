#include "./gui-clients.h"

GraphicalBookstoreClient::GraphicalBookstoreClient(std::shared_ptr<BookstoreService> const &bookstoreService, int argc, char** argv): QApplication(argc, argv)
{
	this->setBookstoreService(bookstoreService);

	// creating widgets

	// main menu
	this->mainMenu = make_shared<QWidget>();
	// main menu layout
	this->mainMenuLayout = make_shared<QVBoxLayout>();
	this->mainMenu->setLayout(this->mainMenuLayout.get());

	// library side
	this->librarySide = make_shared<QGroupBox>(tr("library"), mainMenu.get());
	// library side layout
	this->librarySideLayout = make_shared<QHBoxLayout>();
	this->librarySide->setLayout(this->librarySideLayout.get());
	// cart side
	this->cartSide = make_shared<QGroupBox>(tr("cart"), mainMenu.get());
	// cart side layout
	this->cartSideLayout = make_shared<QHBoxLayout>();
	this->cartSide->setLayout(this->cartSideLayout.get());

	// library books list
	this->libraryBooksList = make_shared<QListWidget>(this->librarySide.get());
	this->InitLibraryBooksList();
	// cart books list
	this->cartBooksList = make_shared<QListWidget>(this->cartSide.get());
	this->InitCartBooksList();

	// library actions
	this->libraryActions = make_shared<QWidget>();
	// library actions layout
	this->libraryActionsLayout = make_shared<QGridLayout>();
	this->libraryActions->setLayout(this->libraryActionsLayout.get());
	// cart actions
	this->cartActions = make_shared<QWidget>();
	// cart actions layout
	this->cartActionsLayout = make_shared<QGridLayout>();
	this->cartActions->setLayout(this->cartActionsLayout.get());

	// library actions labels
	this->libraryActionsLabel = make_shared<QLabel>(tr("library actions:"));
	// library actions labels
	this->cartActionsLabel = make_shared<QLabel>(tr("cart actions:"));

	// library actions buttons
	this->libraryActionsAddButton = make_shared<QPushButton>(tr("Add"));
	this->libraryActionsModifyButton = make_shared<QPushButton>(tr("Modify"));
	this->libraryActionsDeleteButton = make_shared<QPushButton>(tr("Delete"));
	this->libraryActionsSearchButton = make_shared<QPushButton>(tr("Search"));
	this->libraryActionsFilterButton = make_shared<QPushButton>(tr("Filter"));
	this->libraryActionsSortButton = make_shared<QPushButton>(tr("Sort"));
	this->libraryActionsUndoButton = make_shared<QPushButton>(tr("Undo"));
	// cart actions buttons
	this->cartActionsEmptyButton = make_shared<QPushButton>(tr("Empty"));
	this->cartActionsAddButton = make_shared<QPushButton>(tr("Add"));
	this->cartActionsAddRandomButton = make_shared<QPushButton>(tr("Add random"));
	this->cartActionsExportButton = make_shared<QPushButton>(tr("Export"));
	this->cartActionsTitlesButton = make_shared<QPushButton>(tr("Titles"));

	// adding widgets to layouts

	// adding library actions buttons
	this->libraryActionsLayout->addWidget(this->libraryActionsAddButton.get(), 2, 0, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryActionsModifyButton.get(), 2, 2, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryActionsDeleteButton.get(), 4, 0, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryActionsSearchButton.get(), 4, 2, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryActionsFilterButton.get(), 6, 0, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryActionsSortButton.get(), 6, 2, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryActionsUndoButton.get(), 8, 0, Qt::AlignCenter);
	// adding cart actions buttons
	this->cartActionsLayout->addWidget(this->cartActionsEmptyButton.get(), 2, 0, Qt::AlignCenter);
	this->cartActionsLayout->addWidget(this->cartActionsAddButton.get(), 2, 2, Qt::AlignCenter);
	this->cartActionsLayout->addWidget(this->cartActionsAddRandomButton.get(), 4, 0, Qt::AlignCenter);
	this->cartActionsLayout->addWidget(this->cartActionsExportButton.get(), 4, 2, Qt::AlignCenter);
	this->cartActionsLayout->addWidget(this->cartActionsTitlesButton.get(), 6, 0, Qt::AlignCenter);

	// adding library actions labels
	this->libraryActionsLayout->addWidget(this->libraryActionsLabel.get(), 0, 0, Qt::AlignCenter);
	// adding cart actions labels
	this->cartActionsLayout->addWidget(this->cartActionsLabel.get(), 0, 0, Qt::AlignCenter);

	// adding library book list
	this->librarySideLayout->addWidget(this->libraryBooksList.get());
	// adding cart book list
	this->cartSideLayout->addWidget(this->cartBooksList.get());

	// adding library actions
	this->librarySideLayout->addWidget(this->libraryActions.get());
	// adding cart actions
	this->cartSideLayout->addWidget(this->cartActions.get());

	// adding library side
	this->mainMenuLayout->addWidget(this->librarySide.get());
	// adding cart side
	this->mainMenuLayout->addWidget(this->cartSide.get());

	// show main menu
	this->mainMenu->show();
}

void GraphicalBookstoreClient::InitLibraryBooksList()
{
	try
	{
		std::vector<Book> books = this->getBookstoreService()->GetBooks();
		for (Book book: books)
		{
			shared_ptr<QListWidgetItem> item = make_shared<QListWidgetItem>(tr("hello"), this->libraryBooksList.get());
		}
	}
	catch (EmptyRepoError &e) { }
}

void GraphicalBookstoreClient::InitCartBooksList()
{
	try
	{
		std::vector<Book> books = this->getBookstoreService()->GetCartBooks();
		for (Book book: books)
		{
			shared_ptr<QListWidgetItem> item = make_shared<QListWidgetItem>(tr("hehe"), this->cartBooksList.get());
		}
	}
	catch (EmptyRepoError &e) { }
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

