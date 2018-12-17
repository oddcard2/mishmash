#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {

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

	int get_inv_mod(int a, int m) {
		int x, y;
		int g = gcdex(a, m, x, y);
		if (g != 1)
			return -1;
		else {
			x = (x % m + m) % m;
			return x;
		}
	}

	TEST(inverse_at_mod_ring, extended_gcd_test) {
		EXPECT_EQ(3, get_inv_mod(3, 8));

		EXPECT_EQ(9, get_inv_mod(5, 11));
	}

}
