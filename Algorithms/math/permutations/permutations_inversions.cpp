#include <gtest/gtest.h>
#include <common.h>

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

	int count_inversions(const vi& p) {
		fenwick_tree t(sz(p)+1);

		int res = 0;
		forn(i, sz(p)) {
			res += t.sum(p[i], sz(p));
			t.inc(p[i], 1);
		}
		return res;
	}
	
	TEST(perm_tests, inv_count_test) {
		vi perm1 = { 0,2,3,1,5,4 }; //index is from 1!
		int cnt1 = count_inversions(perm1);
		EXPECT_EQ(3, cnt1);

		vi perm2 = { 0,1,2,3,4,5 }; //index is from 1!
		int cnt2 = count_inversions(perm2);
		EXPECT_EQ(0, cnt2);

		vi perm3 = { 0,5,4,3,2,1 }; //index is from 1!
		int cnt3 = count_inversions(perm3);
		EXPECT_EQ(1+2+3+4, cnt3);
	}

}

