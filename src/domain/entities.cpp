#include "./entities.h"

Book::Book(std::string title, std::string author, std::string genre, int releaseYear)
{
	this->ValidateData(title, author, genre, releaseYear);
	// setting fields of Book instance to parameter values
	this->setTitle(title);
	this->setAuthor(author);
	this->setGenre(genre);
	this->setReleaseYear(releaseYear);
}

Book::~Book()
{
	// setting fields of Book instance to default values
	this->setTitle("");
	this->setAuthor("");
	this->setGenre("");
	this->setReleaseYear(0);
}

void Book::ValidateData(const std::string title, const std::string author, const std::string genre, const int releaseYear) const
{
	std::string message = "";
	if (title.empty())
	{ message += "\ninvalid title"; }
	if (author.empty())
	{ message += "\ninvalid author"; }
	if (genre.empty())
	{ message += "\ninvalid genre"; }
	if (releaseYear < 0)
	{ message += "\ninvalid release year"; }
	
	if (!message.empty())
	{ throw ValidationError(message); }
}
