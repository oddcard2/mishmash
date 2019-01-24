#include <gtest/gtest.h>
#include "common.h"

using namespace std;

namespace {

	/***********************/
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

	//!!! Don't forget to check return value!!!
	template<typename T>
	bool find_any_solution(T a, T b, T c, T & x0, T & y0, T & g) {
		g = gcdex(abs(a), abs(b), x0, y0);
		if (c % g != 0)
			return false;
		x0 *= c / g;
		y0 *= c / g;
		if (a < 0)   x0 *= -1;
		if (b < 0)   y0 *= -1;
		return true;
	}
	/***********************/


	TEST(diofant_2_equation_tests, simple_soultion_test) {
		//5x+7y=1
		int x0, y0, g;
		int a = 5, b = 7, c = 1;
		EXPECT_TRUE(find_any_solution(a,b,c, x0, y0, g));
		EXPECT_EQ(3, x0);
		EXPECT_EQ(-2, y0);
		EXPECT_EQ(1, g);

		//other solutions
		//x=x0+k*b/g
		//y=y0+k*a/g
		//k c Z
		int k = -5;
		int x = x0 + k * b / g;
		int y = y0 - k * a / g;

		EXPECT_EQ(1, a*x + b * y);

		EXPECT_FALSE(find_any_solution(5, 10, 3, x0, y0, g));
		EXPECT_EQ(5, g);
	}

}

