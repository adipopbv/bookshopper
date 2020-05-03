#include "./gui-clients.h"

GraphicalBookstoreClient::GraphicalBookstoreClient(std::shared_ptr<BookstoreService> const &bookstoreService, int argc, char** argv): QApplication(argc, argv)
{
	this->setBookstoreService(bookstoreService);

	this->InitMainMenu();
	this->InitAddMenu();
	this->InitModifyMenu();
	this->InitDeleteMenu();

	this->ShowMainMenu();
}

GraphicalBookstoreClient::~GraphicalBookstoreClient()
{
	this->setBookstoreService(std::make_shared<BookstoreService>());
}

void GraphicalBookstoreClient::InitMainMenu()
{
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
	// cart books list
	this->cartBooksList = make_shared<QListWidget>(this->cartSide.get());

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
	QObject::connect(this->libraryActionsAddButton.get(), &QPushButton::clicked, [this] () { this->ShowAddMenu(); });
	this->libraryActionsModifyButton = make_shared<QPushButton>(tr("Modify"));
	QObject::connect(this->libraryActionsModifyButton.get(), &QPushButton::clicked, [this] () { this->ShowModifyMenu(); });
	this->libraryActionsDeleteButton = make_shared<QPushButton>(tr("Delete"));
	QObject::connect(this->libraryActionsDeleteButton.get(), &QPushButton::clicked, [this] () { this->ShowDeleteMenu(); });
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
}

void GraphicalBookstoreClient::InitAddMenu()
{
	// creating widgets

	// add menu
	this->addMenu = make_shared<QGroupBox>(tr("add menu"));
	// add menu layout
	this->addMenuLayout = make_shared<QGridLayout>();
	this->addMenu->setLayout(this->addMenuLayout.get());

	// book fields
	this->addTitleLabel = make_shared<QLabel>(tr("Title:"));
	this->addAuthorLabel = make_shared<QLabel>(tr("Author:"));
	this->addGenreLabel = make_shared<QLabel>(tr("Genre:"));
	this->addReleaseYearLabel = make_shared<QLabel>(tr("Release year:"));
	this->addTitle = make_shared<QLineEdit>();
	this->addAuthor = make_shared<QLineEdit>();
	this->addGenre = make_shared<QLineEdit>();
	this->addReleaseYear = make_shared<QLineEdit>();

	// accept and cancel buttons
	this->addAccept = make_shared<QPushButton>(tr("Accept"));
	QObject::connect(this->addAccept.get(), &QPushButton::clicked, [this] () { this->AddBook(); this->ShowMainMenu(); });
	this->addCancel = make_shared<QPushButton>(tr("Cancel"));
	QObject::connect(this->addCancel.get(), &QPushButton::clicked, [this] () { this->ShowMainMenu(); });

	// adding widgets to layouts

	// adding accept and cancel buttons
	this->addMenuLayout->addWidget(this->addAccept.get(), 8, 0, Qt::AlignCenter);
	this->addMenuLayout->addWidget(this->addCancel.get(), 8, 2, Qt::AlignCenter);

	// adding book fields
	this->addMenuLayout->addWidget(this->addTitleLabel.get(), 0, 0, Qt::AlignCenter);
	this->addMenuLayout->addWidget(this->addTitle.get(), 0, 2, Qt::AlignCenter);
	this->addMenuLayout->addWidget(this->addAuthorLabel.get(), 2, 0, Qt::AlignCenter);
	this->addMenuLayout->addWidget(this->addAuthor.get(), 2, 2, Qt::AlignCenter);
	this->addMenuLayout->addWidget(this->addGenreLabel.get(), 4, 0, Qt::AlignCenter);
	this->addMenuLayout->addWidget(this->addGenre.get(), 4, 2, Qt::AlignCenter);
	this->addMenuLayout->addWidget(this->addReleaseYearLabel.get(), 6, 0, Qt::AlignCenter);
	this->addMenuLayout->addWidget(this->addReleaseYear.get(), 6, 2, Qt::AlignCenter);
}

