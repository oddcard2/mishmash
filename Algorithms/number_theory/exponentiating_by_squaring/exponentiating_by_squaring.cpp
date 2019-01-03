#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {

	template<typename T>
	T binpow(T a, int n) {
		T res = 1;
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
