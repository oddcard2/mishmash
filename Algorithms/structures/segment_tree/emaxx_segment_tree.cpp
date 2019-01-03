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
			int val;
			int ad = 0;

			//assigns new value to the segment node
			void apply(int tl, int tr, int v) {
				ad += v;
				val += v * (tr - tl + 1);
			}
		};

		node unite(const node &a, const node &b) const {
			node res;
			res.val = a.val + b.val;
			return res;
		}

		void push(int v, int tl, int tr) { ///
			if (tree[v].ad != 0) {
				int tm = (tl + tr) / 2;
				tree[v * 2].apply(tl, tm, tree[v].ad);
				tree[v * 2 + 1].apply(tm + 1, tr, tree[v].ad);
				tree[v].ad = 0;
			}
		}

		void pull(int v) { //combines results from sons to parent
			tree[v] = unite(tree[v * 2], tree[v * 2 + 1]);
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
				tree[v].apply(tl,tr,a[tl]);
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
			push(v,tl,tr);
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
				tree[v].apply(tl,tr,d...);
			else {
				push(v,tl,tr);
				int tm = (tl + tr) / 2;
				if (l <= tm)
					update(v * 2,		tl,		tm, l, r, d...);
				if (r > tm)
					update(v * 2 + 1,	tm + 1, tr, l, r, d...);
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

	TEST(emaxx_segment_tree_tests, sum_test) {

		vector<int> a = { 1,0,-5,3,2 };
		/***********************/
		seg_tree t;
		t.build(a);

		/***********************/

		EXPECT_EQ(1, t.get(0, 4).val);
		EXPECT_EQ(0, t.get(1, 4).val);
		EXPECT_EQ(-5, t.get(1, 2).val);
		EXPECT_EQ(3, t.get(3, 3).val);

		t.update(1, 5); //1,5,-5,3,2

		EXPECT_EQ(1, t.get(0).val);
		EXPECT_EQ(5, t.get(1).val);
		EXPECT_EQ(-5, t.get(2).val);
		EXPECT_EQ(3, t.get(3).val);
		EXPECT_EQ(2, t.get(4).val);

		EXPECT_EQ(6, t.get(0, 4).val);
		EXPECT_EQ(6, t.get(0, 1).val);

		t.update_range(0, 2,-1); //0,4,-6,3,2
		EXPECT_EQ(3, t.get(0, 4).val);
		EXPECT_EQ(5, t.get(3, 4).val);

		EXPECT_EQ(0, t.get(0).val);
		EXPECT_EQ(4, t.get(1).val);
		EXPECT_EQ(-6, t.get(2).val);
		EXPECT_EQ(3, t.get(3).val);
		EXPECT_EQ(2, t.get(4).val);
	}

}