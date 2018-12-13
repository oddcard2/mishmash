#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include <queue>
#include <structures/dsu/dsu.h>

using namespace std;

typedef long long ll;

namespace {
	int n;
	vector<vector<pair<int, int>>> g;

	class prim_mst_test : public testing::Test
	{
		virtual void SetUp() {
		}

		virtual void TearDown() {
		}
	};

	vector<int> sel;

	ll mst_prim(int root) {
		ll sum = 0;

		vector<int> mine(n, numeric_limits<int>::max());
		vector<int> used(n);
		sel[root] = root;
		mine[root] = 0;

		//weight is first, vertex number is second
		set<pair<int, int> > q;
		q.insert({ 0,root });

		for (int i = 0; i < n; i++)
		{
			auto v = q.begin()->second;
			q.erase({ mine[v], v });

			used[v] = 1;
			sum += mine[v];

			for (auto u: g[v]) {
				int to = u.first;
				if (used[to])
					continue;

				int cost = u.second;
				if (cost < mine[to]) {
					q.erase({ mine[to], to });

					mine[to] = cost;
					sel[to] = v;

					q.insert({cost, to });
				}
			}
		}

		return sum;
	}


	TEST_F(prim_mst_test, simple_test) {
		//full graph
		n = 4;
		g.resize(4);

		g[0] = { {1,-1},{2,2},{3,5} };
		g[1] = { {0,-1},{2,2},{3,-2} };
		g[2] = { {0,2},{1,2},{3,0} };
		g[3] = { {0,5},{1,-2},{2,0} };

		sel.resize(4);

		ll sum = mst_prim(0);

		EXPECT_EQ(0, sel[0]);
		EXPECT_EQ(0, sel[1]);
		EXPECT_EQ(3, sel[2]);
		EXPECT_EQ(1, sel[3]);
		EXPECT_EQ(-3, sum);
	}

}