#include <gtest/gtest.h>
#include "common.h"


namespace {
	//http://e-maxx.ru/algo/fenwick_tree
	//MAX with modifications
	/***********************/
	struct fenwick_tree_max
	{
		vi t;
		vi ix;
		int n;

		fenwick_tree_max(int nn)
		{
			n = nn;
			t.assign(n, 0);
			ix.assign(n, -1);
		}

		pii max(int r)
		{
			pii res = { -INF, -1 };
			for (; r >= 0; r = (r & (r + 1)) - 1) {
				if (t[r] > res.first)
					res = { t[r], ix[r] };
			}
			return res;
		}

		//NB: we can only INCREASE values! Because max has no inverse function
		//    for min we can only DECREASE values!
		void set(int i, int val, int pos)
		{
			for (; i < n; i = (i | (i + 1))) {
				if (val > t[i]) {
					t[i] = val;
					ix[i] = pos;
				}
			}
		}
	};
	/***********************/

	vi find_lss(const vi& v) {
		int n = sz(v);
		int mxv = -INF;
		forn(i, n) mxv = max(mxv, v[i]);

		int mx = 0;
		//vi dp(mxv+1);
		vi par(n + 1);

		fenwick_tree_max ft(mxv+1);
		forn(i, n + 1) {
			par[i] = -1;
		}

		forn(i, n) {
			int a = v[i];

			//supposed a > 0
			auto prev = ft.max(a - 1);
			ft.set(a, prev.first + 1, i);
			par[i] = prev.second;
		}

		vi ans;
		int pos = ft.max(mxv).second;
		while (pos >= 0) {
			ans.push_back(v[pos]);
			pos = par[pos];
		}

		reverse(all(ans));
		return ans;
	}

	TEST(longset_ss, fenwick_test) {
		vi seq1 = { 1, 7, 3, 5, 2, 9 };
		vi ans1 = find_lss(seq1);
		EXPECT_EQ(vi({ 1,3,5,9 }), ans1);

		vi seq2 = { 5, 6, 1, 2, 5, 6, 10, 1, 2, 3, 4, 5, 7 };
		vi ans2 = find_lss(seq2);
		EXPECT_EQ(vi({ 1,2,3,4,5,7 }), ans2);
	}

}

