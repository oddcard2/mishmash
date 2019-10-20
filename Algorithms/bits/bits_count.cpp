#include <gtest/gtest.h>
#include <bitset> // before common.h! Because common.h has macro for "all"
#include <common.h>




static int bit_count(uint64_t v) {
	return (int)std::bitset<64>(v).count();
}

static int bit_count(int v) {
	return (int)std::bitset<32>(v).count();
}

namespace {
	TEST(bit_counts_tests, simple_test) {
		EXPECT_EQ(2, bit_count(3));
		EXPECT_EQ(1, bit_count(8));
		EXPECT_EQ(0, bit_count(0));
	}
}