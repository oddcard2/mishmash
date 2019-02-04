#include <gtest/gtest.h>
#include "common.h"

using namespace std;

namespace {

	//http://e-maxx.ru/algo/fenwick_tree
	//MIN with index
	/***********************/
	struct fenwick_tree_min
	{
		struct node {
			typedef ll T;
			T v = INF64;
			int idx;

			inline T get() const {
				return v;
			}
		};
		inline node build_node(node::T val, int idx) {
			return node{ val, idx };
		}

		vector<node> t;
		int n;

		fenwick_tree_min(int nn)
		{
			n = nn;
			t.assign(n, {});
		}

		fenwick_tree_min(const vector<int>& a) : fenwick_tree_min((int)a.size())
		{
			for (unsigned i = 0; i < a.size(); i++)
				set(i, a[i]);
		}

		//i is range [0,n-1], calc for [0,r]
		node get(int r)
		{
			node result;
			for (; r >= 0; r = (r & (r + 1)) - 1) {
				if (t[r].get() < result.get()) {
					result = t[r];
				}
			}
			return result;
		}

		//NB: we can only INCREASE values! Because max has no inverse function
		//    for min we can only DECREASE values!
		//i is range [0,n-1]
		void set(int i, node::T val)
		{
			int idx = i;
			for (; i < n; i = (i | (i + 1))) {
				if (t[i].get() > val) { //set min
					t[i] = build_node(val, idx);
				}
			}
		}
	};
	/***********************/

	//gets min elem and its index
	//values may only be decreased
	TEST(fenwick_tree_tests, min_idx_test) {
		fenwick_tree_min t(10);

		t.set(5, 10);
		auto r = t.get(9);
		EXPECT_EQ(5, r.idx);
		EXPECT_EQ(10, r.v);

		r = t.get(5);
		EXPECT_EQ(5, r.idx);
		EXPECT_EQ(10, r.v);

		t.set(8, 9);
		r = t.get(8);
		EXPECT_EQ(8, r.idx);
		EXPECT_EQ(9, r.v);

		r = t.get(5);
		EXPECT_EQ(5, r.idx);
		EXPECT_EQ(10, r.v);

		t.set(5, 7);
		r = t.get(9);
		EXPECT_EQ(5, r.idx);
		EXPECT_EQ(7, r.v);

		r = t.get(5);
		EXPECT_EQ(5, r.idx);
		EXPECT_EQ(7, r.v);

		t.set(0, 0);
		r = t.get(9);
		EXPECT_EQ(0, r.idx);
		EXPECT_EQ(0, r.v);

		r = t.get(0);
		EXPECT_EQ(0, r.idx);
		EXPECT_EQ(0, r.v);
	}
}