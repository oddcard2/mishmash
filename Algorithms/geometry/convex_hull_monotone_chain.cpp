#include <gtest/gtest.h>
#include <vector>

using namespace std;

typedef long long ll;

struct pt {
	typedef ll T;
	ll x;
	ll y;

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

static pt::T cross(pt a, pt b) {
	return a.x*b.y - a.y*b.x;
}

//between b-a and c-a
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

//https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C++
vector<pt> convex_hull(vector<pt> P)
{
	size_t n = P.size(), k = 0;
	if (n <= 3) return P;
	vector<pt> H(2 * n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (size_t i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (size_t i = n - 1, t = k + 1; i > 0; --i) {
		while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) <= 0) k--;
		H[k++] = P[i - 1];
	}

	H.resize(k - 1);
	return H;
}

TEST(convex_hull_mc, simple_test) {
	vector<pt> pv = { {1,0}, {-1,0}, {0,1}, {0,0} };
	vector<pt> ch = convex_hull(pv);

	EXPECT_EQ(4, pv.size());
	EXPECT_EQ(3, ch.size());

	EXPECT_TRUE(find(begin(ch), end(ch), pt(0,0)) == end(ch));
}
