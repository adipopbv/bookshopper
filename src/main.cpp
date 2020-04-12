#include <iostream>
#include <vector>

#include "business/services.h"
#include "domain/entities.h"
#include "infrastructure/repos.h"
#include "interface/clients.h"

auto main() -> int
{
	std::vector<Book> booksRepo = std::vector<Book>(); // the books repository
	std::vector<Book> cart = std::vector<Book>(); // the shopping cart
	BookstoreService bookstoreService = BookstoreService(booksRepo, cart); // the library service
	BookstoreClient bookstoreClient = BookstoreClient(bookstoreService); // the library client

	bookstoreClient.RunApplication(); // application loop

	return 0;
}
