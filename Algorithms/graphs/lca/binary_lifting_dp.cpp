#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {

	//My binary lifting LCA
	/*******************************/
	int l;
	vector<vector<pair<int,int>>> g;
	vector<int> tin, tout;
	vector<vector<int> > up;
	int timer = 0;

	vector<vector<int>> updp; ///
	vector<int> vh;///

	void dfs(int v, int p = 0) {
		tin[v] = ++timer;

		up[v][0] = p;
		for (int i = 1; i <= l; ++i) {
			up[v][i] = up[up[v][i - 1]][i - 1];
			updp[v][i] = max(updp[v][i - 1], updp[up[v][i - 1]][i - 1]); ///
		}
		for (auto pr : g[v]) {
			int u = pr.first; ///
			if (u == v)
				continue;

			updp[u][0] = pr.second; ///
			vh[u] = vh[v] + 1;///
			dfs(u, v);
		}
		tout[v] = ++timer;
	}

	bool upper(int a, int b) {
		return tin[a] <= tin[b] && tout[a] >= tout[b];
	}

	void init_lca(int n) {
		tin.resize(n), tout.resize(n), up.resize(n);
		vh.resize(n); ///
		updp.resize(n); ///
		l = 1;
		while ((1 << l) <= n)  ++l;
		for (int i = 0; i < n; ++i) {
			up[i].resize(l + 1);
			updp[i].resize(l + 1); ///
		}
		dfs(0);
	}

	int lca(int a, int b) {
		if (upper(a, b))
			return a;
		if (upper(b, a))
			return b;

		int u = a;
		int i = l;
		do {
			if (!upper(up[u][i], b))
				u = up[u][i];
			--i;
		} while (i >= 0);
		return up[u][0];
	}

	///
	int get_best(int v, int span)
	{
		int ret = numeric_limits<int>::min();
		for (int i = l; i >= 0; --i)
		{
			if (span & (1 << i))
			{
				ret = max(ret, updp[v][i]);
				v = up[v][i];
			}
		}
		return ret;
	}
	/*******************************/

	TEST(lca_binary_lifting, simple_test) {
		//				    0	
		//      1		    2		3
		// 4    5    6      7    8      9
		//10 11 12    13				14
		//          15 16 17

		int n = 18;

		g.resize(18);

		g[0] = { {1,1},{2,2},{3,3} };
		g[1] = { {4,1},{5,3},{6,-3} };
		g[2] = { {7,2} };
		g[3] = { {8,5},{9,-1} };
		g[4] = { {10,1}, {11, 3} };
		g[5] = { {12,-3} };
		g[6] = { {13,4} };
		g[9] = { {14,2} };
		g[13] = { {15,-6},{16, 2},{17,6} };

		/*******************************/
		init_lca(n);
		/*******************************/

		EXPECT_EQ(0, lca(0, 0));
		EXPECT_EQ(0, lca(0, 7));
		EXPECT_EQ(0, lca(14, 15));
		EXPECT_EQ(1, lca(10, 12));
		EXPECT_EQ(9, lca(9, 14));
		EXPECT_EQ(13, lca(15, 17));

		int lc = lca(14, 16);
		int mx = max(get_best(14, vh[14] - vh[lc]), get_best(16, vh[16] - vh[lc]));
		EXPECT_EQ(4, mx);
	}
}