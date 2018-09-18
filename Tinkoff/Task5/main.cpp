#include "bits/stdc++.h"

using namespace std;

/*(3,0) one makes loop*/
string input = "5 " \
"0 1 1 0 0 "\
"0 0 0 0 0 "\
"0 1 0 1 1 "\
"1 0 0 0 0 "\
"0 0 0 1 0 ";



string input2 = "5 " \
"0 1 1 0 0 "\
"0 0 0 0 0 "\
"0 1 0 1 1 "\
"0 1 0 0 0 "\
"0 0 0 1 0 ";

vector<int> vis; //0 - not visited, 1 - entered, 2 - exited
vector<vector<int>> v;

bool dfs(int k) {
	vis[k] = 1;
	for (auto i = 0; i < v[k].size(); ++i) {
		int child = v[k][i];
		if (vis[child] == 1)
			return true;
		if (dfs(child))
			return true;
	}
	vis[k] = 2;
	return false;
}

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

	vis.resize(n);
	std::fill(vis.begin(), vis.end(), 0);
	v.resize(n);

	for (int i = 0; i < n; i++) {
		v[i].reserve(n);
		for (int j = 0; j < n; j++) {
			int b;
			icp >> b;
			if (b) {
				v[i].push_back(j);
			}
		}
	}

	int det = 0;
	std::fill(vis.begin(), vis.end(), 0);
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			if (dfs(i)) {
				det = 1;
				break;
			}
		}
	}
	
	cout << det;
	
	return 0;
}