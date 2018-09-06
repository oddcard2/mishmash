#include "bits/stdc++.h"

using namespace std;

string input = "";

template<class T>
class FenwickTree
{
public:
	template<class ForwardIt>
	FenwickTree(ForwardIt begin, ForwardIt end) {
		_size = (int)std::distance(begin, end);
		_sums.assign(_size, 0);
		_v.assign(begin, end);
	
		for (int i = 0; i < _size; i++) {
			inc(i, _v[i]);
		}
	}

	FenwickTree(int size) {
		_size = size;
		_sums.assign(_size, 0);
		_v.assign(_size, 0);
	}

	T get(int pos) const { return _v[pos]; }

	void inc(int pos, T val) {
		//updates sums
		int p = pos;
		while (p < _size) {
			_sums[p] += val;
			p = p | (p + 1);
		}

	}

	T sum(int endPos) const {
		int p = endPos;
		int sum = 0;
		while (p >= 0) {
			sum += _sums[p];
			p = p & (p + 1);
			p = p - 1;
		}
		return sum;
	}
private:
	std::vector<T> _v;
	std::vector<T> _sums;
	int _size;
};

template<class T>
class SegmentTree
{
public:
	template<class ForwardIt>
	SegmentTree(ForwardIt begin, ForwardIt end) {
		_size = (int)std::distance(begin, end);

		_sums.assign(2*_size, 0);
		_v.assign(begin, end);

		//recursive top->buttom
		init(0, 0, _size);
	}

	//indexes of childrens of N vertex are 2N+1 and 2N+2
	T init(int n, int start, int end) {
		int middle = start + (end - start + 1) / 2;

		if (start + 1 == end) {
			_sums[n] = _v[start];
			return _v[start];
		}

		T sum = init(2*n + 1, start, middle) + init(2*n + 2, middle, end);
		_sums[n] = sum;
		return sum;
	}

	T get(int start, int end) {
		return getRecursive(0, 0, _size, start, end);
	}

	T getRecursive(int n, int start, int end, int userStart, int userEnd) {
		if (userStart <= start && userEnd >= end)
			return _sums[n];

		int middle = start + (end - start + 1) / 2;

		int sum = 0;
		if (userStart < middle)
			sum += getRecursive(2 * n + 1, start, middle, userStart, userEnd);
		if (userEnd > middle)
			sum += getRecursive(2 * n + 2, middle, end, userStart, userEnd);
		return sum;
	}

	void inc(int start, int end, T val) {
		incRecursive(0, 0, _size, start, end, val);
	}

	T incRecursive(int n, int start, int end, int userStart, int userEnd, T val) {
		if (userStart <= start && userEnd >= end) {
			_sums[n] += (end - start) * val; //updates if user interval is inside
			return (end - start) * val;
		}

		int middle = start + (end - start + 1) / 2;

		T change = 0;
		if (userStart < middle)
			change += incRecursive(2 * n + 1, start, middle, userStart, userEnd, val);
		if (userEnd > middle)
			change += incRecursive(2 * n + 2, middle, end, userStart, userEnd, val);
		_sums[n] += change;
		return change;
	}

private:
	int _size;
	std::vector<T> _v;
	std::vector<T> _sums;
};

template<typename T>
void binarySearchDp(vector<T> seq) {
	vector<T> dp;
	dp.assign(seq.size(), numeric_limits<T>::max()); //elem at the end of increasing subsequence of length N
	dp[0] = seq[0];

	int maxLen = 1;
	for (auto i = 0; i < seq.size(); i++) {
		//searches in dp value >= current val from seq
		//and updates it by current val
		auto notLessVal = std::lower_bound(begin(dp), end(dp), seq[i]);
		if (*notLessVal > seq[i]) {
			*notLessVal = seq[i];
			maxLen = distance(begin(dp), notLessVal);
		}
	}
	for (auto i = 0; i < maxLen + 1; i++) {
		cout << dp[i] << endl;
	}
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


	vector<int> searchSeq = { 5, 3, 2, 10, 8, 4, 11, 7, 20 };
	binarySearchDp(searchSeq);

	vector<int> seq = { 1, 2, 3, 4, 5 };
	//vector<int> seq = { 2, 2, -4, 8, 10 };

	SegmentTree<int> sTree(begin(seq), end(seq));

	int s24 = sTree.get(2, 4); //7

	int s05 = sTree.get(0, 5); //15

	int s01 = sTree.get(0, 1); //1

	sTree.inc(2, 4, 3);

	int s24_new = sTree.get(2, 4); //7 + 2*3 = 13
	int s05_new = sTree.get(0, 5); //15 + 2*3 = 21
	
	FenwickTree<int> tree(begin(seq), end(seq));

	for (auto i = 0; i < seq.size(); i++) {
		auto s = tree.sum((int)i);
		cout << "Sum of " << i << " elems = " << s << endl;
	}

	return 0;
}