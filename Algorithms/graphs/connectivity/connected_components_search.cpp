#include <gtest/gtest.h>
#include "common.h"


using namespace std;

namespace {

	//Option 1 - for each callback
	/***********************/
	vector<int> used;
	vector<vector<int>> g;

	vector<int> comp;
	function<void(int)> dfs = [&](int v) {
		used[v] = 1;
		comp.push_back(v);
		for (auto u : g[v]) {
			if (used[u])
				continue;

			dfs(u);
		}
	};

	//searches component and process it
	void conn_components_for_each(function<void(vi&)> cb) {
		for (int i = 0; i<sz(used); ++i)
			used[i] = false;
		for (int i = 0; i<sz(used); ++i)
			if (!used[i]) {
				comp.clear();
				dfs(i);

				cb(comp);
			}
	}
	/***********************/

	//Option2: save all components
	/***********************/
	//TODO:
	/***********************/

	TEST(connectivity_tests, connected_components_search) {
		int n = 10;

		//copy these lines
		/***********************/
		g.resize(n);
		used.resize(n);
		/***********************/

		//1 - 0,1,2,3,4
		//2 - 5,6,7,9
		//3 - 8
		g[0] = { 1,2,3 };
		g[1] = { 0,4,2 };
		g[2] = { 0,1 };
		g[3] = { 0 };
		g[4] = { 1 };
		g[5] = { 6,7 };
		g[6] = { 5 };
		g[7] = { 5,9 };
		g[8] = { };
		g[9] = { 7 };

		vector<vi> comps;
		auto cb = [&](vi& v) {
			comps.push_back(v);
		};
		conn_components_for_each(cb);

		ASSERT_EQ(3, sz(comps));

		ASSERT_EQ(5, sz(comps[0]));
		ASSERT_EQ(4, sz(comps[1]));
		ASSERT_EQ(1, sz(comps[2]));

		for (auto& c : comps)
			sort(all(c));

		EXPECT_EQ(vi({ 0,1,2,3,4 }), comps[0]);
		EXPECT_EQ(vi({ 5,6,7,9 }), comps[1]);
		EXPECT_EQ(vi({ 8 }), comps[2]);
	}
}