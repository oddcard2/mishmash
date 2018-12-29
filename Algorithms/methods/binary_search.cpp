#include <gtest/gtest.h>
#include <vector>
#include <functional>

using namespace std;

namespace {

	pair<int,int> bin_search(int n, std::function<bool(int)> ok) {
		int l = -1, r = n, mid;
		while (r - l > 1) {
			mid = (l + r) / 2;
			if (ok(mid))
				r = mid;
			else
				l = mid;
		}
		return { l,r };
	}
	
	TEST(binary_search_tests, simple_search_test) {
		vector<int> a1 = { 0,0,0,0,1,1,1 };
		int n = 7;

		//NB: n is value after max check val, for example auto res = bin_search(n+1, check); if we want to check [0,n] segment

		auto res = bin_search(n, [&](int v) { return a1[v]; });

		//left is last pos with false
		EXPECT_EQ(3, res.first);
		//right is first pos with true
		EXPECT_EQ(4, res.second);

		vector<int> a2 = { 0,0,0,0,0,0,0 };
		res = bin_search(n, [&](int v) { return a2[v]; });
		EXPECT_EQ(6, res.first);
		EXPECT_EQ(7, res.second); //=n

		vector<int> a3 = { 1,1,1,1,1,1,1 };
		res = bin_search(n, [&](int v) { return a3[v]; });
		EXPECT_EQ(-1, res.first);
		EXPECT_EQ(0, res.second);

		vector<int> a4 = { 0,0,0,0,0,0,1 };
		res = bin_search(n, [&](int v) { return a4[v]; });
		EXPECT_EQ(5, res.first);
		EXPECT_EQ(6, res.second);
	}

}

