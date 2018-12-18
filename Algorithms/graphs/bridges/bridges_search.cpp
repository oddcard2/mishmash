#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {
	
	//Copy this lines
	//http://e-maxx.ru/algo/bridge_searching
	/***********************/
	vector<vector<int>> g;
	vector<bool> used;
	vector<int> tin, tout, fup;
	int dfs_timer;

	vector<pair<int, int>> bridges; ///CHANGE

	void dfs(int v, int p = -1) {
		used[v] = true;
		tin[v] = fup[v] = dfs_timer++;
		for (size_t i = 0; i<g[v].size(); ++i) {
			int to = g[v][i];
			if (to == p)  continue;
			if (used[to])
				fup[v] = min(fup[v], tin[to]);
			else {
				dfs(to, v);
				fup[v] = min(fup[v], fup[to]);
				if (fup[to] > tin[v]) {
					bridges.push_back({ v, to }); ///CHANGE
				}
			}
		}
	}

	void find_bridges() {
		int n = (int)g.size();
		dfs_timer = 0;
		for (int i = 0; i<n; ++i)
			used[i] = false;
		for (int i = 0; i<n; ++i)
			if (!used[i])
				dfs(i);
	}
	/***********************/

	TEST(bridges_search_tests, simple_test) {

		int n = 7;
		//Copy this lines
		/***********************/
		g.resize(n);
		used.resize(n);
		tin.resize(n);
		tout.resize(n);
		fup.resize(n);
		/***********************/

		g[0] = { 1,2 };
		g[1] = { 0,3 };
		g[2] = { 0,3 };
		g[3] = { 1,2,4 };
		g[4] = { 3,5,6 };
		g[5] = { 4,6 };
		g[6] = { 4,5 };

		find_bridges();
		ASSERT_EQ(1, bridges.size());
		EXPECT_EQ(make_pair(3, 4), bridges[0]);
	}

}

