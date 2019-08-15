#include <gtest/gtest.h>
#include "common.h"

using namespace std;

// Idea: we have array with 1 and 0.
// Operations: 
// 1. find most right range of 0's with specific len, for example for array 1100100001 we have gap with len=3 in pos 5, len=2 in pos 2 (from zero)
// 2. Fill specific gap by 1's
// 3. Fill specific range by 0's

namespace {
	
	/***********************/
	struct seg_tree {
		struct node { ///
			int max_gap; // max gap in segment, 01100001000 - max_gap=4
			int left_gap; // gap len from left, 01100001000 - left_gap=3
			int right_gap; // gap len from right, 01100001000 - right_gap=1
			bool filled_zeros;

			//assigns new value to the segment node
			void apply(int tl, int tr, int v) {
				max_gap = (tr - tl + 1)*(v==0);
				left_gap = max_gap;
				right_gap = max_gap;
				filled_zeros = (v == 0);
			}
		};

		node unite(const node &a, const node &b) const {
			node res;
			int max_inside = max(a.max_gap, b.max_gap);
			int between_gap = a.right_gap + b.left_gap;
			res.max_gap = max(max_inside, between_gap);

			res.left_gap = a.left_gap;
			if (a.filled_zeros) // left side is zeros 
				res.left_gap += b.left_gap;

			res.right_gap = b.right_gap;
			if (b.filled_zeros)
				res.right_gap += a.right_gap;

			res.filled_zeros = a.filled_zeros && b.filled_zeros;
			return res;
		}

		void push(int v, int tl, int tr) {

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

		pii get(int v, int tl, int tr, int gap_len) {
			if (tree[v].max_gap < gap_len)
				return mp(-1, -1);

			int tm = (tl + tr) / 2;
			if (tree[2 * v].max_gap >= gap_len) {
				return get(2 * v, tl, tm, gap_len);
			}
			//we can't go to right anymore, try to use current right part
			if (tree[2 * v].right_gap + tree[2 * v + 1].left_gap >= gap_len) {
				int start_pos = tm - tree[2 * v].right_gap + 1;
				return mp(start_pos, start_pos + gap_len);
			}
			if (tree[2 * v + 1].max_gap >= gap_len) {
				return get(2 * v + 1, tm + 1, tr, gap_len);
			}

			assert(0);
			return mp(-1, -1);
		}

		void set(int v, int tl, int tr, int l, int r, int val) {
			if (l > r)
				return;

			if (l <= tl && r >= tr) {
				tree[v].apply(tl, tr, val);
			}
			else {
				int tm = (tl + tr) / 2;
				if (l <= tm)
					set(v * 2, tl, tm, l, r, val);
				if (r > tm)
					set(v * 2 + 1, tm + 1, tr, l, r, val);
				pull(v);
			}
		}

		pii find_most_right_gap(int gap_len) {
			return get(1, 0, n - 1, gap_len);
		}

		void set_val(int l, int r, int val) {
			set(1, 0, n - 1, l, r, val);
		}

		void set_val(int pos, int val) {
			set_val(pos, pos, val);
		}

		int n;
		vector<node> tree;
	};

	/***********************/

	TEST(emaxx_segment_tree_tests, sum_test) {

		vector<int> a = { 1,0,0,1,1,0,0,0,1,0,0,0,0 };
		/***********************/
		seg_tree t;
		t.build(a);

		auto p = t.find_most_right_gap(2);
		EXPECT_EQ(1, p.first);
		EXPECT_EQ(3, p.second);

		p = t.find_most_right_gap(3);
		EXPECT_EQ(5, p.first);
		EXPECT_EQ(8, p.second);

		p = t.find_most_right_gap(4);
		EXPECT_EQ(9, p.first);
		EXPECT_EQ(13, p.second);

		p = t.find_most_right_gap(1);
		EXPECT_EQ(1, p.first);
		EXPECT_EQ(2, p.second);

		p = t.find_most_right_gap(5);
		EXPECT_EQ(-1, p.first);
		EXPECT_EQ(-1, p.second);

		t.set_val(3, 5, 0);

		p = t.find_most_right_gap(7);
		EXPECT_EQ(1, p.first);
		EXPECT_EQ(8, p.second);

		t.set_val(2, 1);
		p = t.find_most_right_gap(7);
		EXPECT_EQ(-1, p.first);
		EXPECT_EQ(-1, p.second);

		p = t.find_most_right_gap(5);
		EXPECT_EQ(3, p.first);
		EXPECT_EQ(8, p.second);
		/***********************/
	}

}