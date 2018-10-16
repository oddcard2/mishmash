#include "bits/stdc++.h"

using namespace std;

string input = "5\n3\n2\n4\n8\n5"; //ans: 2 2 4

string input2 = "5\n4\n5\n5\n5\n6"; //ans:0

string input3 = "6\n1\n1\n3\n3\n2\n2"; //-1

string input4 = "6\n400\n300\n310\n300\n310\n500"; //-1


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

	vector<vector<int> > dp(n, vector<int>(n));
	vector<vector<int> > dpv(n, vector<int>(n));
	vector<vector<int> > dpr(n, vector<int>(n));

	function<int(int, int)> rem = [&](int l, int r) {
		if (dpr[l][r])
			return dpr[l][r];

		if (r - l == 1)
			return 0;

		int res = -1;
		if (r - l == 2) { //3 oaks
			int m = l + 1;
			if ((h[r] > h[m] && h[l] > h[m]) ||
				(h[r] < h[m] && h[l] < h[m]))
				res = m;
			else 
				res = -1;
		}
		else {
			for (int i = l + 1; i < r; i++) { //last removed
				int r1 = rem(l, i);
				int r2 = rem(i, r);
				if (r1 > 0 && r2 > 0) {
					dpr[l][r] = i;
					res = i;
					break;
				}
			}
		}
		if (res == -1)
			return -1;
		dpr[l][r] = res; //last removed
		return res;
	};

	function<int(int, int)> sch = [&](int l, int r) {
		if (dpv[l][r])
			return dpv[l][r];
		if (l + 1 == r && h[l] <= h[r])
			return 2;
		if (h[l] > h[r])
			return -1;

		int res = -1;
		int best_mid;
		for (int mid = l + 1; mid < r; mid++) {
			if (h[mid] >= h[l] && h[mid] <= h[r]) { //can be keeped
				int res1 = sch(l, mid);
				if (res1 == -1)
					return -1;
				int res2 = sch(mid, r);
				if (res2 == -1)
					return -1;
				if (res1 + res2 > res) {
					res = res1 + res2;
					best_mid = mid;
				}
			}
		}
		if (res == -1) {
			if (rem(l, r) != -1)
				res = 0; //all removed
			else
				res = -1;
		}
		else {
			dp[l][r] = best_mid;
			dpv[l][r] = res;
		}
		return res;
	};

	vector<int> ans;

	function<void(int, int)> ans_rem = [&](int l, int r) {
		int last = dpr[l][r];
		if (!last)
			return;
		ans_rem(l, last);
		ans_rem(last, r);
		ans.push_back(last);
	};

	function<void(int, int)> ans_walk = [&](int l, int r) {
		int mid = dp[l][r];
		if (mid == 0) { //all removed
			ans_rem(l, r);
			return;
		}
		ans_walk(l, mid);
		ans_walk(mid, r);
	};

	if (sch(0, n - 1) == -1) {
		cout << "-1";
		return 0;
	}
	ans_walk(0, n - 1);
	cout << ans.size() << endl;
	for (auto a : ans) {
		cout << a+1 << endl;
	}

	return 0;
}