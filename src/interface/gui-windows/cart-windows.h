#pragma once

#include <memory>
#include <QGroupBox>
#include <QPainter>
#include <random>
#include <QHBoxLayout>
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>

#include "../../infrastructure/observers.h"
#include "../../domain/entities.h"
#include "../../business/services.h"

using namespace std;

class CartReadOnlyWindow: public QGroupBox, public Observer
{
	protected:
		/// Service reference
		shared_ptr<BookstoreService> service;

	public:
		/**
		 * @brief CartReadOnlyWindow constructor
		 *
		 * @param service Service reference
		 */
		CartReadOnlyWindow(shared_ptr<BookstoreService> service);

		/// CartReadOnlyWindow destructor
		~CartReadOnlyWindow();

		/**
		 * @brief Invoked when service books changed
		 */
		void Update() override;

		/// Repaints window
		void paintEvent(QPaintEvent* ev) override;

		void Show();

		void Hide();
};

class BookListModel: public QAbstractListModel
{
	public:
		vector<Book> books;

		/// Gets data of item at index and with role
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

		/// Gets row count
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
};

class CartReadWriteWindow: public QGroupBox, public Observer
{
	protected:
		/// Service reference
		shared_ptr<BookstoreService> service;

		shared_ptr<QHBoxLayout> windowLayout;

		shared_ptr<QListView> booksList;
		shared_ptr<BookListModel> booksListModel;

		shared_ptr<QGroupBox> actions;
		shared_ptr<QGridLayout> actionsLayout;

	public:
		shared_ptr<QPushButton> emptyButton, addRandomButton;
		shared_ptr<QSpinBox> addRandomField;

		/**
		 * @brief CartReadWriteWindow constructor
		 *
		 * @param service Service reference
		 */
		CartReadWriteWindow(shared_ptr<BookstoreService> service);

		/// CartReadWriteWindow destructor
		~CartReadWriteWindow();

		/**
		 * @brief Invoked when service books changed
		 */
		void Update() override;

		/**
		 * @brief Reloads books list
		 */
		void ReloadList();

		void Show();

		void Hide();
};

