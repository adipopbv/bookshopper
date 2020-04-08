#include <gtest/gtest.h>
#include "../../src/business/services.h"

TEST(BookstoreService, GetBooks)
{
	Repo<Book> books = Repo<Book>();
	Book book = Book("ceva", "cineva", "careva", 2020);
	books.Add(book);
	BookstoreService service = BookstoreService();
	ASSERT_THROW(service.GetBooks()[0], EmptyRepoError);
	service.getBooksRepo().FreeRepo();
	service = BookstoreService(books);
	ASSERT_TRUE(service.GetBooks()[0] == books[0]);
	books.FreeRepo();
}

TEST(BookstoreService, AddBookToRepo)
{
	Book book1 = Book("ceva", "cineva", "careva", 2020);
	Book book2 = Book("ce", "se", "intampla", 301);
	BookstoreService service = BookstoreService();
	service.AddBookToRepo("ceva", "cineva", "careva", 2020);
	service.AddBookToRepo("ce", "se", "intampla", 301);
	ASSERT_TRUE(service.GetBooks()[0] == book1);
	ASSERT_TRUE(service.GetBooks()[1] == book2);
	ASSERT_THROW(service.AddBookToRepo("ce", "se", "petrece", 123), DuplicateError);
	ASSERT_THROW(service.AddBookToRepo("", "", "", -3), ValidationError);
	ASSERT_TRUE(service.GetBooks().Size() == 2);
	service.getBooksRepo().FreeRepo();
}

TEST(BookstoreService, ModifyBookInRepo)
{
	Book book1 = Book("ceva", "cineva", "careva", 2020);
	Book book2 = Book("ce", "se", "intampla", 301);
	Book book3 = Book("vai", "de", "noi", 2020);
	BookstoreService service = BookstoreService();
	service.AddBookToRepo("ceva", "cineva", "careva", 2020);
	service.AddBookToRepo("ce", "se", "intampla", 301);
	ASSERT_THROW(service.ModifyBookInRepo("ceva", "cineva", "ce", "se", "intampla", 301), DuplicateError);
	ASSERT_THROW(service.ModifyBookInRepo("ceva", "cineva", "", "", "", -88), ValidationError);
	ASSERT_THROW(service.ModifyBookInRepo("", "a", "", "", "", -3), SearchFieldsError);
	ASSERT_THROW(service.ModifyBookInRepo("haa", "yaa", "", "", "", 1), NotFoundError);
	service.ModifyBookInRepo("ceva", "cineva", "vai", "de", "noi", 2020);
	ASSERT_TRUE(service.GetBooks()[0] == book3);
	ASSERT_TRUE(service.GetBooks().Size() == 2);
	service.getBooksRepo().FreeRepo();
}

TEST(BookstoreService, DeleteBookFromRepo)
{
	Book book1 = Book("ceva", "cineva", "careva", 2020);
	Book book2 = Book("ce", "se", "intampla", 301);
	BookstoreService service = BookstoreService();
	service.AddBookToRepo("ceva", "cineva", "careva", 2020);
	service.AddBookToRepo("ce", "se", "intampla", 301);
	ASSERT_THROW(service.DeleteBookFromRepo("a", ""), SearchFieldsError);
	ASSERT_THROW(service.DeleteBookFromRepo("a", "b"), NotFoundError);
	service.DeleteBookFromRepo("ceva", "cineva");
	ASSERT_TRUE(service.GetBooks()[0] == book2);
	ASSERT_TRUE(service.GetBooks().Size() == 1);
	service.getBooksRepo().FreeRepo();
}

TEST(BookstoreService, SearchBook)
{
	Book book1 = Book("ceva", "cineva", "careva", 2020);
	Book book2 = Book("ceva", "se", "intampla", 301);
	BookstoreService service = BookstoreService();
	service.AddBookToRepo("ceva", "cineva", "careva", 2020);
	service.AddBookToRepo("ceva", "se", "intampla", 301);
	ASSERT_THROW(service.SearchBook("", "", "", -1), SearchFieldsError);
	ASSERT_THROW(service.SearchBook("a", "b", "c", 1), NotFoundError);
	ASSERT_TRUE(service.SearchBook("ceva", "", "", -1) == book1);
	ASSERT_TRUE(service.SearchBook("ceva", "", "intampla", -1) == book2);
	service.getBooksRepo().FreeRepo();
}

