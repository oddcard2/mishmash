#include "bits/stdc++.h"

using namespace std;

string input = "11";

static int dp[1001][1001];

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

	int n = 11;
	//int n = 1000;
	//cin >> n;

	dp[0][0] = 1;

	for (int i = 1; i <= n; i++) { //num of kisses (beze)
		for (int m = 1; m <= i; m++) { //first elem
			for (int p=min(m-1, i-m);p >=0; p--) //prev elem
				dp[i][m] += dp[i - m][p];
		}
	}

	int64_t ans = 0;
	for (int i = 0; i <= n; i++) {
		ans += dp[n][i];
	}

	cout << ans << endl;
	
	return 0;
}