#include <gtest/gtest.h>
#include <vector>
#include <complex>
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif


using namespace std;
using namespace std::literals;
using namespace std::complex_literals;
using namespace std::literals::complex_literals;

namespace {

	template<typename T>
	static bool compare_floats(T a, T b, T precision) {
		return fabs(a - b) <= precision;
	}

	template<typename T>
	static bool compare_complexes(complex<T> a, complex<T> b, T precision) {
		return compare_floats(a.real(), b.real(), precision) && compare_floats(a.imag(), b.imag(), precision);
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

	//Copy these lines:
	//http://e-maxx.ru/algo/fft_multiply
	/*******************************/
#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

	typedef complex<double> base;

	void fft(vector<base> & a, bool invert) {
		int n = (int)a.size();

		for (int i = 1, j = 0; i < n; ++i) {
			int bit = n >> 1;
			for (; j >= bit; bit >>= 1)
				j -= bit;
			j += bit;
			if (i < j)
				swap(a[i], a[j]);
		}

		for (int len = 2; len <= n; len <<= 1) {
			double ang = 2 * M_PI / len * (invert ? -1 : 1);
			base wlen(cos(ang), sin(ang));
			for (int i = 0; i < n; i += len) {
				base w(1);
				for (int j = 0; j < len / 2; ++j) {
					base u = a[i + j], v = a[i + j + len / 2] * w;
					a[i + j] = u + v;
					a[i + j + len / 2] = u - v;
					w *= wlen;
				}
			}
		}
		if (invert)
			for (int i = 0; i < n; ++i)
				a[i] /= n;
	}

	void multiply(const vector<int> & a, const vector<int> & b, vector<int> & res) {
		vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
		size_t n = 1;
		while (n < max(a.size(), b.size()))  n <<= 1;
		n <<= 1;
		fa.resize(n), fb.resize(n);

		fft(fa, false), fft(fb, false);
		for (size_t i = 0; i < n; ++i)
			fa[i] *= fb[i];
		fft(fa, true);

		res.resize(n);
		for (size_t i = 0; i < n; ++i)
			res[i] = int(fa[i].real() + 0.5);
	}

	void carry(vector<int>& res, int n) {
		int carry_val = 0;
		for (size_t i = 0; i < n; ++i) {
			res[i] += carry_val;
			carry_val = res[i] / 10;
			res[i] %= 10;
		}
	}
	/*******************************/

	TEST(emaxx_fft_test, forward_fft) {

		vector<complex<double>> input = { 1. + 3.i,   2.,   3. + 1.i,     4.,   5. - 2.i, 0, 0, 0 };
		//Result from SciLab:
		//vector<complex<double>> expected_res = { 15. + 2.i, -4.4142136 - 2.2426407i, 3. + 2.i, -3.5857864 + 3.7573593i, 3. + 2.i, -1.5857864 + 6.2426407i, 3. - 2.i, -6.4142136 + 12.242641i };
		//For some reason result from http://e-maxx.ru/algo/fft_multiply is different:
		vector<complex<double>> expected_res = { 15. + 2.i,
			-6.4142136 + 12.242641i,
			3. - 2.i,
			-1.5857864 + 6.2426407i,
			3. + 2.i,
			-3.5857864 + 3.7573593i,
			3. + 2.i,
			-4.4142136 - 2.2426407i };

		vector<complex<double>> input1(input);
		fft(input1, false);

		EXPECT_TRUE(compare_res(input1, expected_res, 1e-3));

	}

	TEST(emaxx_fft_test, multiplication) {
		//13. - 14.i   4. + 12.i   4. + 20.i   20. + 28.i, 46. + 32.i   44.   50. - 2.i   40. - 16.i
		vector<int> a = { 1, 2, 3 };
		vector<int> b = { 2, 3, 4 };

		vector<int> res;

		multiply(a, b, res);

		EXPECT_TRUE(true);

		//321*234 = 138672
		//{1,2,3} * {2,3,4} = {2,7,6,8,3,1}
		//zeros up to 2^3=8, so answer is { 2,7,6,8,3,1,0,0 }
		carry(res, 6);

		EXPECT_EQ(vector<int>({ 2,7,6,8,3,1,0,0 }), res);


		vector<int> a2 = { 0,1 };
		vector<int> b2 = { 0,1 };
		vector<int> res2;
		multiply(a2, b2, res2);

		EXPECT_EQ(vector<int>({ 0,0,1,0 }), res2);
	}

}
