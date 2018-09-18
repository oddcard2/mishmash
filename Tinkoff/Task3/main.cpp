#include "bits/stdc++.h"

using namespace std;

//string input = "6 10";
string input = "6 15";

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

	int n, k;
	icp >> n >> k;
	
	int maxi = n * (n - 1);
	if (k > maxi) {
		cout << "-1";
		return 0;
	}

	vector<int> s;
	s.resize(n);
	fill(begin(s), end(s), 0);

	//greedy
	int rest = k;
	int elem = n;
	for (int i = n - 1; i > 0 && rest > 0; i--) {
		if (i <= rest) {
			rest -= i;
			int pos = n - i - 1;
			s[pos] = elem--;
		}
	}
	elem = 1;
	for (int i = 0; i < n; i++) {
		if (!s[i])
			s[i] = elem++;
	}

	int inv = 0;
	//code for check - calcs number of inversions:
	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (s[i] > s[j])
				inv++;
		}
	}

	if (inv != k) {
		cout << inv << " != " << k << "!!!" << endl;
	}

	for (int i = 0; i < n; i++) {
		cout << s[i];
		if (i != n-1)
			cout << " ";
	}
	return 0;
}