#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {
	int gcd(int a, int b) {
		while (b) {
			a %= b;
			swap(a, b);
		}
		return a;
	}

	int gcdex(int a, int b, int & x, int & y) {
		if (a == 0) {
			x = 0; y = 1;
			return b;
		}
		int x1, y1;
		int d = gcdex(b%a, a, x1, y1);
		x = y1 - (b / a) * x1;
		y = x1;
		return d;
	}


	TEST(gcd_tests, simple_gcd_test) {
		EXPECT_EQ(7, gcd(119, 35));
	}

}

