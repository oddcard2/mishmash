#include "bits/stdc++.h"
#include <random>

using namespace std;

string input = "";
string file = "input.txt";

struct Point {
	int x;
	int y;
	Point(int x, int y) : x(x), y(y) {}
	Point() {}
};

static bool operator<(const Point& a, const Point& b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

vector<Point> generate_p(int minX, int maxX, int minY, int maxY, int n) {
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
	int n = 1000;
	auto p = generate_p(-100000, 100000, -100000, 100000, n);

	ofstream f(file_path);
	f << n << endl;
	for (auto it : p) {
		f << it.x << " " << it.y << endl;
	}
}

/*
 1<=N<=1000
 N lines of 2 numbers - x y (|x|,|y|<= 10e5)
 precision = 15 numbers after point
 About precision:
 https://codeforces.com/blog/entry/6345
 https://codeforces.com/blog/entry/1443
 https://habr.com/company/xakep/blog/257897/
 https://habr.com/post/309812/
 */
int main(int argc, char **argv) {
	cout.sync_with_stdio(false);
	cin.sync_with_stdio(false);

	istream *pinp;
#ifndef ONLINE_JUDGE
	unique_ptr<istream> stream;
	if (argc > 1 || !file.empty()) {
		string file_path = (argc > 1) ? argv[1] : file;
		pinp = new ifstream(file_path);
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

	//generate_and_save_to_file("input.txt");
	//return 0;

	//read p as double
	int n;
	icp >> n;

	struct point {
		int64_t x; //TODO: try int64
		int64_t y;
	};

	double minX = 1e7;
	double minY = 1e7;
	double maxX = -1e7;
	double maxY = -1e7;

	vector<point> p;
	p.resize(n);
	for (int i = 0; i < n; i++) {
		icp >> p[i].x >> p[i].y;
		if (p[i].x < minX)
			minX = p[i].x;
		if (p[i].x > maxX)
			maxX = p[i].x;

		if (p[i].y < minY)
			minY = p[i].y;
		if (p[i].y > maxY)
			maxY = p[i].y;
	}

	vector<vector<double>> dists(n, vector<double>(n));
	for (size_t i = 0; i < n-1; i++)
	{
		for (size_t j = 1; j < n; j++)
		{
			double d = sqrt((double)((p[j].x - p[i].x)*(p[j].x - p[i].x) + (p[j].y - p[i].y)*(p[j].y - p[i].y)));
			dists[i][j] = d;
		}
	}

	double maxP = 0;
	for (int i = 0; i < n-2; i++)
	{
		for (int j = i+1; j < n-1; j++)
		{
			for (int k = j+1; k < n; k++)
			{
				if (p[k].y*(p[j].x - p[i].x) != p[i].y*(p[j].x - p[i].x) + (p[j].y - p[i].y)*(p[k].x - p[i].x))
				{
					double per = dists[i][j] + dists[i][k] + dists[j][k];
					if (per > maxP) {
						maxP = per;
					}
				}
			}
		}
	}

	cout.precision(15);
	cout << maxP;

	//double maxXDist = abs(maxX - minX);
	//double maxYDist = abs(maxY - minY);
	//double maxDist = max(maxXDist, maxYDist);

	//double maxPerimiter = (maxXDist + maxYDist + sqrt(maxXDist*maxXDist + maxYDist * maxYDist)) * 1.1;
	//double maxOfSquares = maxDist * maxDist + maxDist * maxDist;

	//find max, calc n and multiply to 10^n uint64_t
	//calc distance matrix
	//loop for 
	
	return 0;
}