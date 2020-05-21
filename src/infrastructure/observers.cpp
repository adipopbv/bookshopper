#include "./observers.h"

void Observable::AddObserver(Observer* observer)
{
	observers.push_back(observer);
}

void Observable::RemoveObserver(Observer* observer)
{
	observers.erase(remove(begin(observers), end(observers), observer), observers.end());
}

