#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {
	template<typename T>
	T gcd(T a, T b) {
		while (b) {
			a %= b;
			swap(a, b);
		}
		return a;
	}

	template<typename T>
	T gcdex(T a, T b, T & x, T & y) {
		if (a == 0) {
			x = 0; y = 1;
			return b;
		}
		T x1, y1;
		T d = gcdex(b%a, a, x1, y1);
		x = y1 - (b / a) * x1;
		y = x1;
		return d;
	}


	TEST(gcd_tests, simple_gcd_test) {
		EXPECT_EQ(7, gcd(119, 35));
	}

}

