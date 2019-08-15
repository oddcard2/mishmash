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
		vector<ll> lens;

		struct node { ///

			// lets consider frog as segment [n, t]
			// n - frog number in sorted seq (may be replaced by position)
			// t - tongue position = p + tongue_len, where p - frog position
			// so set is sorted by t, then by n, so if t is the same, first after gnat will be most left frog
			set<pli> f;
			
			//assigns new value to the segment node
			template<typename T>
			void apply(int tl, int tr, T v) {
				f.erase(mp(tl, lens[tl]));
				lens[tl] = v;
				f.insert(mp(tl, lens[tl]));
			}
		};

		node unite(const node &a, const node &b) const {
			node res;

			set_union(std::begin(a.f), std::end(a.f),
				std::begin(b.f), std::end(b.f),
				std::inserter(res.f, std::begin(res.f)));

			return res;
		}

		void push(int v, int tl, int tr) { ///
			
		}

		void pull(int v) { //combines results from sons to parent
			tree[v] = unite(tree[v * 2], tree[v * 2 + 1]);
		}

		template<typename T>
		void build(const vector<T>& a) {
			tl = a;

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

		node get_first_more(int v, int tl, int tr, int l, int r) {
			if (l <= tl && r >= tr) {
				return tree[v];
			}
			push(v, tl, tr);
			node res{};
			int tm = (tl + tr) / 2;

			if (r <= tm) {
				res = get_first_more(2 * v, tl, tm, l, r);
			}
			else {
				if (l > tm) {
					res = get_first_more(2 * v + 1, tm + 1, tr, l, r);
				}
				else {
					res = unite(get_first_more(2 * v, tl, tm, l, r), get_first_more(2 * v + 1, tm + 1, tr, l, r));
				}
			}
			pull(v);
			return res;
		}

		// returns number of first element in which t >= val 
		template<typename T>
		int get_first_more(int l, int r, T val) {
			return get(1, 0, n - 1, l, r);
		}

		node get_first_more(int pos) {
			return get_first_more(1, 0, n - 1, pos, pos);
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
		void update_range(int l, int r, const M&... v) {
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

	TEST(emaxx_segment_tree_set, bound_search_test) {

		
	}

}