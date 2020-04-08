#include <gtest/gtest.h>
#include "../../src/infrastructure/repos.h"
#include "../../src/domain/exceptions.h"

TEST(Repo, SubscriptionOperator)
{
	Repo<int> repo = Repo<int>();
	int element = 0;
	ASSERT_THROW(repo[0], IndexError);
	repo.Add(element);
	ASSERT_TRUE(repo[0] == 0);
	ASSERT_TRUE(repo[0] == element);
	ASSERT_THROW(repo[1], IndexError);
	repo[0] = 1;
	ASSERT_TRUE(repo[0] == 1);
	ASSERT_TRUE(repo[0] != element);
	element = 2;
	ASSERT_TRUE(repo[0] == 1);
	repo.FreeRepo();
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
	repo.FreeRepo();
}

TEST(Repo, Empty)
{
	Repo<int> repo = Repo<int>();
	ASSERT_TRUE(repo.Empty());
	repo.Add(0);
	ASSERT_FALSE(repo.Empty());
	repo.FreeRepo();
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
	repo.FreeRepo();
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
	repo.Add(element3, true);
	ASSERT_TRUE(repo[0] == element3);
	ASSERT_TRUE(repo[1] == element1);
	ASSERT_TRUE(repo[2] == element2);
	ASSERT_THROW(repo.Add(element4), DuplicateError);
	repo.FreeRepo();
}

TEST(Repo, Insert)
{
	Repo<int> repo = Repo<int>();
	int element1 = 1, element2 = 2, element3 = 3, element4 = 4;
	ASSERT_THROW(repo.Insert(element1, 1), IndexError);
	repo.Insert(element1, 0);
	ASSERT_TRUE(repo[0] == element1);
	repo.Insert(element2, 1);
	ASSERT_TRUE(repo[0] == element1);
	ASSERT_TRUE(repo[1] == element2);
	repo.Insert(element3, 1);
	ASSERT_TRUE(repo[0] == element1);
	ASSERT_TRUE(repo[1] == element3);
	ASSERT_TRUE(repo[2] == element2);
	ASSERT_THROW(repo.Insert(element3, 2), DuplicateError);
	ASSERT_THROW(repo.Insert(element4, 4), IndexError);
	repo.Insert(element4, 0);
	ASSERT_TRUE(repo[0] == element4);
	ASSERT_TRUE(repo[1] == element1);
	ASSERT_TRUE(repo[2] == element3);
	ASSERT_TRUE(repo[3] == element2);
	repo.FreeRepo();
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
	repo.FreeRepo();
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
	repo.FreeRepo();
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
	repo.FreeRepo();
}
