#include "./cart-windows.h"

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

QVariant BookListModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		Book const &book = books[index.row()];
		return QString(tr(("Title: " + book.getTitle() + 
					"\n  Author: " + book.getAuthor() +
					"\n  Genre: " + book.getGenre() +
					"\n  Release year: " + std::to_string(book.getReleaseYear())).c_str()));
	}

	return QVariant();
}

int BookListModel::rowCount(const QModelIndex &parent) const
{
	return books.size();
}

CartReadWriteWindow::CartReadWriteWindow(shared_ptr<BookstoreService> service)
{
	this->service = service;
	service->AddObserver(this);

	windowLayout = make_shared<QHBoxLayout>();
	setLayout(windowLayout.get());

	booksList = make_shared<QListView>();
	booksListModel = make_shared<BookListModel>();
	booksList->setModel(booksListModel.get());
	windowLayout->addWidget(booksList.get());

	actions = make_shared<QGroupBox>(tr("actions:"));
	actionsLayout = make_shared<QGridLayout>();
	actions->setLayout(actionsLayout.get());
	windowLayout->addWidget(actions.get());

	emptyButton = make_shared<QPushButton>(tr("Empty cart"));
	actionsLayout->addWidget(emptyButton.get(), 0, 0, Qt::AlignCenter);
	addRandomButton = make_shared<QPushButton>(tr("Add random"));
	actionsLayout->addWidget(addRandomButton.get(), 2, 0, Qt::AlignCenter);
	addRandomField = make_shared<QSpinBox>();
	addRandomField->setMaximum(20);
	actionsLayout->addWidget(addRandomField.get(), 2, 2, Qt::AlignCenter);
}

CartReadWriteWindow::~CartReadWriteWindow()
{
	service->RemoveObserver(this);
}

void CartReadWriteWindow::Update()
{
	ReloadList();
}

void CartReadWriteWindow::ReloadList()
{
	booksListModel = make_shared<BookListModel>();
	booksListModel->books = service->getCart()->toVector();
	booksList->setModel(booksListModel.get());
}

void CartReadWriteWindow::Show()
{
	addRandomField->setValue(0);
	ReloadList();
	this->show();
}

void CartReadWriteWindow::Hide()
{
	this->hide();
}

