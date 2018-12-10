#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include <structures/dsu/dsu.h>

using namespace std;

typedef long long ll;

namespace {
	int n;
	vector<vector<int>> g;
	vector<vector<int>> w;

	class kruskal_mst_test : public testing::Test
	{
		virtual void SetUp() {
		}

		virtual void TearDown() {
		}
	};

	vector<tuple<int,int, ll>> edges;
	vector<pair<int, int>> ans;

	ll mst_kruskal() {
		ll sum = 0;
		//sort edges
		sort(begin(edges), end(edges), [](const tuple<int, int, ll>& a, const tuple<int, int, ll> & b) { return get<2>(a) < get<2>(b); });

		dsu d(n);
		for (int i = 0; i < n; i++)
		{
			d.make(i);
		}

		for (int i = 0; i < edges.size(); i++) {
			int u, v;
			ll w;
			tie(u, v, w) = edges[i];

			if (d.find(u) != d.find(v)) {
				d.unite(u, v);
				ans.push_back({ u, v });
				sum += w;
			}
		}
		return sum;
	}


	TEST_F(kruskal_mst_test, simple_test) {
		//full graph
		n = 4;
		g.resize(4);
		w.resize(4);

		g[0] = { 1,2,3 };
		g[1] = { 0,2,3 };
		g[2] = { 0,1,3 };
		g[3] = { 0,1,2 };

		w[0] = { -1,2,5 };
		w[1] = { -1,2,-2 };
		w[2] = { 2,2,0 };
		w[3] = { 5,-2,0 };

		//creates vector of edges
		int v = 0;
		for (auto vec: g)
		{
			for (int i = 0; i < (int)g[v].size(); ++i) {
				int u = g[v][i];
				edges.push_back({ v, u, w[v][i] });
			}
			v++;
		}

		ll sum = mst_kruskal();

		EXPECT_EQ(3, ans.size());
		EXPECT_EQ(-3, sum);
	}

}