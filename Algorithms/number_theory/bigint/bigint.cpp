#include <gtest/gtest.h>
#include "common.h"

using namespace std;

namespace {
	//http://e-maxx.ru/algo/big_integer
	typedef vector<int> bigint;
	const int base = 1000 * 1000 * 1000;

	static inline std::ostream& operator<<(std::ostream& os, const bigint& a) {
		os << (a.empty() ? 0 : a.back());

		char prevf = os.fill('x');
		auto prevw = os.width(9);
		os << setw(9) << setfill('0');
		for (int i = (int)a.size() - 2; i >= 0; --i)
			os << a[i]; //printf("%09d", a[i]);

		os.width(prevw);
		os.fill(prevf);
		return os;
	}


	TEST(bigint_tests, bigint_test1) {
	}
}