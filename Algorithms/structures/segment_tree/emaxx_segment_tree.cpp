#include <gtest/gtest.h>
#include <vector>
#include <functional>
#include <bitset>

using namespace std;

namespace {
	
	//Copy this lines
	//http://e-maxx.ru/algo/segment_tree
	//with modifications
	/***********************/
	struct seg_tree {
		struct node { ///
			int lazy = 0;
			int color;
			
			uint64_t mask;

			//assigns new value to the segment node
			void apply(int col) {
				lazy = 1;
				color = col;
				mask = (1ull << col);
			}
		};

		node unite(const node &a, const node &b) const {
			node res;
			res.mask = a.mask | b.mask;
			return res;
		}

		void push(int v) { ///
			if (tree[v].lazy) {
				tree[2 * v].apply(tree[v].color);
				tree[2 * v + 1].apply(tree[v].color);
				tree[v].lazy = 0;
			}
		}

		void pull(int v) { //combines results from sons to parent
			tree[v].mask = tree[v * 2].mask |  tree[v * 2 + 1].mask;
		}

		template<typename T>
		void build(const vector<T>& a) {
			n = (int)a.size();
			tree.resize(4*n);
			build(1, 0, n - 1, a);
		}

		template<typename T>
		void build(int v, int tl, int tr, const vector<T>& a) {
			if (tl == tr)
				tree[v].apply(a[tl]);
			else {
				int tm = (tl + tr) / 2;
				build(v * 2, tl, tm, a);
				build(v * 2 + 1, tm + 1, tr, a);
				pull(v);
			}
		}

		node get(int v, int tl, int tr, int l, int r) {
			if (l <= tl && r >= tr) {
				return tree[v];
			}
			push(v);
			node res{};
			int tm = (tl + tr) / 2;

			if (r <= tm) {
				res = get(2*v, tl, tm, l, r);
			}
			else {
				if (l > tm) {
					res = get(2*v+1, tm+1, tr, l, r);
				}
				else {
					res = unite(get(2*v, tl, tm, l, r), get(2*v+1, tm + 1, tr, l, r));
				}
			}
			pull(v);
			return res;
		}


		node get(int l, int r) {
			return get(1, 0, n - 1, l, r);
		}

		node get(int pos) {
			return get(1, 0, n - 1, pos, pos);
		}

		//v - current tree node
		//l,r - required range
		//tl,tr - current tree node range
		template <typename... M>
		void update(int v, int tl, int tr, int l, int r, const M&... d) {
			if (l > r)
				return;
			if (l <= tl && r >= tr)
				tree[v].apply(d...);
			else {
				push(v);
				int tm = (tl + tr) / 2;
				if (l <= tm)
					update(v * 2,		tl,		tm, l, r, d...);
				if (r > tm)
					update(v * 2 + 1,	tm + 1, tr, l, r, d...);
				pull(v);
			}
		}

		template <typename... M>
		void update(int l, int r, const M&... v) {
			update(1, 0, n - 1, l, r, v...);
		}

		template <typename... M>
		void update(int pos, const M&... v) {
			update(1, 0, n - 1, pos, pos, v...);
		}

		int n;
		vector<node> tree;
	};

	/***********************/
	struct range { ///
		int s;
		int e;
	};
	vector<range> vertex_range; ///

	vector<int> used;
	vector<vector<int>> g;
	int timer = -1;

	function<void(int)> dfs = [&](int v) {
		used[v] = 1;

		vertex_range[v].s = ++timer;

		for (auto u : g[v]) {
			if (used[u])
				continue;

			dfs(u);
		}
		vertex_range[v].e = timer;
	};

	int bit_count(uint64_t v) {
		return std::bitset<64>(v).count();
	}

