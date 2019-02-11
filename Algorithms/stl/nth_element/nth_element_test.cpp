#include <gtest/gtest.h>
#include "common.h"

using namespace std;

namespace {
	//1C module1 lesson5 problem J (https://informatics.mccme.ru/mod/statements/view3.php?id=7408&chapterid=1001#1)

	TEST(stl_tests, nth_element_test1) {
		int n = 19;
		vll v = { 1, 1, 2, 2, 2, 2, 2, 3, 3, 4, 5, -7, -1, -1, -1, -1, -1, -2, -2 };

		vll elems;

		auto pos = std::partition(all(v), [](int a) { return a <= 0; });
		if (pos == end(v)) { //no pos
			if (v.size() <= 6) {
				elems = v;
			}
			else {
				nth_element(begin(v), begin(v) + 3, end(v));
				elems.insert(end(elems), begin(v), begin(v) + 3);
				nth_element(begin(v), end(v) - 3, end(v));
				elems.insert(end(elems), end(v) - 3, end(v));
			}
		}
		else {
			auto negs = distance(begin(v), pos);
			if (negs <= 6) {
				elems.insert(end(elems), begin(v), pos);
			}
			else {
				nth_element(begin(v), begin(v) + 3, pos);
				elems.insert(end(elems), begin(v), begin(v) + 3);
				nth_element(begin(v), pos - 3, pos);
				elems.insert(end(elems), pos - 3, pos);
			}
			if (v.size() - negs <= 6) {
				elems.insert(end(elems), pos, end(v)); //pos
			}
			else {
				nth_element(pos, pos + 3, end(v));
				elems.insert(end(elems), pos, pos + 3);
				nth_element(pos, end(v) - 3, end(v));
				elems.insert(end(elems), end(v) - 3, end(v));
			}
		}
		int ii, jj, kk;
		ll mx = numeric_limits<ll>::min();
		for (int i = 0; i < sz(elems) - 2; i++) {
			for (int j = i + 1; j < sz(elems) - 1; j++) {
				for (int k = j + 1; k < sz(elems); k++) {
					if (elems[i] * elems[j] * elems[k] > mx) {
						tie(ii, jj, kk) = tie(i, j, k);
						mx = elems[i] * elems[j] * elems[k];
					}
				}
			}
		}

		EXPECT_EQ(-7, elems[ii]);
		EXPECT_EQ(-2, elems[jj]);
		EXPECT_EQ(5, elems[kk]);
	}
}