void GraphicalBookstoreClient::InitModifyMenu()
{
	// creating widgets

	// modify menu
	this->modifyMenu = make_shared<QGroupBox>(tr("modify menu"));
	// modify menu layout
	this->modifyMenuLayout = make_shared<QHBoxLayout>();
	this->modifyMenu->setLayout(this->modifyMenuLayout.get());

	// books list
	this->modifyBooksList = make_shared<QListWidget>();
	QObject::connect(this->modifyBooksList.get(), &QListWidget::itemSelectionChanged, 
			[this] () 
			{ 
				QVariant bookDataVar = this->modifyBooksList->currentItem()->data(Qt::UserRole);
				QList<QVariant> bookData = bookDataVar.toList();
				this->modifyTitle->setText(bookData[0].toString());
				this->modifyAuthor->setText(bookData[1].toString());
				this->modifyGenre->setText(bookData[2].toString());
				this->modifyReleaseYear->setText(bookData[3].toString());
			}
	);

	// actions
	this->modifyActions = make_shared<QWidget>();
	this->modifyActionsLayout = make_shared<QGridLayout>();
	// actions layout
	this->modifyActions->setLayout(this->modifyActionsLayout.get());

	// book fields
	this->modifyTitleLabel = make_shared<QLabel>(tr("Title:"));
	this->modifyAuthorLabel = make_shared<QLabel>(tr("Author:"));
	this->modifyGenreLabel = make_shared<QLabel>(tr("Genre:"));
	this->modifyReleaseYearLabel = make_shared<QLabel>(tr("Release year:"));
	this->modifyTitle = make_shared<QLineEdit>();
	this->modifyAuthor = make_shared<QLineEdit>();
	this->modifyGenre = make_shared<QLineEdit>();
	this->modifyReleaseYear = make_shared<QLineEdit>();

	// accept and cancel buttons
	this->modifyAccept = make_shared<QPushButton>(tr("Accept"));
	QObject::connect(this->modifyAccept.get(), &QPushButton::clicked, [this] () { this->ModifyBook(); this->ShowMainMenu(); });
	this->modifyCancel = make_shared<QPushButton>(tr("Cancel"));
	QObject::connect(this->modifyCancel.get(), &QPushButton::clicked, [this] () { this->ShowMainMenu(); });

	// adding widgets to layouts
	
	// adding accept and cancel buttons
	this->modifyActionsLayout->addWidget(this->modifyAccept.get(), 8, 0, Qt::AlignCenter);
	this->modifyActionsLayout->addWidget(this->modifyCancel.get(), 8, 2, Qt::AlignCenter);

	// adding book fields
	this->modifyActionsLayout->addWidget(this->modifyTitleLabel.get(), 0, 0, Qt::AlignCenter);
	this->modifyActionsLayout->addWidget(this->modifyTitle.get(), 0, 2, Qt::AlignCenter);
	this->modifyActionsLayout->addWidget(this->modifyAuthorLabel.get(), 2, 0, Qt::AlignCenter);
	this->modifyActionsLayout->addWidget(this->modifyAuthor.get(), 2, 2, Qt::AlignCenter);
	this->modifyActionsLayout->addWidget(this->modifyGenreLabel.get(), 4, 0, Qt::AlignCenter);
	this->modifyActionsLayout->addWidget(this->modifyGenre.get(), 4, 2, Qt::AlignCenter);
	this->modifyActionsLayout->addWidget(this->modifyReleaseYearLabel.get(), 6, 0, Qt::AlignCenter);
	this->modifyActionsLayout->addWidget(this->modifyReleaseYear.get(), 6, 2, Qt::AlignCenter);

	// adding books list and actions
	this->modifyMenuLayout->addWidget(this->modifyBooksList.get());
	this->modifyMenuLayout->addWidget(this->modifyActions.get());
}

void GraphicalBookstoreClient::InitDeleteMenu()
{
	// creating widgets

	// delete menu
	this->deleteMenu = make_shared<QGroupBox>(tr("delete menu"));
	// delete menu layout
	this->deleteMenuLayout = make_shared<QVBoxLayout>();
	this->deleteMenu->setLayout(this->deleteMenuLayout.get());

	// books list
	this->deleteBooksList = make_shared<QListWidget>();
	QObject::connect(this->deleteBooksList.get(), &QListWidget::itemSelectionChanged, 
			[this] () 
			{ 
				QVariant bookDataVar = this->deleteBooksList->currentItem()->data(Qt::UserRole);
				QList<QVariant> bookData = bookDataVar.toList();
				this->modifyTitle->setText(bookData[0].toString());
				this->modifyAuthor->setText(bookData[1].toString());
				this->modifyGenre->setText(bookData[2].toString());
				this->modifyReleaseYear->setText(bookData[3].toString());
			}
	);

	// actions
	this->deleteActions = make_shared<QWidget>();
	this->deleteActionsLayout = make_shared<QHBoxLayout>();
	// actions layout
	this->deleteActions->setLayout(this->deleteActionsLayout.get());

	// accept and cancel buttons
	this->deleteAccept = make_shared<QPushButton>(tr("Accept"));
	QObject::connect(this->deleteAccept.get(), &QPushButton::clicked, [this] () { this->DeleteBook(); this->ShowMainMenu(); });
	this->deleteCancel = make_shared<QPushButton>(tr("Cancel"));
	QObject::connect(this->deleteCancel.get(), &QPushButton::clicked, [this] () { this->ShowMainMenu(); });

	// adding widgets to layouts
	
	// adding accept and cancel buttons
	this->deleteActionsLayout->addWidget(this->deleteAccept.get());
	this->deleteActionsLayout->addWidget(this->deleteCancel.get());

	// adding books list and actions
	this->deleteMenuLayout->addWidget(this->deleteBooksList.get());
	this->deleteMenuLayout->addWidget(this->deleteActions.get());
}

void GraphicalBookstoreClient::ShowMainMenu()
{
	this->UpdateLibraryBooksList();
	this->UpdateCartBooksList();

	this->addMenu->hide(); 
	this->modifyMenu->hide(); 
	this->deleteMenu->hide(); 
	this->mainMenu->show();
}

