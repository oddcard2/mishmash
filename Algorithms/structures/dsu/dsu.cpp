#include "dsu.h"
#include <gtest/gtest.h>


dsu::dsu(int n)
{
	reinit_dsu(n);
}

void dsu::reinit_dsu(int n)
{
	parent.resize(n);
	rank.resize(n);
}

void dsu::make(int r)
{
	parent[r] = r;
	rank[r] = 1;
}

int dsu::find(int elem)
{
	if (parent[elem] == elem)
		return elem;
	parent[elem] = find(parent[elem]);
	return parent[elem];
}

int dsu::unite(int s1, int s2)
{
	s1 = find(s1);
	s2 = find(s2);

	//from s1 to s2
	if (rank[s2] < rank[s1])
		std::swap(s1, s2);

	parent[s1] = s2;
	if (rank[s1] == rank[s2])
		rank[s2]++;
	return s2;
}

TEST(dsu_tests, simple_test) {
	dsu d(5);
	d.make(1);
	d.make(2);

	EXPECT_EQ(1, d.find(1));
	EXPECT_EQ(2, d.find(2));

	int s1 = d.unite(1, 2);
	EXPECT_EQ(s1, d.find(1));
	EXPECT_EQ(s1, d.find(2));

	d.make(3);
	int s2 = d.unite(s1, 3);
	EXPECT_EQ(s1, s2);
}
