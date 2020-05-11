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
	// exit button
	this->exitAppButton = make_shared<QPushButton>(tr("Exit application"));
	// initializing cart side
	this->InitCartSide();

	// adding widgets to layout

	// adding library side
	this->menuLayout->addWidget(this->librarySide.get());
	// adding cart side
	this->menuLayout->addWidget(this->cartSide.get());
	// adding exit button
	this->menuLayout->addWidget(this->exitAppButton.get(), Qt::AlignCenter);
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

	// library books as buttons list
	this->booksAsButtons = make_shared<QGroupBox>(tr("books as buttons"));
	this->booksAsButtonsLayout = make_shared<QVBoxLayout>();
	this->booksAsButtons->setLayout(this->booksAsButtonsLayout.get());

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

	// adding books as button list
	this->librarySideLayout->addWidget(this->booksAsButtons.get());
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

void MainMenu::UpdateLibraryList()
{
	this->libraryBooksList->clear();
	this->libraryBooksList->clearSelection();
	for (shared_ptr<QPushButton> button: this->booksAsButtonsList)
	{
		this->booksAsButtonsLayout->removeWidget(button.get());
	}
	this->booksAsButtonsList.clear();

	std::vector<Book> libraryBooks;
	try { libraryBooks = this->service->GetBooks(); }
	catch (EmptyRepoError) { }
	for (int i = 0; i < (int)libraryBooks.size(); i++)
	{ 
		Book book = libraryBooks[i];
		this->libraryBooksList->addItem(tr(("Title: " + book.getTitle() + 
					"\n  Author: " + book.getAuthor() +
					"\n  Genre: " + book.getGenre() +
					"\n  Release year: " + std::to_string(book.getReleaseYear())).c_str()));    

		shared_ptr<QPushButton> button = make_shared<QPushButton>(tr((book.getTitle() + " | " + book.getAuthor()).c_str()));
		this->booksAsButtonsList.push_back(button);
		QObject::connect(button.get(), &QPushButton::clicked, [i, this] ()
				{
					std::string text = this->booksAsButtonsList[i]->text().toStdString();

					size_t pos = text.find(" | ");
					std::string title = text.substr(0, pos);
					text.erase(0, pos + std::string(" | ").length());
					std::string author = text;

					this->service->DeleteBookFromRepo(title, author);
					this->booksAsButtonsLayout->removeWidget(this->booksAsButtonsList[i].get());
					this->booksAsButtonsList.erase(this->booksAsButtonsList.begin() + i);
					this->UpdateLibraryList();
				});
		this->booksAsButtonsLayout->addWidget(button.get());
	}
}

void MainMenu::UpdateCartList()
{
	this->cartBooksList->clear();
	this->cartBooksList->clearSelection();

	std::vector<Book> cartBooks;
	try { cartBooks = this->service->GetCartBooks(); }
	catch (EmptyRepoError) { }
	for (Book const &book: cartBooks)
	{
		this->cartBooksList->addItem(tr(("Title: " + book.getTitle() + 
					"\n  Author: " + book.getAuthor() +
					"\n  Genre: " + book.getGenre() +
					"\n  Release year: " + std::to_string(book.getReleaseYear())).c_str())); 
	}
}

void MainMenu::Show()
{
	// update library books list view
	this->UpdateLibraryList();

	// update cart books list view
	this->UpdateCartList();

	// show main menu
	this->show();
}

void MainMenu::Hide()
{
	this->hide();
}

