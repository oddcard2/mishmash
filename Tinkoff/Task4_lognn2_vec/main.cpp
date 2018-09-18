#include "bits/stdc++.h"
#include <chrono>
#include <random>

using namespace std;

string input1 = "4 "\
"0 3 "\
"3 0 "\
"0 -3 "\
"-3 0";

//20 triangles
string input = "9 "\
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

static int squares[2001];

static int squares_dists[1500][1500];

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
	}
	else
#endif	
	{
		pinp = &cin;
	}
	istream &icp = *pinp;

	int n;
	icp >> n;

	vector<Point> p;
	p.resize(n);

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

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			int dist = squares[abs(p[j].x - p[i].x)] + squares[abs(p[j].y - p[i].y)];
			squares_dists[i][j] = dist;
			squares_dists[j][i] = dist;
		}
	}

	int64_t count = 0;
	int64_t count3 = 0;
	vector<vector<pair<int, int>> > dists;
	dists.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;

			int dist = squares_dists[i][j];
			dists[i].push_back(make_pair(dist, j));
		}
	}

	for (int i = 0; i < n; i++) {
		sort(begin(dists[i]), end(dists[i]), [](const pair<int, int>& a, const pair<int, int>& b) {return a.first < b.first;  });
	}

	for (int i = 0; i < n; i++) {
		//i - main vertex
		//take all possible pairs with the same distance
		for (auto d1 = dists[i].begin(); d1 != dists[i].end(); d1++) {
			auto start = d1;
			for (auto d2 = next(start); d2 != dists[i].end() && d2->first == d1->first; ++d2) {
				//so d1 == d2
				int j = d1->second;
				int k = d2->second;
				if (p[k].y*(p[j].x - p[i].x) != p[i].y*(p[j].x - p[i].x) + (p[j].y - p[i].y)*(p[k].x - p[i].x)) {
					if (squares_dists[j][k] == start->first) //equilateral triangle
						count3++;
					else //isosceles triangle
						count++;
				}
			}
		}
	}

	cout << count + count3 / 3;
	return 0;
}