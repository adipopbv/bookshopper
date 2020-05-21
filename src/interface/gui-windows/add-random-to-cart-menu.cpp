#include "./add-random-to-cart-menu.h"

AddRandomToCartMenu::AddRandomToCartMenu()
{
	// menu title
	this->setTitle(tr("add random to cart menu"));
	// menu layout
	this->menuLayout = make_shared<QGridLayout>();
	this->setLayout(this->menuLayout.get());

	// creating widgets

	// count options
	this->countLabel = make_shared<QLabel>(tr("How many:"));
	this->countField = make_shared<QSpinBox>();
	this->countField->setMaximum(10);

	// accept and cancel buttons
	this->acceptButton = make_shared<QPushButton>(tr("Accept"));
	this->cancelButton = make_shared<QPushButton>(tr("Cancel"));

	// adding widgets to layout

	// adding accept and cancel buttons
	this->menuLayout->addWidget(this->acceptButton.get(), 2, 0, Qt::AlignCenter);
	this->menuLayout->addWidget(this->cancelButton.get(), 2, 2, Qt::AlignCenter);

	// adding book fields
	this->menuLayout->addWidget(this->countLabel.get(), 0, 0, Qt::AlignCenter);
	this->menuLayout->addWidget(this->countField.get(), 0, 2, Qt::AlignCenter);
}

void AddRandomToCartMenu::Show()
{
	this->show();
}

void AddRandomToCartMenu::Hide()
{
	this->hide();

	this->countField->clear();
}

