#include <gtest/gtest.h>
#include <vector>
#include "common.h"

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

	pll mul2(pll a, pll b) {
		ll na = (a.first*b.first) % mod;
		ll nb = add((a.first*b.second) % mod, a.second);
		return { na,nb };
	}

	//Ed 13 D (https://codeforces.com/contest/678/problem/D)
	TEST(exponentiating_by_squaring, ed13d_test) {

		ll a = 3, b = 10, n = 723, x = 6;

		pll res = { 1,0 };
		pll m = { a,b };
		while (n) {
			if (n & 1) {
				ll na = (res.first*m.first) % mod;
				ll nb = add((res.first*m.second) % mod, res.second);
				res = mul2(res, m);
			}

			m = mul2(m, m);
			n >>= 1;
		}

		ll ans = (res.first*x) % mod + res.second;
		ans %= mod;

		EXPECT_EQ(443623217, ans);
	}

}
