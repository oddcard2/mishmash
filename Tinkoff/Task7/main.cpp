#include "bits/stdc++.h"

using namespace std;

string input = "";


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

	//read points as double
	int n;
	icp >> n;

	std::string line;
	std::getline(icp, line); //current line

	struct point {
		double x;
		double y;
	};

	double minX = 1e7;
	double minY = 1e7;
	double maxX = -1e7;
	double maxY = -1e7;

	vector<point> points;
	points.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y;
		if (points[i].x < minX)
			minX = points[i].x;
		if (points[i].x > maxX)
			maxX = points[i].x;

		if (points[i].y < minY)
			minY = points[i].y;
		if (points[i].y > maxY)
			maxY = points[i].y;
	}

	double maxXDist = abs(maxX - minX);
	double maxYDist = abs(maxY - minY);
	double maxDist = max(maxXDist, maxYDist);

	double maxPerimiter = (maxXDist + maxYDist + sqrt(maxXDist*maxXDist + maxYDist * maxYDist)) * 1.1;
	double maxOfSquares = maxDist * maxDist + maxDist * maxDist;

	//find max, calc n and multiply to 10^n uint64_t
	//calc distance matrix
	//loop for 
	
	return 0;
}