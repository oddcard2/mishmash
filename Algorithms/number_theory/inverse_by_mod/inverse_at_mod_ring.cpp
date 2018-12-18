#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {

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

	template<typename T>
	T get_inv_mod(T a, T m) {
		T x, y;
		T g = gcdex(a, m, x, y);
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

	template<typename T>
	T binpow_mod(T a, int n, int p) {
		T res = 1;
		while (n) {
			if (n & 1) {
				res *= a;
				if (res >= p)
					res %= p;
			}
			a *= a;
			if (a >= p)
				a %= p;
			n >>= 1;
		}
		return res;
	}

	template<typename T>
	T get_inv_prime(T a, T p) {
		return binpow_mod(a, p - 2, p);
	}

	TEST(inverse_at_mod_ring, ferma_test) {
		EXPECT_EQ(9, get_inv_prime(5, 11));
	}

}