void GraphicalBookstoreClient::ShowAddMenu()
{
	this->addTitle->clear();
	this->addAuthor->clear();
	this->addGenre->clear();
	this->addReleaseYear->clear();

	this->mainMenu->hide();
	this->addMenu->show();
}

void GraphicalBookstoreClient::ShowModifyMenu()
{
	this->modifyBooksList->clearSelection();
	this->modifyBooksList->clear();
	this->modifyTitle->clear();
	this->modifyAuthor->clear();
	this->modifyGenre->clear();
	this->modifyReleaseYear->clear();

	try
	{
		std::vector<Book> books = this->getBookstoreService()->GetBooks();
		for (Book const &book: books)
		{
			QListWidgetItem* item = new QListWidgetItem(tr((book.getTitle() + " | " + book.getAuthor()).c_str()));
    
			QList<QVariant> bookData;
			QVariant field = QVariant(tr(book.getTitle().c_str()));
			bookData.append(field);
			field = QVariant(tr(book.getAuthor().c_str()));
			bookData.append(field);
			field = QVariant(tr(book.getGenre().c_str()));
			bookData.append(field);
			field = QVariant(tr(std::to_string(book.getReleaseYear()).c_str()));
			bookData.append(field);
			item->setData(Qt::UserRole, bookData);
    
			this->modifyBooksList->addItem(item);
		}
	}
	catch (EmptyRepoError &e) { }

	this->mainMenu->hide();
	this->modifyMenu->show();
}

void GraphicalBookstoreClient::ShowDeleteMenu()
{
	this->deleteBooksList->clearSelection();
	this->deleteBooksList->clear();

	try
	{
		std::vector<Book> books = this->getBookstoreService()->GetBooks();
		for (Book const &book: books)
		{
			QListWidgetItem* item = new QListWidgetItem(tr((book.getTitle() + " | " + book.getAuthor()).c_str()));
    
			QList<QVariant> bookData;
			QVariant field = QVariant(tr(book.getTitle().c_str()));
			bookData.append(field);
			field = QVariant(tr(book.getAuthor().c_str()));
			bookData.append(field);
			field = QVariant(tr(book.getGenre().c_str()));
			bookData.append(field);
			field = QVariant(tr(std::to_string(book.getReleaseYear()).c_str()));
			bookData.append(field);
			item->setData(Qt::UserRole, bookData);
    
			this->deleteBooksList->addItem(item);
		}
	}
	catch (EmptyRepoError &e) { }

	this->mainMenu->hide();
	this->deleteMenu->show();
}

void GraphicalBookstoreClient::UpdateLibraryBooksList()
{
	this->libraryBooksList->clear();
	try
	{
		std::vector<Book> books = this->getBookstoreService()->GetBooks();
		for (Book const &book: books)
		{ this->libraryBooksList->addItem(tr((book.getTitle() + " | " + book.getAuthor()).c_str())); }
	}
	catch (EmptyRepoError &e) { }
}

void GraphicalBookstoreClient::UpdateCartBooksList()
{
	try
	{
		std::vector<Book> books = this->getBookstoreService()->GetCartBooks();
		for (Book book: books)
		{ shared_ptr<QListWidgetItem> item = make_shared<QListWidgetItem>(
				tr((book.getTitle() + " | " + book.getAuthor()).c_str()),
				this->cartBooksList.get()); }
	}
	catch (EmptyRepoError &e) { }
}

void GraphicalBookstoreClient::AddBook()
{
	std::string title = this->addTitle->text().toStdString();
	std::string author = this->addAuthor->text().toStdString();
	std::string genre = this->addGenre->text().toStdString();
	std::string releaseYearStr = this->addReleaseYear->text().toStdString();
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

	if (this->modifyBooksList->count() == 0)
	{
		succesMessage.setText(tr("Error:\nempty repo!"));
		succesMessage.exec();
		return;
	}

	if (this->modifyBooksList->currentItem() == NULL)
	{
		succesMessage.setText(tr("Error:\nnothing selected!"));
		succesMessage.exec();
		return;
	}

	QVariant bookDataVar = this->modifyBooksList->currentItem()->data(Qt::UserRole);
	QList<QVariant> bookData = bookDataVar.toList();
	std::string titleSearch = bookData[0].toString().toStdString();
	std::string authorSearch = bookData[1].toString().toStdString();

	std::string title = this->modifyTitle->text().toStdString();
	std::string author = this->modifyAuthor->text().toStdString();
	std::string genre = this->modifyGenre->text().toStdString();
	std::string releaseYearStr = this->modifyReleaseYear->text().toStdString();
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

	if (this->deleteBooksList->count() == 0)
	{
		succesMessage.setText(tr("Error:\nempty repo!"));
		succesMessage.exec();
		return;
	}

	if (this->deleteBooksList->currentItem() == NULL)
	{
		succesMessage.setText(tr("Error:\nnothing selected!"));
		succesMessage.exec();
		return;
	}

	QVariant bookDataVar = this->deleteBooksList->currentItem()->data(Qt::UserRole);
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

