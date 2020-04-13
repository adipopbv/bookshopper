#include <gtest/gtest.h>
#include "../../src/infrastructure/repos.h"
#include "../../src/domain/exceptions.h"

TEST(Repo, SubscriptionOperator)
{
	Repo<int> repo = Repo<int>();
	int element = 0;
	ASSERT_THROW(repo[0], EmptyRepoError);
	repo.Add(element);
	ASSERT_TRUE(repo[0] == 0);
	ASSERT_TRUE(repo[0] == element);
	ASSERT_THROW(repo[1], IndexError);
	repo[0] = 1;
	ASSERT_TRUE(repo[0] == 1);
	ASSERT_TRUE(repo[0] != element);
	element = 2;
	ASSERT_TRUE(repo[0] == 1);
}

TEST(Repo, Size)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 2, element3 = 3;
	ASSERT_TRUE(repo.Size() == 0);
	repo.Add(element1);
	ASSERT_TRUE(repo.Size() == 1);
	repo.Add(element2);
	ASSERT_TRUE(repo.Size() == 2);
	repo.Add(element3, true);
	ASSERT_TRUE(repo.Size() == 3);
}

TEST(Repo, Empty)
{
	Repo<int> repo = Repo<int>();
	ASSERT_TRUE(repo.Empty());
	repo.Add(0);
	ASSERT_FALSE(repo.Empty());
}

TEST(Repo, Swap)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 2;
	repo.Add(element1);
	repo.Add(element2);
	ASSERT_TRUE(repo[0] == element1 && repo[1] == element2);
	ASSERT_THROW(repo.Swap(0, 3), IndexError);
	ASSERT_THROW(repo.Swap(8, -3), IndexError);
	repo.Swap(0, 1);
	ASSERT_TRUE(repo[0] == element2 && repo[1] == element1);
}

TEST(Repo, Add)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 2, element3 = 3, element4 = 2;
	repo.Add(element1);
	ASSERT_TRUE(repo[0] == element1);
	repo.Add(element2);
	ASSERT_TRUE(repo[0] == element1);
	ASSERT_TRUE(repo[1] == element2);
	repo.Add(element3);
	ASSERT_TRUE(repo[0] == element1);
	ASSERT_TRUE(repo[1] == element2);
	ASSERT_TRUE(repo[2] == element3);
	ASSERT_THROW(repo.Add(element4), DuplicateError);
}

TEST(Repo, Insert)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 2, element3 = 3, element4 = 4;
	ASSERT_THROW(repo.Insert(1, element1), EmptyRepoError);
	repo.Add(element1);
	ASSERT_TRUE(repo[0] == element1);
	repo.Insert(0, element2);
	ASSERT_TRUE(repo[0] == element2);
	ASSERT_TRUE(repo[1] == element1);
	repo.Insert(1, element3);
	ASSERT_TRUE(repo[0] == element2);
	ASSERT_TRUE(repo[1] == element3);
	ASSERT_TRUE(repo[2] == element1);
	ASSERT_THROW(repo.Insert(element3, 2), DuplicateError);
	ASSERT_THROW(repo.Insert(element4, 4), IndexError);
	repo.Insert(0, element4);
	ASSERT_TRUE(repo[0] == element4);
	ASSERT_TRUE(repo[1] == element2);
	ASSERT_TRUE(repo[2] == element3);
	ASSERT_TRUE(repo[3] == element1);
}

TEST(Repo, Erase)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 2, element3 = 3;
	repo.Add(element1);
	repo.Add(element2);
	repo.Add(element3);
	ASSERT_THROW(repo.Erase(3), IndexError);
	repo.Erase(1);
	ASSERT_TRUE(repo[0] == element1);
	ASSERT_TRUE(repo[1] == element3);
	repo.Erase(0);
	ASSERT_TRUE(repo[0] == element3);
}

TEST(Repo, GetElement)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 1;
	ASSERT_THROW(repo.GetElement([](int currentElem){ return true; }), EmptyRepoError);
	repo.Add(element1);
	ASSERT_TRUE(repo.GetElement([&element2](int currentElem){ return currentElem == element2; }) == element1);
	element2 = 2;
	ASSERT_THROW(repo.GetElement([&element2](int currentElem){ return currentElem == element2; }), NotFoundError);
}

TEST(Repo, GetIndexOfElement)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 1;
	ASSERT_THROW(repo.GetIndexOfElement([](int currentElem){ return true; }), EmptyRepoError);
	repo.Add(element1);
	ASSERT_TRUE(repo.GetIndexOfElement([&element2](int currentElem){ return currentElem == element2; }) == 0);
	element2 = 2;
	ASSERT_THROW(repo.GetIndexOfElement([&element2](int currentElem){ return currentElem == element2; }), NotFoundError);
}

TEST(Repo, Sort)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 2, element3 = 3;
	ASSERT_THROW(repo.Sort([](int first, int second){ return (first < second); }), EmptyRepoError);
	repo.Add(element2);
	repo.Add(element3);
	repo.Add(element1);
	repo.Sort([](int first, int second){ return (first < second); });
	ASSERT_TRUE(repo.getElements()[0] == element1
			&& repo.getElements()[1] == element2
			&& repo.getElements()[2] == element3);
}

