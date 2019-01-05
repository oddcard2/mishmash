#include <gtest/gtest.h>
#include <common.h>

namespace {

	/***********************/
	struct pt {
		typedef ll T;
		T x;
		T y;

		pt() {}
		pt(T x, T y) :x(x), y(y) {}

		const pt& operator=(const pt& o) {
			tie(x, y) = tie(o.x, o.y);
			return *this;
		}
	};

	static bool operator==(const pt& a, const pt& b) {
		return tie(a.x, a.y) == tie(b.x, b.y);
	}

	static pt operator+(const pt& a, const pt& b) {
		return pt(a.x + b.x, a.y + b.y);
	}

	static pt operator-(const pt& a, const pt& b) {
		return pt(a.x - b.x, a.y - b.y);
	}

	static bool operator<(const pt& a, const pt& b) {
		return a.x < b.x || a.x == b.x && a.y < b.y;
	}

	static pt::T dot(pt a, pt b) {
		return a.x*b.x + a.y*b.y;
	}

	// > 0, if a clockwise b, for example a=(1,0),b=(-1,1) 
	static pt::T cross(pt a, pt b) {
		return a.x*b.y - a.y*b.x;
	}

	//between b - a and c - a
	// > 0 if ab clockwise ac
	static pt::T cross(pt a, pt b, pt c) {
		return cross(b - a, c - a);
	}

	bool cmp(pt a, pt b) {
		return a.x < b.x || a.x == b.x && a.y < b.y;
	}

	bool cw(pt a, pt b, pt c) {
		return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) < 0;
	}

	bool ccw(pt a, pt b, pt c) {
		return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) > 0;
	}
	/***********************/

	TEST(points_and_vectors_tests, cross_mul_test) {

		pt a(3, 1), b(5,5), c(-5,3), d(-3,-3);

		EXPECT_TRUE(cross(a, b) > 0);
		EXPECT_TRUE(cross(b, a) < 0);
		EXPECT_TRUE(cross(c, b) < 0);
		EXPECT_TRUE(cross(b, d) == 0);
		EXPECT_TRUE(cross(a,b,c) > 0);
		EXPECT_TRUE(cross(c, b, a) < 0);
	}

}