TEST(BookstoreService, GetFilteredBooks)
{
	Book book1 = Book("ceva", "cineva", "careva", 2020);
	Book book2 = Book("ceva", "se", "intampla", 301);
	Book book3 = Book("ce", "se", "intampla", 2020);
	BookstoreService service = BookstoreService();
	ASSERT_THROW(service.GetFilteredBooks("ceva"), EmptyRepoError);
	ASSERT_THROW(service.GetFilteredBooks(2020), EmptyRepoError);
	ASSERT_THROW(service.GetFilteredBooks(""), SearchFieldsError);
	ASSERT_THROW(service.GetFilteredBooks(-20), SearchFieldsError);
	service.AddBookToRepo("ceva", "cineva", "careva", 2020);
	service.AddBookToRepo("ceva", "se", "intampla", 301);
	service.AddBookToRepo("ce", "se", "intampla", 2020);
	ASSERT_THROW(service.GetFilteredBooks("va"), NotFoundError);
	ASSERT_THROW(service.GetFilteredBooks(1900), NotFoundError);
	Repo<Book> filteredBooks = service.GetFilteredBooks("ceva");
	ASSERT_TRUE(filteredBooks[0] == book1 && filteredBooks[1] == book2);
	filteredBooks.FreeRepo();
	filteredBooks = service.GetFilteredBooks(2020);
	ASSERT_TRUE(filteredBooks[0] == book1 && filteredBooks[1] == book3);
	filteredBooks.FreeRepo();
	service.getBooksRepo().FreeRepo();
}

TEST(BookstoreService, SortBooksByTitle)
{
	Book book1 = Book("ce", "se", "intampla", 301);
	Book book2 = Book("vai", "de", "noi", 2020);
	Book book3 = Book("ceva", "cineva", "careva", 2020);
	BookstoreService service = BookstoreService();
	service.AddBookToRepo("ce", "se", "intampla", 301);
	service.AddBookToRepo("vai", "de", "noi", 2020);
	service.AddBookToRepo("ceva", "cineva", "careva", 2020);
	service.SortBooksByTitle();
	ASSERT_TRUE(service.GetBooks()[0] == book1
			&& service.GetBooks()[1] == book3
			&& service.GetBooks()[2] == book2);
	service.getBooksRepo().FreeRepo();
}

TEST(BookstoreService, SortBooksByAuthor)
{
	Book book1 = Book("ce", "se", "intampla", 301);
	Book book2 = Book("vai", "de", "noi", 2020);
	Book book3 = Book("ceva", "cineva", "careva", 2020);
	BookstoreService service = BookstoreService();
	service.AddBookToRepo("ce", "se", "intampla", 301);
	service.AddBookToRepo("vai", "de", "noi", 2020);
	service.AddBookToRepo("ceva", "cineva", "careva", 2020);
	service.SortBooksByAuthor();
	ASSERT_TRUE(service.GetBooks()[0] == book3
			&& service.GetBooks()[1] == book2
			&& service.GetBooks()[2] == book1);
	service.getBooksRepo().FreeRepo();
}

TEST(BookstoreService, SortBooksByReleaseYearAndGenre)
{
	Book book1 = Book("ce", "se", "intampla", 301);
	Book book2 = Book("vai", "de", "noi", 2020);
	Book book3 = Book("ceva", "cineva", "careva", 2020);
	BookstoreService service = BookstoreService();
	service.AddBookToRepo("ce", "se", "intampla", 301);
	service.AddBookToRepo("vai", "de", "noi", 2020);
	service.AddBookToRepo("ceva", "cineva", "careva", 2020);
	service.SortBooksByReleaseYearAndGenre();
	ASSERT_TRUE(service.GetBooks()[0] == book1
			&& service.GetBooks()[1] == book3
			&& service.GetBooks()[2] == book2);
	service.getBooksRepo().FreeRepo();
}
