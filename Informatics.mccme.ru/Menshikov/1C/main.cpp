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
#define x first
#define y second

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

pair<int, int> bin_search(int n, std::function<bool(int)> ok) {
	int l = -1, r = n, mid;
	while (r - l > 1) {
		mid = (l + r) / 2;
		if (ok(mid))
			r = mid;
		else
			l = mid;
	}
	return { l,r };
}

#if 1
int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);

	rvn;

	int mx = 0;
	vi dp(n + 1);
	vi par(n + 1);
	vi ix(n + 1);
	forn(i, n + 1) {
		dp[i] = numeric_limits<int>::max();
		par[i] = -1;
		ix[i] = -1;
	}


	forn(i, n) {
		int a = v[i];

		auto r = bin_search(mx, [&](int pos) { return dp[pos] >= a; });
		int pos = r.first + 1;
		if (dp[pos] > a) {

			ix[pos+1] = i;
			if (pos > 0)
				par[i] = ix[pos];
			dp[pos] = a;
			mx = max(mx, pos + 1);
		}
	}

	cout << mx << '\n';
	vi ans;
	int pos = ix[mx];
	while (pos >= 0) {
		ans.push_back(v[pos]);
		pos = par[pos];
	}

	reverse(all(ans));
	forn(i, mx)
		cout << ans[i] << " ";

	return 0;
}
#else
//Counter-example:
//6
//1 7 3 5 2 9
int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	rvn;

	int mx = 0;
	vi dp(n + 1);
	forn(i, n + 1) dp[i] = numeric_limits<int>::max();

	forn(i, n) {
		int a = v[i];

		auto r = bin_search(mx, [&](int pos) { return dp[pos] >= a; });

		dp[r.first + 1] = min(dp[r.first + 1], a);
		mx = max(mx, r.first + 1 + 1);
	}

	cout << mx << '\n';
	forn(i, mx)
		cout << dp[i] << " ";

	return 0;
}
#endif