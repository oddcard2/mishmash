#include <gtest/gtest.h>
#include <set>
#include "common.h"

using namespace std;

namespace {
	//Copy this lines
	//http://e-maxx.ru/algo/segment_tree
	//with modifications
	/***********************/
	struct seg_tree {
		struct node { ///

					  // lets consider frog as segment [n, t]
					  // n - frog number in sorted seq (may be replaced by position)
					  // t - tongue position = p + tongue_len, where p - frog position
					  // node keeps max position where gnat may be eaten
					  // frogs are sorted by its positions
					  // operations:
					  // 1. find most left frog with max >= gnat pos and frog pos >= gnat pos
					  // 2. change t - tongue tip pos
			ll max_rpos = -1; // tongue tip pos
			int n = -1; //number of the frog

						//assigns new value to the segment node
			template<typename T>
			void apply(int tl, int tr, T v) {
				n = tl;
				max_rpos = v;
			}
		};

		node unite(const node &a, const node &b) const {
			node res;
			res.max_rpos = max(a.max_rpos, b.max_rpos);
			return res;
		}

		void push(int v, int tl, int tr) { ///

		}

		void pull(int v) { //combines results from sons to parent
			tree[v] = unite(tree[v * 2], tree[v * 2 + 1]);
		}

		template<typename T>
		void build(const vector<T>& a) {
			n = (int)a.size();
			tree.resize(4 * n);
			build(1, 0, n - 1, a);
		}

		template<typename T>
		void build(int v, int tl, int tr, const vector<T>& a) {
			if (tl == tr)
				tree[v].apply(tl, tr, a[tl]);
			else {
				int tm = (tl + tr) / 2;
				build(v * 2, tl, tm, a);
				build(v * 2 + 1, tm + 1, tr, a);
				pull(v);
			}
		}

		template<typename T>
		node get_first_more(int v, int tl, int tr, int l, int r, T val) {
			if (tl == tr) {
				if (tree[v].max_rpos >= val)
					return tree[v];
				return node{};
			}

			node res{};
			int tm = (tl + tr) / 2;

			if (l <= tm && tree[2 * v].max_rpos >= val) {
				res = get_first_more(2 * v, tl, tm, l, r, val);
			}
			else if (r > tm && tree[2 * v + 1].max_rpos >= val) {
				res = get_first_more(2 * v + 1, tm + 1, tr, l, r, val);
			}
			else {
				return node{};
			}

			return res;
		}

		// returns number of first element in which t >= val 
		template<typename T>
		node get_first_more(int l, int r, T val) {
			return get_first_more(1, 0, n - 1, l, r, val);
		}

		//v - current tree node
		//l,r - required range
		//tl,tr - current tree node range
		template <typename... M>
		void update(int v, int tl, int tr, int l, int r, const M&... d) {
			if (l > r)
				return;
			if (l <= tl && r >= tr)
				tree[v].apply(tl, tr, d...);
			else {
				push(v, tl, tr);
				int tm = (tl + tr) / 2;
				if (l <= tm)
					update(v * 2, tl, tm, l, r, d...);
				if (r > tm)
					update(v * 2 + 1, tm + 1, tr, l, r, d...);
				pull(v);
			}
		}

		template <typename... M>
		void update(int pos, const M&... v) {
			update(1, 0, n - 1, pos, pos, v...);
		}

		int n;
		vector<node> tree;
	};

	/***********************/

	struct frog {
		ll pos;
		ll tpos;
		int n;

		frog() {}
		frog(int n, ll pos, ll tpos) : pos(pos), tpos(tpos), n(n) {}
	};

	struct gnut {
		ll pos;
		ll w;
		int n;

		gnut() {}
		gnut(int n, ll pos, ll w) : pos(pos), w(w), n(n) {}
	};

	bool operator < (const frog& a, const frog& b) {
		return a.pos < b.pos;
	}

	bool operator < (const gnut& a, const gnut& b) {
		if (a.pos == b.pos) {
			return a.n < b.n;
		}
		return a.pos < b.pos;
	}

