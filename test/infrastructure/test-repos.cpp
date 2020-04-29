#include <gtest/gtest.h>
#include "../../src/infrastructure/repos.h"
#include "../../src/domain/exceptions.h"

TEST(DictRepo, OperatorSubscription)
{
	DictRepo<int> repo = DictRepo<int>();
	int element = 0;
	ASSERT_THROW(repo[0], EmptyRepoError);
	repo.Add(element);
	ASSERT_TRUE(repo[0] == 0
			&& repo[0] == element);
	ASSERT_THROW(repo[1], IndexError);
	repo[0] = 1;
	ASSERT_TRUE(repo[0] == 1
			&& repo[0] != element);
	element = 2;
	ASSERT_TRUE(repo[0] == 1);
}

TEST(DictRepo, Size)
{
	DictRepo<int> repo = DictRepo<int>();
	int element1 = 1, element2 = 2, element3 = 3;
	ASSERT_TRUE(repo.Size() == 0);
	repo.Add(element1);
	ASSERT_TRUE(repo.Size() == 1);
	repo.Add(element2);
	ASSERT_TRUE(repo.Size() == 2);
	repo.Add(element3, true);
	ASSERT_TRUE(repo.Size() == 3);
}

TEST(DictRepo, Empty)
{
	DictRepo<int> repo = DictRepo<int>();
	ASSERT_TRUE(repo.Empty());
	repo.Add(0);
	ASSERT_FALSE(repo.Empty());
}

TEST(DictRepo, Swap)
{
	DictRepo<int> repo = DictRepo<int>();
	int element1 = 1, element2 = 2;
	repo.Add(element1);
	repo.Add(element2);
	ASSERT_TRUE(repo[0] == element1
			&& repo[1] == element2);
	ASSERT_THROW(repo.Swap(0, 3), IndexError);
	ASSERT_THROW(repo.Swap(0, 0), IndexError);
	ASSERT_THROW(repo.Swap(8, -3), IndexError);
	repo.Swap(0, 1);
	ASSERT_TRUE(repo[0] == element2
			&& repo[1] == element1);
}

TEST(DictRepo, Add)
{
	DictRepo<int> repo = DictRepo<int>();
	int element1 = 1, element2 = 2, element3 = 3, element4 = 2;
	repo.Add(element1);
	ASSERT_TRUE(repo[0] == element1);
	repo.Add(element2);
	ASSERT_TRUE(repo[0] == element1
			&& repo[1] == element2);
	repo.Add(element3);
	ASSERT_TRUE(repo[0] == element1
			&& repo[1] == element2
			&& repo[2] == element3);
	ASSERT_THROW(repo.Add(element4), DuplicateError);
}

TEST(DictRepo, Insert)
{
	DictRepo<int> repo = DictRepo<int>();
	int element1 = 1, element2 = 2, element3 = 3, element4 = 4;
	ASSERT_THROW(repo.Insert(1, element1), EmptyRepoError);
	repo.Add(element1);
	ASSERT_TRUE(repo[0] == element1);
	repo.Insert(0, element2);
	ASSERT_TRUE(repo[0] == element2
			&& repo[1] == element1);
	repo.Insert(1, element3);
	ASSERT_TRUE(repo[0] == element2
			&& repo[1] == element3
			&& repo[2] == element1);
	ASSERT_THROW(repo.Insert(2, element3), DuplicateError);
	ASSERT_THROW(repo.Insert(4, element4), IndexError);
	repo.Insert(0, element4);
	ASSERT_TRUE(repo[0] == element4
			&& repo[1] == element2
			&& repo[2] == element3
			&& repo[3] == element1);
}

TEST(DictRepo, Erase)
{
	DictRepo<int> repo = DictRepo<int>();
	int element1 = 1, element2 = 2, element3 = 3;
	repo.Add(element1);
	repo.Add(element2);
	repo.Add(element3);
	ASSERT_THROW(repo.Erase(3), IndexError);
	repo.Erase(1);
	ASSERT_TRUE(repo[0] == element1
			&& repo[1] == element3);
	repo.Erase(0);
	ASSERT_TRUE(repo[0] == element3);
	repo.Erase(0);
	ASSERT_TRUE(repo.Size() == 0);
}

TEST(DictRepo, FindIf)
{
	DictRepo<int> repo = DictRepo<int>();
	int element1 = 1, element2 = 1;
	ASSERT_THROW(repo.FindIf([](int currentElem){ return true; }), EmptyRepoError);
	repo.Add(element1);
	ASSERT_TRUE(repo.FindIf([&element2](int currentElem){ return currentElem == element2; }) == 0);
	element2 = 2;
	ASSERT_THROW(repo.FindIf([&element2](int currentElem){ return currentElem == element2; }), NotFoundError);
}

TEST(DictRepo, Sort)
{
	DictRepo<int> repo = DictRepo<int>();
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

