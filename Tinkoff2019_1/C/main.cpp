#include "bits/stdc++.h"

using namespace std;

typedef int64_t ll;

template <typename T>
vector<T> multiply(const vector<T>& A, const vector<T>& B, int m, int n)
{
	vector<T> prod(m + n - 1);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			prod[i + j] += A[i] * B[j];
	}
	return prod;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	vector<string> parts[2];
	std::string line;

	for (size_t i = 0; i < 2; i++)
	{
		cin >> line;
		if (line[0] != '-')
			line = "+" + line;

		std::size_t prev = 1, pos;
		while ((pos = line.find_first_of("+-", prev)) != std::string::npos)
		{
			if (pos > prev)
				parts[i].push_back(line.substr(prev-1, pos - prev+1));
			prev = pos + 1;
		}
		if (prev < line.length())
			parts[i].push_back(line.substr(prev-1, std::string::npos));
	}

	vector<ll> poly[2];
	poly[0].resize(21);
	poly[1].resize(21);

	int degrees[2] = { 1,1 };
	for (size_t i = 0; i < 2; i++)
	{
		for (auto s : parts[i]) {
			int coef = 1;
			int degree = 0;
			size_t x_pos = s.find('x');
			if (x_pos == string::npos) {
				coef = stoi(s);
			}
			else {
				if (x_pos == 1) {
					if (s[0] == '-')
						coef = -1;
				}
				else {
					coef = stoi(s.substr(0, x_pos));
				}

				size_t exp_pos = s.find('^');
				if (exp_pos == string::npos)
					degree = 1;
				else
					degree = stoi(s.substr(exp_pos + 1));
			}
			if (coef != 0) {
				poly[i][degree] += coef;
				degrees[i] = max(degrees[i], degree + 1);
			}
		}
	}
	
	vector<ll> ans = multiply(poly[0], poly[1], degrees[0], degrees[1]);

	if (degrees[0] == 1 && degrees[1] == 1) {
		cout << poly[0][0] * poly[1][0];
		return 0;
	}

	stringstream ss;
	bool first = true;
	for (int i = (int)ans.size()-1; i >=0; --i) {
		if (ans[i] == 0)
			continue;

		if (ans[i] > 0 && !first) {
			ss << '+';
		}
		if (ans[i] != 1) {
			if (ans[i] == -1)
				ss << '-';
			else
				ss << ans[i];
		} 
		
		if (i > 0) {
			ss << 'x';
		}
		if (i > 1) {
			ss << '^';
			ss << i;
		}

		first = false;
	}

	const string& ans_string = ss.str();
	if (ans_string.empty())
		cout << "0";
	else
		cout << ss.str();
	return 0;
}