	TEST(emaxx_segment_tree_tests, new_year_problem_test) {
		//https://codeforces.com/contest/620/problem/E


		int n = 23;

		vector<int> colors = { 1, 2, 2, 6, 5, 3, 2, 1, 1, 1, 2, 4, 5, 3, 4, 4, 3, 3, 3, 3, 3, 4, 6 };

		/***********************/
		g.resize(n);
		vertex_range.resize(n);
		used.resize(n);
		/***********************/

		g[0] = { 1,2,3 };
		g[1] = { 4,5 };
		g[2] = { 6,7 };
		g[3] = { 8,9,10 };
		g[4] = {};

		g[5] = { 11,12 };
		g[6] = { 13,14,15 };
		g[7] = { 16,17 };
		g[8] = {};
		g[9] = { 18,19,20 };

		g[10] = { 21,22 };

		dfs(0);

		vector<int> colors_tree(n);

		for (int i = 0; i < n; i++)
		{
			colors_tree[vertex_range[i].s] = colors[i];
		}

		/***********************/
		seg_tree t;
		t.build(colors_tree);

		/***********************/

		seg_tree::node q = t.get(vertex_range[0].s, vertex_range[0].e);
		EXPECT_EQ(6, bit_count(q.mask));

		q = t.get(vertex_range[4].s, vertex_range[4].e);
		EXPECT_EQ(1, bit_count(q.mask));

		q = t.get(vertex_range[5].s, vertex_range[5].e);
		EXPECT_EQ(3, bit_count(q.mask));

		q = t.get(vertex_range[6].s, vertex_range[6].e);
		EXPECT_EQ(3, bit_count(q.mask));

		q = t.get(vertex_range[7].s, vertex_range[7].e);
		EXPECT_EQ(2, bit_count(q.mask));

		q = t.get(vertex_range[8].s, vertex_range[8].e);
		EXPECT_EQ(1, bit_count(q.mask));

		q = t.get(vertex_range[9].s, vertex_range[9].e);
		EXPECT_EQ(2, bit_count(q.mask));

		q = t.get(vertex_range[10].s, vertex_range[10].e);
		EXPECT_EQ(3, bit_count(q.mask));

		q = t.get(vertex_range[3].s, vertex_range[3].e);
		EXPECT_EQ(5, bit_count(q.mask));

		t.update(vertex_range[11].s, vertex_range[11].e, 1);
		q = t.get(vertex_range[5].s, vertex_range[5].e);
		EXPECT_EQ(3, bit_count(q.mask));

		t.update(vertex_range[12].s, vertex_range[12].e, 1);
		t.update(vertex_range[13].s, vertex_range[13].e, 1);

		t.update(vertex_range[14].s, vertex_range[14].e, 1);
		t.update(vertex_range[15].s, vertex_range[15].e, 1);
		t.update(vertex_range[16].s, vertex_range[16].e, 1);

		t.update(vertex_range[17].s, vertex_range[17].e, 1);
		t.update(vertex_range[18].s, vertex_range[18].e, 1);
		t.update(vertex_range[19].s, vertex_range[19].e, 1);

		t.update(vertex_range[20].s, vertex_range[20].e, 1);
		t.update(vertex_range[21].s, vertex_range[21].e, 1);
		t.update(vertex_range[22].s, vertex_range[22].e, 1);

		//for (int i = 0; i < n; ++i) {
		//	cout << t.get(i).color << " ";
		//}

		q = t.get(vertex_range[0].s, vertex_range[0].e);
		EXPECT_EQ(5, bit_count(q.mask));

		q = t.get(vertex_range[4].s, vertex_range[4].e);
		EXPECT_EQ(1, bit_count(q.mask));

		q = t.get(vertex_range[5].s, vertex_range[5].e);
		EXPECT_EQ(2, bit_count(q.mask));

		q = t.get(vertex_range[6].s, vertex_range[6].e);
		EXPECT_EQ(2, bit_count(q.mask));

		q = t.get(vertex_range[7].s, vertex_range[7].e);
		EXPECT_EQ(1, bit_count(q.mask));

		q = t.get(vertex_range[8].s, vertex_range[8].e);
		EXPECT_EQ(1, bit_count(q.mask));

		q = t.get(vertex_range[9].s, vertex_range[9].e);
		EXPECT_EQ(1, bit_count(q.mask));

		q = t.get(vertex_range[10].s, vertex_range[10].e);
		EXPECT_EQ(2, bit_count(q.mask));

		q = t.get(vertex_range[3].s, vertex_range[3].e);
		EXPECT_EQ(3, bit_count(q.mask));
	}

}