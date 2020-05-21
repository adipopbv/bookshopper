#include "./filter-menu.h"

FilterMenu::FilterMenu()
{
	// menu title
	this->setTitle(tr("filter menu"));
	// menu layout
	this->menuLayout = make_shared<QHBoxLayout>();
	this->setLayout(this->menuLayout.get());

	// creating widgets
	
	// rezult
	this->rezult = make_shared<QGroupBox>(tr("rezult"));
	// rezult layout
	this->rezultLayout = make_shared<QVBoxLayout>();
	this->rezult->setLayout(this->rezultLayout.get());

	// books list
	this->booksList = make_shared<QListWidget>();

	// ok button
	this->okButton = make_shared<QPushButton>(tr("Done"));

	// actions
	this->actions = make_shared<QGroupBox>(tr("search fields"));
	// actions layout
	this->actionsLayout = make_shared<QGridLayout>();
	this->actions->setLayout(this->actionsLayout.get());

	// book fields
	this->searchByYear = make_shared<QCheckBox>(tr("Search by release year"));
	QObject::connect(this->searchByYear.get(), &QCheckBox::stateChanged, [this] () {
		if (this->searchByYear->isChecked())
		{
			this->titleField->setDisabled(true);
			this->releaseYearField->setEnabled(true);
		}
		else
		{
			this->titleField->setEnabled(true);
			this->releaseYearField->setDisabled(true);
		}
	});
	this->titleLabel = make_shared<QLabel>(tr("Title:"));
	this->releaseYearLabel = make_shared<QLabel>(tr("Release year:"));
	this->titleField = make_shared<QLineEdit>();
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
	this->actionsLayout->addWidget(this->searchByYear.get(), 0, 0, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->titleLabel.get(), 2, 0, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->titleField.get(), 2, 2, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->releaseYearLabel.get(), 4, 0, Qt::AlignCenter);
	this->actionsLayout->addWidget(this->releaseYearField.get(), 4, 2, Qt::AlignCenter);

	// adding book list
	this->rezultLayout->addWidget(this->booksList.get());

	// adding ok button
	this->rezultLayout->addWidget(this->okButton.get(), Qt::AlignCenter);

	// adding books list and actions
	this->menuLayout->addWidget(this->rezult.get());
	this->menuLayout->addWidget(this->actions.get());
}

void FilterMenu::Show()
{
	this->rezult->setDisabled(true);

	this->searchByYear->setChecked(false);
	this->releaseYearField->setDisabled(true);

	this->show();
}

void FilterMenu::Hide()
{
	this->hide();

	this->booksList->clearSelection();
	this->booksList->clear();

	this->titleField->clear();
	this->releaseYearField->clear();

	this->rezult->setEnabled(true);
	this->actions->setEnabled(true);
}

void FilterMenu::SwitchFocus()
{
	this->rezult->setEnabled(true);
	this->actions->setDisabled(true);
}

