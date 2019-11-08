#include <gtest/gtest.h>
#include "common.h"

using namespace std;

struct rect {
	int n;
	int x1;
	int y1;
	int x2;
	int y2;
};

struct node {
	node() : r(-1), l(-1) {}
	int r, l;
	int c;
	vector<pair<int, int>> s;
};

vector<rect> rects;
vector<node> nodes;
vector<bool> used;


int get_mid(vector<int>& r) {
	auto res = make_pair(numeric_limits<int>::max(), 0);
	for (auto v : r) {
		if (rects[v].x1 < res.first) {
			res.first = rects[v].x1;
		}
		if (rects[v].x2 > res.second) {
			res.second = rects[v].x2;
		}
	}
	return res.first + (res.second - res.first) / 2;
}

void build(int n, vector<int>& r) {
	vector<int> lv;
	vector<int> rv;

	for (auto v : r) {
		if (rects[v].x2 < nodes[n].c) {
			lv.push_back(v);
		}
		else if (rects[v].x1 > nodes[n].c) {
			rv.push_back(v);
		}
		else {
			nodes[n].s.push_back({ rects[v].y1, v });
		}
	}

	if (!lv.empty()) {
		int len = int(nodes.size());
		nodes.resize(len + 1);
		nodes[len].c = get_mid(lv);
		nodes[n].l = len;
		build(len, lv);
	}
	if (!rv.empty()) {
		int len = int(nodes.size());
		nodes.resize(len + 1);
		nodes[len].c = get_mid(rv);
		nodes[n].r = len;
		build(len, rv);
	}
}

int get_y(int n, int x, int y) {
	auto s = nodes[n].s;
	if (s.empty()) {
		return -1;
	}
	auto res = upper_bound(begin(s), end(s), make_pair(y, numeric_limits<int>::max()));
	if (res == begin(s))
		return -1;

	--res;
	if (used[res->second])
		return -1;

	auto r = rects[res->second];
	if (y <= r.y2 && x >= r.x1 && x <= r.x2)
		return res->second;

	return -1;
}

int find_rect(int n, int x, int y) {
	int res = get_y(n, x, y);
	if (res != -1) {
		used[res] = 1;
		return res + 1;
	}

	if (x < nodes[n].c && nodes[n].l != -1)
		return find_rect(nodes[n].l, x, y);
	if (x > nodes[n].c && nodes[n].r != -1)
		return find_rect(nodes[n].r, x, y);
	return -1;
}


namespace {

	TEST(interval_tree_rect_finder, simple_test) {
		int n = 5;

		vector<int> nums(n);
		rects.resize(n);
		for (int i = 0; i < n; i++)
		{
			nums[i] = i;
		}
		rects[0] = rect{ 0, 0,0,10,10 };
		rects[1] = rect{ 0, 5,15,6,20 };
		rects[2] = rect{ 0, 30,10,40,11 };
		rects[3] = rect{ 0, 0,50,10,60 };
		rects[4] = rect{ 0, 100,100,101,101 };

		sort(begin(nums), end(nums), [&](int a, int b) { return rects[a].y1 < rects[b].y1; });

		used.resize(n);
		nodes.reserve(10 * n);
		nodes.resize(1);
		nodes[0].c = get_mid(nums);
		build(0, nums);

		EXPECT_EQ(1, find_rect(0, 1, 1));
		EXPECT_EQ(-1, find_rect(0, 10, 11));
		EXPECT_EQ(2, find_rect(0, 6, 15));
		EXPECT_EQ(-1, find_rect(0, 6, 15)); // again
		EXPECT_EQ(3, find_rect(0, 35, 10));
		EXPECT_EQ(4, find_rect(0, 5, 50));
		EXPECT_EQ(5, find_rect(0, 100, 100));
	}
}