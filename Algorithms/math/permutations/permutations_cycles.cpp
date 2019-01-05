#include <gtest/gtest.h>
#include <common.h>

namespace {

	//a indexes from 1! so a has size len+1 and a[0] is not used
	vector<vi> perm2cycles(const vi& a) {
		vector<vi> res;
		vector<bool> used(a.size()); //elems starts with 1!

		for (int i = 1; i < (int)a.size(); i++) {
			if (used[i])
				continue;

			int start = i, curr = start;
			res.emplace_back(vi{});

			do {
				res.back().push_back(curr);
				used[curr] = true;
				curr = a[curr];
			} while (curr != start);
		}
		return res;
	}

	//res indexes from 1! so its size is len+1, res[0] is unused
	vi cycles2perm(const vector<vi>& c, int len) {
		vi res(len + 1);
		for (auto e : c) {
			for (size_t i = 0; i < e.size() - 1; i++)
			{
				res[e[i]] = e[i + 1];
			}
			res[e.back()] = e.front();
		}
		return res;
	}

	TEST(perm_tests, cycles_splitting_test) {

		vi perm = { 0, 4, 1, 2, 3, 7, 8, 6, 5 };

		auto cycles = perm2cycles(perm);

		ASSERT_EQ(2, cycles.size());
		ASSERT_EQ(4, cycles[0].size());
		ASSERT_EQ(4, cycles[1].size());

		vi c1 = { 1,4,3,2 };
		vi c2 = { 5,7,6,8 };
		EXPECT_EQ(c1, cycles[0]);
		EXPECT_EQ(c2, cycles[1]);

		vi perm_from_cycles = cycles2perm(cycles, 8);
		EXPECT_EQ(perm, perm_from_cycles);
	}

}

