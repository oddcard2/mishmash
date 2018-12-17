#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {

	int binpow(int a, int n) {
		int res = 1;
		while (n) {
			if (n & 1)
				res *= a;
			a *= a;
			n >>= 1;
		}
		return res;
	}

	TEST(exponentiating_by_squaring, simple_test) {
		EXPECT_EQ(1977326743, binpow(7, 11));
	}

}
