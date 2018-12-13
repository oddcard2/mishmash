#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {
#if 0
	int n, l;
	vector < vector<int> > g;
	vector<int> tin, tout;
	int timer;
	vector < vector<int> > up;

	void dfs(int v, int p = 0) {
		tin[v] = ++timer;
		up[v][0] = p;
		for (int i = 1; i <= l; ++i)
			up[v][i] = up[up[v][i - 1]][i - 1];
		for (size_t i = 0; i < g[v].size(); ++i) {
			int to = g[v][i];
			if (to != p)
				dfs(to, v);
		}
		tout[v] = ++timer;
	}

	bool upper(int a, int b) {
		return tin[a] <= tin[b] && tout[a] >= tout[b];
	}

	int lca(int a, int b) {
		if (upper(a, b))  return a;
		if (upper(b, a))  return b;
		for (int i = l; i >= 0; --i)
			if (!upper(up[a][i], b))
				a = up[a][i];
		return up[a][0];
	}
#endif























	//My binary lifting LCA
	int l;
	vector<vector<int> > g;
	vector<int> tin, tout;
	vector<vector<int> > up;
	int timer = 0;

	void dfs(int v, int p = 0) {
		tin[v] = ++timer;

		up[v][0] = p;
		for (int i = 1; i <= l && up[v][i - 1] > 0; ++i) {
			up[v][i] = up[up[v][i - 1]][i - 1];
		}
		for (auto u : g[v]) {
			if (u == v)
				continue;
			dfs(u, v);
		}
		tout[v] = ++timer;
	}

	bool upper(int a, int b) {
		return tin[a] <= tin[b] && tout[a] >= tout[b];
	}

	void init_lca(int n) {
		tin.resize(n), tout.resize(n), up.resize(n);
		l = 1;
		while ((1 << l) <= n)  ++l;
		for (int i = 0; i < n; ++i)  up[i].resize(l + 1);
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

	class lca_binary_lifting : public testing::Test
	{
		virtual void SetUp() {
		}

		virtual void TearDown() {
		}
	};

	TEST_F(lca_binary_lifting, simple_test) {
		//				    0	
		//      1		    2		3
		// 4    5    6      7    8      9
		//10 11 12    13				14
		//          15 16 17

		int n = 18;

		g.resize(18);

		g[0] = { 1,2,3 };
		g[1] = { 4,5,6 };
		g[2] = { 7 };
		g[3] = { 8,9 };
		g[4] = { 10,11 };
		g[5] = { 12 };
		g[6] = { 13 };
		g[9] = { 14 };
		g[13] = { 15,16,17 };

		init_lca(n);

		EXPECT_EQ(0, lca(0, 0));
		EXPECT_EQ(0, lca(0, 7));
		EXPECT_EQ(0, lca(14, 15));
		EXPECT_EQ(1, lca(10, 12));
		EXPECT_EQ(9, lca(9, 14));
		EXPECT_EQ(13, lca(15, 17));
	}
}