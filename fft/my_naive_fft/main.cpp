#define _USE_MATH_DEFINES
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>


using namespace std;
using namespace std::complex_literals;

template<typename T>
static bool compare_floats(T a, T b, T precision) {
	return fabs(a - b) <= precision;
}

template<typename T>
static bool compare_complexes(complex<T> a, complex<T> b, T precision) {
	return compare_floats(a.real(), b.real(), precision) && compare_floats(a.imag(), b.imag(), precision);
}

//only 32 bits
static size_t next_power_of_2(size_t v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	return v;
}

static vector<complex<double>> do_fft(const vector<complex<double>>& input) {
	//special case for one elem vector
	if (input.size() == 1) {
		return input;
	}
	//recursive calls for 2 halfs of input
	size_t size = input.size();
	size_t half_size = size / 2;

	vector<complex<double>> input1;
	vector<complex<double>> input2;
	for (auto i = 0; i < size; i++) {
		if (i & 1)
			input2.push_back(input[i]);
		else
			input1.push_back(input[i]);
	}

	auto half1_res = do_fft(input1);
	auto half2_res = do_fft(input2);

	//merges results
	vector<complex<double>> res(size);
	for (size_t i = 0; i < half_size; i++) {
		complex<double> coef = exp(-1i * 2.0 * M_PI * (double)i / (double)size);
		res[i] = half1_res[i] + coef * half2_res[i];
		res[i + half_size] = half1_res[i] - coef * half2_res[i];
	}
	return res;
}

static vector<complex<double>> my_naive_fft(const vector<complex<double>>& input) {
	//fills zeros to 2^n size
	size_t len = input.size();
	bool isPower2 = len && (!(len & (len - 1)));
	if (isPower2) {
		return do_fft(input);
	}
	else {
		size_t new_len = next_power_of_2(len);
#if 0		
		vector<complex<double>> input2(new_len - len, 0);
		std::copy(begin(input), end(input), std::back_inserter(input2));
		auto res = do_fft(input2);
#else		
		vector<complex<double>> input2(input);
		input2.reserve(new_len);
		for (auto i = 0; i < new_len - len; i++) {
			input2.push_back(0);
		}
		auto res = do_fft(input2);
#endif
		
		//removes end elems
		res.resize(len);
		return res;
	}
}

static bool compare_res(const vector<complex<double>>& res, const vector<complex<double>>& expected_res, double precision) {
	if (res.size() != expected_res.size()) {
		return false;
	}

	for (auto i = 0; i < res.size(); i++) {
		if (!compare_complexes(res[i], expected_res[i], precision))
			return false;
	}
	return true;
}

int main()
{
	//1. + 3.i   2.   3. + i     4.   5. - 2.i
	//FFT: 15. + 2.i  -0.0101017 + 5.0139038i  -2.275486 + 5.7393502i -2.724514 + 4.1147517i  -4.9898983 - 1.8680058i
	//vector<complex<double>> input = { 1. + 3.i,   2.,   3. + 1.i,     4.,   5. - 2.i };
	//vector<complex<double>> expected_res = { 15. + 2.i,  -0.0101017 + 5.0139038i, -2.275486 + 5.7393502i, -2.724514 + 4.1147517i, -4.9898983 - 1.8680058i };

	vector<complex<double>> input = { 1. + 3.i,   2.,   3. + 1.i,     4.,   5. - 2.i, 0, 0, 0 };
	vector<complex<double>> expected_res = { 15. + 2.i, -4.4142136 - 2.2426407i, 3. + 2.i, -3.5857864 + 3.7573593i, 3. + 2.i, -1.5857864 + 6.2426407i, 3. - 2.i, -6.4142136 + 12.242641i };


	//vector<complex<double>> input = { 1, 2, 3, 4 };
	//vector<complex<double>> expected_res = { 10, -2. + 2.i, - 2., - 2. - 2.i };
	//vector<complex<double>> input = { 1, 2, 0, 0 };
	//vector<complex<double>> expected_res = { 3, -1 };
	auto res = my_naive_fft(input);

	if (compare_res(res, expected_res, 1e-3)) {
		cout << "OK";
	}
	else {
		cout << "ERROR";
	}
	return 0;
}
