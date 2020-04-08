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
	{ message += "invalid title\n"; }
	if (author.empty())
	{ message += "invalid author\n"; }
	if (genre.empty())
	{ message += "invalid genre\n"; }
	if (releaseYear < 0)
	{ message += "invalid release year\n"; }
	
	if (!message.empty())
	{ throw ValidationError(message); }
}
