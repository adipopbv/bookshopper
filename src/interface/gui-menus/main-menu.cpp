#include "./main-menu.h"

MainMenu::MainMenu(shared_ptr<BookstoreService> const &service)
{
	// service reference
	this->service = service;

	// menu title
	this->setTitle(tr("main menu"));
	
	// menu layout
	this->menuLayout = make_shared<QVBoxLayout>();
	this->setLayout(this->menuLayout.get());

	// creating widgets

	// initializing library side
	this->InitLibrarySide();
	// initializing cart side
	this->InitCartSide();

	// adding widgets to layout

	// adding library side
	this->menuLayout->addWidget(this->librarySide.get());
	// adding cart side
	this->menuLayout->addWidget(this->cartSide.get());
}

void MainMenu::InitLibrarySide()
{
	// library side
	this->librarySide = make_shared<QGroupBox>(tr("library operations"));
	// library side layout
	this->librarySideLayout = make_shared<QHBoxLayout>();
	this->librarySide->setLayout(this->librarySideLayout.get());

	// creating widgets

	// library books list
	this->libraryBooksList = make_shared<QListWidget>(this->librarySide.get());
	this->libraryBooksList->setDisabled(true);

	// library actions
	this->libraryActions = make_shared<QGroupBox>(tr("library actions:"));
	// library actions layout
	this->libraryActionsLayout = make_shared<QGridLayout>();
	this->libraryActions->setLayout(this->libraryActionsLayout.get());

	// library buttons
	this->libraryAddButton = make_shared<QPushButton>(tr("Add"));
	this->libraryModifyButton = make_shared<QPushButton>(tr("Modify"));
	this->libraryDeleteButton = make_shared<QPushButton>(tr("Delete"));
	this->librarySearchButton = make_shared<QPushButton>(tr("Search"));
	this->libraryFilterButton = make_shared<QPushButton>(tr("Filter"));
	this->librarySortButton = make_shared<QPushButton>(tr("Sort"));
	this->libraryUndoButton = make_shared<QPushButton>(tr("Undo"));

	// adding widgets to layouts

	// adding library buttons
	this->libraryActionsLayout->addWidget(this->libraryAddButton.get(), 0, 0, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryModifyButton.get(), 0, 2, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryDeleteButton.get(), 2, 0, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->librarySearchButton.get(), 2, 2, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryFilterButton.get(), 4, 0, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->librarySortButton.get(), 4, 2, Qt::AlignCenter);
	this->libraryActionsLayout->addWidget(this->libraryUndoButton.get(), 6, 0, Qt::AlignCenter);

	// adding library book list
	this->librarySideLayout->addWidget(this->libraryBooksList.get());

	// adding library actions
	this->librarySideLayout->addWidget(this->libraryActions.get());
}

void MainMenu::InitCartSide()
{
	// cart side
	this->cartSide = make_shared<QGroupBox>(tr("cart operations"));
	// cart side layout
	this->cartSideLayout = make_shared<QHBoxLayout>();
	this->cartSide->setLayout(this->cartSideLayout.get());

	// creating widgets

	// cart books list
	this->cartBooksList = make_shared<QListWidget>(this->cartSide.get());
	this->cartBooksList->setDisabled(true);

	// cart actions
	this->cartActions = make_shared<QGroupBox>(tr("cart actions:"));
	// cart actions layout
	this->cartActionsLayout = make_shared<QGridLayout>();
	this->cartActions->setLayout(this->cartActionsLayout.get());

	// cart buttons
	this->cartEmptyButton = make_shared<QPushButton>(tr("Empty"));
	this->cartAddButton = make_shared<QPushButton>(tr("Add"));
	this->cartAddRandomButton = make_shared<QPushButton>(tr("Add random"));
	this->cartExportButton = make_shared<QPushButton>(tr("Export"));
	this->cartTitlesButton = make_shared<QPushButton>(tr("Titles"));

	// adding widgets to layouts
	
	// adding cart buttons
	this->cartActionsLayout->addWidget(this->cartEmptyButton.get(), 0, 0, Qt::AlignCenter);
	this->cartActionsLayout->addWidget(this->cartAddButton.get(), 0, 2, Qt::AlignCenter);
	this->cartActionsLayout->addWidget(this->cartAddRandomButton.get(), 2, 0, Qt::AlignCenter);
	this->cartActionsLayout->addWidget(this->cartExportButton.get(), 2, 2, Qt::AlignCenter);
	this->cartActionsLayout->addWidget(this->cartTitlesButton.get(), 4, 0, Qt::AlignCenter);

	// adding cart book list
	this->cartSideLayout->addWidget(this->cartBooksList.get());

	// adding cart actions
	this->cartSideLayout->addWidget(this->cartActions.get());
}

void MainMenu::Show()
{
	// update library books list view
	std::vector<Book> libraryBooks;
	try { libraryBooks = this->service->GetBooks(); }
	catch (EmptyRepoError) { }
	for (Book const &book: libraryBooks)
	{ this->libraryBooksList->addItem(tr(("Title: " + book.getTitle() + " | Author: " + book.getAuthor()).c_str())); }

	// update cart books list view
	std::vector<Book> cartBooks;
	try { cartBooks = this->service->GetCartBooks(); }
	catch (EmptyRepoError) { }
	for (Book const &book: cartBooks)
	{ this->cartBooksList->addItem(tr(("Title: " + book.getTitle() + " | Author: " + book.getAuthor()).c_str())); }

	// show main menu
	this->show();
}

void MainMenu::Hide()
{
	this->libraryBooksList->clear();
	this->cartBooksList->clear();

	this->hide();
}

