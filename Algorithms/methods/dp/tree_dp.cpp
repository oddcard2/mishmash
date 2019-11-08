#include <gtest/gtest.h>
#include "common.h"

using namespace std;

// https://codeforces.com/contest/1249/problem/F
namespace {
	int n, k;
	vector<int> a;
	vector<int> used;
	vector<vector<int>> g;

	int dp[210][210] = { 0 };

	function<void(int, int)> dfs = [&](int v, int p) {
		used[v] = 1;

		for (auto u : g[v]) {
			if (used[u])
				continue;

			dfs(u, v);
		}

		for (int d = k; d >= 1; d--) {
			int best = 0;
			for (int j = 0; j < sz(g[v]); j++) {
				if (g[v][j] == p)
					continue;

				int val = dp[g[v][j]][d - 1];
				for (int h = 0; h < sz(g[v]); h++) {
					if (j == h || g[v][h] == p) continue;

					// there is not evident thing, but we have 2 options (k/2 >= d) and (k/2 < d)
					// so we should avoid that 2 branches have vertecies with d1,d2, d1+d2<k
					// in first case if we take vertex with depth d in selected branch, other branches will depth (k-(d+1)) = (k/2+k/2-(d+1)) >= k/2
					// in second case we have depth on all branches d > k/2 and all is ok.
					int dep = max(d - 1, k - (d + 1)); 
					val += dp[g[v][h]][dep];
				}
				if (val > best) {
					best = val;
				}
			}
			dp[v][d] = max(best, dp[v][d + 1]);
		}
		if (v == 0)
			v = 0;
		dp[v][0] = a[v];
		for (int j = 0; j < sz(g[v]); j++) {
			if (g[v][j] == p)
				continue;

			dp[v][0] += dp[g[v][j]][k - 1];
		}
		dp[v][0] = max(dp[v][0], dp[v][1]);
	};

	TEST(tree_dp, cf595_e_test) {
		/*
		5 1
		1 2 3 4 5
		1 2
		2 3
		3 4
		3 5
		*/
		n = 5;
		k = 1;

		k++;
		a.resize(n);
		used.resize(n);
		g.resize(n);

		forn(i, n) {
			a[i] = i+1; // 1 2 3 4 5
		}

		g[0].push_back(1);
		g[1].push_back(0);

		g[1].push_back(2);
		g[2].push_back(1);

		g[2].push_back(3);
		g[3].push_back(2);

		g[2].push_back(4);
		g[4].push_back(2);

		dfs(0, -1);

		EXPECT_EQ(11, dp[0][0]);
	}
}