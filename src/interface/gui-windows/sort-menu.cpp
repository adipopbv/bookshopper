#include "./sort-menu.h"

SortMenu::SortMenu()
{
	// menu title
	this->setTitle(tr("sort menu"));
	// menu layout
	this->menuLayout = make_shared<QGridLayout>();
	this->setLayout(this->menuLayout.get());

	// creating widgets

	// sort options
	this->sortByTitle = make_shared<QCheckBox>(tr("by title"));
	this->sortByTitle->setChecked(true);
	this->sortByAuthor = make_shared<QCheckBox>(tr("by author"));
	this->sortByAuthor->setChecked(false);
	this->sortByReleaseYearAndGenre = make_shared<QCheckBox>(tr("by release year and genre"));
	this->sortByReleaseYearAndGenre->setChecked(false);
	this->sortOptions = make_shared<QButtonGroup>();
	this->sortOptions->setExclusive(true);
	this->sortOptions->addButton(this->sortByTitle.get());
	this->sortOptions->addButton(this->sortByAuthor.get());
	this->sortOptions->addButton(this->sortByReleaseYearAndGenre.get());

	// accept and cancel buttons
	this->acceptButton = make_shared<QPushButton>(tr("Accept"));
	this->cancelButton = make_shared<QPushButton>(tr("Cancel"));

	// adding widgets to layout

	// adding accept and cancel buttons
	this->menuLayout->addWidget(this->acceptButton.get(), 6, 0, Qt::AlignCenter);
	this->menuLayout->addWidget(this->cancelButton.get(), 6, 2, Qt::AlignCenter);

	// adding book fields
	this->menuLayout->addWidget(this->sortByTitle.get(), 0, 0, Qt::AlignLeft);
	this->menuLayout->addWidget(this->sortByAuthor.get(), 2, 0, Qt::AlignLeft);
	this->menuLayout->addWidget(this->sortByReleaseYearAndGenre.get(), 4, 0, Qt::AlignLeft);
}

void SortMenu::Show()
{
	this->show();
}

void SortMenu::Hide()
{
	this->hide();

	this->sortByTitle->setChecked(true);
	this->sortByAuthor->setChecked(false);
	this->sortByReleaseYearAndGenre->setChecked(false);
}

