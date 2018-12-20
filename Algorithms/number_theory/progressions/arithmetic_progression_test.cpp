#include <gtest/gtest.h>
#include <vector>

using namespace std;

#define MOD 1000000007ll

namespace {
	
	template<typename T>
	T progress_sum(T n) {
		return n * (n + 1) / 2;
	}

	template<typename T>
	T progress_sum(T start, T end) {
		T n = (end - start + 1);
		return (start - 1)*n + n*(n+1)/2;
	}

	template<typename T>
	T progress_sum_mod(T start, T end, T m) {
		T n = (end - start + 1) % m;
		return (((start - 1) % m)*n + n * (n + 1) / 2) % m;
	}

	TEST(gcd_tests, simple_gcd_test) {
		EXPECT_EQ(55, progress_sum(10));
		EXPECT_EQ(75, progress_sum(10, 15));
		EXPECT_EQ(733950, progress_sum_mod(100000000000ll, 200000000000ll, MOD));
	}

}

