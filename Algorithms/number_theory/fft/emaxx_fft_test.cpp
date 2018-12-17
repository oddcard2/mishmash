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

	/********************************/
	typedef complex<double> Comp;
#define FOR(x,to) for(x=0;x<(to);x++)

	vector<Comp> fft2(vector<Comp> v, bool rev = false) {
		int n = v.size(), i, j, m;

		for (i = 0, j = 1; j < n - 1; j++) {
			for (int k = n >> 1; k > (i ^= k); k >>= 1);
			if (i > j) swap(v[i], v[j]);
		}
		for (int m = 2; m <= n; m *= 2) {
			double deg = (rev ? -1 : 1) * 2 * acos(-1) / m;
			Comp wr(cos(deg), sin(deg));
			for (i = 0; i < n; i += m) {
				Comp w(1, 0);
				for (int j1 = i, j2 = i + m / 2; j2 < i + m; j1++, j2++) {
					Comp t1 = v[j1], t2 = w * v[j2];
					v[j1] = t1 + t2, v[j2] = t1 - t2;
					w *= wr;
				}
			}
		}
		if (rev) FOR(i, n) v[i] *= 1.0 / n;
		return v;
	}

	vector<Comp> MultPoly(vector<Comp> P, vector<Comp> Q, bool resize = false) {
		if (resize) {
			int maxind = 0, pi = 0, qi = 0, i;
			int s = 2;
			FOR(i, P.size()) if (norm(P[i])) pi = i;
			FOR(i, Q.size()) if (norm(Q[i])) qi = i;
			maxind = pi + qi + 1;
			while (s * 2 < maxind) s *= 2;
			P.resize(s * 2); Q.resize(s * 2);
		}
		P = fft2(P), Q = fft2(Q);
		for (int i = 0; i < P.size(); i++) P[i] *= Q[i];
		return fft2(P, true);
	}
	/********************************/
	//Copy these lines:
	//http://e-maxx.ru/algo/fft_multiply
	/*******************************/
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

		auto res = fft2(input);
		EXPECT_TRUE(compare_res(input1, expected_res, 1e-3));

	}

	TEST(emaxx_fft_test, multiplication) {
		//13. - 14.i   4. + 12.i   4. + 20.i   20. + 28.i, 46. + 32.i   44.   50. - 2.i   40. - 16.i
		vector<int> a = { 1, 2, 3 };
		vector<int> b = { 2, 3, 4 };

		vector<int> res;

		vector<Comp> aa(a.begin(), a.end());
		vector<Comp> bb(b.begin(), b.end());

		auto rr = MultPoly(aa, bb, true);

		multiply(a, b, res);

		EXPECT_TRUE(true);

		//321*234 = 138672
		//{1,2,3} * {2,3,4} = {2,7,6,8,3,1}
		//zeros up to 2^3=8, so answer is { 2,7,6,8,3,1,0,0 }
		carry(res, 6);

		EXPECT_EQ(vector<int>({ 2,7,6,8,3,1,0,0 }), res);
	}

}
