#include "bits/stdc++.h"

using namespace std;

string input = "5\n3\n2\n4\n8\n5";

int main(int argc, char **argv) {
	cout.sync_with_stdio(false);
	cin.sync_with_stdio(false);

	istream *pinp;
#ifndef ONLINE_JUDGE
	unique_ptr<istream> stream;
	if (argc > 1) {
		pinp = new ifstream(argv[1]);
		stream.reset(pinp);
	}
	else if (!input.empty()) {
		pinp = new istringstream(input);
		stream.reset(pinp);
	} else
#endif	
	{
		pinp = &cin;
	}
	istream &icp = *pinp;

	int n;
	icp >> n;

	vector<int> h(n);
	for (int i = 0; i < n; i++)
	{
		icp >> h[i];
	}

	vector<vector<int> > dp(vector<int>(n));
	vector<vector<int> > dpr(vector<int>(n));

	function<int(int, int)> rem = [&](int l, int r) {
		if (dpr[l][r])
			return dpr[l][r];
		int res = -1;
		if (r - l == 2) {
			int m = r + 1;
			if (h[r] > h[r] && h[l] > h[r])
				res = 1;
			if (h[r] < h[r] && h[l] < h[r])
				res = 1;
		}
		else {
			int del = n+1;
			for (int i = l + 1; i < r; i++) {

			}
			if (del == n + 1)
				res = -1;
			res = del;
		}
		if (res == -1)
			return -1;
		dpr[l][r] = res;
		return res;
	};

	function<int(int, int)> sch = [&](int l, int r) {
		if (dp[l][r])
			return dp[l][r];
		if (l + 1 == r && h[l] <= h[r])
			return 2;
		if (h[l] > h[r])
			return -1;
		int res = -1;
		for (int mid = l + 1; mid < r; mid++) {
			if (h[mid] >= h[l] && h[mid] <= h[r]) { //can be keeped
				int res1 = sch(l, mid);
				if (res1 == -1)
					return -1;
				int res2 = sch(mid, r);
				if (res2 == -1)
					return -1;
				res = max(res, res1 + res2);
			}
		}
		if (res == -1)
			return (r-l+1) - rem(l, r);
		else {
			dp[l][r] = res;
			return res;
		}
	};
	
	return 0;
}