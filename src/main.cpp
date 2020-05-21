#include <iostream>
#include <memory>
#include <cstring>
#include <vector>

#include "./business/services.h"
#include "./domain/entities.h"
#include "./infrastructure/repos.h"
#include "./interface/gui-clients.h"
#include "./interface/tui-clients.h"

int main(int argc, char** argv)
{
	// the books repository
	std::shared_ptr<Repo<Book>> booksRepo = std::make_shared<DictRepo<Book>>();
	// the shopping cart
	std::shared_ptr<Repo<Book>> cart = std::make_shared<DictRepo<Book>>();
	// the bookshop service
	std::shared_ptr<BookstoreService> bookstoreService = std::make_shared<BookstoreService>(booksRepo, cart);
	
	// the bookshop client
	std::shared_ptr<BookstoreClient> bookstoreClient;

	// start the application with the wanted interface
	if (argc >= 2)
	{
		if (!std::strcmp(argv[1], "-g") || !std::strcmp(argv[1], "--gui"))
		{ bookstoreClient = std::make_shared<GraphicalBookstoreClient>(bookstoreService, argc, argv); }
		else if (!std::strcmp(argv[1], "-t") || !std::strcmp(argv[1], "--tui"))
		{ bookstoreClient = std::make_shared<TerminalBookstoreClient>(bookstoreService); }
	}
	else
	{ bookstoreClient = std::make_shared<GraphicalBookstoreClient>(bookstoreService, argc, argv); }
	return bookstoreClient->RunApplication();
}