	void test(vector<frog>& frogs, vector<gnut>& gnuts_list, vector<ll>& cnt_ans, vector<ll>& len_ans) {
		// set for gnuts
		set<gnut> gnuts; //pos, n

		sort(all(frogs));

		vector<ll> lposes;
		vector<ll> rposes;
		for (auto& f : frogs) {
			lposes.push_back(f.pos);
			rposes.push_back(f.tpos);
		}

		seg_tree tree;
		tree.build(rposes);

		vector<ll> cnt(lposes.size());

		for (auto& g : gnuts_list) {
			auto last_f = upper_bound(all(lposes), g.pos);
			if (g.pos < lposes[0]) {
				continue;
			}
			auto node = tree.get_first_more(0, (int)distance(begin(lposes), last_f) - 1, g.pos);
			if (node.max_rpos < 0) {
				gnuts.insert(g);
				continue;
			}

			// eats all gnats
			// cout << "Frog #" << node.n << " eat #" << g.n << " gnat" << endl;
			ll pos = node.max_rpos + g.w;
			cnt[node.n]++;
			while (true) {
				auto gnats_start = gnuts.lower_bound(gnut{ -1, lposes[node.n], 0 });
				auto gnats_end = gnuts.upper_bound(gnut{ INF, pos, 0 });
				if (gnats_end == gnats_start)
					break;
				for (auto i = gnats_start; i != gnats_end; ++i) {
					pos += i->w;
					cnt[node.n]++;
					// cout << "Frog #" << node.n << " eat #" << i->n << " gnat" << endl;
				}
				gnuts.erase(gnats_start, gnats_end);
			}

			rposes[node.n] = pos;
			tree.update(node.n, pos);
		}

		cnt_ans.resize(lposes.size());
		len_ans.resize(lposes.size());
		
		for (auto i = 0; i < lposes.size(); ++i) {
			cnt_ans[frogs[i].n] = cnt[i];
			len_ans[frogs[i].n] = rposes[i] - frogs[i].pos;
		}
	}

	TEST(emaxx_segment_tree_frogs, test1) {
		// sort frogs by its pos

		vector<frog> frogs;
		frogs.push_back(frog{ 0, 10, 10 + 2 });
		frogs.push_back(frog{ 1, 15, 15+0 });
		frogs.push_back(frog{ 2, 6, 6+1 });
		frogs.push_back(frog{ 3, 0, 0 + 1 });

		vector<gnut> gnuts_list;
		gnuts_list.push_back(gnut(0, 110, 10));
		gnuts_list.push_back(gnut(1, 1, 1));
		gnuts_list.push_back(gnut(2, 6, 0));
		gnuts_list.push_back(gnut(3, 15, 10));
		gnuts_list.push_back(gnut(4, 14, 100));
		gnuts_list.push_back(gnut(5, 12, 2));

		vector<ll> cnt_ans, len_ans;

		test(frogs, gnuts_list, cnt_ans, len_ans);

		EXPECT_EQ(3, cnt_ans[0]);
		EXPECT_EQ(1, cnt_ans[1]);
		EXPECT_EQ(1, cnt_ans[2]);
		EXPECT_EQ(1, cnt_ans[3]);

		EXPECT_EQ(114, len_ans[0]);
		EXPECT_EQ(10, len_ans[1]);
		EXPECT_EQ(1, len_ans[2]);
		EXPECT_EQ(2, len_ans[3]);
	}

	TEST(emaxx_segment_tree_frogs, test2) {
		// sort frogs by its pos

		vector<frog> frogs;
		frogs.push_back(frog{ 0, 10, 10 + 2 });

		vector<gnut> gnuts_list;
		gnuts_list.push_back(gnut(0, 20, 2));
		gnuts_list.push_back(gnut(1, 12, 1));

		vector<ll> cnt_ans, len_ans;

		test(frogs, gnuts_list, cnt_ans, len_ans);

		EXPECT_EQ(1, cnt_ans[0]);

		EXPECT_EQ(3, len_ans[0]);
	}

}