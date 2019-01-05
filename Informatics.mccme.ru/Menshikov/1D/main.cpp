#include "bits/stdc++.h"

using namespace std;

////////////

const int mod = 1000000007;

template<typename T>
inline int add(T a, T b) { return a + b >= mod ? a + b - mod : a + b; }
template<typename T>
inline void inc(T& a, T b) { a = add(a, b); }
template<typename T>
inline int sub(T a, T b) { return a - b < 0 ? a - b + mod : a - b; }
template<typename T>
inline void dec(T& a, T b) { a = sub(a, b); }

typedef long long ll;
typedef long double ld;

typedef vector<int> vi;

typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tri;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define ford(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
#define correct(x, y, n, m) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
#define all(a) (a).begin(), (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define mp(x, y) make_pair((x), (y))
//#define x first
//#define y second

using namespace std;

template<typename X> inline X abs(const X& a) { return a < 0 ? -a : a; }
template<typename X> inline X sqr(const X& a) { return a * a; }

const int INF = int(1e9);
const ll INF64 = ll(1e18);
const ld EPS = 1e-9, PI = 3.1415926535897932384626433832795;

#define rn\
int n; cin>>n;

#define rvi(name, count)\
vi name(count);\
for (int i = 0; i < count; i++) cin >> name[i];

#define rvn \
int n; cin >> n;\
vi v(n); \
for (int i = 0; i < n; i++) cin >> v[i];

#define rvn1 \
int n; cin >> n;\
vi v(n+1); \
for (int i = 0; i < n; i++) cin >> v[i+1];

////////////

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

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);

	pt a, b, c, d;
	cin >> a.x >> a.y;
	cin >> b.x >> b.y;
	cin >> c.x >> c.y;
	cin >> d.x >> d.y;

	bool ok = true;
	if (cross(a, d, b)*cross(a, d, c) > 0)
		ok = false;
	if (cross(b, d, a)*cross(b, d, c) > 0)
		ok = false;
	if (cross(c, d, a)*cross(c, d, b) > 0)
		ok = false;
	
	if (ok)
		cout << "In";
	else
		cout << "Out";
	return 0;
}