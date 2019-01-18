#include "bits/stdc++.h"

using namespace std;

bool pal(const string& str)
{
	int i = 0;
	int j = str.length() - 1;

	for (; i < j; ++i, --j)
		if (str[i] != str[j])
			return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int x;
	cin >> x;

	int ans = 0;
	string s;
	for (int i = 1; i <= x; ++i) {
		s = std::to_string(i);
		if (pal(s))
			ans++;
	}

	cout << ans;
	
	return 0;
}