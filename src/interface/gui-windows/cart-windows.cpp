#include "./cart-windows.h"
#include <iostream>

CartReadOnlyWindow::CartReadOnlyWindow(shared_ptr<BookstoreService> service)
{
	this->service = service;
	service->AddObserver(this);
}

CartReadOnlyWindow::~CartReadOnlyWindow()
{
	service->RemoveObserver(this);
}

void CartReadOnlyWindow::Update()
{
	this->repaint();
}

void CartReadOnlyWindow::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	for (Book const &book: service->getCart()->toVector())
	{
		random_device rd;
		mt19937 rng(rd());
		uniform_int_distribution<int> uni = uniform_int_distribution<int>(1, this->width());
		auto randomX = uni(rng);
		uni = uniform_int_distribution<int>(1, this->height());
		auto randomY = uni(rng);

		painter.drawText(randomX, randomY, QString(tr(book.getTitle().c_str())));
	}
}

void CartReadOnlyWindow::Show()
{
	this->show();
	this->Update();
}

void CartReadOnlyWindow::Hide()
{
	this->hide();
}

CartReadWriteWindow::CartReadWriteWindow(shared_ptr<BookstoreService> service)
{

}

CartReadWriteWindow::~CartReadWriteWindow()
{

}

void CartReadWriteWindow::Update()
{

}

void CartReadWriteWindow::ReloadList()
{

}

void CartReadWriteWindow::Show()
{
	this->show();
}

void CartReadWriteWindow::Hide()
{
	this->hide();
}

