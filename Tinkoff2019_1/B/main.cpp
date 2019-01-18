#include "bits/stdc++.h"

using namespace std;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	cin >> s;

	vector<int> cnt(30);
	for (auto c : s) {
		cnt[c - 'a']++;
	}
	for (size_t i = 0; i < cnt.size(); i++) {
		if (cnt[i] > 1)
			cout << char(i + 'a');
	}
	return 0;
}