#include "./delete-menu.h"

DeleteMenu::DeleteMenu(shared_ptr<BookstoreService> const &service)
{
	// service reference
	this->service = service;

	// menu title
	this->setTitle(tr("delete menu"));
	// menu layout
	this->menuLayout = make_shared<QVBoxLayout>();
	this->setLayout(this->menuLayout.get());

	// creating widgets

	// books list
	this->booksList = make_shared<QListWidget>();

	// actions
	this->actions = make_shared<QGroupBox>();
	// actions layout
	this->actionsLayout = make_shared<QHBoxLayout>();
	this->actions->setLayout(this->actionsLayout.get());

	// accept and cancel buttons
	this->acceptButton = make_shared<QPushButton>(tr("Accept"));
	this->cancelButton = make_shared<QPushButton>(tr("Cancel"));

	// adding widgets to layouts
	
	// adding accept and cancel buttons
	this->actionsLayout->addWidget(this->acceptButton.get());
	this->actionsLayout->addWidget(this->cancelButton.get());

	// adding books list and actions
	this->menuLayout->addWidget(this->booksList.get());
	this->menuLayout->addWidget(this->actions.get());
}

void DeleteMenu::Show()
{
	try
	{
		std::vector<Book> books = this->service->GetBooks();
		for (Book const &book: books)
		{
			QListWidgetItem* item = new QListWidgetItem(tr(("Title: " + book.getTitle() + 
							"\n  Author: " + book.getAuthor() +
							"\n  Genre: " + book.getGenre() +
							"\n  Release year: " + std::to_string(book.getReleaseYear())).c_str()));
    
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
    
			this->booksList->addItem(item);
		}
	}
	catch (EmptyRepoError &e) { }

	this->booksList->clearSelection();
	this->show();
}

void DeleteMenu::Hide()
{
	this->hide();

	this->booksList->clearSelection();
	this->booksList->clear();
}

