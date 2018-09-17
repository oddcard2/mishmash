#include "bits/stdc++.h"
#include <chrono>
#include <random>

using namespace std;

string input = "4 "\
"0 3 "\
"3 0 "\
"0 -3 "\
"-3 0";

//20 triangles
string input2 = "9 "\
"-4 -3 "\
"-2 -3 "\
"0 -3 "\

"-4 1 "\
"-2 1 "\
"0 1 "\

"-4 5 "\
"-2 5 "\
"0 5 ";

//72 - is it correct?
string input3 = "16 "\
"-4 -3 "\
"-2 -3 "\
"0 -3 "\
"2 -3 "\

"-4 1 "\
"-2 1 "\
"0 1 "\
"2 1 "\

"-4 5 "\
"-2 5 "\
"0 5 "\
"2 5 "\

"-4 9 "\
"-2 9 "\
"0 9 "\
"2 9 ";

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

struct Point {
	int16_t x;
	int16_t y;
	Point(int16_t x, int16_t y) : x(x), y(y) {}
	Point() {}
};

static bool operator<(const Point& a, const Point& b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

vector<Point> generate_points(int minX, int maxX, int minY, int maxY, int n) {
	vector<Point> res;
	res.resize(n);
	set<Point> points;

	//https://en.cppreference.com/w/cpp/numeric/random
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uniX(minX, maxX); // guaranteed unbiased
	std::uniform_int_distribution<int> uniY(minY, maxY); // guaranteed unbiased

	while ((int)points.size() < n) {
		Point p(uniX(rng), uniY(rng));
		points.emplace(p);
	}
	copy(begin(points), end(points), begin(res));
	return res;
}

void generate_and_save_to_file(string file_path) {
	int n = 1500;
	auto p = generate_points(-1000, 1000, -1000, 1000, n);
	
	ofstream f(file_path);
	f << n << endl;
	for (auto it: p) {
		f << it.x << " " << it.y <<endl;
	}
}

static int squares[2001];

//PowerShell:
//Measure-Command {.\Task4.exe}
//Measure-Command {.\Task4.exe ..\..\input.txt}
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


#if 1
	//brut force
	int n;
	icp >> n;

	vector<Point> p;
	p.resize(n);

	//n = 1500;
	//p = generate_points(-1000, 1000, -1000, 1000, n);

	//generate_and_save_to_file("input.txt");
	//return 0;

	int minX = 10000, maxX = -10000;
	int minY = 10000, maxY = -10000;
	for (int i = 0; i < n; i++) {
		icp >> p[i].x >> p[i].y;
		if (p[i].x < minX)
			minX = p[i].x;
		if (p[i].y < minY)
			minY = p[i].y;
		//max
		if (p[i].x > maxX)
			maxX = p[i].x;
		if (p[i].y > maxY)
			maxY = p[i].y;
	}

	int maxDistance = max(maxX - minX, maxY - minY);
	for (int i = 0; i <= maxDistance; i++) {
		squares[i] = i * i;
	}

	int64_t count = 0;
	for (int i = 0; i < n-2; i++) {
		for (int j = i+1; j < n - 1; j++) {
			for (int k = j+1; k < n; k++) {
				//check that it's correct triangle
				int d[5] = { squares[abs(p[j].x - p[i].x)] + squares[abs(p[j].y - p[i].y)],
								squares[abs(p[k].x - p[i].x)] + squares[abs(p[k].y - p[i].y)],
								squares[abs(p[k].x - p[j].x)] + squares[abs(p[k].y - p[j].y)] };
				d[3] = d[0];
				d[4] = d[1];

				//y3=y1+(y2-y1)/(x2-x1)*(x3-x1)
				//y3(x2-x1)=y1(x2-x1)+(y2-y1)*(x3-x1)
				if (p[k].y*(p[j].x - p[i].x) != p[i].y*(p[j].x - p[i].x) + (p[j].y-p[i].y)*(p[k].x - p[i].x))
				{
					for (int s = 0; s < 3; s++) {
						if (d[s] == d[s + 1]) {
							//if (d[s] + d[s + 1] > d[s + 2]) {
								count++;
							//}
							//cout << i << " " << j << " " << k << endl;
							break;
						}
					}
				}

			}
		}
	}

	cout << count;
#else
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
#endif
	return 0;
}