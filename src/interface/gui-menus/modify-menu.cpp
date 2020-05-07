#include "./modify-menu.h"

ModifyMenu::ModifyMenu(shared_ptr<BookstoreService> const &service)
{
	// service reference
	this->service = service;

	// menu title
	this->setTitle(tr("modify menu"));
	// menu layout
	this->menuLayout = make_shared<QHBoxLayout>();
	this->setLayout(this->menuLayout.get());

	// creating widgets

	// books list
	this->booksList = make_shared<QListWidget>();
	QObject::connect(this->booksList.get(), &QListWidget::itemSelectionChanged, 
			[this] () 
			{ 
				QVariant bookDataVar = this->booksList->currentItem()->data(Qt::UserRole);
				QList<QVariant> bookData = bookDataVar.toList();
				this->titleField->setText(bookData[0].toString());
				this->authorField->setText(bookData[1].toString());
				this->genreField->setText(bookData[2].toString());
				this->releaseYearField->setValue(bookData[3].toInt());
			}
	);

	// actions
	this->actions = make_shared<QGroupBox>(tr("fields"));
	// actions layout
	this->actionsLayout = make_shared<QGridLayout>();
	this->actions->setLayout(this->actionsLayout.get());

	// book fields
	this->titleLabel = make_shared<QLabel>(tr("Title:"));
	this->authorLabel = make_shared<QLabel>(tr("Author:"));
	this->genreLabel = make_shared<QLabel>(tr("Genre:"));
	this->releaseYearLabel = make_shared<QLabel>(tr("Release year:"));
	this->titleField = make_shared<QLineEdit>();
	this->authorField = make_shared<QLineEdit>();
	this->genreField = make_shared<QLineEdit>();
	this->releaseYearField = make_shared<QSpinBox>();
	this->releaseYearField->setMaximum(2020);

	// accept and cancel buttons
	this->acceptButton = make_shared<QPushButton>(tr("Accept"));
	this->cancelButton = make_shared<QPushButton>(tr("Cancel"));

	// adding widgets to layouts
	
	// adding accept and cancel buttons
	this->actionsLayout->addWidget(this->acceptButton.get(), 8, 0, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->cancelButton.get(), 8, 2, Qt::AlignCenter);

	// adding book fields
	this->actionsLayout->addWidget(this->titleLabel.get(), 0, 0, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->titleField.get(), 0, 2, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->authorLabel.get(), 2, 0, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->authorField.get(), 2, 2, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->genreLabel.get(), 4, 0, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->genreField.get(), 4, 2, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->releaseYearLabel.get(), 6, 0, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->releaseYearField.get(), 6, 2, Qt::AlignCenter);

	// adding books list and actions
	this->menuLayout->addWidget(this->booksList.get());
	this->menuLayout->addWidget(this->actions.get());
}

void ModifyMenu::Show()
{
	try
	{
		std::vector<Book> books = this->service->GetBooks();
		for (Book const &book: books)
		{
			QListWidgetItem* item = new QListWidgetItem(tr(("Title: " + book.getTitle() + " | Author: " + book.getAuthor()).c_str()));
    
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

void ModifyMenu::Hide()
{
	this->booksList->clearSelection();
	this->booksList->clear();

	this->titleField->clear();
	this->authorField->clear();
	this->genreField->clear();
	this->releaseYearField->clear();

	this->hide();
}

