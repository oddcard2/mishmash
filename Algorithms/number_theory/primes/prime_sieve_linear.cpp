#include <gtest/gtest.h>
#include <vector>

using namespace std;

vector<int> lp;
vector<int> pr;

//lp is from ZERO!
void prime_sieve_linear(int n) {
	for (int i = 2; i <= n; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] <= n; ++j)
			lp[i * pr[j]] = pr[j];
	}
}

TEST(prime_sieve_linear, simple_test) {
	lp.resize(11);
	int n = 10;

	prime_sieve_linear(n);

	EXPECT_EQ(pr, vector<int>({ 2,3,5,7 }));
	EXPECT_EQ(2, lp[2]);
	EXPECT_EQ(3, lp[3]);
	EXPECT_EQ(2, lp[4]);
	EXPECT_EQ(5, lp[5]);

	EXPECT_EQ(2, lp[6]);
	EXPECT_EQ(7, lp[7]);
	EXPECT_EQ(2, lp[8]);
	EXPECT_EQ(3, lp[9]);
	EXPECT_EQ(2, lp[10]);
}
