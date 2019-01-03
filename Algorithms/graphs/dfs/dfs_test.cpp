#include <gtest/gtest.h>
#include <vector>
#include <functional>

using namespace std;

namespace {

	//Copy this lines
	/***********************/
	vector<int> used;
	vector<vector<int>> g;

	function<void(int)> dfs = [&](int v) {
		used[v] = 1;
		for (auto u: g[v]) {
			if (used[u])
				continue;

			dfs(u);
		}
	};

	/***********************/

	//Copy this lines
	/***********************/
	vector<int> colors;
	vector<int> tin, tout;
	int depv = 0;///
	vector<int> depth; ///
	int dfs_timer = 0;

	function<void(int)> dfst = [&](int v) {
		colors[v] = 1;
		tin[v] = dfs_timer++;
		depth[v] = depv++; ///
		for (auto u : g[v]) {
			if (colors[u])
				continue;

			dfst(u);
		}
		colors[v] = 2;
		tout[v] = dfs_timer++;
		--depv; ///
	};


	TEST(dfs_test, simple_test) {
		int n = 10;

		//copy these lines
		/***********************/
		g.resize(n);
		used.resize(n);
		depth.resize(n);
		/***********************/

		//				    0	
		//      1		    2		3
		// 4    5    6      7    8      9

		g[0] = { 1,2,3 };
		g[1] = { 0,4,5,6 };
		g[2] = { 0,7 };
		g[3] = { 0,8,9 };
		g[4] = { 1 };
		g[5] = { 1 };
		g[6] = { 1 };
		g[7] = { 2 };
		g[8] = { 3 };
		g[9] = { 3 };

		dfs(0);

		EXPECT_EQ(10, count(begin(used), end(used), 1));
	}

	TEST(dfs_test, time_test) {
		int n = 10;

		g.clear();

		//Copy this lines
		/***********************/
		g.resize(n);
		colors.resize(n);
		tin.resize(n);
		tout.resize(n);
		/***********************/

		g[0] = { 1,2,3 };
		g[1] = { 0,4,5,6 };
		g[2] = { 0,7 };
		g[3] = { 0,8,9 };
		g[4] = { 1 };
		g[5] = { 1 };
		g[6] = { 1 };
		g[7] = { 2 };
		g[8] = { 3 };
		g[9] = { 3 };

		dfst(0);

		EXPECT_EQ(10, count(begin(colors), end(colors), 2));
		EXPECT_EQ(0, tin[0]);
		EXPECT_EQ(1, tin[1]);
		EXPECT_EQ(2, tin[4]);
		EXPECT_EQ(3, tout[4]);
		EXPECT_EQ(4, tin[5]);
		EXPECT_EQ(5, tout[5]);
		EXPECT_EQ(6, tin[6]);
		EXPECT_EQ(7, tout[6]);
		EXPECT_EQ(8, tout[1]);

		EXPECT_EQ(9, tin[2]);
		EXPECT_EQ(10, tin[7]);
		EXPECT_EQ(11, tout[7]);
		EXPECT_EQ(12, tout[2]);
		EXPECT_EQ(13, tin[3]);

		EXPECT_EQ(14, tin[8]);
		EXPECT_EQ(15, tout[8]);

		EXPECT_EQ(16, tin[9]);
		EXPECT_EQ(17, tout[9]);

		EXPECT_EQ(18, tout[3]);

		EXPECT_EQ(19, tout[0]);

	}
}