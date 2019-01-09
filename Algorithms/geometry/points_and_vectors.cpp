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

	//Sorting by polar angle and finds nearests
	pair<pt, pt> get_nearests_by_angle(vector<pt>& p) {

		auto cmp = [](const pt& a, const pt& b) {
			bool isbtna = a.y < 0 || (a.y == 0 && a.x > 0);
			bool isbtnb = b.y < 0 || (b.y == 0 && b.x > 0);
			if (isbtna != isbtnb)
				return isbtna;
			return cross(a, b) < 0;
		};

		sort(begin(p), end(p), cmp);

		pt a = p[0], b = p[1];
		auto measure = [&](const pt& a1, const pt& b1, const pt& a2, const pt& b2) {
			pt p1(dot(a1, b1), cross(a1, b1));
			pt p2(dot(a2, b2), cross(a2, b2));

			p1.y = abs(p1.y);
			p2.y = abs(p2.y);
			return cmp(p2, p1);
		};
		int n = sz(p);
		for (int i = 0; i < n; i++)
		{
			int next = (i + 1) % n;
			if (measure(p[i], p[next], a, b)) {
				tie(a, b) = tie(p[i], p[next]);
			}
		}
		return { a,b };
	}

	TEST(points_and_vectors_tests, cross_mul_test) {

		pt a(3, 1), b(5,5), c(-5,3), d(-3,-3);

		EXPECT_TRUE(cross(a, b) > 0);
		EXPECT_TRUE(cross(b, a) < 0);
		EXPECT_TRUE(cross(c, b) < 0);
		EXPECT_TRUE(cross(b, d) == 0);
		EXPECT_TRUE(cross(a,b,c) > 0);
		EXPECT_TRUE(cross(c, b, a) < 0);
	}

	TEST(points_and_vectors_tests, nearests_by_angle_test) {
		vector<pt> p = { pt(2, 2), pt(1, 0), pt(-1, 0), pt(-1, -1), pt(0,1), pt(1,2) };
		auto res = get_nearests_by_angle(p);

		EXPECT_TRUE(res.first == pt(2, 2) || res.second == pt(2, 2));
		EXPECT_TRUE(res.first == pt(1, 2) || res.second == pt(1, 2));
	}
}

