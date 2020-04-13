#include <iostream>
#include <vector>

#include "business/services.h"
#include "domain/entities.h"
#include "infrastructure/repos.h"
#include "interface/clients.h"

auto main() -> int
{
	Repo<Book> booksRepo = Repo<Book>(); // the books repository
	Repo<Book> cart = Repo<Book>(); // the shopping cart
	BookstoreService bookstoreService = BookstoreService(booksRepo, cart); // the library service
	BookstoreClient bookstoreClient = BookstoreClient(bookstoreService); // the library client

	bookstoreClient.RunApplication(); // application loop

	return 0;
}
