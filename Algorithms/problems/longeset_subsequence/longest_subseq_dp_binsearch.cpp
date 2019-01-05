#include <gtest/gtest.h>
#include "common.h"


namespace {
	pair<int, int> bin_search(int n, std::function<bool(int)> ok) {
		int l = -1, r = n, mid;
		while (r - l > 1) {
			mid = (l + r) / 2;
			if (ok(mid))
				r = mid;
			else
				l = mid;
		}
		return { l,r };
	}

	vi find_lss(const vi& v) {
		int n = sz(v);
		int mx = 0;
		vi dp(n + 1);
		vi par(n + 1);
		vi ix(n + 1);
		forn(i, n + 1) {
			dp[i] = numeric_limits<int>::max();
			par[i] = -1;
			ix[i] = -1;
		}

		forn(i, n) {
			int a = v[i];

			auto r = bin_search(mx, [&](int pos) { return dp[pos] >= a; });
			int pos = r.first + 1;
			if (dp[pos] > a) {

				ix[pos + 1] = i;
				if (pos > 0)
					par[i] = ix[pos];
				dp[pos] = a;
				mx = max(mx, pos + 1);
			}
		}

		vi ans;
		int pos = ix[mx];
		while (pos >= 0) {
			ans.push_back(v[pos]);
			pos = par[pos];
		}

		reverse(all(ans));
		return ans;
	}

	TEST(longset_ss, dp_binsearch_test) {
		vi seq1 = { 1, 7, 3, 5, 2, 9 };
		vi ans1 = find_lss(seq1);
		EXPECT_EQ(vi({ 1,3,5,9 }), ans1);

		vi seq2 = { 5, 6, 1, 2, 5, 6, 10, 1, 2, 3, 4, 5, 7 };
		vi ans2 = find_lss(seq2);
		EXPECT_EQ(vi({ 1,2,3,4,5,7 }), ans2);
	}

}

