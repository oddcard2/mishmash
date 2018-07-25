#include "bits/stdc++.h"

using namespace std;

string matrix1 =	"0 0 0\n"\
					"0 0 0\n";

string matrix2 =	"1 1 1 1\n"\
					"1 1 1 1\n"\
					"1 1 1 1\n"\
					"1 1 1 1\n";

string matrix3 =	"1 1 1 1\n"\
					"0 1 1 1\n";

string matrix4 =	"1 0 1 0\n"\
					"0 0 0 1\n"\
					"0 0 1 0\n"\
					"0 1 0 0\n";

string matrix5 =	"1 0 1 0 0 1 0 0\n"\
					"0 1 0 1 0 0 0 1\n"\
					"1 1 1 0 0 0 1 0\n"\
					"0 0 0 0 0 0 0 0\n"\
					"1 0 1 1 1 0 1 1\n"\
					"1 0 0 0 1 0 0 1\n";

string matrix6 =	"1 0 1 0 0 0 0 0\n"\
					"0 1 0 1 0 0 0 1\n"\
					"1 1 1 0 0 0 1 0\n"\
					"0 1 0 0 0 0 0 0\n"\
					"1 0 1 1 1 0 1 1\n"\
					"1 0 0 0 1 0 0 1\n"\
					"1 0 0 0 1 0 0 1\n"\
					"1 0 1 1 0 0 0 0\n";

string input = matrix6;

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

	vector<vector<int>> v;
	int n = 0, m = 0;
	string str;
	while (getline(icp, str))
	{
		istringstream ss(str);
		int num;
		m = 0;
		while (ss >> num)
		{
			if (v.size() <= n)
				v.push_back({});
			v[n].push_back(num);
			m++;
		}
		n++;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << v[i][j] << " ";
		}
		cout << endl;
	}

	const int x = 0;
	vector<int> dp(m,0); //height of column of x, including current entity
	vector<int> x1(m, 0); //left borders
	vector<int> x2(m, 0); //right borders
	stack<int> s; //border stacks

	int max_square = 0;
	int max_x = 0, max_y = 0, max_w = 0, max_h = 0;

	for (int i = 0; i < n; i++) { //lines
		//recalc dp for this line
		for (int j = 0; j < m; j++) {
			if (v[i][j] == x)
				dp[j] = 1 + dp[j];
			else
				dp[j] = 0;
		}

		while (!s.empty()) s.pop();
		//try to expand sub-matrix to left
		for (int j = 0; j < m; j++) {
			//it rests to top or some previous stack elems
			while (dp[j] && !s.empty() && dp[s.top()] >= dp[j]) {
				s.pop();
			}
			//left column
			x1[j] = (s.empty()) ? 0 : s.top() + 1;
			s.push(j);
		}
		while (!s.empty()) s.pop();

		//try to expand sub-matrix to left
		for (int j = m-1; j >= 0; j--) {
			//it rests to top or some previous stack elems
			while (dp[j] && !s.empty() && dp[s.top()] >= dp[j]) {
				s.pop();
			}
			//left column
			x2[j] = (s.empty()) ? m : s.top();
			s.push(j);
		}


		for (int j = 0; j < m; j++) {
			int sq = dp[j] * (x2[j] - x1[j]);
			if (sq > max_square) {
				max_square = sq;
				max_x = x1[j];
				max_y = i + 1 - dp[j];
				max_w = x2[j] - x1[j];
				max_h = dp[j];
			}
		}
	}

	cout << "max square = " << max_square << "(" << max_x << ", " << max_y << "), (" << max_w << ", " << max_h << ")" << endl;

	return 0;
}