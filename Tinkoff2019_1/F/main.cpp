#include "bits/stdc++.h"

using namespace std;

typedef long double ld;

const double EPS = 1E-9;

/***********************/
struct pt {
	typedef long double T;
	T x;
	T y;

	pt() {}
	pt(T x, T y) :x(x), y(y) {}

	const pt& operator=(const pt& o) {
		tie(x, y) = tie(o.x, o.y);
		return *this;
	}

	pt operator*(T w) const {
		return pt(x * w, y * w);
	}

	pt operator-(const pt& w) const {
		return pt(x - w.x, y - w.y);
	}
	pt operator+(const pt& w) const {
		return pt(x + w.x, y + w.y);
	}

	bool operator< (const pt & p) const {
		return x < p.x - EPS || abs(x - p.x) < EPS && y < p.y - EPS;
	}
};

struct line {
	ld a, b, c;

	line() {}
	line(pt p, pt q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = -a * p.x - b * p.y;
		norm();
	}

	void norm() {
		ld z = sqrt(a*a + b * b);
		if (abs(z) > EPS)
			a /= z, b /= z, c /= z;
	}

	ld dist(pt p) const {
		return a * p.x + b * p.y + c;
	}
};

#define det(a,b,c,d)  (a*d-b*c)

inline bool betw(ld l, ld r, ld x) {
	return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool intersect_1d(ld a, ld b, ld c, ld d) {
	if (a > b)  swap(a, b);
	if (c > d)  swap(c, d);
	return max(a, c) <= min(b, d) + EPS;
}

bool intersect(pt a, pt b, pt c, pt d, pt & left, pt & right) {
	if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
		return false;
	line m(a, b);
	line n(c, d);
	ld zn = det(m.a, m.b, n.a, n.b);
	if (abs(zn) < EPS) {
		if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
			return false;
		if (b < a)  swap(a, b);
		if (d < c)  swap(c, d);
		left = max(a, c);
		right = min(b, d);
		return true;
	}
	else {
		left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
		left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
		return betw(a.x, b.x, left.x)
			&& betw(a.y, b.y, left.y)
			&& betw(c.x, d.x, left.x)
			&& betw(c.y, d.y, left.y);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	struct seg {
		pt a;
		pt b;
	};

	ld min_x = numeric_limits<ld>::max();
	ld max_x = numeric_limits<ld>::min();
	vector<pt> points(n);
	for (int i = 0; i < n; ++i) {
		cin >> points[i].x >> points[i].y;
		if (points[i].x < min_x)
			min_x = points[i].x;
		if (points[i].x > max_x)
			max_x = points[i].x;
	}

	ld x, y;
	cin >> x >> y;

	pt t(x, y);

	vector<seg> segs(n);
	int p = 0;
	for (int i = 0; i < n-1; ++i) {
		segs[i].a = points[i];
		segs[i].b = points[i+1];
	}

	segs[n - 1].a = points[n - 1];
	segs[n - 1].b = points[0];

	seg l;
	l.a = { x,y };
	if (abs(min_x - x) < abs(max_x - x))
		l.b = { min_x - 1, y };
	else
		l.b = { max_x + 1, y };

	for (int i = 0; i < n; ++i) {
		line ll(segs[i].a, segs[i].b);
		if (abs(ll.dist(t)) <= EPS) {
			ld x1 = segs[i].a.x, x2 = segs[i].b.x;
			if (x1 > x2) {
				swap(x1, x2);
			}

			if (t.x > x1 - EPS && t.x < x2 + EPS) {
				cout << "YES";
				return 0;
			}
		}
	}
	
	int cnt = 0;
	int inter2 = 0;
	for (int i = 0; i < n; ++i) {
		pt p1, p2;
		if (intersect(l.a, l.b, segs[i].a, segs[i].b, p1, p2)) {
			if ((abs(segs[i].a.x - p1.x) <= EPS && abs(segs[i].a.y - p1.y) <= EPS) ||
				(abs(segs[i].b.x - p1.x) <= EPS && abs(segs[i].b.y - p1.y) <= EPS)) {
				inter2++;
			} else
				cnt++;
		}
	}

	cnt += inter2 / 2;

	if (cnt % 2) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}

	return 0;
}