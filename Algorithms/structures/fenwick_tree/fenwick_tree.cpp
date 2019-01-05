#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {

	//http://e-maxx.ru/algo/fenwick_tree
	//SUM with modifications
	/***********************/
	struct fenwick_tree
	{
		vector<int> t;
		int n;

		fenwick_tree(int nn)
		{
			n = nn;
			t.assign(n, 0);
		}

		fenwick_tree(const vector<int>& a) : fenwick_tree((int)a.size())
		{
			for (unsigned i = 0; i < a.size(); i++)
				inc(i, a[i]);
		}

		int sum(int r)
		{
			int result = 0;
			for (; r >= 0; r = (r & (r + 1)) - 1)
				result += t[r];
			return result;
		}

		void inc(int i, int delta)
		{
			for (; i < n; i = (i | (i + 1)))
				t[i] += delta;
		}

		int sum(int l, int r)
		{
			return sum(r) - sum(l - 1);
		}
	};
	/***********************/

	//http://e-maxx.ru/algo/fenwick_tree
	//MAX with modifications
	/***********************/
	struct fenwick_tree_max
	{
		vector<int> t;
		int n;

		fenwick_tree_max(int nn)
		{
			n = nn;
			t.assign(n, 0);
		}

		fenwick_tree_max(const vector<int>& a) : fenwick_tree_max((int)a.size())
		{
			for (unsigned i = 0; i < a.size(); i++)
				set(i, a[i]);
		}

		int max(int r)
		{
			int result = numeric_limits<int>::min();
			for (; r >= 0; r = (r & (r + 1)) - 1)
				result = std::max(t[r], result);
			return result;
		}

		//NB: we can only INCREASE values! Because max has no inverse function
		//    for min we can only DECREASE values!
		void set(int i, int val)
		{
			for (; i < n; i = (i | (i + 1)))
				t[i] = std::max(t[i], val);
		}
	};
	/***********************/

	TEST(fenwick_sum_tests, simple_test) {
		fenwick_tree t1(10);

		t1.inc(0, 1);
		t1.inc(5, 2);
		t1.inc(9, 3);

		EXPECT_EQ(6, t1.sum(0, 9));
		EXPECT_EQ(1, t1.sum(0, 4));
		EXPECT_EQ(3, t1.sum(0, 5));
		EXPECT_EQ(2, t1.sum(1, 5));
		EXPECT_EQ(3, t1.sum(9, 9));
		EXPECT_EQ(5, t1.sum(5, 9));

		t1.inc(0, -1);
		t1.inc(5, -2);
		t1.inc(9, -3);

		EXPECT_EQ(0, t1.sum(0, 9));
	}

	TEST(fenwick_max_tests, simple_test) {
		fenwick_tree_max t(10);

		EXPECT_EQ(0, t.max(9));
		t.set(5, 3);
		EXPECT_EQ(3, t.max(5));
		EXPECT_EQ(0, t.max(4));
		t.set(5, 4);
		EXPECT_EQ(4, t.max(9));
		t.set(0, 10);
		EXPECT_EQ(10, t.max(0));
		EXPECT_EQ(10, t.max(4));
		EXPECT_EQ(10, t.max(9));
	}

}

