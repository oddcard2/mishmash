#include "bits/stdc++.h"

using namespace std;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int x, y;
	cin >> x >> y;

	int ans = numeric_limits<int>::max();
	std::function<void(int,int)> f = [&](int n, int d) {
		if (n == y) {
			if (d < ans)
				ans = d;
		}
		int a = n + 3;
		if (a <= y)
			f(a, d + 1);
		int b = n * 4;
		if (b <= y)
			f(b, d + 1);
	};

	f(x, 0);
	if (ans == numeric_limits<int>::max()) {
		cout << "-1";
	}
	else {
		cout << ans;
	}
	
	return 0;
}