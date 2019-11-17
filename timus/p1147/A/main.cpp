#include "bits/stdc++.h"

using namespace std;

////////////

const int mod = 1000000007;

template<typename T>
inline T add(T a, T b) { return a + b >= mod ? a + b - mod : a + b; }
template<typename T>
inline void inc(T& a, T b) { a = add(a, b); }
template<typename T>
inline T sub(T a, T b) { return a - b < 0 ? a - b + mod : a - b; }
template<typename T>
inline void dec(T& a, T b) { a = sub(a, b); }

typedef long long ll;
typedef long double ld;

typedef vector<int> vi;
typedef vector<ll> vll;

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

/// DEBUG
/// https://codeforces.com/blog/entry/68809
/// TODO: compare with https://codeforces.com/blog/entry/65311

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V> &x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T &x) { int f = 0; cerr << '{'; for (auto &i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif


struct pnt {
	pnt(int y, int num, int cl, int bk, int col) :y(y), num(num), close(cl), back(bk), col(col) {}
	int y;
	int num;
	bool close;
	bool back;
	int col;
};

bool operator<(const pnt& a, const pnt& b) {
	return make_tuple(a.y, a.num, a.close) < make_tuple(b.y, b.num, b.close);
}

////////////
// http://acm.timus.ru/problem.aspx?space=1&num=1147
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int a, b, n;
	cin >> a >> b >> n;

	vector<vector<pnt>> v(a);
	vi coef(a);

	forn(i, n) {
		int x1, y1, x2, y2, col;
		cin >> x1 >> y1 >> x2 >> y2 >> col;

		if (x2 - x1 > 1) {
			v[x1].push_back(pnt{y1, i, 0, 0, col});
			v[x1].push_back(pnt{y2-1, i, 1, 0, col });
		}
		v[x2-1].push_back(pnt{ y1, i, 0, 1, col });
		v[x2-1].push_back(pnt{ y2-1, i, 1, 1, col });
	}

	int cf = 1;
	ford(i, a) {
		if (!sz(v[i])) {
			cf++;
		}
		else {
			coef[i] = cf;
			cf = 1;
		}
	}

	vector<int> stat(2501);

	set<pii> opencol;
	set<pnt> points;
	
	forn(i, a) {
		if (!sz(v[i])) continue;

		forn(j, sz(v[i])) {
			points.insert(v[i][j]);
		}

		opencol.clear();

		int prev = -1;
		auto p = begin(points);
		while (p != end(points)) {
			int yy = p->y;
			// 1. stat for [prev+1, curr-1]
			int prev_cnt = yy - 1 - prev;

			int curr_col = 1;
			if (!opencol.empty()) {
				curr_col = opencol.rbegin()->second;
			}
			stat[curr_col] += prev_cnt * coef[i];

			prev = yy;

			auto it = p;
			// 2. processes all openings for this y
			while (it != end(points) && it->y == yy) {
				if (!it->close) {
					opencol.insert({ it->num, it->col });
				}
				++it;
			}

			// 3. colors current point
			curr_col = 1;
			if (!opencol.empty()) {
				curr_col = opencol.rbegin()->second;
			}
			stat[curr_col] += coef[i];

			// 4. processes all closings
			while (p != end(points) && p->y == yy) {
				if (p->close) {
					opencol.erase({ p->num, p->col });
				}

				if (p->back) {
					p = points.erase(p);
				}
				else {
					++p;
				}
			}
		}
		// 5. colors remains
		int prev_cnt = b - 1 - prev;

		int curr_col = 1;
		if (!opencol.empty()) {
			curr_col = opencol.rbegin()->second;
		}
		stat[curr_col] += prev_cnt * coef[i];

	}

	for (int i = 1; i < 2501; i++) {
		if (stat[i]) {
			cout << i << " " << stat[i] << endl;
		}
	}
	
	return 0;
}