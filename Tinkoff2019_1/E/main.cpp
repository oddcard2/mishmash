#include "bits/stdc++.h"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	vector<pair<int, int>> p(m);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		p[i] = { a,b };
	}

	int cnt = 0;

	vector<int> r(m,1);

	for (int i = 0; i < m; i++) {
		int x, y;
		tie(x, y) = p[i];
		for (int j = i-1; j >=0; --j) {
			int x2, y2;
			tie(x2, y2) = p[j];

			if ((x2 >= x && x2 <= y) || (y2 >= x && y2 <= y)) {
				r[j] = 0;
			}
		}
	}

	cout << count(begin(r), end(r), 1);
	return 0;
}