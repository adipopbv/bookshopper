#include <iostream>
#include <vector>

#include "./business/services.h"
#include "./domain/entities.h"
#include "./infrastructure/repos.h"
#include "./interface/clients.h"

auto main() -> int
{
	// the books repository
	Repo<Book> booksRepo = Repo<Book>();
	// the shopping cart
	Repo<Book> cart = Repo<Book>();
	// the bookshop service
	BookstoreService bookstoreService = BookstoreService(booksRepo, cart);
	// the bookshop client
	BookstoreClient bookstoreClient = BookstoreClient(bookstoreService);

	// start the application
	bookstoreClient.RunApplication();
	return 0;
}

