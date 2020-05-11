#include "./list-cart-titles-menu.h"

ListCartTitlesMenu::ListCartTitlesMenu(shared_ptr<BookstoreService> const &service)
{
	// service reference
	this->service = service;

	// menu title
	this->setTitle(tr("titles menu"));
	// menu layout
	this->menuLayout = make_shared<QVBoxLayout>();
	this->setLayout(this->menuLayout.get());

	// creating widgets

	// books list
	this->titlesList = make_shared<QListWidget>();

	// accept and cancel buttons
	this->okButton = make_shared<QPushButton>(tr("Ok"));

	// adding widgets to layouts

	// adding books list and actions
	this->menuLayout->addWidget(this->titlesList.get());
	this->menuLayout->addWidget(this->okButton.get());
}

void ListCartTitlesMenu::Show()
{
	try
	{
		std::vector<std::string> titles = this->service->GetCartTitles();
		for (std::string const &title: titles)
			this->titlesList->addItem(tr(title.c_str()));
		this->titlesList->clearSelection();
	}
	catch (AppException &e) { QMessageBox errorMessage; errorMessage.setText(tr(("Error:\n" + e.getMessage()).c_str())); errorMessage.exec(); }
	this->show();
}

void ListCartTitlesMenu::Hide()
{
	this->hide();

	this->titlesList->clearSelection();
	this->titlesList->clear();
}

