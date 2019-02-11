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

////////////

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vll v(n);
	forn(i, n)
		cin >> v[i];

	vll elems;

	auto pos = std::partition(all(v), [](int a) { return a <= 0; });
	if (pos == end(v)) { //no pos
		if (v.size() <= 6) {
			elems = v;
		}
		else {
			nth_element(begin(v), begin(v) + 3, end(v));
			elems.insert(end(elems), begin(v), begin(v) + 3);
			nth_element(begin(v), end(v) - 3, end(v));
			elems.insert(end(elems), end(v)-3, end(v));
		}
	}
	else {
		auto negs = distance(begin(v), pos);
		if (negs <= 6) {
			elems.insert(end(elems), begin(v), pos);
		}
		else {
			nth_element(begin(v), begin(v) + 3, pos);
			elems.insert(end(elems), begin(v), begin(v) + 3);
			nth_element(begin(v), pos - 3, pos);
			elems.insert(end(elems), pos - 3, pos);
		}
		if (v.size() - negs <= 6) {
			elems.insert(end(elems), pos, end(v)); //pos
		}
		else {
			nth_element(pos, pos + 3, end(v));
			elems.insert(end(elems), pos, pos + 3);
			nth_element(pos, end(v) - 3, end(v));
			elems.insert(end(elems), end(v) - 3, end(v));
		}
	}
	int ii, jj, kk;
	ll mx = numeric_limits<ll>::min();
	for (int i = 0; i < sz(elems)-2; i++) {
		for (int j = i + 1; j < sz(elems) - 1; j++) {
			for (int k = j + 1; k < sz(elems); k++) {
				if (elems[i] * elems[j] * elems[k] > mx) {
					tie(ii, jj, kk) = tie(i, j, k);
					mx = elems[i] * elems[j] * elems[k];
				}
			}
		}
	}


	cout << elems[ii] << " " << elems[jj] << " " << elems[kk];
	
	return 0;
}