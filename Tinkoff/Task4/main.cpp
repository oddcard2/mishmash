#include "bits/stdc++.h"
#include <chrono>

using namespace std;

string input = "";

static vector<int> generate_squares(int min, int max) {
	vector<int> res;
	res.resize(max + 1);
	for (int i = min; i <= max; i++) {
		res[i] = i * i;
	}
	return res;
}

static vector<vector<pair<int, int>>> generate_sum_squares(const vector<int>& squares, int min, int max) {
	vector<vector<pair<int, int>>> res;
	res.resize(squares[max] + squares[max]+1);
	for (int i = min; i <= max; i++) {
		for (int j = i; j <= max; j++) {
			int sum = squares[i] + squares[j];
			res[sum].push_back(make_pair(i, j));
		}
	}
	return res;
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

	vector<int> sq = generate_squares(0, 1000);
	auto sums = generate_sum_squares(sq, 0, 1000);

	vector<pair<size_t, int>> sum_nums;
	for (auto i = 0; i < sums.size(); i++) {
		if (sums[i].empty())
			continue;
		sum_nums.push_back(make_pair(sums[i].size(), (int)i));
	}
	const int to_see_num = 10;
	partial_sort(begin(sum_nums), begin(sum_nums) + to_see_num, end(sum_nums), [](const pair<size_t, int>& a, const pair<size_t, int>& b) { return a.first > b.first; });

	for (int i = 0; i < to_see_num; i++) {
		cout << i << " - " << sum_nums[i].first <<", sum = " << sum_nums[i].second << endl;
	}
	cout << endl;

	int largest_options_sum = sum_nums[0].second;
	cout << "Sum " << largest_options_sum << " options:" << endl;
	for (auto it : sums[largest_options_sum]) {
		cout << it.first << " + " << it.second << endl;
	}
	return 0;
}