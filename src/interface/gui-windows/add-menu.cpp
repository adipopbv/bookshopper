#include "./add-menu.h"

AddMenu::AddMenu()
{
	// menu title
	this->setTitle(tr("add menu"));
	// menu layout
	this->menuLayout = make_shared<QGridLayout>();
	this->setLayout(this->menuLayout.get());

	// creating widgets

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

	// adding widgets to layout

	// adding accept and cancel buttons
	this->menuLayout->addWidget(this->acceptButton.get(), 8, 0, Qt::AlignCenter);
	this->menuLayout->addWidget(this->cancelButton.get(), 8, 2, Qt::AlignCenter);

	// adding book fields
	this->menuLayout->addWidget(this->titleLabel.get(), 0, 0, Qt::AlignCenter);
	this->menuLayout->addWidget(this->titleField.get(), 0, 2, Qt::AlignCenter);
	this->menuLayout->addWidget(this->authorLabel.get(), 2, 0, Qt::AlignCenter);
	this->menuLayout->addWidget(this->authorField.get(), 2, 2, Qt::AlignCenter);
	this->menuLayout->addWidget(this->genreLabel.get(), 4, 0, Qt::AlignCenter);
	this->menuLayout->addWidget(this->genreField.get(), 4, 2, Qt::AlignCenter);
	this->menuLayout->addWidget(this->releaseYearLabel.get(), 6, 0, Qt::AlignCenter);
	this->menuLayout->addWidget(this->releaseYearField.get(), 6, 2, Qt::AlignCenter);
}

void AddMenu::Show()
{
	this->show();
}

void AddMenu::Hide()
{
	this->hide();

	this->titleField->clear();
	this->authorField->clear();
	this->genreField->clear();
	this->releaseYearField->clear();
}

