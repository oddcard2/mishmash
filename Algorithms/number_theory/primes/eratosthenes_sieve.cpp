#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {


	/***********/
	void sieve(int n, vector<char>& prime) {
		prime[0] = prime[1] = false;
		for (int i = 2; i*i <= n; ++i)
			if (prime[i])
					for (int j = i * i; j <= n; j += i)
						prime[j] = false;
	}
	/***********/


	TEST(prime_sieve_linear, simple_test) {
		/***********/
		int n = 9;
		vector<char> prime (n + 1, true);
		sieve(n, prime);
		/***********/

		EXPECT_EQ(0, prime[0]);
		EXPECT_EQ(0, prime[1]);
		EXPECT_EQ(1, prime[2]);
		EXPECT_EQ(1, prime[3]);
		EXPECT_EQ(0, prime[4]);
		EXPECT_EQ(1, prime[5]);
		EXPECT_EQ(0, prime[6]);
		EXPECT_EQ(1, prime[7]);
		EXPECT_EQ(0, prime[8]);
		EXPECT_EQ(0, prime[9]);
	}

}
